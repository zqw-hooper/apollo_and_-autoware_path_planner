#!/usr/bin/python
# -*- coding: UTF-8 -*-

# 二次规划问题
# https://osqp.org/docs/

import osqp
import numpy as np
import matplotlib
matplotlib.use('tkagg')
from matplotlib import pyplot as plt

import scipy.sparse as sparse
from scipy.linalg import block_diag
import time

class QPPathPlanner:
    def __init__(self, horizon):
        self.horizon = horizon
        # 计算cost函数时，q中对l的权重        
        self.l_ref = np.zeros(self.horizon)
        self.l_weight = 1
        self.dl_weight = 100
        self.ddl_weight = 30000
        # optimized的结果
        self.l_res = np.zeros(self.horizon)
        
    def set_initial_condition(self, init_l, init_dl,init_ddl):
        self.init_l = init_l
        self.init_dl = init_dl
        self.init_ddl = init_ddl

    # 设置l的边界
    def set_l_boundary(self, l_max, l_min):
        self.l_max = np.reshape(l_max, (self.horizon, 1))
        self.l_min = np.reshape(l_min, (self.horizon, 1))

    # 设置 ddl 的边界
    def set_ddl_boundary(self, ddl_max, ddl_min):
        self.ddl_max = np.ones((self.horizon, 1))*ddl_max
        self.ddl_min = np.ones((self.horizon, 1))*ddl_min
    
    # 设置两个路径点间的时间间隔
    def set_uniform_ds(self, ds):
        self.uniform_ds = ds
        # 这里假设每两个路径点之间的时间间隔相等
        self.ds = np.ones(self.horizon - 1)*self.uniform_ds
    
    # optimized的结果
    def get_optimized_l(self):
        return self.l_res
    
    # cost函数里面的P和q矩阵
    def compute_P_q(self):
        weight = np.array([[self.l_weight, 0.0, 0.0],
                    [0.0, self.dl_weight, 0.0],
                    [0.0, 0.0, self.ddl_weight]])
        print("weight.shape  ",weight.shape)
        # print(weight)
        # 构造稀疏矩阵  # scipy.sparse.kron(A, B, format=None)[source]   kronecker product of sparse matrices A and B
        # CSC是压缩存储稀疏矩阵的类，其中的C就是指column，也就是按照列来压缩存储压缩矩阵
        P = sparse.kron(sparse.eye(self.horizon),weight).tocsc()
        print("P.shape  ",P.shape)
        # print(P)
        # q中对l的权重
        q = np.zeros(self.horizon*3)
        for i in range(self.horizon):
            q[i*3] = -self.l_weight*self.l_ref[i]
        return P, q

    # 计算矩阵A
    def compute_A(self):
        Ad = []
        for i in range(self.horizon - 1):
            f_i = np.array([[1.0, self.ds[i], 0.0],
                            [0.0, 1.0, self.ds[i]]])  
            Ad.append(f_i)  
        Ax = sparse.csr_matrix(block_diag(*Ad))
        f_2 = np.array([[-1.0, 0.0, 0.0],
                        [0.0, -1.0, 0.0]])
        Ay = sparse.kron(sparse.eye(self.horizon - 1), f_2)
        off_set = np.zeros(((self.horizon - 1)*2, 3))
        Ax = sparse.hstack([Ax, off_set])
        Ay = sparse.hstack([off_set, Ay])
        Aeq = Ax + Ay # 数学的加法
        print("Aeq.shape  ",Aeq.shape)
        
        #  ( l_0, l_0', l_0'' )
        ineq_l = np.array([1.0, 0.0, 0.0])
        ineq_ddl = np.array([0.0, 0.0, 1.0])
        # 位置上下限
        Aineq_l = sparse.kron(sparse.eye(self.horizon), ineq_l)
        # 加速度上下限
        Aineq_ddl = sparse.kron(sparse.eye(self.horizon), ineq_ddl)
        
        # 初始状态
        A_init_l = np.zeros(self.horizon*3)
        A_init_l[0] = 1
        A_init_dl = np.zeros(self.horizon*3)
        A_init_dl[1] = 1
        A_init_ddl = np.zeros(self.horizon*3)
        A_init_ddl[2] = 1

        # 位置相等，速度相等，位置上下边界，加速度上下边界，初始状态
        # vertical方向叠加
        A = sparse.vstack([Aeq, Aineq_l, Aineq_ddl, A_init_l, A_init_dl, A_init_ddl]).tocsc()
        return A

    def compute_u_l(self):
        # 位置相等，速度相等
        # l_0 + ds*l_0' = l_1      // 位置相等
        # l_0' + ds*l_0'' = l_1'   // 速度相等
        ueq = np.zeros(((self.horizon - 1)*2, 1))
        leq = ueq
        # print("leq.shape  ",leq.shape)
        
        # 位置和加速度的上下边界
        uineq = np.vstack([self.l_max, self.ddl_max])
        lineq = np.vstack([self.l_min, self.ddl_min])
        # print("lineq.shape  ",lineq.shape)

        # 初始状态
        u_init = np.array([[self.init_l],[self.init_dl], [self.init_ddl]])
        l_init = u_init
        # print("l_init.shape  ",l_init.shape)
        
        # vertical方向合并
        l = np.vstack([leq, lineq, l_init])
        u = np.vstack([ueq, uineq, u_init])
        return u, l

    def __call__(self):
        P, q = self.compute_P_q()
        A = self.compute_A()
        u, l = self.compute_u_l()

        print("A.shape  ",A.shape)
        print("P.shape  ",P.shape)
        print("q.shape  ",q.shape)
        print("l shape  ",l.shape)
        print("u shape  ",u.shape)  

        prob = osqp.OSQP()
        prob.setup(P, q, A, l, u, warm_start=True, verbose=False)

        res = prob.solve()

        for i in range(self.horizon):
            self.l_res[i] = res.x[i*3]
        print("l_res.shape  ", self.l_res.shape)
        print("self.l_res")
        # print(self.l_res)

 
    def plot(self):
        plt.plot(self.l_res)
        plt.plot(self.l_min)
        plt.plot(self.l_max)
        plt.show()

if __name__ == '__main__':
    # 路径点点的数目
    horizon = 500
    # 两个路径点之间的时间间隔
    ds = 0.5
    # 初始状态
    init_l = 0
    init_dl = 0
    init_ddl = 0
    # lower and upper
    l_max = []
    l_min = []
    
    ddl_max = 0.2
    ddl_min = -0.2
    for i in range(horizon):
        u = 5
        if (i > 100 and i < 140):
            u = -2
        if (i > 350 and i < 380):
            u = 3
        l_max.append(u)
        l = -5
        if (i > 300 and i < 340):
            l = 2
        l_min.append(l)


    # for i in range(horizon):
    #     u = 5
    #     if (i > 100 and i < 150):
    #         u = -2
    #     l_max.append(u)
    #     l = -5
    #     if (i > 300 and i < 350):
    #         l = 2
    #     l_min.append(l)



    planner = QPPathPlanner(horizon)  # 创建实例

    # 设置两个路径点间的时间间隔
    planner.set_uniform_ds(ds)

    # 设置初始状态
    planner.set_initial_condition(init_l, init_dl, init_ddl)

    # 设置l和ddl的边界
    planner.set_l_boundary(l_max, l_min)
    planner.set_ddl_boundary(ddl_max, ddl_min)

    planner() # 实例可以象函数那样执行,调用 __call__
    planner.plot()



# python3 QP_path_planner.py
# sudo apt install python3.6
# sudo ln -s python3.6 python3
# pip3 install osqp

# sudo apt install python3.6-tk