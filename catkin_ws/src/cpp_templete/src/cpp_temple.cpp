/* For ros 
 * This roscpp templete is written by CT-Hung
*/


// For ROS
#include "cpp_temple.h"

/*                                    */
/************ Constructor *************/
/*                                    */
TEMPLETE::TEMPLETE()
{
    m_loopFreq = 4;
    m_count = 1;
}

/*                                    */
/************* Destructor *************/
/*                                    */
TEMPLETE::~TEMPLETE()
{
}

/* Set the start varible here from yaml file. */
void TEMPLETE::OnStartUp()
{
    // Import parameter from yaml file
    string key;
    if (ros::param::search("loopFreq", key))
        ros::param::get(key, m_loopFreq);
    if (ros::param::search("count", key))
        ros::param::get(key, m_count);
}

/* Set the publihers here. */
void TEMPLETE::PublishedSetting()
{
    // Setup the publisher
    pub_foo = m_nh.advertise<std_msgs::Int16>("publish_foobar", 10);
}

/* Set the subscribers here. */
void TEMPLETE::SubscribedSetting()
{
    sub_foo = m_nh.subscribe("subscribe_foobar", 1000, &TEMPLETE::sub_callback, this);
}

/* Set the callback function of subscriber. */
void TEMPLETE::sub_callback(const std_msgs::Float64::ConstPtr& msg)
{
    ROS_INFO("Sub Get : [%f]", msg->data); //need to use pointer to get the value.
    m_count = msg->data;
}

/* Loop setting. Do your main thing here. */
void TEMPLETE::Iterate(const ros::TimerEvent&)
{
    std_msgs::Int16 msg;
    m_count++;
    ROS_INFO("Iterate Get : [%d]", m_count);
    msg.data = m_count;
    pub_foo.publish(msg);

}


/* main function */ 
/* Don't change this part normally.*/
int main (int argc, char** argv)
{
    // Initialize ROS
    ros::init(argc, argv, "cpp_templete_node");
    
    // Create object
    TEMPLETE templete_obj;
    templete_obj.OnStartUp();
    templete_obj.PublishedSetting();
    templete_obj.SubscribedSetting();
    templete_obj.timer = templete_obj.m_nh.createTimer(ros::Duration(templete_obj.m_loopFreq), &TEMPLETE::Iterate, &templete_obj);
    ros::spin();

    return 0;
}
