#!/usr/bin/env python
import math
import matplotlib.pyplot as plt
import pandas as pd
import numpy as np
import os
pwd = os.getcwd()


fig = plt.figure()
ax = fig.add_subplot(121)
st_data = pd.read_csv(pwd+"/st_test.csv")
t = st_data["t"].values
l = st_data["l"].values
u = st_data["u"].values
s = st_data["s"].values
reference_s = st_data["reference"].values
plt.scatter(t, l, color='r')
plt.scatter(t, u, color='r')
plt.scatter(t, s, color='b')
# plt.scatter(t, reference_s, color='g')
ax.set_title("st_test.csv")
plt.xlabel('t')
plt.ylabel('s')

v_data = pd.read_csv(pwd+"/v_test.csv")
s = v_data["s"].values
v_limit = v_data["b"].values
v = v_data["v"].values
bx = fig.add_subplot(122)
plt.scatter(s, v_limit, color="r")
plt.scatter(s, v, color="b")
bx.set_title("v_test.csv")
plt.xlabel('s')
plt.ylabel('v')



fig_1 = plt.figure()
ref_data = pd.read_csv(pwd+"/ref.csv")
index =  ref_data["t"].values
ref = ref_data["ref"].values
optimized_ref = ref_data["optimized_ref"].values
s_bounds_lower = ref_data["s_bounds_lower"].values
s_bounds_upper = ref_data["s_bounds_upper"].values
velocity = ref_data["velocity"].values
plt.scatter(index,ref, color="b")
plt.scatter(index,optimized_ref, color="r")
plt.scatter(index,s_bounds_lower, color="m")
plt.scatter(index,s_bounds_upper, color="m")
# plt.scatter(index,velocity, color="k")
plt.title("ref.csv")
plt.xlabel("t")
plt.ylabel("s")




fig_2 = plt.figure()
path_optimizer_data = pd.read_csv(pwd+"/path_optimizer.csv")
s =  path_optimizer_data["s"].values
l = path_optimizer_data["l"].values
l_bounds_lower = path_optimizer_data["l_boundaries_lower"].values
l_bounds_upper = path_optimizer_data["l_boundaries_upper"].values
plt.scatter(s,l, color="b")
plt.plot(s,l_bounds_lower, color="r")
plt.plot(s,l_bounds_upper, color="r")
plt.title("path_optimizer")
plt.xlabel("s")
plt.ylabel("l")





plt.show()