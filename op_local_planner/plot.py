#!/usr/bin/python
# -*- coding: UTF-8 -*-

# import sys

# reload(sys)

# sys.setdefaultencoding('utf-8')


import matplotlib.pyplot as plt
import numpy as np

data = np.loadtxt('/home/zy/Desktop/op_local_planner/local_map_ROI.csv')
data_best = np.loadtxt('/home/zy/Desktop/op_local_planner/local_map_ROI_best.csv')
data_center = np.loadtxt('/home/zy/Desktop/op_local_planner/local_map_ROI_center.csv')
data_obstacle = np.loadtxt('/home/zy/Desktop/op_local_planner/local_map_ROI_obstacle.csv')


each_trajectory_point_number = 19
print( len( data[:,0] ) )
num = len( data[:,0])/each_trajectory_point_number

i = 0;
while i< num:
    plt.plot(data[(i)*each_trajectory_point_number:(i+1)*each_trajectory_point_number,0],data[(i)*each_trajectory_point_number:(i+1)*each_trajectory_point_number,1],label=i)
    i+=1

plt.plot(data_center[:,0],data_center[:,1],'b.')
plt.plot(data_best[:,0],data_best[:,1],'r*')

plt.plot(data_obstacle[:,0],data_obstacle[:,1],'y.')

plt.title('best_traj:red_star')
# plt.gca().set_aspect('equal', adjustable='box')
plt.axis('equal')
plt.grid('on')
plt.legend()

plt.show()
