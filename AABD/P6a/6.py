import numpy as np
import matplotlib.pyplot as plt
from sklearn.metrics import mean_squared_error
from sklearn.model_selection import train_test_split
from sklearn.preprocessing import PolynomialFeatures
from sklearn.linear_model import LinearRegression
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
x, y, _, _ = gen_data(1000)

_x = x[:, None]
_y = y[:, None]

# Dividir los datos en conjunto de entrenamiento y validación
x_train, x_temp, y_train, y_temp = train_test_split(_x, _y, test_size=0.4, random_state=1)
x_val, x_test, y_val, y_test = train_test_split(x_temp, y_temp, test_size=0.5, random_state=1)

train_errors = []
val_errors = []

# Configurar el modelo de regresión polinómica de grado 16
model = Pipeline([
    ("poly_features", PolynomialFeatures(degree=16)),
    ("lin_reg", LinearRegression())
])

# Entrenar el modelo con diferentes tamaños de conjunto de entrenamiento
for m in range(50, 601, 50):
    # Seleccionar un subconjunto de datos de entrenamiento
    x_subset = x_train[:m]
    y_subset = y_train[:m]
    
    # Entrenar el modelo
    model.fit(x_subset, y_subset)
    
    # Predecir en el conjunto de entrenamiento
    y_train_pred = model.predict(x_subset)
    train_error = mean_squared_error(y_subset, y_train_pred)
    train_errors.append(train_error)
    
    # Predecir en el conjunto de validación
    y_val_pred = model.predict(x_val)
    val_error = mean_squared_error(y_val, y_val_pred)
    val_errors.append(val_error)

# Graficar los errores de entrenamiento y validación
plt.plot(range(50, 601, 50), train_errors, label='Train error')
plt.plot(range(50, 601, 50), val_errors, label='Validation error')
plt.xlabel('Número de ejemplos de entrenamiento')
plt.ylabel('Error cuadrático medio')
plt.title('Efecto del aumento del número de ejemplos de entrenamiento')
plt.legend()
plt.show()
