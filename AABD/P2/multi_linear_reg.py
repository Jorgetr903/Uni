import numpy as np
import copy
import math
import matplotlib.pyplot as plt
from public_tests import*

def zscore_normalize_features(X):
    """
    computes  X, zcore normalized by column

    Args:
      X (ndarray (m,n))     : input data, m examples, n features

    Returns:
      X_norm (ndarray (m,n)): input normalized by column
      mu (ndarray (n,))     : mean of each feature
      sigma (ndarray (n,))  : standard deviation of each feature
    """

    mu = np.mean(X, axis=0)  # Calcula la media por columna
    sigma = np.std(X, axis=0)  # Calcula la desviación estándar por columna

    X_norm = (X - mu) / sigma  # Normaliza los datos utilizando z-score

    return (X_norm, mu, sigma)


def compute_cost(X, y, w, b):
    """
    compute cost
    Args:
      X (ndarray (m,n)): Data, m examples with n features
      y (ndarray (m,)) : target values
      w (ndarray (n,)) : model parameters  
      b (scalar)       : model parameter
    Returns
      cost (scalar)    : cost
    """

    cost = np.dot(X, w) + b
    cost = np.sum((cost - y) ** 2) / (2 * len(y))

    return cost


def compute_gradient(X, y, w, b):
    """
    Computes the gradient for linear regression 
    Args:
      X : (ndarray Shape (m,n)) matrix of examples 
      y : (ndarray Shape (m,))  target value of each example
      w : (ndarray Shape (n,))  parameters of the model      
      b : (scalar)              parameter of the model      
    Returns
      dj_dw : (ndarray Shape (n,)) The gradient of the cost w.r.t. the parameters w. 
      dj_db : (scalar)             The gradient of the cost w.r.t. the parameter b. 
    """
    
    predictions = np.dot(X, w) + b

    dj_dw = np.dot(X.T, (predictions - y)) / len(y)
    dj_db = np.sum(predictions - y) / len(y)

    return dj_db, dj_dw


def gradient_descent(X, y, w_in, b_in, cost_function, gradient_function, alpha, num_iters):
    """
    Performs batch gradient descent to learn theta. Updates theta by taking 
    num_iters gradient steps with learning rate alpha

    Args:
      X : (array_like Shape (m,n)    matrix of examples 
      y : (array_like Shape (m,))    target value of each example
      w_in : (array_like Shape (n,)) Initial values of parameters of the model
      b_in : (scalar)                Initial value of parameter of the model
      cost_function: function to compute cost
      gradient_function: function to compute the gradient
      alpha : (float) Learning rate
      num_iters : (int) number of iterations to run gradient descent
    Returns
      w : (array_like Shape (n,)) Updated values of parameters of the model
          after running gradient descent
      b : (scalar)                Updated value of parameter of the model 
          after running gradient descent
      J_history : (ndarray): Shape (num_iters,) J at each iteration,
          primarily for graphing later
    """

    w = np.copy(w_in)  # Inicializa los parámetros del modelo
    b = b_in
    m = len(X)  # Número de ejemplos
    J_history = np.zeros(num_iters)  # Almacena el costo en cada iteración

    for iter in range(num_iters):

      dj_db, dj_dw = gradient_function(X, y, w, b)

      # Actualiza los parámetros usando el descenso de gradiente
      w -= np.dot(alpha, dj_dw)
      b -= np.dot(alpha, dj_db)

      J = cost_function(X, y, w, b)

      J_history[iter] = J
    
    plt.plot(J_history, label='Coste')
    plt.xlabel('Tiempo')
    plt.ylabel('Coste')
    plt.title('Evolución del coste en el tiempo')
    plt.legend()
    plt.show()

    return w, b, J_history

def visualize_data(x_predicted):
  data=np.loadtxt("C:/Users/jorge/source/repos/AABD/P2/data/houses.txt",delimiter=',')
  X_train=data[:,:4]
  y_train=data[:,4]

  X_features=['size(sqft)','bedrooms','floors','age']
  fig,ax=plt.subplots(1,4,figsize=(25,5),sharey=True)
  for i in range(len(ax)):
    ax[i].scatter(X_train[:,i],y_train)
    ax[i].scatter(X_train[:,i], x_predicted, color='orange')
    ax[i].set_xlabel(X_features[i])
  ax[0].set_ylabel("Price(1000's)")

  plt.show()

def load_data_multi():
    data = np.loadtxt("C:/Users/jorge/source/repos/AABD/P2/data/houses.txt", delimiter=',')
    X = data[:,:4]
    y = data[:,4]
    return X, y

def predict(w, b, X):
    return np.dot(X, w) + b

def main():

  x, y = load_data_multi()
  w = np.zeros(len(x.T))
  b = 0
  X_norm, mu, sigma = zscore_normalize_features(x)
  w2, b2, J_history = gradient_descent(X_norm, y, w, b, compute_cost, compute_gradient, 0.1, 1000)

  print(f'w: {w2}, b: {b2}')

  x_predicted = predict(w2, b2, X_norm)
  
  visualize_data(x_predicted)

  predit = np.array([1200, 3, 1, 40])
  predict_norm = (predit - mu) / sigma
  profit_1 = predict(w2, b2, predict_norm)

  print(profit_1)


if __name__ == "__main__":
    main()