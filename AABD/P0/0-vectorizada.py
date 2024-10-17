import numpy as np;
import matplotlib.pyplot as plt

def cuadrado(x):
    return x * x

def integra_mc_vectorizada(fun, a, b, num_puntos=10000):

    x = np.linspace(a, b, num_puntos)

    y_max = np.max(fun(x))  # Obtener el máximo de la función
    y = np.random.uniform(0, y_max, num_puntos)
    debajo_funcion = np.sum(y <= fun(x))


    x_puntos = np.array(x)
    y_puntos = np.array(y)

    area_rectangulo = (b - a) * np.max(fun(np.linspace(a, b, 1000)))
    integral_aproximada = area_rectangulo * (debajo_funcion / num_puntos)
    
    '''
     # Gráfica de la función y puntos generados
    plt.plot(x_puntos, y_puntos, 'ro', label='Puntos generados')
    x_values = np.linspace(a, b, 1000)
    plt.plot(x_values, fun(x_values), label='Función cuadrado(x)')
    plt.xlabel('x')
    plt.ylabel('y')
    plt.title('Aproximación Monte Carlo de la integral')
    plt.legend()
    plt.show()
    '''
    return integral_aproximada



# Ejemplo de uso
a = 0
b = 200
resultado_mc_vectorizada = integra_mc_vectorizada(cuadrado, a, b)

print(f"Resultado Monte Carlo (vectorizado): {resultado_mc_vectorizada}")