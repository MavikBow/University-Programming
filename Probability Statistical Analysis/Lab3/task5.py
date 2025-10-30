#!/usr/bin/env python

import folium
import pandas as pd
import seaborn as sns
import matplotlib.pyplot as plt

df = pd.read_csv('data/5/globalterrorismdb_0718dist.csv', delimiter=',', encoding='latin-1')

map_variable = folium.Map(location=[37.8, -96], zoom_start=4)

#for idx, row in df[:100].iterrows():
for idx, row in df[:200].iterrows():
    if pd.notnull(row['latitude']) and pd.notnull(row['longitude']):
        folium.Marker(
            location=[row['latitude'], row['longitude']],
            popup=f"{row['city']}, {row['country']}",
        ).add_to(map_variable)

map_variable.save('img/5/terrorism_map.html')

