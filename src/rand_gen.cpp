#include <iostream>
#include "ros/ros.h"
#include "rand_numb/rand_numb.h"
#include <random>

class ROS_PUB{
  public:
  	ROS_PUB();
  	void _publish(rand_numb::rand_numb ms);
  	ros::Publisher _topic_pub;
  private :
  	ros::NodeHandle _nh;
};

ROS_PUB::ROS_PUB() {
	_topic_pub = _nh.advertise <rand_numb::rand_numb>("/rand_numb",20);
}

void ROS_PUB::_publish(rand_numb::rand_numb ms){
	_topic_pub.publish(ms);
}


int main(int argc,char **argv){
	ros::init (argc,argv, "rand_numb");
	ROS_PUB pub;
	ros::Rate rate(1); // 1 Hz

	std::random_device rd;  //Will be used to obtain a seed for the random number engine
	std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd() (gives int random)
	std::uniform_real_distribution<> dis(0.0, 100.0); //specifies the interval of float numbers
	
	while(ros::ok()){
	
	      rand_numb::rand_numb rand_msg;
		rand_msg.rand1 = dis(gen);
		rand_msg.rand2 = dis(gen);	

		pub._publish(rand_msg);

            ROS_INFO("random numb: %f   %f", rand_msg.rand1, rand_msg.rand2);
		rate.sleep();
	}
	return 0;
}


