#include "socketradium.h"

class threadRadium
{
public:
	threadRadium();

	virtual ~threadRadium();
	
	//创建获取数据包类
	SocketRadium *sockRadium;	

	//开启线程,获取数据，默认端口2368
	bool startGetLidarData(int nSocketPort, const char* lpszSocketAddress);

	//获取一帧数据
	bool getLidarData(LIDARDATA& lidar);

	//兼容新旧协议
	//1.0/2.0协议为 2 
	//3.0/4.0协议为 4
	//返回值说明：								
	//无
	inline void setDistance_Accuracy(int nAccuracy)
	{
		sockRadium->setDistance_Accuracy(nAccuracy);
	}

	//停止线程 
	int SetStopFlag();	
};

 