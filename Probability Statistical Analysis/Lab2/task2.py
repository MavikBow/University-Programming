#!/usr/bin/env python

import pandas as pd
from datetime import datetime

files = [
    "data/2_GlobalLandTemperaturesByCity.csv",
    "data/2_GlobalLandTemperaturesByCountry.csv",
    "data/2_GlobalLandTemperaturesByMajorCity.csv",
    "data/2_GlobalLandTemperaturesByState.csv",
    "data/2_GlobalTemperatures.csv",
    "data/2_bla.csv"
]

for file in files:
    print("\n")
    print(f"Checking: {file}")
    df = pd.read_csv(file)
    date_column = df.columns[0]
    
    # turns bat dates to NaT
    parsed_dates = pd.to_datetime(df[date_column], errors='coerce')
    # counts deez Nats
    failed_count = parsed_dates.isna().sum()
    failed_percent = (failed_count / len(df)) * 100

    print(f"Date column: '{date_column}'")
    print(f"Failed to parse: {failed_count} rows ({failed_percent:.2f}%)")

    if failed_count > 0:
        print("Example of problematic entries:")
        print(df[parsed_dates.isna()][date_column].head())
        
print("\n")
