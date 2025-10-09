#!/usr/bin/env python

import pandas as pd

df = pd.read_csv('data/3_covid19_tweets.csv')

# identify the date column
date_column = [col for col in df.columns if 'date' in col.lower()][0]
df[date_column] = pd.to_datetime(df[date_column], errors='coerce')
# deletes deez NaTs
df = df.dropna(subset=[date_column])

# Sort by date descending (newest first)
df_sorted = df.sort_values(by=date_column, ascending=False)

# Display the 10 newest tweets
print("10 newest tweets:")
print(df_sorted[['user_name', 'text', date_column]].head(10))

