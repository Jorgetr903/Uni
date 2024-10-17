import numpy as np
import copy
import math
from public_tests import*
from utils import*
import matplotlib.pyplot as plt

def sigmoid(z):
    """
    Compute the sigmoid of z
    Args:
        z (ndarray): A scalar, numpy array of any size.
    Returns:
        g (ndarray): sigmoid(z), with the same shape as z
    """

    g = 1 / (1 + np.exp(-z))

    return g


#########################################################################
# logistic regression
#
def compute_cost(X, y, w, b, lambda_=None):
    """
    Computes the cost over all examples
    Args:
      X : (ndarray Shape (m,n)) data, m examples by n features
      y : (array_like Shape (m,)) target value
      w : (array_like Shape (n,)) Values of parameters of the model
      b : scalar Values of bias parameter of the model
      lambda_: unused placeholder
    Returns:
      total_cost: (scalar)         cost
    """

    m = len(y)  # número de ejemplos de entrenamiento

    z = np.dot(X, w) + b
    g = sigmoid(z)

    # Calcular la función de costo
    total_cost = (-1/m) * np.sum(y * np.log(g) + (1 - y) * np.log(1 - g))

    return total_cost


def compute_gradient(X, y, w, b, lambda_=None):
    """
    Computes the gradient for logistic regression
    Args:
      X : (ndarray Shape (m,n)) variable such as house size
      y : (array_like Shape (m,1)) actual value
      w : (array_like Shape (n,1)) values of parameters of the model
      b : (scalar)                 value of parameter of the model
      lambda_: unused placeholder
    Returns
      dj_db: (scalar)                The gradient of the cost w.r.t. the parameter b.
      dj_dw: (array_like Shape (n,1)) The gradient of the cost w.r.t. the parameters w.
    """
    
    m = len(y)
    z = np.dot(X, w) + b
    g = sigmoid(z)

    dj_dw = np.dot((g - y), X) / m
    dj_db = np.sum(g - y) / m

    return dj_db, dj_dw


#########################################################################
# regularized logistic regression
#
def compute_cost_reg(X, y, w, b, lambda_=1):
    """
    Computes the cost over all examples
    Args:
      X : (array_like Shape (m,n)) data, m examples by n features
      y : (array_like Shape (m,)) target value 
      w : (array_like Shape (n,)) Values of parameters of the model      
      b : (array_like Shape (n,)) Values of bias parameter of the model
      lambda_ : (scalar, float)    Controls amount of regularization
    Returns:
      total_cost: (scalar)         cost 
    """
    m = len(y)  # número de ejemplos de entrenamiento

    z = np.dot(X, w) + b
    g = sigmoid(z)

    # Calcular la función de costo
    cost = (-1/m) * np.sum(y * np.log(g) + (1 - y) * np.log(1 - g))
    total_cost = cost + (lambda_/(2*m) * np.sum(w**2))
    
    return total_cost


def compute_gradient_reg(X, y, w, b, lambda_=1):
    """
    Computes the gradient for linear regression 

    Args:
      X : (ndarray Shape (m,n))   variable such as house size 
      y : (ndarray Shape (m,))    actual value 
      w : (ndarray Shape (n,))    values of parameters of the model      
      b : (scalar)                value of parameter of the model  
      lambda_ : (scalar,float)    regularization constant
    Returns
      dj_db: (scalar)             The gradient of the cost w.r.t. the parameter b. 
      dj_dw: (ndarray Shape (n,)) The gradient of the cost w.r.t. the parameters w. 
    """
  
    m = len(y)
    z = np.dot(X, w) + b
    g = sigmoid(z)

    dj_dw = (np.dot((g - y), X) / m) + np.dot((lambda_/m), w)
    dj_db = np.sum(g - y) / m

    return dj_db, dj_dw


#########################################################################
# gradient descent
#
def gradient_descent(X, y, w_in, b_in, cost_function, gradient_function, alpha, num_iters, lambda_=None):

    w = np.copy(w_in)  # Inicializa los parámetros del modelo
    b = b_in
    J_history = np.zeros(num_iters)  # Almacena el costo en cada iteración

    for iter in range(num_iters):

      dj_db, dj_dw = gradient_function(X, y, w, b, lambda_)

      # Actualiza los parámetros usando el descenso de gradiente
      w = w - alpha * dj_dw
      b = b - alpha * dj_db

      J = cost_function(X, y, w, b, lambda_)

      J_history[iter] = J
    
    plt.plot(J_history, label='Coste')
    plt.xlabel('Tiempo')
    plt.ylabel('Coste')
    plt.title('Evolución del coste en el tiempo')
    plt.legend()
    plt.show()
    
    return w, b, J_history


#########################################################################
# predict
#
def predict(X, w, b):

    z = np.dot(X, w) + b
    p = sigmoid(z)
    p = p > 0.5
    return p

def load_data():
    data = np.loadtxt("C:/Users/jorge/source/repos/AABD/P3/data/ex2data1.txt", delimiter=',')
    X = data[:, :2]
    y = data[:, 2].astype(int)
    return X, y

def main():
  #sigmoid_test(sigmoid)
  #compute_cost_test(compute_cost)
  #compute_gradient_test(compute_gradient)
  #compute_cost_reg_test(compute_cost_reg)
  #compute_gradient_reg_test(compute_gradient_reg)
  #predict_test(predict)

  
  x, y = load_data()
  #x2 = map_feature(x[:,0], x[:,1])
  w = np.zeros(len(x.T))
  b = -8
  w2, b2, j = gradient_descent (x, y, w, b, compute_cost, compute_gradient, 0.001, 10000)

  plot_decision_boundary(w2, b2, x, y)


  p = predict(x, w2, b2)
  p = np.sum(p)
  y = np.sum(y)
  dif = np.abs(y - p)
  dif = y - dif
  porcentaje = dif * 100 / y


  print(f'w: {w2}, b: {b2}, p: {porcentaje}')




if __name__ == "__main__":
    main()