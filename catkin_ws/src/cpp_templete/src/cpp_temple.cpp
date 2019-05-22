/* For RobotX competition
   Recorder controll part is written by CT-Hung and modified to ROS version by Sam Liu
*/


// For ROS
#include <ros/ros.h>
#include "std_msgs/Float64.h"
#include "std_msgs/Int16.h"

using namespace std;

class TEMPLETE
{
    public:
        TEMPLETE();                     // Constructor
        ~TEMPLETE();                    // Destructor
        void OnStartUp();
        void Iterate(const ros::TimerEvent&);

        // ROS parameter
        ros::NodeHandle m_nh;                         // Private node handler
        ros::Timer timer;

        // Publisher
        void PublishedSetting();
        ros::Publisher pub_foo;                   // Private publisher instance
        
        // Subscriber
        ros::Subscriber sub_foo;
        void SubscribedSetting();
        void sub_callback(const std_msgs::Float64::ConstPtr& msg);

    private:
        int m_startup_msg;
        int m_count;
};

/*                                    */
/************ Constructor *************/
/*                                    */
TEMPLETE::TEMPLETE()
{
    m_count = 1;
}

void TEMPLETE::OnStartUp()
{
    // Import parameter from yaml file
    if (!ros::param::get("Foo", m_startup_msg))
        m_startup_msg = 0;
}

void TEMPLETE::PublishedSetting()
{
    // Setup the publisher
    pub_foo = m_nh.advertise<std_msgs::Int16>("publish_foobar", 10);
}

void TEMPLETE::sub_callback(const std_msgs::Float64::ConstPtr& msg)
{
    double a;
    a = msg->data;
    ROS_INFO("Get : [%f]", a);
}

void TEMPLETE::Iterate(const ros::TimerEvent&)
{
    std_msgs::Int16 msg;
    m_count++;
  //  ROS_INFO("Iterate Get : [%d]", m_count);
    msg.data = m_count;
    pub_foo.publish(msg);

}

void TEMPLETE::SubscribedSetting()
{

    sub_foo = m_nh.subscribe("subscribe_foobar", 1000, &TEMPLETE::sub_callback, this);
}
/*                                    */
/************* Destructor *************/
/*                                    */
TEMPLETE::~TEMPLETE()
{
}

int main (int argc, char** argv)
{
    // Initialize ROS
    ros::init(argc, argv, "hydrophone_data_node");
    
    // Create hydrophone object
    TEMPLETE templete_obj;
    templete_obj.PublishedSetting();
    templete_obj.SubscribedSetting();
    templete_obj.timer = templete_obj.m_nh.createTimer(ros::Duration(1), &TEMPLETE::Iterate, &templete_obj);
    ros::spin();


    return 0;
}
