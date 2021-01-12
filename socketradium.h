#include <stdlib.h>
#include <vector>
//#include <thread>
#include <iostream>
# include <stdint.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <math.h>

#define INVALID_SOCKET 0
typedef  struct _LidarData
{
	std::vector<float> angle;					//每个块的角度
	std::vector<float> distance;					//每条线距离
	std::vector<int> intensity;					//******强度
	std::vector<float> azimuth;					//******水平角度
	std::vector<uint64_t>  mtimestamp;			//******时间戳
}LIDARDATA;


class SocketRadium
{
protected:
	int m_RadiumSocket;
	int Distance_Accuracy;
public:
	bool setLidarZero;
	//int StartThread();				//启动线程
	//int SetStopFlag(bool flag);		 //停止线程
	std::vector<LIDARDATA*> lidarData;
	bool m_bStopFlag;			 //停止线程的

	//**************************************************************************								
	//setDistance_Accuracy:设置距离分辨率				
	//参数说明：								
	//nAccuracy			距离分辨率		
	//1.0/2.0协议为 2 
	//3.0/4.0协议为 4
	//返回值说明：								
	//无
	//**************************************************************************	
	inline void setDistance_Accuracy(int nAccuracy)
	{
		Distance_Accuracy = nAccuracy;
	}
	//**************************************************************************								
	//Create:初始化Socket参数							
	//参数说明：								
	//nSocketPort			监听端口 						
	//nSocketType			UDP协议			
	//lpszSocketAddress		监听地址信息
	//返回值说明：								
	//读取失败返回false		否则返回true
	//**************************************************************************	
	bool Create(unsigned int nSocketPort = 2368, const char* lpszSocketAddress = NULL);



	//**************************************************************************								
	//GetLidarData:			获取雷达数据							
	//参数说明：							
	//返回值说明：								
	//读取失败返回false		否则返回true
	//**************************************************************************	
    bool GetLidarData();

	//**************************************************************************								
	//Close:			释放数据							
	//参数说明：							
	//无				
	//返回值说明：								
	//无
	//**************************************************************************	
	void Close()
	{
		shutdown(m_RadiumSocket,SHUT_RDWR);
		//m_RadiumSocket = INVALID_SOCKET;
		if (lidarData.size() > 0)
		{
			for(int i = 0; i < lidarData.size(); i++)
			{
				delete lidarData[i];
				lidarData[i] = NULL;
			}
			lidarData.clear();
		}
	}



	int SOCKET() const
	{
		return m_RadiumSocket;
	}

/*#ifdef _UNICODE
	inline static void Pton(const char* sHostAddr, in_addr& in)
	{
		in.s_addr = inet_addr(_bstr_t(sHostAddr));
	}
	inline static void Ntop(in_addr& in, char* sHostAddr)
	{
		_tcscpy(sHostAddr, _bstr_t(inet_ntoa(in)));
	}*/

//#else
	inline static void Pton(const char* sHostAddr, in_addr& in)
	{
		in.s_addr = inet_addr(sHostAddr);
	}
	inline static void Ntop(in_addr& in, char*  sHostAddr)
	{
		strcpy(sHostAddr, inet_ntoa(in));
	}
//#endif
	SocketRadium();
	virtual ~SocketRadium();

};

