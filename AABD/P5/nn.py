import numpy as np
import scipy.io
from utils import*

def sigmoid(z):
    g = 1 / (1 + np.exp(-z))

    return g

def sigmoidGradient(z):
    g = sigmoid(z) * (1 - sigmoid(z))

    return g

def cost(theta1, theta2, X, y, lambda_):
    """
    Compute cost for 2-layer neural network. 

    Parameters
    ----------
    theta1 : array_like
        Weights for the first layer in the neural network.
        It has shape (2nd hidden layer size x input size + 1)

    theta2: array_like
        Weights for the second layer in the neural network. 
        It has shape (output layer size x 2nd hidden layer size + 1)

    X : array_like
        The inputs having shape (number of examples x number of dimensions).

    y : array_like
        1-hot encoding of labels for the input, having shape 
        (number of examples x number of labels).

    lambda_ : float
        The regularization parameter. 

    Returns
    -------
    J : float
        The computed value for the cost function. 

    """
    J = 0
    m = X.shape[0]

    for i in range(m):

        a1 = X[i, :]
        a1 = np.insert(a1, 0, 1) # add bias unit
        z2 = np.dot(theta1, a1)
        a2 = np.insert(sigmoid(z2), 0, 1) #add bias unit
        z3 = np.dot(theta2, a2)
        h= sigmoid(z3)

        # One-hot encoding
        y_onehot = np.zeros((10,))
        y_onehot[y[i]] = 1

        aux_J = np.sum(y_onehot * np.log(h) + (1 - y_onehot) * np.log(1 - h))
        J += aux_J

    # Regularización
    reg_term = (lambda_ / (2 * m)) * (np.sum(np.square(theta1[:,1:])) + np.sum(np.square(theta2[:,1:])))

    J = -J/m + reg_term

    return J



def backprop(theta1, theta2, X, y, lambda_):
    """
    Compute cost and gradient for 2-layer neural network. 

    Parameters
    ----------
    theta1 : array_like
        Weights for the first layer in the neural network.
        It has shape (2nd hidden layer size x input size + 1)

    theta2: array_like
        Weights for the second layer in the neural network. 
        It has shape (output layer size x 2nd hidden layer size + 1)

    X : array_like
        The inputs having shape (number of examples x number of dimensions).

    y : array_like
        1-hot encoding of labels for the input, having shape 
        (number of examples x number of labels).

    lambda_ : float
        The regularization parameter. 

    Returns
    -------
    J : float
        The computed value for the cost function. 

    grad1 : array_like
        Gradient of the cost function with respect to weights
        for the first layer in the neural network, theta1.
        It has shape (2nd hidden layer size x input size + 1)

    grad2 : array_like
        Gradient of the cost function with respect to weights
        for the second layer in the neural network, theta2.
        It has shape (output layer size x 2nd hidden layer size + 1)

    """
    
    m = len(X)
    Delta1 = np.zeros_like(theta1)
    Delta2 = np.zeros_like(theta2)
    J = 0
    
    for i in range(m):
        #propagacion hacia delante
        a1 = X[i, :]
        a1 = np.insert(a1, 0, 1)
        z2 = np.dot(theta1, a1)
        a2 = sigmoid(z2)
        a2 = np.insert(a2, 0, 1)
        z3 = np.dot(theta2, a2)
        a3 = sigmoid(z3)
        
        y_onehot = np.zeros_like(a3)
        y_onehot[y[i]] = 1
        
        #calcular coste
        epsilon = 1e-10 #Para evitar logaritmos de 0
        aux_J = np.sum(y_onehot * np.log(a3) + (1 - y_onehot) * np.log(1 - a3 + epsilon))
        J += aux_J
        
        # Retropropagación
        delta3 = a3 - y_onehot
        delta2 = np.dot(theta2.T, delta3) * (a2 * (1- (a2)))
        delta2 = delta2[1:]

        Delta2 += np.outer(delta3, a2)
        Delta1 += np.outer(delta2, a1)


    reg_term1 = (lambda_ / m) * theta1
    reg_term1[:, 0] = 0  # No regularizar el sesgo
    reg_term2 = (lambda_ / m) * theta2
    reg_term2[:, 0] = 0  # No regularizar el sesgo
    Delta1 += reg_term1
    Delta2 += reg_term2
    
    # Calcular gradientes
    grad1 = Delta1 / m
    grad2 = Delta2 / m
    
    # Regularización del coste
    reg_term = (lambda_ / (2 * m)) * (np.sum(np.square(theta1[:,1:])) + np.sum(np.square(theta2[:,1:])))
    J = -J/m + reg_term
    
    return J, grad1, grad2

def gradient_descent(X, y, w_in, b_in, cost_function, gradient_function, alpha, num_iters, lambda_=None):

    w = np.copy(w_in)  # Inicializa los parámetros del modelo
    b = b_in
    J_history = np.zeros(num_iters)  # Almacena el costo en cada iteración

    for iter in range(num_iters):
        J2, dj_dw, dj_db = gradient_function(w, b, X, y, lambda_)

        # Actualiza los parámetros usando el descenso de gradiente
        w = w - alpha * dj_dw
        b = b - alpha * dj_db

        J = cost_function(w, b, X, y, lambda_)

        J_history[iter] = J
    """
    plt.plot(J_history, label='Coste')
    plt.xlabel('Tiempo')
    plt.ylabel('Coste')
    plt.title('Evolución del coste en el tiempo')
    plt.legend()
    plt.show()
    """
    return w, b

def predict(theta1, theta2, X):
    """
    Predict the label of an input given a trained neural network.

    Parameters
    ----------
    theta1 : array_like
        Weights for the first layer in the neural network.
        It has shape (2nd hidden layer size x input size)

    theta2: array_like
        Weights for the second layer in the neural network. 
        It has shape (output layer size x 2nd hidden layer size)

    X : array_like
        The image inputs having shape (number of examples x image dimensions).

    Return 
    ------
    p : array_like
        Predictions vector containing the predicted label for each example.
        It has a length equal to the number of examples.
    """

    m = X.shape[0]
    X1s = np.hstack([np.ones((m, 1)), X])

    z2 = np.dot(X1s, theta1.T)
    a2 = sigmoid(z2)

    a2 = np.column_stack((np.ones(a2.shape[0]), a2))

    z3 = np.dot(a2, theta2.T)
    a3 = sigmoid(z3)

    p = np.argmax(a3, axis=1)

    return p

def main():

    data = scipy.io.loadmat("C:/Users/jorge/source/repos/AABD/P5/data/ex3data1.mat", squeeze_me = True)
    x = data['X']
    y = data['y']

    m = x.shape[0]
    Einit = 0.12
    num_iters = 200
    lambda_ = 1
    alpha = 1

    weights = scipy.io.loadmat("C:/Users/jorge/source/repos/AABD/P4/data/ex3weights.mat")
    theta1, theta2 = weights['Theta1'], weights['Theta2']

    c = cost(theta1, theta2, x, y, 1)
    print(f'Coste: {c}')

    J, grad1, grad2 = backprop(theta1, theta2, x, y, 0)
    print(f'J: {J}')

    theta1_shape = np.shape(theta1)
    theta2_shape = np.shape(theta2)
    theta1 = np.random.uniform(-Einit, Einit, theta1_shape)
    theta2 = np.random.uniform(-Einit, Einit, theta2_shape)
    
    t1, t2 = gradient_descent(x, y, theta1, theta2, cost, backprop, alpha, num_iters, lambda_)

    p2 = predict(t1, t2, x)
    accuracy2 = np.mean(p2 == y) * 100
    print(f'Precisión: {accuracy2:.2f}')
    
if __name__ == "__main__":
    main()