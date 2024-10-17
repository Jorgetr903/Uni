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

def compute_cost(y_true, y_pred):
    """
    Calcula el costo mediante el error cuadrático medio.
    
    Parámetros:
    y_true -- etiquetas verdaderas
    y_pred -- etiquetas predichas
    
    Retorna:
    cost -- costo calculado
    """
    # Calcula el error cuadrático medio
    cost = mean_squared_error(y_true, y_pred)
    return cost


# Generar datos
x_train, y_train, x_ideal, y_ideal = gen_data(64)

# Gráfica Figure 1.1: Datos de entrenamiento artificiales
plt.figure(figsize=(8, 6))
plt.plot(x_ideal, y_ideal, color='red', label='y_ideal')
plt.scatter(x_train, y_train, color='blue')
plt.xlabel('x')
plt.ylabel('y')
plt.title('Figure 1.1: Datos de entrenamiento artificiales')
plt.show()
plt.savefig("Datos Entrenamiento_Model.png")

X = x_train[:, None]
Y = y_train[:, None]

# Dividir datos en entrenamiento y prueba
x_train, x_test, y_train, y_test = train_test_split(X, Y, test_size=0.33, random_state=1)

# Sobre-ajuste a los datos de entrenamiento (Figure 1.2)
poly = PolynomialFeatures(degree=15, include_bias=False)
scaler = StandardScaler()
x_train_poly = poly.fit_transform(x_train)
x_train_scaled = scaler.fit_transform(x_train_poly)

model = LinearRegression()
model.fit(x_train_scaled, y_train)

#Pintamos el score (habrá overfitting)
print('Score en entrenamiento -> ',model.score(x_train_scaled, y_train))
    
#Transformamos la X de test a grado 15 y las escalamos
x_test_poly = poly.fit_transform(x_test)
x_test_scaled = scaler.fit_transform(x_test_poly)
    
#Pintamos su score (será malo)
print('Score en test -> ',model.score(x_test_scaled, y_test))
    
#Generamos predicciones para calcular el coste
train_predicion = model.predict(x_train_scaled)
test_predicion = model.predict(x_test_scaled)
    
#Calculamos el coste
train_cost = compute_cost(y_train, train_predicion)
test_cost = compute_cost(y_test, test_predicion)

print('Coste en entrenamiento -> ',train_cost)
print('Coste en test -> ', test_cost)
    
#Obtrenemos el vector de pesos y el término independiente del modelo
weights = model.coef_
intercept = model.intercept_

#DIBUJAMOS
plt.plot(x_ideal, y_ideal, c='r', label='y_ideal') #Lo que debería salir
plt.scatter(x_train, y_train, c='b', marker='o', label='train') #Ptos Con ruido
#Con los pesos del modelo dibujo el polinomio
xAux = poly.transform(X)
xAux = scaler.fit_transform(xAux)
ptos = np.dot(xAux, weights.T) + intercept 
plt.plot(X,ptos, c='orange', label='Predicted')
plt.legend()
plt.savefig("OverFitting_Model.png")
plt.show()
