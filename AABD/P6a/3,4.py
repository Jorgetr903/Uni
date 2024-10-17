import numpy as np
from sklearn.metrics import mean_squared_error
from sklearn.model_selection import train_test_split, GridSearchCV
from sklearn.preprocessing import PolynomialFeatures, StandardScaler
from sklearn.linear_model import LinearRegression, Ridge
from sklearn.pipeline import Pipeline
import matplotlib.pyplot as plt

def gen_data(m, seed=1, scale=0.7):
    """Genera un conjunto de datos basado en x^2 con ruido"""
    c = 0
    x_train = np.linspace(0, 49, m)
    np.random.seed(seed)
    y_ideal = x_train**2 + c
    y_train = y_ideal + scale * y_ideal * (np.random.sample((m,)) - 0.5)
    x_ideal = x_train
    return x_train, y_train, x_ideal, y_ideal

x_train, y_train, x_ideal, y_ideal = gen_data(64)

X = x_train[:, None]
Y = y_train[:, None]

# Dividir datos en entrenamiento, validacion y prueba
x_train, x_valtest, y_train, y_valtest = train_test_split(X, Y, test_size=0.4, random_state=1)
x_val, x_test, y_val, y_test = train_test_split(x_valtest, y_valtest, test_size=0.5, random_state=1)

# Lista de grados polinomiales a probar
degrees = range(1, 11)

best_degree = None
best_mse = float('inf')

# Entrenar modelos con diferentes grados polinomiales
for degree in degrees:
    # Crear pipeline para regresión polinomial
    pipeline = Pipeline([
        ('poly', PolynomialFeatures(degree=degree, include_bias=False)),
        ('scaler', StandardScaler()),
        ('regressor', LinearRegression())
    ])
    
    # Entrenar el modelo
    pipeline.fit(x_train.reshape(-1, 1), y_train)
    
    # Evaluar en conjunto de validación
    y_pred_val = pipeline.predict(x_val.reshape(-1, 1))
    mse = mean_squared_error(y_val, y_pred_val)
    
    # Guardar el mejor modelo
    if mse < best_mse:
        best_mse = mse
        best_degree = degree

print("El mejor grado polinomial encontrado es:", best_degree)
print("Error cuadrático medio en el conjunto de validación:", best_mse)

# Entrenar el modelo final con el mejor grado polinomial encontrado
pipeline = Pipeline([
    ('poly', PolynomialFeatures(degree=best_degree, include_bias=False)),
    ('scaler', StandardScaler()),
    ('regressor', LinearRegression())
])

pipeline.fit(x_train.reshape(-1, 1), y_train)

# Predicción del modelo en los datos ideales
y_pred_ideal = pipeline.predict(x_ideal.reshape(-1, 1))


# Dibujar los datos ideales
plt.plot(x_ideal, y_ideal, c='r', label='y_ideal')
plt.scatter(x_train, y_train, c='b', marker='o', label='train')
plt.plot(x_ideal, y_pred_ideal, c='orange', label='Predicted')
plt.xlabel('x')
plt.ylabel('y')
plt.title('Predicción del mejor polinomio')
plt.legend()
plt.show()
plt.savefig("Grado óptimo polinomio.png")


# Grado del polinomio
degree = 15

# Lista de lambdas a probar
lambdas = [1e-6, 1e-5, 1e-4, 1e-3, 1e-2, 1e-1, 1, 10, 100, 300, 600, 900]

best_lambda = None
best_mse = float('inf')

# Entrenar modelos con diferentes valores de lambda
for lmbda in lambdas:
    # Crear pipeline para regresión polinomial con regularización Ridge
    pipeline = Pipeline([
        ('poly', PolynomialFeatures(degree=degree, include_bias=False)),
        ('scaler', StandardScaler()),
        ('regressor', Ridge(alpha=lmbda))
    ])

    # Entrenar el modelo
    pipeline.fit(x_train.reshape(-1, 1), y_train)

    # Evaluar en conjunto de validación
    y_pred_val = pipeline.predict(x_val.reshape(-1, 1))
    mse = mean_squared_error(y_val, y_pred_val)

    # Guardar el mejor modelo
    if mse < best_mse:
        best_mse = mse
        best_lambda = lmbda

print("El mejor valor de lambda encontrado es:", best_lambda)
print("Error cuadrático medio en el conjunto de validación:", best_mse)

# Entrenar el modelo final con el mejor valor de lambda encontrado
pipeline = Pipeline([
    ('poly', PolynomialFeatures(degree=degree, include_bias=False)),
    ('scaler', StandardScaler()),
    ('regressor', Ridge(alpha=best_lambda))
])

pipeline.fit(x_train.reshape(-1, 1), y_train)

# Predicción del modelo en los datos ideales
y_pred_ideal = pipeline.predict(x_ideal.reshape(-1, 1))

# Dibujar los datos ideales
plt.plot(x_ideal, y_ideal, c='r', label='y_ideal')
plt.scatter(x_train, y_train, c='b', marker='o', label='train')
plt.plot(x_ideal, y_pred_ideal, c='orange', label='Predicted')
plt.xlabel('x')
plt.ylabel('y')
plt.title('Predicción del mejor polinomio')
plt.legend()
plt.show()
plt.savefig("Mejor parámetro regularización.png")