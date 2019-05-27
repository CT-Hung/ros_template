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
    context << "    <node name=\\\"" << node_name << "\\\" pkg=\\\"" << pkg_name << "\\\" type=\\\"" << node_name << ".py\\\" output=\\\"screen\\\" clear_params=\\\"true\\\" required=\\\"true\\\">" << "\n";
    context << "        <rosparam command=\\\"load\\\" file=\\\"\\$(find " << pkg_name << ")/config/\\$(arg param_file).yaml\\\" />" << "\n";
    context << "    </node>" << "\n";
    context << "</launch>" << "\n";
    context << "\" >> launch/" << node_name << ".launch";
    system(context.str().c_str());
    cout << "Create launch file in launch folder successfully." << endl;
    return 0;
}

int createPyFile(string arthor_name, string node_name, string pkg_name)
{
    stringstream folderPath;
    folderPath << "src/" << node_name << ".py";
    if(fileExist(folderPath.str().c_str()) == 1)
    {
        cout << node_name << ".cpp " << "is already existed" << endl;
        return -1;
    }
    stringstream context;
    context << "echo \"";
    context << "#!/usr/bin/env python " << "\n";
    context << "# this rospy templete is written by " << arthor_name << "\n";
    context << "import rospy " << "\n";
    context << "from std_msgs.msg import Int32MultiArray, Float64" << "\n";
    context << "\n";
    context << "class " << node_name << "(object):" << "\n";
    context << "    def __init__(self):" << "\n";
    context << "        # Initulize" << "\n";
    context << "        self.count = 1" << "\n";
    context << "        self.loopFreq = 4" << "\n";
    context << "\n";
    context << "        #On Start up " << "\n";
    context << "        self.OnStartUp()" << "\n";
    context << "\n";
    context << "        #Iterate Function" << "\n";
    context << "        rospy.Timer(rospy.Duration(self.loopFreq), self.Iterate)" << "\n";
    context << "\n";        
    context << "        #Publisher" << "\n";
    context << "        self.pub_bar = rospy.Publisher(\\\"pub_foo\\\", Float64, queue_size=1)" << "\n";
    context << "\n";
    context << "        #Subscriber" << "\n";
    context << "        self.sub_bar = rospy.Subscriber(\\\"sub_foo\\\", Float64, self.callBack, queue_size=1)" << "\n";
    context << "\n";
    context << "    def OnStartUp(self):" << "\n";
    context << "        #Set the params at yaml file" << "\n";
    context << "        if rospy.has_param('~loopFreq'):" << "\n";
    context << "            self.loopFreq = rospy.get_param('~loopFreq')" << "\n";
    context << "        if rospy.has_param('~count'):" << "\n";
    context << "            self.count = rospy.get_param('~count')" << "\n";
    context << "\n";
    context << "    def Iterate(self, event):" << "\n";
    context << "        #do ur thing here" << "\n";
    context << "        #self.pub_bar.publish(data)" << "\n";
    context << "        self.count = self.count+1" << "\n";
    context << "        rospy.loginfo(\\\"Iterate : [%f]\\\", self.count)" << "\n";
    context << "        self.pub_bar.publish(self.count)" << "\n";
    context << "\n";
    context << "    def callBack(self, msg):" << "\n";
    context << "        self.count = msg.data" << "\n";
    context << "        rospy.loginfo(\\\"Sub : [%f]\\\", self.count)" << "\n";
    context << "\n";
    context << "    def onShutdown(self):" << "\n";
    context << "        rospy.loginfo(\\\"[%s] Shutdown.\\\" %(self.node_name))" << "\n";
    context << "\n";
    context << "if __name__ == '__main__':" << "\n";
    context << "    rospy.init_node('" << node_name << "_node', anonymous=False)" << "\n";
    context << "    " << node_name << "_obj = " << node_name << "()" << "\n";
    context << "    rospy.on_shutdown(" << node_name << "_obj.onShutdown)" << "\n";
    context << "    rospy.spin()" << "\n";
    context << "\" >> src/" << node_name << ".py";
    system(context.str().c_str());
    cout << "Create py file in src folder successfully." << endl;
    return 0;
}

int main(int argc, char **argv)
{
    if(argc != 4){
        cout << "Plz input createRosPyTemplete <arthor_name> <node_name> <pkg_name>" << endl;
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
    createPyFile(arthor_name, node_name, pkg_name);
    return 0;
}

