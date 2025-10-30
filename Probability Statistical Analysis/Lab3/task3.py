#!/usr/bin/env python

import pandas as pd
import plotly.express as px

df = pd.read_csv("data/3/1976-2020-president.csv")

# Filter for a specific year
df = df[df['year'] == 2020]

fig = px.choropleth(
    df,
    locations='state_po',
    locationmode='USA-states',
    #color='candidatevotes',
    color='party_detailed',
    hover_name='candidate',
    hover_data=['party_simplified'],
    scope='usa'
)

fig.update_layout(
    geo=dict(bgcolor= 'rgba(0,0,0,0)'),
    template='plotly'
)

fig.write_html("img/3/presidential_map.html")

