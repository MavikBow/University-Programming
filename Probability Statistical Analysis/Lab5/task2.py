#!/usr/bin/env python

import seaborn as sns
import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
from sklearn.datasets import load_wine
from sklearn.ensemble import RandomForestRegressor

data = load_wine(as_frame=True).frame

X, y = load_wine(as_frame=True).data, load_wine(as_frame=True).target
model = RandomForestRegressor(max_depth=10, random_state=13)
model.fit(X, y)
RandomForestRegressor(max_depth=10, random_state=13)

importance = model.feature_importances_

for i, score in zip(X.columns, importance):
    print(f'Feature: {i}, Score: {score:.5f}')

plt.figure(figsize=(10, 8))
plt.bar([x for x in X.columns], importance)
plt.xticks(rotation=90)
plt.savefig('img/2/heatmap.png')
