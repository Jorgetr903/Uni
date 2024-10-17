import numpy as np
import matplotlib.pyplot as plt
import scipy
from sklearn import svm
from scipy.io import loadmat


# Cargar los datos del archivo .mat
data = scipy.io.loadmat("C:/Users/jorge/source/repos/AABD/P7/data/ex6data1.mat", squeeze_me = True)
X = data['X']
y = data['y'].ravel()

# Visualizar los datos de entrenamiento
plt.figure()
plt.scatter(X[:, 0], X[:, 1], c=y, cmap=plt.cm.Paired, marker='o', edgecolors='k')
plt.title('Conjunto de Datos de Entrenamiento')
plt.savefig("Figure 1,1.jpg")


# Entrenar el clasificador SVM con kernel lineal y diferentes valores de C
C_values = [1, 100]
plt.figure(figsize=(12, 6))

for i, C in enumerate(C_values, 1):
    svm_model = svm.SVC(kernel='linear', C=C)
    svm_model.fit(X, y)
    
    # Predecir las etiquetas para cada punto de la malla
    x1 = np.linspace(X[:, 0].min(), X[:, 0].max(), 100)
    x2 = np.linspace(X[:, 1].min(), X[:, 1].max(), 100)
    x1, x2 = np.meshgrid(x1, x2)
    yp = svm_model.predict(np.array([x1.ravel(), x2.ravel()]).T).reshape(x1.shape)
    
    # Visualizar la frontera de decisión
    plt.subplot(1, len(C_values), i)
    plt.contour(x1, x2, yp)
    pos = (y == 1).ravel()
    neg = (y == 0).ravel()
    plt.scatter(X[pos, 0], X[pos, 1], color='black', marker='+')
    plt.scatter(X[neg, 0], X[neg, 1], color='yellow', edgecolors='black', marker='o')
    plt.title(f'SVM con C = {C}')

plt.tight_layout()
plt.savefig("Figure 1,2.jpg")
plt.close()

#--------------------
# Kernel gaussiano
#--------------------

# Cargar los datos del archivo .mat
data = scipy.io.loadmat("C:/Users/jorge/source/repos/AABD/P7/data/ex6data2.mat", squeeze_me = True)
X = data['X']
y = data['y'].ravel()

# Definir los parámetros C y sigma (1/2*sigma^2)
C = 1
sigma = 0.1
gamma = 1 / (2 * sigma**2)

# Crear una instancia de SVC con kernel RBF
svm1 = svm.SVC(kernel='rbf', C=C, gamma=gamma)

# Entrenar el clasificador SVM
svm1.fit(X, y)

# Predecir las etiquetas para cada punto de la malla
x1 = np.linspace(X[:, 0].min(), X[:, 0].max(), 100)
x2 = np.linspace(X[:, 1].min(), X[:, 1].max(), 100)
x1, x2 = np.meshgrid(x1, x2)
yp = svm1.predict(np.array([x1.ravel(), x2.ravel()]).T).reshape(x1.shape)

# Visualizar la frontera de decisión y los datos de entrenamiento
plt.figure()
plt.contour(x1, x2, yp)
pos = (y == 1).ravel()
neg = (y == 0).ravel()
plt.scatter(X[pos, 0], X[pos, 1], color='black', marker='+', label='Positivo')
plt.scatter(X[neg, 0], X[neg, 1], color='yellow', edgecolors='black', marker='o', label='Negativo')
plt.title(f'SVM con kernel RBF (C={C}, sigma={sigma})')
plt.savefig("Figure 1,3.jpg")


#-------------------------------
#Elección de los parámetros C y o
#-------------------------------

# Cargar los datos del archivo .mat
data = scipy.io.loadmat("C:/Users/jorge/source/repos/AABD/P7/data/ex6data3.mat", squeeze_me = True)
X = data['X']
y = data['y'].ravel()
Xval = data['Xval']
yval = data['yval'].ravel()

# Definir los valores de C y sigma a probar
C_values = [0.01, 0.03, 0.1, 0.3, 1, 3, 10, 30]
sigma_values = [0.01, 0.03, 0.1, 0.3, 1, 3, 10, 30]

# Inicializar variables para el mejor modelo
best_score = 0
best_params = {'C': None, 'sigma': None}

# Iterar sobre todos los valores de C y sigma
for C in C_values:
    for sigma in sigma_values:
        # Crear una instancia de SVC con kernel RBF y los parámetros C y sigma
        svm1 = svm.SVC(kernel='rbf', C=C, gamma=1 / (2 * sigma**2))
        # Entrenar el clasificador SVM
        svm1.fit(X, y)
        # Evaluar el modelo en el conjunto de validación
        score = svm1.score(Xval, yval)
        # Actualizar el mejor modelo si es necesario
        if score > best_score:
            best_score = score
            best_params['C'] = C
            best_params['sigma'] = sigma

# Entrenar el mejor modelo con todos los datos de entrenamiento
best_svm = svm.SVC(kernel='rbf', C=best_params['C'], gamma=1 / (2 * best_params['sigma']**2))
best_svm.fit(X, y)

# Visualizar la frontera de decisión del mejor modelo
plt.figure()
pos = (y == 1).ravel()
neg = (y == 0).ravel()
plt.scatter(X[pos, 0], X[pos, 1], color='black', marker='+', label='Positivo')
plt.scatter(X[neg, 0], X[neg, 1], color='yellow', edgecolors='black', marker='o', label='Negativo')
# Crear una malla para visualizar la frontera de decisión
x1_min, x1_max = X[:, 0].min() - 0.1, X[:, 0].max() + 0.1
x2_min, x2_max = X[:, 1].min() - 0.1, X[:, 1].max() + 0.1
x1, x2 = np.meshgrid(np.linspace(x1_min, x1_max, 100), np.linspace(x2_min, x2_max, 100))
yp = best_svm.predict(np.c_[x1.ravel(), x2.ravel()]).reshape(x1.shape)
plt.contour(x1, x2, yp)
plt.savefig("Figure 1,4.jpg")

print(f'Mejor modelo: C={best_params["C"]}, sigma={best_params["sigma"]}, precisión en validación={best_score}')
# Mejor modelo: C=1, sigma=0.1, precisión en validación=0.965