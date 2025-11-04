#!/usr/bin/env python

import seaborn as sns
import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
from sklearn.datasets import load_wine

data = load_wine(as_frame=True).frame

plt.figure(figsize=(10, 10))
sns.heatmap(data.corr(), annot=True)
plt.savefig('img/1/heatmap.png')
