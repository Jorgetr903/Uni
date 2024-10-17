import numpy as np
import scipy.io
from utils import*
import matplotlib.pyplot as plt

def sigmoid(z):
    g = 1 / (1 + np.exp(-z))

    return g

#########################################################################
# regularized logistic regression
#
def compute_cost_reg(X, y, w, b, lambda_=1):

    m = len(y)  # número de ejemplos de entrenamiento

    z = np.dot(X, w) + b
    g = sigmoid(z)

    # Calcular la función de costo
    cost = (-1/m) * np.sum(y * np.log(g) + (1 - y) * np.log(1 - g))
    total_cost = cost + (lambda_/(2*m) * np.sum(w**2))
    
    return total_cost


def compute_gradient_reg(X, y, w, b, lambda_=1):

    m = len(y)
    z = np.dot(X, w) + b
    g = sigmoid(z)

    dj_dw = (np.dot((g - y), X) / m) + np.dot((lambda_/m), w)
    dj_db = np.sum(g - y) / m

    return dj_db, dj_dw

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
    """
    plt.plot(J_history, label='Coste')
    plt.xlabel('Tiempo')
    plt.ylabel('Coste')
    plt.title('Evolución del coste en el tiempo')
    plt.legend()
    plt.show()
    """
    return w, b

#########################################################################
# one-vs-all
#
def oneVsAll(X, y, n_labels, lambda_):
    """
     Trains n_labels logistic regression classifiers and returns
     each of these classifiers in a matrix all_theta, where the i-th
     row of all_theta corresponds to the classifier for label i.

     Parameters
     ----------
     X : array_like
         The input dataset of shape (m x n). m is the number of
         data points, and n is the number of features. 

     y : array_like
         The data labels. A vector of shape (m, ).

     n_labels : int
         Number of possible labels.

     lambda_ : float
         The logistic regularization parameter.

     Returns
     -------
     all_theta : array_like
         The trained parameters for logistic regression for each class.
         This is a matrix of shape (K x n+1) where K is number of classes
         (ie. `n_labels`) and n is number of features without the bias.
     """
    m, n = X.shape
    all_theta = np.zeros((n_labels, n + 1))

    for i in range (n_labels):
        y_aux = (y == i).astype(int)
        w_train, b_train = gradient_descent(X, y_aux, np.zeros(len(X[i])), 0, compute_cost_reg, compute_gradient_reg, 0.01, 20000, lambda_)
        all_theta[i, 0] = b_train
        all_theta[i, 1:] = w_train

    return all_theta


def predictOneVsAll(all_theta, X):
    """
    Return a vector of predictions for each example in the matrix X. 
    Note that X contains the examples in rows. all_theta is a matrix where
    the i-th row is a trained logistic regression theta vector for the 
    i-th class. You should set p to a vector of values from 0..K-1 
    (e.g., p = [0, 2, 0, 1] predicts classes 0, 2, 0, 1 for 4 examples) .

    Parameters
    ----------
    all_theta : array_like
        The trained parameters for logistic regression for each class.
        This is a matrix of shape (K x n+1) where K is number of classes
        and n is number of features without the bias.  

    X : array_like
        Data points to predict their labels. This is a matrix of shape 
        (m x n) where m is number of data points to predict, and n is number 
        of features without the bias term. Note we add the bias term for X in 
        this function. 

    Returns
    -------
    p : array_like
        The predictions for each data point in X. This is a vector of shape (m, ).
    """

    result = []
    p = []
    numejemplos = X.shape[0]
    for i in range(numejemplos):
        result = np.dot(all_theta[:,1:], X[i,:])
        result += all_theta[:,0]
        posmax = np.argmax(result)
        p.append(posmax)

    return p


#########################################################################
# NN
#
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

    data = scipy.io.loadmat("C:/Users/jorge/source/repos/AABD/P4/data/ex3data1.mat", squeeze_me = True)
    x = data['X']
    y = data['y']

    all_theta = oneVsAll(x, y, 10, 0.01)
    p = predictOneVsAll(all_theta, x)

    accuracy = np.mean(p == y) * 100
    print(f'Precisión: {accuracy:.2f}')

    weights = scipy.io.loadmat("C:/Users/jorge/source/repos/AABD/P4/data/ex3weights.mat")
    theta1, theta2 = weights['Theta1'], weights['Theta2']
    p2 = predict(theta1, theta2, x)

    accuracy2 = np.mean(p2 == y) * 100
    print(f'Precisión: {accuracy2:.2f}')

    displayData(x)

if __name__ == "__main__":
    main()