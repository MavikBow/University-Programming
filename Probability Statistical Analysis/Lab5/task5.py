#!/usr/bin/env python

import seaborn as sns
import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
from sklearn.datasets import load_wine
from sklearn.model_selection import train_test_split
from sklearn.feature_selection import RFE
from sklearn.linear_model import LinearRegression

X, y = load_wine(as_frame=True).data, load_wine(as_frame=True).target

model = LinearRegression()
rfe = RFE(model, n_features_to_select=5)

rfe.fit(X, y)

rfe_features = X.columns[rfe.support_]

print(X.columns[rfe.support_])
