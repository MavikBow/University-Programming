#!/usr/bin/env python

# 1. merge datasets into one
# 2. clean missing values
# 3. separate into different countries
# 4. compute correlations across numeric columns

import pandas as pd
import seaborn as sns
import matplotlib.pyplot as plt

temp = pd.read_csv("data/2/temperature.csv")
humidity = pd.read_csv("data/2/humidity.csv")
pressure = pd.read_csv("data/2/pressure.csv")
wind = pd.read_csv("data/2/wind_speed.csv")

temp_melted = temp.melt(id_vars='datetime', var_name='city', value_name='temperature')
humidity_melted = humidity.melt(id_vars='datetime', var_name='city', value_name='humidity')
pressure_melted = pressure.melt(id_vars='datetime', var_name='city', value_name='pressure')
wind_melted = wind.melt(id_vars='datetime', var_name='city', value_name='wind_speed')

merged = temp_melted.merge(humidity_melted, on=['datetime', 'city']) \
                    .merge(pressure_melted, on=['datetime', 'city']) \
                    .merge(wind_melted, on=['datetime', 'city'])

canada_cities = ['Toronto', 'Vancouver', 'Montreal', 'Calgary', 'Ottawa']
israel_cities = ['Tel Aviv', 'Jerusalem', 'Haifa', 'Beersheba', 'Eilat']

# Function to plot heatmap for a given country
def plot_country_heatmap(country_name, city_list):
    country_df = merged[merged['city'].isin(city_list)]
    numeric_df = country_df.drop(columns=['datetime', 'city'])
    corr_matrix = numeric_df.corr()

    plt.figure(figsize=(10, 8))
    sns.heatmap(corr_matrix, annot=True, cmap='coolwarm', fmt=".2f")
    plt.title(f'Correlation Matrix of Weather Metrics - {country_name}')
    plt.savefig(f'img/2/heatmap_{country_name.lower()}.png')
    plt.close()

plot_country_heatmap('Canada', canada_cities)
plot_country_heatmap('Israel', israel_cities)

