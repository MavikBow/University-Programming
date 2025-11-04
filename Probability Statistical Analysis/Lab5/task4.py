#!/usr/bin/env python

import seaborn as sns
import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
from sklearn.datasets import load_wine

from sklearn.feature_selection import mutual_info_regression

X, y = load_wine(as_frame=True).data, load_wine(as_frame=True).target
mutual_info = mutual_info_regression(X, y)

mig_features = X.columns[mutual_info > 0.05]

for i, score in zip(X.columns, mutual_info):
    print(f'Feature: {i}, Score: {score:.5f}')

plt.figure(figsize=(10, 8))
plt.bar([x for x in X.columns], mutual_info)
plt.xticks(rotation=90)
plt.savefig('img/4/barchart.png')

print(X.columns[mutual_info > 0.3])
