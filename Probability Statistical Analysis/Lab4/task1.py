#!/usr/bin/env python

import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
import seaborn as sns

# Z-score показывает, на сколько стандартных отклонений 
# значение отстоит от среднего значения в выборке.

df = pd.read_csv('data/1-2/creditcard.csv') 

# Выводим базовую информацию
print(df.info())
print(df.describe())

# Выбираем числовые признаки (исключаем 'Class', так как это целевая переменная)
features = df.drop(columns=['Class'])

# Z-score
def detect_zscore_outliers(data, threshold=3):
    z_scores = np.abs((data - data.mean()) / data.std())
    return (z_scores > threshold)

z_outliers = detect_zscore_outliers(features)
df['Z_outlier'] = z_outliers.any(axis=1)

print("Аномалии по Z-score:", df['Z_outlier'].sum())

sns.countplot(x='Z_outlier', data=df)
plt.title('Аномалии по Z-score')
plt.savefig('img/1-2/z.png')
