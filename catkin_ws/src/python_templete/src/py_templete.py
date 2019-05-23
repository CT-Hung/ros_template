#!/usr/bin/env python 
# this rospy templete is written by cthung
import rospy 
from std_msgs.msg import Int32MultiArray, Float64

class TEMPLETE(object):
    def __init__(self):
        # Initulize
        self.count = 1
        self.loopFreq = 4

        #On Start up 
        self.OnStartUp()

        #Iterate Function
        rospy.Timer(rospy.Duration(self.loopFreq), self.Iterate)
        
        #Publisher
        self.pub_bar = rospy.Publisher("FOO", Float64, queue_size=1)

        #Subscriber
        self.sub_bar = rospy.Subscriber("FOO", Float64, self.callBack, queue_size=1)

    def OnStartUp(self):
        #Set the params at yaml file
        if rospy.has_param('~loopFreq'):
            self.loopFreq = rospy.get_param('~loopFreq')
        if rospy.has_param('~count'):
            self.count = rospy.get_param('~count')

    def Iterate(self, event):
        #do ur thing here
        #self.pub_bar.publish(data)
        self.count = self.count+1
        rospy.loginfo("Iterate : [%f]", self.count)
        self.pub_bar.publish(self.count)

    def callBack(self, msg):
        self.count = msg.data
        rospy.loginfo("Sub : [%f]", self.count)

    def onShutdown(self):
        rospy.loginfo("[%s] Shutdown." %(self.node_name))

if __name__ == '__main__':
    rospy.init_node('templete', anonymous=False)
    foobar = TEMPLETE()
    rospy.on_shutdown(foobar.onShutdown)
    rospy.spin()
