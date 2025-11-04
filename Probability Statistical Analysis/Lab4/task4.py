#!/usr/bin/env python

import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
import seaborn as sns
from sklearn.linear_model import LinearRegression

data = pd.read_csv('data/4/diabetes.csv')

print("checking for NaN values:")
print(data.isna().sum())
print('=======================================')
print("checking for 0 values:")
print((data==0).sum())
print('=======================================')

features = data.columns[1:6]
for column in features: 
    train_data = data[data[column] != 0]
    predict_data = data[data[column] == 0]

    feature_cols = [col for col in features if col != column]

    X_train = train_data[feature_cols]
    y_train = train_data[column]
    X_pred = predict_data[feature_cols]

    y_pred = LinearRegression().fit(X_train, y_train).predict(X_pred).astype(int)
    data.loc[data[data[column] == 0].index, column] = y_pred

features = data.columns[3:5]
for column in features: 
    train_data = data[data[column] != 0]
    predict_data = data[data[column] == 0]

    feature_cols = [col for col in features if col != column]

    X_train = train_data[feature_cols]
    y_train = train_data[column]
    X_pred = predict_data[feature_cols]

    y_pred = LinearRegression().fit(X_train, y_train).predict(X_pred).astype(int)
    data.loc[data[data[column] == 0].index, column] = y_pred

print('=======================================')
print("checking for 0 values:")
print((data==0).sum()[data.columns[1:6]])
