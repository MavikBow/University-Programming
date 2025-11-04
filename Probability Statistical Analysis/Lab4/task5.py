#!/usr/bin/env python

import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
import seaborn as sns

data = sns.load_dataset('titanic')

sns.histplot(data['age'], kde=True)
plt.savefig('img/5/ageplot_before.png')

print('column data misses:')
print(data.isna().sum())

# because interval values
data['age'] = data['age'].fillna(data['age'].median())

sns.histplot(data['age'], kde=True)
plt.savefig('img/5/ageplot_after.png')

print('deck unique data:')
print(data['deck'].unique())

# because nominal values
data['deck'] = data['deck'].fillna(data['deck'].mode()[0])
# easy to predict
data['embarked'] = data['embarked'].fillna(data['embarked'].mode()[0])
# hard to predict
data = data.dropna(subset=["embark_town"])

print('column data fixes:')
print(data.isna().sum())
