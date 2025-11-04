#!/usr/bin/env python

#import numpy as np
#import pandas as pd
#from sklearn.datasets import load_wine
#from sklearn.model_selection import train_test_split, cross_val_score
#from sklearn.preprocessing import StandardScaler
#from sklearn.ensemble import RandomForestClassifier
#from sklearn.feature_selection import SelectKBest, f_classif, RFE, SelectFromModel, mutual_info_classif
#from sklearn.linear_model import LogisticRegression
#from sklearn.decomposition import PCA
#import matplotlib.pyplot as plt
#
## Загрузка данных
#data = load_wine()
#X, y = data.data, data.target
#feature_names = data.feature_names
#
## Масштабирование признаков
#scaler = StandardScaler()
#X_scaled = scaler.fit_transform(X)
#
## Разделение на обучающую и тестовую выборки
#X_train, X_test, y_train, y_test = train_test_split(X_scaled, y, test_size=0.3, random_state=42)
#
## Словарь для хранения результатов
#results = {}
#
## Базовая модель
#def evaluate_model(X_train, X_test, y_train, y_test, name):
    #model = RandomForestClassifier(random_state=42)
    #model.fit(X_train, y_train)
    #acc = model.score(X_test, y_test)
    #results[name] = acc
#
## 1. SelectKBest (ANOVA F-test)
#skb = SelectKBest(score_func=f_classif, k=8)
#X_train_skb = skb.fit_transform(X_train, y_train)
#X_test_skb = skb.transform(X_test)
#evaluate_model(X_train_skb, X_test_skb, y_train, y_test, "SelectKBest")
#
## 2. RFE (Recursive Feature Elimination)
#rfe = RFE(estimator=LogisticRegression(max_iter=1000), n_features_to_select=8)
#X_train_rfe = rfe.fit_transform(X_train, y_train)
#X_test_rfe = rfe.transform(X_test)
#evaluate_model(X_train_rfe, X_test_rfe, y_train, y_test, "RFE")
#
## 3. SelectFromModel (на основе важности признаков)
#sfm = SelectFromModel(RandomForestClassifier(random_state=42), threshold="median")
#sfm.fit(X_train, y_train)
#X_train_sfm = sfm.transform(X_train)
#X_test_sfm = sfm.transform(X_test)
#evaluate_model(X_train_sfm, X_test_sfm, y_train, y_test, "SelectFromModel")
#
## 4. Mutual Information
#mi = SelectKBest(score_func=mutual_info_classif, k=8)
#X_train_mi = mi.fit_transform(X_train, y_train)
#X_test_mi = mi.transform(X_test)
#evaluate_model(X_train_mi, X_test_mi, y_train, y_test, "MutualInfo")
#
## 5. PCA (Principal Component Analysis)
#pca = PCA(n_components=8)
#X_train_pca = pca.fit_transform(X_train)
#X_test_pca = pca.transform(X_test)
#evaluate_model(X_train_pca, X_test_pca, y_train, y_test, "PCA")
#
## 6. Без отбора признаков (Baseline)
#evaluate_model(X_train, X_test, y_train, y_test, "All Features")
#
## 📊 Визуализация результатов
#plt.figure(figsize=(10, 6))
#plt.bar(results.keys(), results.values(), color='skyblue')
#plt.ylabel("Accuracy")
#plt.title("Сравнение методов отбора признаков")
#plt.xticks(rotation=45)
#plt.grid(axis='y')
#plt.tight_layout()
#plt.savefig('img/6/plot.png')

import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
from sklearn.datasets import load_wine
from sklearn.model_selection import train_test_split, cross_val_score
from sklearn.preprocessing import StandardScaler
from sklearn.ensemble import RandomForestClassifier
from sklearn.feature_selection import SelectKBest, f_classif, RFE, SelectFromModel, mutual_info_classif
from sklearn.linear_model import LogisticRegression
from sklearn.decomposition import PCA

# Загрузка и подготовка данных
data = load_wine()
X, y = data.data, data.target
feature_names = data.feature_names

scaler = StandardScaler()
X_scaled = scaler.fit_transform(X)

# Разделение на обучающую и тестовую выборки
X_train, X_test, y_train, y_test = train_test_split(X_scaled, y, test_size=0.3, random_state=42)

# Функция оценки модели с кросс-валидацией
def evaluate_cv(X, y, name):
    model = RandomForestClassifier(random_state=42)
    scores = cross_val_score(model, X, y, cv=5)
    return name, scores.mean()

# Словарь для хранения результатов
results = []

# 1. Все признаки
results.append(evaluate_cv(X_scaled, y, "All Features"))

# 2. SelectKBest
skb = SelectKBest(score_func=f_classif, k=8)
X_skb = skb.fit_transform(X_scaled, y)
results.append(evaluate_cv(X_skb, y, "SelectKBest"))

# 3. RFE
rfe = RFE(estimator=LogisticRegression(max_iter=1000), n_features_to_select=8)
X_rfe = rfe.fit_transform(X_scaled, y)
results.append(evaluate_cv(X_rfe, y, "RFE"))

# 4. SelectFromModel
sfm = SelectFromModel(RandomForestClassifier(random_state=42), threshold="median")
sfm.fit(X_scaled, y)
X_sfm = sfm.transform(X_scaled)
results.append(evaluate_cv(X_sfm, y, "SelectFromModel"))

# 5. Mutual Information
mi = SelectKBest(score_func=mutual_info_classif, k=8)
X_mi = mi.fit_transform(X_scaled, y)
results.append(evaluate_cv(X_mi, y, "MutualInfo"))

# 6. PCA
pca = PCA(n_components=8)
X_pca = pca.fit_transform(X_scaled)
results.append(evaluate_cv(X_pca, y, "PCA"))

# 📊 Визуализация точности
labels, scores = zip(*results)
plt.figure(figsize=(10, 6))
plt.bar(labels, scores, color='blue')
plt.ylabel("Cross-validated Accuracy")
plt.title("Сравнение методов отбора признаков")
plt.xticks(rotation=45)
plt.grid(axis='y')
plt.tight_layout()
for i, (label, score) in enumerate(zip(labels, scores)):
    plt.text(i, score + 0.005, f"{score:.3f}", ha='center', va='bottom', fontsize=10)

plt.tight_layout()
plt.savefig('img/6/fig1.png')

# 📈 Визуализация важности признаков
model = RandomForestClassifier(random_state=42)
model.fit(X_scaled, y)
importances = model.feature_importances_
indices = np.argsort(importances)[::-1]

plt.figure(figsize=(10, 6))
plt.bar([feature_names[i] for i in indices], importances[indices], color='red')
plt.title("Важность признаков (RandomForest)")
plt.ylabel("Importance")
plt.xticks(rotation=45)
plt.tight_layout()
plt.savefig('img/6/fig2.png')

