import numpy as np
import copy
import math
from public_tests import*
from utils import*
import matplotlib.pyplot as plt

#########################################################################
# Cost function
#
def compute_cost(x, y, w, b):
    
    total_cost = 0

    for i in range(len(x)):
        total_cost += ((w*x[i] + b) - y[i])**2

    total_cost = total_cost / (2 * len(x))

    return total_cost


#########################################################################
# Gradient function
#
def compute_gradient(x, y, w, b):

    dj_dw = 0
    dj_db = 0

    for i in range(len(x)):
        dj_dw += ((w*x[i] + b) - y[i]) * x[i]
        dj_db += ((w*x[i] + b) - y[i])

    dj_db = dj_db / len(x)
    dj_dw = dj_dw / len(x)
    

    return dj_dw, dj_db


#########################################################################
# gradient descent
#
def gradient_descent(x, y, w_in, b_in, cost_function, gradient_function, alpha, num_iters):
    m = len(x)
    w = w_in
    b = b_in
    J_history = np.zeros(num_iters)

    for i in range(num_iters):
        # Calcula el gradiente
        dj_dw, dj_db = gradient_function(x, y, w, b)

        # Actualiza los parámetros usando el descenso de gradiente
        w = w - alpha * dj_dw
        b = b - alpha * dj_db
        # Calcula el coste
        J = cost_function(x, y, w, b)

        # Almacena el costo en cada iteración para graficar posteriormente
        J_history[i] = J
        
        if (i == 2 or i == 10 or i == 50 or i == 100 or i == 500 or i == 1000):
            plt.scatter(x[:i], y[:i], color='red', marker='x', label='Datos reales')
            plt.plot(x[:i], w * x[:i] + b, color='blue', label='Recta ajustada por descenso de gradiente')
            plt.xlabel('Population of City in 10,000s')
            plt.ylabel('Profit in $10,000')
            plt.title(' Population iteration ' + str(i))
            plt.legend()
            plt.show()

    # Gráfica de los costes en el tiempo
    plt.plot(J_history, label='Coste')
    plt.xlabel('Tiempo')
    plt.ylabel('Coste')
    plt.title('Evolución del coste en el tiempo')
    plt.legend()
    plt.show()

    '''
    w, b, i, x, y
    Como se puede ver en la gráfica, el coste en las primeras iteraciones es alto en comparación del resto de iteraciones
    En las primeras 1000 iteraciones, más o menos, el coste baja rápidamente, 
    para luego mantenerse casi constante en el resto de iteraciones.

    Empieza con un coste en torno a 6.7 y acaba con un 4.50 aproximadamente
    '''

    return w, b, J_history

def predict(w, b, population):
    return w * population + b


def main():
    w = 0
    b = 0
    x, y = load_data()

    w2, b2, J_history = gradient_descent(x, y, w, b, compute_cost, compute_gradient, 0.01, 1500)

    # Graficar los puntos y la recta ajustada
    plt.scatter(x, y, color='red', marker='x', label='Datos reales')
    plt.plot(x, w2 * x + b2, color='blue', label='Recta ajustada por descenso de gradiente')
    plt.xlabel('Population of City in 10,000s')
    plt.ylabel('Profit in $10,000')
    plt.title(' Profits vs. Population per city')
    plt.legend()
    plt.show()

    print(f'w: {w2}, b: {b2}')
    
    # Hacer predicciones para las áreas de 35,000 y 70,000 personas
    population_1 = 35000
    population_2 = 70000

    profit_1 = predict(w2, b2, population_1)
    profit_2 = predict(w2, b2, population_2)

    print(f'Para una población de 35,000 personas, la predicción de beneficios es: {profit_1}')
    print(f'Para una población de 70,000 personas, la predicción de beneficios es: {profit_2}')

    '''
    Los resultados finales de w y b son:
    w: 1.166362350335582, b: -3.63029143940436
    
    Los resultados de las predicciones son:
    Para una población de 35,000 personas, la predicción de beneficios es: 40819.05197030597
    Para una población de 70,000 personas, la predicción de beneficios es: 81641.73423205134
    '''

if __name__ == "__main__":
    main()
