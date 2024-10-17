import numpy as np
from sklearn.discriminant_analysis import StandardScaler
import torch
from sklearn.datasets import make_blobs
from sklearn.model_selection import train_test_split
import torch.nn as nn
import matplotlib.pyplot as plt

# Generar el conjunto de datos artificial
classes = 6
m = 800
std = 0.4
centers = np.array([[-1, 0], [1, 0], [0, 1], [0,-1], [-2, 1], [-2,-1]])
X, y = make_blobs(n_samples=m, centers=centers, cluster_std=std, random_state=2, n_features=2)

# Dividir el conjunto de datos en entrenamiento, validación cruzada y prueba
X_train, X_temp, y_train, y_temp = train_test_split(X, y, test_size=0.50, random_state=1)
X_cv, X_test, y_cv, y_test = train_test_split(X_temp, y_temp, test_size=0.20, random_state=1)

def plot_data_with_validation(X_train, y_train, X_cv, y_cv, title):
    plt.figure(figsize=(8, 6))
    plt.scatter(X_train[:, 0], X_train[:, 1], c=y_train, cmap=plt.cm.rainbow, marker='o', label='Training Data')
    plt.scatter(X_cv[:, 0], X_cv[:, 1], c=y_cv, cmap=plt.cm.rainbow, marker='^', label='Cross-Validation Data')
    plt.title(title)
    plt.xlabel('Feature 1')
    plt.ylabel('Feature 2')
    plt.show()

# Visualizar los datos de entrenamiento y validación cruzada
plot_data_with_validation(X_train, y_train, X_cv, y_cv, title='Training and Cross-Validation Data')