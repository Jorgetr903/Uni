import numpy as np
import matplotlib.pyplot as plt
from sklearn.metrics import mean_squared_error
from sklearn.model_selection import train_test_split
from sklearn.preprocessing import PolynomialFeatures, StandardScaler
from sklearn.linear_model import Ridge
from sklearn.pipeline import Pipeline

def gen_data(m, seed=1, scale=0.7):
    """Genera un conjunto de datos basado en x^2 con ruido"""
    c = 0
    x_train = np.linspace(0, 49, m)
    np.random.seed(seed)
    y_ideal = x_train**2 + c
    y_train = y_ideal + scale * y_ideal * (np.random.sample((m,)) - 0.5)
    x_ideal = x_train
    return x_train, y_train, x_ideal, y_ideal

# Generar datos
x, y, x_ideal, y_ideal = gen_data(750)

# Dividir datos en entrenamiento, validación y prueba
x_train, x_temp, y_train, y_temp = train_test_split(x, y, test_size=0.4, random_state=1)
x_val, x_test, y_val, y_test = train_test_split(x_temp, y_temp, test_size=0.5, random_state=1)

# Lista de grados polinomiales a probar
degrees = range(1, 16)

# Lista de lambdas a probar
lambdas = [1e-6, 1e-5, 1e-4, 1e-3, 1e-2, 1e-1, 1, 10, 100, 300, 600, 900]

best_degree = None
best_lambda = None
best_mse = float('inf')

# Realizar búsqueda exhaustiva
for degree in degrees:
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
            best_degree = degree
            best_lambda = lmbda

print("La mejor combinación de grado del polinomio y valor de lambda encontrada es:")
print("Grado del polinomio:", best_degree)
print("Valor de lambda:", best_lambda)
print("Error cuadrático medio en el conjunto de validación:", best_mse)

# Entrenar el modelo final con la mejor combinación encontrada
pipeline = Pipeline([
    ('poly', PolynomialFeatures(degree=best_degree, include_bias=False)),
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
plt.savefig('Mejor combinación grado polinomio y parámetro regularización.png')