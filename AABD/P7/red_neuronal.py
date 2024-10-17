import numpy as np
import scipy.io
from sklearn.model_selection import train_test_split


def sigmoidGradient(z):
    return sigmoid(z) * (1 - sigmoid(z))

def initialize_weights(input_size, hidden_size1, hidden_size2, hidden_size3, output_size):
    Einit = 0.12
    theta1 = np.random.uniform(-Einit, Einit, (hidden_size1, input_size + 1))
    theta2 = np.random.uniform(-Einit, Einit, (hidden_size2, hidden_size1 + 1))
    theta3 = np.random.uniform(-Einit, Einit, (hidden_size3, hidden_size2 + 1))
    theta4 = np.random.uniform(-Einit, Einit, (output_size, hidden_size3 + 1))
    return theta1, theta2, theta3, theta4

def forward_propagation(X, theta1, theta2, theta3, theta4):
    m = X.shape[0]
    a1 = np.hstack([np.ones((m, 1)), X])
    
    z2 = np.dot(a1, theta1.T)
    a2 = sigmoid(z2)
    a2 = np.hstack([np.ones((m, 1)), a2])
    
    z3 = np.dot(a2, theta2.T)
    a3 = sigmoid(z3)
    a3 = np.hstack([np.ones((m, 1)), a3])
    
    z4 = np.dot(a3, theta3.T)
    a4 = sigmoid(z4)
    a4 = np.hstack([np.ones((m, 1)), a4])
    
    z5 = np.dot(a4, theta4.T)
    h = sigmoid(z5)
    
    return a1, z2, a2, z3, a3, z4, a4, z5, h

def cost_function(theta1, theta2, theta3, theta4, X, y, lambda_):
    m = len(X)
    J = 0
    
    a1, z2, a2, z3, a3, z4, a4, z5, h = forward_propagation(X, theta1, theta2, theta3, theta4)
    
    y_onehot = np.eye(np.max(y) + 1)[y]  # one-hot encoding
    
    J = np.sum(-y_onehot * np.log(h) - (1 - y_onehot) * np.log(1 - h))
    J /= m
    
    reg_term = (lambda_ / (2 * m)) * (np.sum(np.square(theta1[:, 1:])) + np.sum(np.square(theta2[:, 1:])) + np.sum(np.square(theta3[:, 1:])) + np.sum(np.square(theta4[:, 1:])))
    J += reg_term
    
    return J

def backpropagation(theta1, theta2, theta3, theta4, X, y, lambda_):
    m = len(X)
    Delta1 = np.zeros_like(theta1)
    Delta2 = np.zeros_like(theta2)
    Delta3 = np.zeros_like(theta3)
    Delta4 = np.zeros_like(theta4)
    
    a1, z2, a2, z3, a3, z4, a4, z5, h = forward_propagation(X, theta1, theta2, theta3, theta4)
    
    y_onehot = np.eye(np.max(y) + 1)[y]  # one-hot encoding
    
    delta5 = h - y_onehot
    delta4 = np.dot(delta5, theta4[:, 1:]) * sigmoidGradient(z4)
    delta3 = np.dot(delta4, theta3[:, 1:]) * sigmoidGradient(z3)
    delta2 = np.dot(delta3, theta2[:, 1:]) * sigmoidGradient(z2)
    
    Delta4 += np.dot(delta5.T, a4)
    Delta3 += np.dot(delta4.T, a3)
    Delta2 += np.dot(delta3.T, a2)
    Delta1 += np.dot(delta2.T, a1)
    
    grad1 = Delta1 / m
    grad2 = Delta2 / m
    grad3 = Delta3 / m
    grad4 = Delta4 / m
    
    grad1[:, 1:] += (lambda_ / m) * theta1[:, 1:]
    grad2[:, 1:] += (lambda_ / m) * theta2[:, 1:]
    grad3[:, 1:] += (lambda_ / m) * theta3[:, 1:]
    grad4[:, 1:] += (lambda_ / m) * theta4[:, 1:]
    
    return grad1, grad2, grad3, grad4

def gradient_descent(X, y, theta1, theta2, theta3, theta4, alpha, num_iters, lambda_=0):
    m = len(X)
    J_history = []
    
    for iter in range(num_iters):
        grad1, grad2, grad3, grad4 = backpropagation(theta1, theta2, theta3, theta4, X, y, lambda_)
        
        theta1 -= alpha * grad1
        theta2 -= alpha * grad2
        theta3 -= alpha * grad3
        theta4 -= alpha * grad4
        
        J = cost_function(theta1, theta2, theta3, theta4, X, y, lambda_)
        J_history.append(J)
    
    return theta1, theta2, theta3, theta4, J_history

def predict(theta1, theta2, theta3, theta4, X):
    _, _, _, _, _, _, _, _, h = forward_propagation(X, theta1, theta2, theta3, theta4)
    return np.argmax(h, axis=1)

def red_neuronal(X_train, y_train, X_val, y_val, X_test, y_test, hidden_size1=25, hidden_size2=10, hidden_size3=10, alpha=0.1, num_iters=1000, lambda_=1):
    input_size = X_train.shape[1]
    output_size = len(np.unique(y_train))
    
    theta1, theta2, theta3, theta4 = initialize_weights(input_size, hidden_size1, hidden_size2, hidden_size3, output_size)
    
    theta1_opt, theta2_opt, theta3_opt, theta4_opt, J_history = gradient_descent(X_train, y_train, theta1, theta2, theta3, theta4, alpha, num_iters, lambda_)
    
    predictions_train = predict(theta1_opt, theta2_opt, theta3_opt, theta4_opt, X_train)
    accuracy_train = np.mean(predictions_train == y_train) * 100
    print(f'Precisión en el conjunto de entrenamiento: {accuracy_train:.2f}%')
    
    predictions_val = predict(theta1_opt, theta2_opt, theta3_opt, theta4_opt, X_val)
    accuracy_val = np.mean(predictions_val == y_val) * 100
    print(f'Precisión en el conjunto de validación: {accuracy_val:.2f}%')
    
    predictions_test = predict(theta1_opt, theta2_opt, theta3_opt, theta4_opt, X_test)
    accuracy_test = np.mean(predictions_test == y_test) * 100
    print(f'Precisión en el conjunto de prueba: {accuracy_test:.2f}%')

def main():
    spam_features, hard_ham_features, easy_ham_features = load_and_process_data()

    # Concatena todos los vectores de atributos y etiquetas de clase
    X = np.concatenate([spam_features, hard_ham_features, easy_ham_features])
    y = np.concatenate([np.ones(len(spam_features)), np.zeros(len(hard_ham_features) + len(easy_ham_features))])

    # División de los datos en conjuntos de entrenamiento y prueba
    X_train, X_test1, y_train, y_test1 = train_test_split(X, y, test_size=0.4)
    X_val, X_test, y_val, y_test = train_test_split(X_test1, y_test1, test_size=0.5)

    red_neuronal(X_train, y_train, X_val, y_val, X_test, y_test)

if __name__ == "__main__":
    main()
