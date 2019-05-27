#include <iostream>
#include <stdlib.h>
#include <sstream>
#include <string>
#include <fstream>
using namespace std;

bool fileExist(const char *fileName)
{
    std::ifstream infile(fileName);
    return infile.good();
}

int createYamlFile(string arthor_name, string node_name)
{
    stringstream folderPath;
    folderPath << "config/param_" << node_name << ".yaml";
    if(fileExist(folderPath.str().c_str()) == 1)
    {
        cout << "param_" << node_name << ".yaml " << "is already existed" << endl;
        return -1;
    }
    stringstream context;
    context << "echo \"";
    context << "loopFreq    : 1" << "\n";
    context << "count       : 20" << "\n";
    context << "\" >> config/param_" << node_name << ".yaml";
    system(context.str().c_str());
    cout << "Create yaml file in config folder successfully." << endl;
    return 0;
}

int createLaunchFile(string arthor_name, string node_name, string pkg_name)
{
    stringstream folderPath;
    folderPath << "launch/" << node_name << ".launch";
    if(fileExist(folderPath.str().c_str()) == 1)
    {
        cout << node_name << ".launch " << "is already existed" << endl;
        return -1;
    }
    stringstream context;
    context << "echo \"";
    context << "<launch>" << "\n";
    context << "    <!-- Setup file -->" << "\n";
    context << "    <arg name=\\\"param_file\\\" default=\\\"param_" << node_name << "\\\"/>" << "\n";
    context << "\n";
    context << "    <!-- Node --> "<< "\n";
    context << "    <node name=\\\"" << node_name << "\\\" pkg=\\\"" << pkg_name << "\\\" type=\\\"" << node_name << "\\\" output=\\\"screen\\\" clear_params=\\\"true\\\" required=\\\"true\\\">" << "\n";
    context << "        <rosparam command=\\\"load\\\" file=\\\"\\$(find " << pkg_name << ")/config/\\$(arg param_file).yaml\\\" />" << "\n";
    context << "    </node>" << "\n";
    context << "</launch>" << "\n";
    context << "\" >> launch/" << node_name << ".launch";
    system(context.str().c_str());
    cout << "Create launch file in launch folder successfully." << endl;
    return 0;
}

int createCppFile(string arthor_name, string node_name, string pkg_name)
{
    stringstream folderPath;
    folderPath << "src/" << node_name << ".cpp";
    if(fileExist(folderPath.str().c_str()) == 1)
    {
        cout << node_name << ".cpp " << "is already existed" << endl;
        return -1;
    }
    stringstream context;
    context << "echo \"";
    context << "/* For ros " << "\n";
    context << " * This roscpp app is written by" << arthor_name << "\n";
    context << "*/" << "\n";
    context << "\n";
    context << "// For ROS" << "\n";
    context << "#include \\\"" << node_name << ".h\\\"" << "\n";
    context << "\n";
    context << "/*  Constructor  */" << "\n";
    context << node_name << "::" << node_name << "()" << "\n";
    context << "{" << "\n";  
    context << "    m_loopFreq = 4;" << "\n";
    context << "    m_count = 1;" << "\n";
    context << "}" << "\n";
    context << "\n";       
    context << "/*  Destructor  */" << "\n";
    context << node_name << "::~" << node_name << "()" << "\n";
    context << "{" << "\n";
    context << "}" << "\n";
    context << "\n";
    context << "/* Set the start varible here from yaml file. */" << "\n";
    context << "void " << node_name << "::OnStartUp()" << "\n";
    context << "{" << "\n";
    context << "    // Import parameter from yaml file" << "\n";
    context << "    string key;" << "\n";
    context << "    if (ros::param::search(\\\"loopFreq\\\", key))" << "\n";
    context << "        ros::param::get(key, m_loopFreq);" << "\n";
    context << "    if (ros::param::search(\\\"count\\\", key))" << "\n";
    context << "        ros::param::get(key, m_count);" << "\n";
    context << "}" << "\n";
    context << "\n";
    context << "/* Set the publihers here. */" << "\n";
    context << "void " << node_name << "::PublishedSetting()" << "\n";
    context << "{" << "\n";
    context << "    // Setup the publisher" << "\n";
    context << "    pub_foo = m_nh.advertise<std_msgs::Int16>(\\\"publish_foobar\\\", 10);" << "\n";
    context << "}" << "\n";
    context << "\n";
    context << "/* Set the subscribers here. */" << "\n";
    context << "void " << node_name << "::SubscribedSetting()" << "\n";
    context << "{" << "\n";
    context << "    sub_foo = m_nh.subscribe(\\\"subscribe_foobar\\\", 1000, &" << node_name << "::sub_callback, this);" << "\n";
    context << "}" << "\n";
    context << "\n";
    context << "/* Set the callback function of subscriber. */" << "\n";
    context << "void " << node_name << "::sub_callback(const std_msgs::Float64::ConstPtr& msg)" << "\n";
    context << "{" << "\n";
    context << "    ROS_INFO(\\\"Sub Get : [%f]\\\", msg->data); //need to use pointer to get the value." << "\n";
    context << "    m_count = msg->data;" << "\n";
    context << "}" << "\n";
    context << "\n";
    context << "/* Loop setting. Do your main thing here. */" << "\n";
    context << "void " << node_name << "::Iterate(const ros::TimerEvent&)" << "\n";
    context << "{" << "\n";
    context << "    std_msgs::Int16 msg;" << "\n";
    context << "    m_count++;" << "\n";
    context << "    ROS_INFO(\\\"Iterate Get : [%d]\\\", m_count);" << "\n";
    context << "    msg.data = m_count;" << "\n";
    context << "    pub_foo.publish(msg);" << "\n";
    context << "}" << "\n";
    context << "\n";
    context << "/* main function */ " << "\n";
    context << "/* Don't change this part normally.*/" << "\n";
    context << "int main (int argc, char** argv)" << "\n";
    context << "{" << "\n";
    context << "    // Initialize ROS" << "\n";
    context << "    ros::init(argc, argv, \\\"" << node_name << "_node\\\");" << "\n";
    context << "\n";
    context << "    // Create object" << "\n";
    context << "    " << node_name << "  " << node_name << "_obj;" << "\n";
    context << "    " << node_name << "_obj.OnStartUp();" << "\n";
    context << "    " << node_name << "_obj.PublishedSetting();" << "\n";
    context << "    " << node_name << "_obj.SubscribedSetting();" << "\n";
    context << "    " << node_name << "_obj.timer = " << node_name << "_obj.m_nh.createTimer(ros::Duration(" << node_name << "_obj.m_loopFreq), &" << node_name << "::Iterate, &" << node_name << "_obj);" << "\n";
    context << "    ros::spin();" << "\n";
    context << "\n";
    context << "    return 0;" << "\n";
    context << "}" << "\n";
    context << "\" >> src/" << node_name << ".cpp";
    system(context.str().c_str());
    cout << "Create cpp file in src folder successfully." << endl;
    return 0;
}

int createHeadFile(string arthor_name, string node_name, string pkg_name)
{
    stringstream folderPath;
    folderPath << "src/" << node_name << ".h";
    if(fileExist(folderPath.str().c_str()) == 1)
    {
        cout << node_name << ".h " << "is already existed" << endl;
        return -1;
    }
    stringstream context;
    context << "echo \"";
    context << "/* For ros " << "\n";
    context << " * This roscpp template is written by " << arthor_name << "\n";
    context << "*/" << "\n";
    context << "\n";
    context << "// For ROS" << "\n";
    context << "#include <ros/ros.h>" << "\n";
    context << "#include \\\"std_msgs/Float64.h\\\"" << "\n";
    context << "#include \\\"std_msgs/Int16.h\\\"" << "\n";
    context << "\n";
    context << "using namespace std;" << "\n";
    context << "\n";
    context << "class " << node_name << "\n";
    context << "{" << "\n";
    context << "    public:" << "\n";
    context << "        // Don't move" << "\n";
    context << "        " << node_name << "();                     // Constructor" << "\n";
    context << "        ~" << node_name << "();                    // Destructor" << "\n";
    context << "        void OnStartUp();" << "\n";
    context << "        void SubscribedSetting();" << "\n";
    context << "        void PublishedSetting();" << "\n";
    context << "        void Iterate(const ros::TimerEvent&);" << "\n";
    context << "        ros::NodeHandle m_nh;                         // Private node handler" << "\n";
    context << "        ros::Timer timer;" << "\n";
    context << "        double m_loopFreq;" << "\n";
    context << "\n";
    context << "        // Publisher" << "\n";
    context << "        ros::Publisher pub_foo;                   // Private publisher instance" << "\n";
    context << "\n";        
    context << "        // Subscriber" << "\n";
    context << "        void sub_callback(const std_msgs::Float64::ConstPtr& msg);" << "\n";
    context << "        ros::Subscriber sub_foo;" << "\n";
    context << "\n";
    context << "    private:" << "\n";
    context << "        int m_startup_msg;" << "\n";
    context << "        int m_count;" << "\n";
    context << "};" << "\n";
    context << "\" >> src/" << node_name << ".h";
    system(context.str().c_str());
    cout << "Create Head file in src folder successfully." << endl;
    return 0;
}

int main(int argc, char **argv)
{
    if(argc != 4){
        cout << "Plz input createRosCppTemplete <arthor_name> <node_name> <pkg_name>" << endl;
        return 1;
    }
    string arthor_name = argv[1];
    string node_name = argv[2];
    string pkg_name = argv[3];
    cout << "Arthor name = " << arthor_name << endl;
    cout << "Node name = " << node_name << endl;
    cout << "Package name = " << pkg_name << endl; 

    system("mkdir -p launch config src");
    createYamlFile(arthor_name, node_name);
    createLaunchFile(arthor_name, node_name, pkg_name);
    createCppFile(arthor_name, node_name, pkg_name);
    createHeadFile(arthor_name, node_name, pkg_name);
    return 0;
}

