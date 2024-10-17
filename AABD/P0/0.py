import time
import numpy as np;
import matplotlib.pyplot as plt

def cuadrado(x):
    return x * x

def integra_mc(fun, a, b, num_puntos=10000):
    total_puntos = 0
    debajo_funcion = 0
    x_puntos = []
    y_puntos = []

    # Generar puntos aleatorios y evaluar la función
    for _ in range(num_puntos): 
        x = np.random.uniform(a, b)
        y = np.random.uniform(0, np.max(fun(np.linspace(a, b, 1000))))

        total_puntos += 1
        if y <= fun(x):
            debajo_funcion += 1

        x_puntos.append(x)
        y_puntos.append(y)

    x_puntos = np.array(x_puntos)
    y_puntos = np.array(y_puntos)

    # Calcular la integral aproximada usando Monte Carlo
    area_rectangulo = (b - a) * np.max(fun(np.linspace(a, b, 1000)))
    integral_aproximada = area_rectangulo * (debajo_funcion / total_puntos)

    '''
    # Gráfica de la función y puntos generados
    plt.plot(x_puntos, y_puntos, 'ro', label='Puntos generados')
    x_values = np.linspace(a, b, 1000)
    plt.plot(x_values, fun(x_values), label='Función cuadrado(x)')
    plt.xlabel('x')
    plt.ylabel('y')
    plt.title('Vecsión iterativa')
    plt.legend()
    plt.show()
    '''
    return integral_aproximada


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
    plt.title('Versión vectorizada')
    plt.legend()
    plt.show()
    '''
    return integral_aproximada

# Función para medir el tiempo de ejecución de una función
def execution_time(func, *args, **kwargs):
    start_time = time.time()
    func(*args, **kwargs)
    return time.time() - start_time

def main():
    # Ejemplo de uso
    a = 0
    b = 200
    resultado_mc_iterativa = integra_mc(cuadrado, a, b)
    resultado_mc_vectorizada = integra_mc_vectorizada(cuadrado, a, b)

    print(f"Resultado Monte Carlo (iterativo): {resultado_mc_iterativa}")
    print(f"Resultado Monte Carlo (vectorizado): {resultado_mc_vectorizada}")

    # Generar tamaños de muestra para la comparación de tiempos
    sizes = np.linspace(10, 10**5, 50).astype(int)
    execution_time_mc = []
    execution_time_vectorial = []
    
    for size in sizes:
        # Medir el tiempo de ejecución para la versión iterativa
        time_mc = execution_time(integra_mc, cuadrado, a, b, num_puntos=size)
        execution_time_mc.append(time_mc)

        # Medir el tiempo de ejecución para la versión vectorizada
        time_vectorial = execution_time(integra_mc_vectorizada, cuadrado, a, b, num_puntos=size)
        execution_time_vectorial.append(time_vectorial)

    # Crear y mostrar la gráfica de comparación de tiempos
    plt.figure()
    plt.scatter(sizes, execution_time_mc, c='red', label='bucle')
    plt.scatter(sizes, execution_time_vectorial, c='blue', label='vector')
    plt.legend()
    plt.savefig('time.png')
    plt.show()

if __name__ == "__main__":
    main()
