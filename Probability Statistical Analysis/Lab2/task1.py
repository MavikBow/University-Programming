#!/usr/bin/env python

import pandas as pd

df = pd.read_csv('data/1_online_retail_II.csv')

# Check for missing values
missing_counts = df.isnull().sum()
missing_percent = (missing_counts / len(df)) * 100

missing_summary_table = pd.DataFrame({
    'missing values': missing_counts,
    'percent missing': missing_percent.round(2)
})

print("missing data summary table:")
print(missing_summary_table)

# Overall percentage of missing cells
overall_missing_percent = (missing_counts.sum() / df.size) * 100

print(f"overall missing data: {overall_missing_percent:.2f}% of all cells.")
