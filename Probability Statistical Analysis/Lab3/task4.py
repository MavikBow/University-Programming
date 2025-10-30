#!/usr/bin/env python

import pandas as pd
import seaborn as sns
import matplotlib.pyplot as plt

df_confirmed = pd.read_csv("data/4/time_series_covid19_confirmed_global.csv")
df_deaths = pd.read_csv("data/4/time_series_covid19_deaths_global.csv")
df_recovered = pd.read_csv("data/4/time_series_covid19_recovered_global.csv")

dates_confirmed = df_confirmed.iloc[24][4:].rename('confirmed')
dates_deaths = df_deaths.iloc[24][4:].rename('deaths')
dates_recovered = df_recovered.iloc[24][4:].rename('recovered')

covid_data = pd.concat([dates_confirmed, dates_deaths, dates_recovered], axis=1)
plt.figure(figsize=(20,10))
sns.lineplot(covid_data)
plt.legend()
plt.grid(False)

plt.savefig('img/4/timelapse.png')
