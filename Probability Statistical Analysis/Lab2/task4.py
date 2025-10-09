#!/usr/bin/env python

import pandas as pd
import pycountry

files = [
        "data/4_global_cancer_patients_2015_2024.csv",
        "data/4_with_belarus.csv"
        ]
for file in files:
    df = pd.read_csv(file)

    country_column = [col for col in df.columns if 'country' in col.lower()][0]

    # Get unique countries from the dataset
    dataset_countries = set(df[country_column].dropna().unique())

    # Get official country names from pycountry
    official_countries = set(country.name for country in pycountry.countries)

    missing_countries = official_countries - dataset_countries

    # Summary
    print(f"Dataset: {file}")
    print(f"Countries in dataset: {len(dataset_countries)}")
    print(f"Official countries: {len(official_countries)}")
    print(f"Missing countries: {len(missing_countries)}")

    # Show a few missing ones
    print("\nExamples of missing countries:")
    print(sorted(list(missing_countries))[:10])
    print("")

