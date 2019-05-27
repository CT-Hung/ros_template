# ros_templete

> This is a templete for ros.  
> The python part of autoCreateTemplete isn't done yet.  
> First, create a package by yourself.  
> And then follow following method.  

## Method 1.
> There are python and cpp templetes in catkin_ws folder.  
> Copy the file into your ros pkg and change the node name.  

## Method 2
> `$ cd autoCreateTemplete`  
> `$ mkdir build; cd build`  
> `$ cmake ../`  
> `$ make`  
> add the bin PATH into your .bashrc file.  

## Create cpp templete
> `$ createRosCppTemplete <arthor_name> <node_name> <pkg_name>`  
> This will create three folders and four files:   
1. launch/param_<node_name>.launch 
2. config/<node_name>.yaml 
3. src/<node_name>.cpp 
4. src/<node_name>.h 
