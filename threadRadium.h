#include "socketradium.h"

class threadRadium
{
public:
	threadRadium();

	virtual ~threadRadium();
	
	//������ȡ���ݰ���
	SocketRadium *sockRadium;	

	//�����߳�,��ȡ���ݣ�Ĭ�϶˿�2368
	bool startGetLidarData(int nSocketPort, const char* lpszSocketAddress);

	//��ȡһ֡����
	bool getLidarData(LIDARDATA& lidar);

	//�����¾�Э��
	//1.0/2.0Э��Ϊ 2 
	//3.0/4.0Э��Ϊ 4
	//����ֵ˵����								
	//��
	inline void setDistance_Accuracy(int nAccuracy)
	{
		sockRadium->setDistance_Accuracy(nAccuracy);
	}

	//ֹͣ�߳� 
	int SetStopFlag();	
};

 