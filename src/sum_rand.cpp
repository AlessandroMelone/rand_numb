/*
In this code the node will get a msg of type rand_numb and write a message of type sum_rand_numb. 
The publishing is done by the callback of the subscriber.
*/
#include <iostream>
#include "ros/ros.h"
#include "rand_numb/sum_rand_numb.h"
#include "rand_numb/rand_numb.h"



class ROS_NODE{
	public:
		ROS_NODE();
		void topic_cb(rand_numb::rand_numb ms); //topic callback
	private:
  		ros::NodeHandle _nh;
  		ros::Subscriber _topic_sub;
  		ros::Publisher _topic_pub;
		rand_numb::sum_rand_numb out_ms; //output message  		
};

ROS_NODE::ROS_NODE(){
	_topic_sub = _nh.subscribe("/rand_numb", 10, &ROS_NODE::topic_cb, this); //size message queue 10
	_topic_pub = _nh.advertise <rand_numb::sum_rand_numb>("/sum_rand_numb",10);
}


void ROS_NODE::topic_cb(rand_numb::rand_numb ms){
	ROS_INFO("input random numb: %f   %f", ms.rand1, ms.rand2);
	
	//prepare output
	out_ms.rand1 = ms.rand1;
	out_ms.rand2 = ms.rand2;
	out_ms.sum_rand = ms.rand1 + ms.rand2;
	
	ROS_INFO("output random numb: %f   %f  -->  %f ", out_ms.rand1, out_ms.rand2, out_ms.sum_rand);
	_topic_pub.publish(out_ms); 	 //publish output
}

int main(int argc,char **argv){
	ros::init (argc,argv, "sum_rand_numb");
	ROS_NODE rn;
	
	ros::spin();
	return 0;	
}
