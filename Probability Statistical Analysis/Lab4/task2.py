#!/usr/bin/env python

import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
import seaborn as sns

# interquartile range — это статистический показатель, 
# который измеряет разброс «средних» 50% данных в упорядоченном наборе, игнорируя крайние значения

df = pd.read_csv('data/1-2/creditcard.csv') 

# Выводим базовую информацию
print(df.info())
print(df.describe())

# Выбираем числовые признаки (исключаем 'Class', так как это целевая переменная)
features = df.drop(columns=['Class'])

def detect_iqr_outliers(data):
    Q1 = data.quantile(0.25)
    Q3 = data.quantile(0.75)
    IQR = Q3 - Q1
    return ((data < (Q1 - 1.5 * IQR)) | (data > (Q3 + 1.5 * IQR)))

iqr_outliers = detect_iqr_outliers(features)
df['IQR_outlier'] = iqr_outliers.any(axis=1)

print("Аномалии по IQR:", df['IQR_outlier'].sum())

sns.countplot(x='IQR_outlier', data=df)
plt.title('Аномалии по IQR')
plt.savefig('img/1-2/iqr.png')

