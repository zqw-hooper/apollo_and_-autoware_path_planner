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
plt.scatter(t, l, color='r')
plt.scatter(t, u, color='r')
plt.scatter(t, s, color='b')

v_data = pd.read_csv(pwd+"/v_test.csv")
s = v_data["s"].values;
v_limit = v_data["b"].values
v = v_data["v"].values
bx = fig.add_subplot(122)
plt.scatter(s, v_limit, color="r")
plt.scatter(s, v, color="b")

plt.show()