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
	std::vector<float> angle;					//ÿ����ĽǶ�
	std::vector<float> distance;					//ÿ���߾���
	std::vector<int> intensity;					//******ǿ��
	std::vector<float> azimuth;					//******ˮƽ�Ƕ�
	std::vector<uint64_t>  mtimestamp;			//******ʱ���
}LIDARDATA;


class SocketRadium
{
protected:
	int m_RadiumSocket;
	int Distance_Accuracy;
public:
	bool setLidarZero;
	//int StartThread();				//�����߳�
	//int SetStopFlag(bool flag);		 //ֹͣ�߳�
	std::vector<LIDARDATA*> lidarData;
	bool m_bStopFlag;			 //ֹͣ�̵߳�

	//**************************************************************************								
	//setDistance_Accuracy:���þ���ֱ���				
	//����˵����								
	//nAccuracy			����ֱ���		
	//1.0/2.0Э��Ϊ 2 
	//3.0/4.0Э��Ϊ 4
	//����ֵ˵����								
	//��
	//**************************************************************************	
	inline void setDistance_Accuracy(int nAccuracy)
	{
		Distance_Accuracy = nAccuracy;
	}
	//**************************************************************************								
	//Create:��ʼ��Socket����							
	//����˵����								
	//nSocketPort			�����˿� 						
	//nSocketType			UDPЭ��			
	//lpszSocketAddress		������ַ��Ϣ
	//����ֵ˵����								
	//��ȡʧ�ܷ���false		���򷵻�true
	//**************************************************************************	
	bool Create(unsigned int nSocketPort = 2368, const char* lpszSocketAddress = NULL);



	//**************************************************************************								
	//GetLidarData:			��ȡ�״�����							
	//����˵����							
	//����ֵ˵����								
	//��ȡʧ�ܷ���false		���򷵻�true
	//**************************************************************************	
    bool GetLidarData();

	//**************************************************************************								
	//Close:			�ͷ�����							
	//����˵����							
	//��				
	//����ֵ˵����								
	//��
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

