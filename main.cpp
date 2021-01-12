#include <iostream>
#include <fstream>
#include <unistd.h>
#include "threadRadium.h"


const char* lidar_ip = "192.168.1.125";

//Create a class
threadRadium* pGetData1 = new threadRadium;
/*threadRadium* pGetData2 = new threadRadium;
threadRadium* pGetData3 = new threadRadium;
threadRadium* pGetData4 = new threadRadium;*/

void* lidar_recive_proc(void* port);
/*void* lidar_recive_proc1(void* port);
void* lidar_recive_proc2(void* port);
void* lidar_recive_proc3(void* port);*/

void* lidar_recive_proc(void* port)
{
	int port_num = (int)(*((int*)port));
	pGetData1->setDistance_Accuracy(4);	//old agreement
	pGetData1->startGetLidarData(port_num, lidar_ip);// port    ip
}

/*void* lidar_recive_proc1(void* port)
{
	int port_num = (int)(*((int*)port));
	pGetData2->setDistance_Accuracy(4);		//new agreement
	pGetData2->startGetLidarData(port_num, lidar_ip);// port    ip
}

void* lidar_recive_proc2(void* port)
{
	int port_num = (int)(*((int*)port));
	pGetData3->setDistance_Accuracy(2);		//new agreement
	pGetData3->startGetLidarData(port_num, lidar_ip);// port    ip
}

void* lidar_recive_proc3(void* port)
{
	int port_num = (int)(*((int*)port));
	pGetData4->setDistance_Accuracy(4);		//new agreement
	pGetData4->startGetLidarData(port_num, lidar_ip);// port    ip
}*/

int main()
{
	int z = 0;
	int ret;
	pthread_t id[4];
	
	int port_first = 2368;
	ret=pthread_create(&id[0], NULL, lidar_recive_proc, (void*)(&port_first));
	if(ret!=0)
	{
		printf ("Create pthread1 error!/n");
		exit (1);
	}
	
	/*int port_second = 2369;
	ret=pthread_create(&id[1], NULL, lidar_recive_proc1, (void*)(&port_second));
	if(ret!=0)
	{
		printf ("Create pthread2 error!/n");
		exit (1);
	}
	
	int port_third = 2370;
	ret=pthread_create(&id[2], NULL, lidar_recive_proc2, (void*)(&port_third));
	if(ret!=0)
	{
		printf ("Create pthread3 error!/n");
		exit (1);
	}
	
	int port_four = 2371;
	ret=pthread_create(&id[3], NULL, lidar_recive_proc3, (void*)(&port_four));
	if(ret!=0)
	{
		printf ("Create pthread4 error!/n");
		exit (1);
	}*/

	//Loop data acquisition
	while (true)
	{
		LIDARDATA lidarDataValue1;
		/*LIDARDATA lidarDataValue2;
		LIDARDATA lidarDataValue3;
		LIDARDATA lidarDataValue4;*/
		bool flag1 = pGetData1->getLidarData(lidarDataValue1);
		/*bool flag2 = pGetData2->getLidarData(lidarDataValue2);
		bool flag3 = pGetData3->getLidarData(lidarDataValue3);
		bool flag4 = pGetData4->getLidarData(lidarDataValue4);*/
		if (flag1)
		{
			if (lidarDataValue1.azimuth.size() > 1)
			{
				//std::cout << "flag1  " << lidarDataValue1.angle.size() << ":" << lidarDataValue1.azimuth.size() << ":" << lidarDataValue1.distance.size() << ":" << lidarDataValue1.intensity.size() << ":" << lidarDataValue1.mtimestamp.size() << std::endl;
				for(int i=0; i < lidarDataValue1.intensity.size(); i++)
					std::cout << lidarDataValue1.azimuth[i] << "-" << lidarDataValue1.distance[i] << "-" << lidarDataValue1.intensity[i] << std::endl;
			}
		}
		/*if (flag2)
		{
			if (lidarDataValue2.azimuth.size() > 1)
			{
				std::cout << "flag2  " << lidarDataValue2.angle.size() << ":" << lidarDataValue2.azimuth.size() << ":" << lidarDataValue2.distance.size() << ":"
					<< lidarDataValue2.intensity.size() << ":" << lidarDataValue2.mtimestamp.size() << std::endl;
				for(int i=0; i < lidarDataValue2.intensity.size(); i++)
					std::cout << lidarDataValue2.azimuth[i] << "-" <<lidarDataValue2.distance[i] << std::endl;
			}
		}
		if (flag3)
		{
			if (lidarDataValue3.azimuth.size() > 1)
			{
				std::cout << "flag3  " << lidarDataValue3.angle.size() << ":" << lidarDataValue3.azimuth.size() << ":" << lidarDataValue3.distance.size() << ":"
					<< lidarDataValue3.intensity.size() << ":" << lidarDataValue3.mtimestamp.size() << std::endl;
				//for(int i=0; i < lidarDataValue3.intensity.size(); i++)
					//std::cout << lidarDataValue3.azimuth[i] << std::endl;
			}
		}
		if (flag4)
		{
			if (lidarDataValue4.azimuth.size() > 1)
			{
				std::cout << "flag3  " << lidarDataValue4.angle.size() << ":" << lidarDataValue4.azimuth.size() << ":" << lidarDataValue4.distance.size() << ":"
					<< lidarDataValue4.intensity.size() << ":" << lidarDataValue4.mtimestamp.size() << std::endl;
				//for(int i=0; i < lidarDataValue4.intensity.size(); i++)
					//std::cout << lidarDataValue4.azimuth[i] << std::endl;
			}
		}*/
		usleep(100000);
	}
	
	pGetData1->SetStopFlag();
	delete pGetData1;
	/*pGetData2->SetStopFlag();
	delete pGetData2;
	pGetData3->SetStopFlag();
	delete pGetData3;
	pGetData4->SetStopFlag();
	delete pGetData4;*/
	usleep(100);
	system("pause");
	return 0;
}




