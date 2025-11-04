#!/usr/bin/env python

import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
from sklearn import preprocessing

data = pd.read_csv('data/6/winequality-red.csv')
print('raw data')
print(data)
print(data.describe())
print('')
print('----------------------------------------------------------------------------')

# does z score
# Centers the data around 0 and scales it to have a standard deviation of 1
scaler = preprocessing.StandardScaler().fit(data)
scaled_data = scaler.transform(data)
scaled_dataframe = pd.DataFrame(scaled_data, columns=data.columns)
print('after z scoring:')
print(scaled_dataframe)
print(scaled_dataframe.describe())
print('')
print('----------------------------------------------------------------------------')
# used in machine learning preprocessing to ensure that all features contribute equally to the model

# does min-max normalization
# Scales the data to a fixed range, usually [0, 1]
print('min max:')
min_max_scaler = preprocessing.MinMaxScaler().fit(data)
min_max_scaled_data = min_max_scaler.transform(data)
min_max_scaled_dataframe = pd.DataFrame(min_max_scaled_data, columns=data.columns)
max_abs_scaled_data = preprocessing.MaxAbsScaler().fit(data).transform(data)
max_abs_scaled_dataframe = pd.DataFrame(max_abs_scaled_data, columns=data.columns)
print(scaled_dataframe)
print(scaled_dataframe.describe())
print('')
print('----------------------------------------------------------------------------')
# You need all features in a bounded range like in neural networks

# maximum absolute scaling
# Scales each feature by its maximum absolute value.
max_abs_scaled_data = preprocessing.MaxAbsScaler().fit(data).transform(data)
max_abs_scaled_dataframe = pd.DataFrame(max_abs_scaled_data, columns=data.columns)
print('max abs:')
print(max_abs_scaled_dataframe)
print(max_abs_scaled_dataframe.describe())
print('')
print('----------------------------------------------------------------------------')
# You have sparse data (e.g., lots of zeros).
# Sign preservation
# You need a bounded range but don't want to center the data around zero.
