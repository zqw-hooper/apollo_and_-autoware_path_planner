Apollo和Autoware规划部分使用的算法的demo


1. Apollo_PiecewiseJerk_algorithm
    
    Apollo piecewise_jerk算法主要包括两方面，路径规划和速度规划，最后组合成轨迹
    路径规划: PIECEWISE_JERK_PATH_OPTIMIZER (QP)
    速度规划: SPEED_HEURISTIC_OPTIMIZER (DP)
             PIECEWISE_JERK_NONLINEAR_SPEED_OPTIMIZER  (QP)


2. DP_path_planner
    基于动态规划的路径规划,(s,l),主要是静态障碍物的避障


3. DP_speed_planner
   基于动态规划的速度规划,(s,t),粗略的处理动态障碍物的避障


4. op_local_planner
    Autoware中使用撒点的方法做局部避障


5. ST_graph
   静态障碍物和动态障碍物生成ST_graph
