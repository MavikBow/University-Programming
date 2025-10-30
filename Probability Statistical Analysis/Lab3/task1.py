#!/usr/bin/env python

import pandas as pd

df = pd.read_csv('data/1/CAR DETAILS FROM CAR DEKHO.csv')
print(df.columns)


# Bar Chart — Number of cars by fuel type

import seaborn as sns
import matplotlib.pyplot as plt

sns.countplot(data=df, x='fuel')
plt.title('Number of Cars by Fuel Type')
plt.savefig('img/1/barchart.png')

# Histogram — Distribution of selling prices

plt.hist(df['selling_price'], bins=30, color='blue')
plt.title('Selling Price Distribution')
plt.xlabel('Price')
plt.ylabel('Frequency')
plt.savefig('img/1/histogram.png')

# Line Plot — Average price per year

avg_price_by_year = df.groupby('year')['selling_price'].mean().reset_index()

plt.plot(avg_price_by_year['year'], avg_price_by_year['selling_price'], marker='o')
plt.title('Average Selling Price by Year')
plt.xlabel('Year')
plt.ylabel('Average Price')
plt.grid(True)
plt.savefig('img/1/lineplot.png')

# Box Plot — Price distribution by transmission type

sns.boxplot(data=df, x='transmission', y='selling_price')
plt.title('Selling Price by Transmission Type')
plt.savefig('img/1/boxplot.png')

# Violin Plot (Box with whiskers + density) — Price by fuel type

sns.violinplot(data=df, x='fuel', y='selling_price')
plt.title('Selling Price Distribution by Fuel Type')
plt.savefig('img/1/violinplot.png')

# Radar Chart — Average km driven, price, and year by fuel type

import numpy as np
import plotly.graph_objects as go

# Prepare data
radar_data = df.groupby('fuel')[['selling_price', 'km_driven', 'year']].mean()
categories = radar_data.columns.tolist()

fig = go.Figure()

for fuel_type in radar_data.index:
    fig.add_trace(go.Scatterpolar(
        r=radar_data.loc[fuel_type].values,
        theta=categories,
        fill='toself',
        name=fuel_type
    ))

fig.update_layout(
    polar=dict(radialaxis=dict(visible=True)),
    title='Radar Chart: Fuel Type Comparison',
    showlegend=True
)
fig.show()


# Scatter Plot — Price vs. Kilometers Driven

sns.scatterplot(data=df, x='km_driven', y='selling_price', hue='fuel')
plt.title('Selling Price vs. Kilometers Driven')
plt.savefig('img/1/scallerplot.png')

