#include <ros/ros.h>
#include <topicPubSub/gps.h>//auto generate gps.h
#include <std_msgs/Float32.h>
#include <iostream>
#include <topicPubSub/timeStamp.h>
using namespace ros;
//根据不同的[消息]和[话题]调用不同的回调函数
void gpsCallback(const topicPubSub::gps::ConstPtr& msg){
    std_msgs::Float32 dist;
    dist.data = sqrt(pow(msg->x, 2) + pow(msg->y, 2));
    ROS_INFO("Listener: distance to origin: %2.3f, state: %s", dist.data, msg->state.c_str());
    return;
}
void gpsCallbackRaw(const topicPubSub::gps::ConstPtr& msg){
    ROS_INFO("Listener: gps raw info %3.2f, %3.2f", msg->x, msg->y);
    return;
}
void timeStampCallback(const topicPubSub::timeStamp::ConstPtr& timeSTMP){
    ROS_INFO("Listener: %s, until now", timeSTMP->time.c_str());
    return;
}
int main(int argc, char* argv[]){
    init(argc, argv, "myListener");
    NodeHandle handler;
    Subscriber subGPS = handler.subscribe<topicPubSub::gps>("gpsInfo", 1, gpsCallback);//new subscriber: topic name, buffer size, callback function pointer
    Subscriber subTime = handler.subscribe<topicPubSub::timeStamp>("timeInfo", 1, timeStampCallback);
    Subscriber subGpsRaw = handler.subscribe<topicPubSub::gps>("gpsInfoRaw", 1, gpsCallbackRaw);
    spin();//blocking
    return 0;
}