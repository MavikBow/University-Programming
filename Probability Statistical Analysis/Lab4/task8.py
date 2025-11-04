#!/usr/bin/env python

import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
import seaborn as sns
import nltk
from nltk.corpus import stopwords
from nltk.stem import PorterStemmer, WordNetLemmatizer
from sklearn.feature_extraction.text import CountVectorizer
import re

data = pd.read_csv('data/8/Tweets.csv')

nltk.download('stopwords')
nltk.download('wordnet')

lemmatizer = WordNetLemmatizer()
stop_words = set(stopwords.words('english'))

# Preprocessing function
def preprocess_text(text):
    text = text.lower()
    text = re.sub(r"http\S+|@\S+|[^a-zA-Z\s]", '', text)  # Remove URLs, mentions, punctuation
    words = text.split()
    words = [lemmatizer.lemmatize(word) for word in words if word not in stop_words]
    return ' '.join(words)

data['processed_text'] = data['text'].apply(preprocess_text)
data = data[data['processed_text'].str.strip() != '']

print('original messages:')
print(data['text'])
print('==============================================')
print('NewSpeak:')
print(data['processed_text'])

# Vectorize
vectorizer = CountVectorizer()
X = vectorizer.fit_transform(data['processed_text'])
vector_data = pd.DataFrame(X.toarray(), columns=vectorizer.get_feature_names_out())

print('==============================================')
print(vector_data)
