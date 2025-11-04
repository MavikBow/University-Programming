#!/usr/bin/env python

import seaborn as sns
import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
from sklearn.feature_selection import f_regression
import statsmodels.api as sm

column_names = ['CRIM', 'ZN', 'INDUS', 'CHAS', 'NOX', 'RM', 'AGE', 'DIS', 'RAD', 'TAX', 'PTRATIO', 'B', 'LSTAT', 'MEDV']
data = pd.read_csv('data/housing.csv', header=None, delimiter=r"\s+", names=column_names)

X = data.iloc[:, :-1]
y = data.iloc[:, -1]

X = sm.add_constant(X)
model = sm.OLS(y, X).fit()

p_values = model.pvalues
ols_features = p_values[p_values < 0.05].index

print(model.summary())
print('[3] INDUS and AGE have to low coefs, so they can be excluded')

