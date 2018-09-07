#!/usr/bin/env python 
import rospy 
from std_msgs.msg import Int32MultiArray, Float64

class TEMPLETE(object):
    def __init__(self):
        # Initulize

        #On Start up 
        self.OnStartUp()

        #Iterate Function
        rospy.Timer(rospy.Duration(1), self.Iterate)
        
        #Publisher
        self.pub_bar = rospy.Publisher("FOO", Float64, queue_size=1)

        #Subscriber
        self.sub_bar = rospy.Subscriber("FOO", Float64, self.callBack, queue_size=1)

    def OnStartUp(self):
        #Set the params at yaml file
        if rospy.has_param('~FOO'):
            self.bar = rospy.get_param('~FOO')

    def Iterate(self, event):
        #do ur thing here
        #self.pub_bar.publish(data)

    def callBack(self, msg):
        self.bar = msg.data

    def onShutdown(self):
        rospy.loginfo("[%s] Shutdown." %(self.node_name))

if __name__ == '__main__':
    rospy.init_node('templete', anonymous=False)
    foobar = TEMPLETE()
    rospy.on_shutdown(foobar.onShutdown)
    rospy.spin()
