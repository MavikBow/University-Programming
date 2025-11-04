#!/usr/bin/env python

import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
import seaborn as sns

df = pd.read_csv('data/3/Summary of Weather.csv', low_memory=False)
plt.figure(figsize=(16, 8))
sns.boxplot(df.iloc[:, 4:7])

plt.savefig('img/3/boxchart.png')
plt.close()
