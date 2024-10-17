import numpy as np
import matplotlib.pyplot as plt
import pickle
import os
import torch
import torch.nn as nn
import torch.optim as optim
import seaborn as sns
from sklearn import svm
from utils import*
from sklearn.model_selection import train_test_split
from sklearn.metrics import classification_report, confusion_matrix
from scipy.io import loadmat  # Para cargar archivos .mat


#----------------------
# Regresión Logística
#----------------------

def sigmoid(z):
    g = 1 / (1 + np.exp(-z))

    return g

def compute_cost(X, y, w, b, lambda_=None):
    m = len(y)  # número de ejemplos de entrenamiento

    z = np.dot(X, w) + b
    g = sigmoid(z)

    # Calcular la función de costo
    total_cost = (-1/m) * np.sum(y * np.log(g) + (1 - y) * np.log(1 - g))

    return total_cost


def compute_gradient(X, y, w, b, lambda_=None):
    m = len(y)
    z = np.dot(X, w) + b
    g = sigmoid(z)

    dj_dw = np.dot((g - y), X) / m
    dj_db = np.sum(g - y) / m

    return dj_db, dj_dw

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
    
    plt.plot(J_history, label='Coste')
    plt.xlabel('Tiempo')
    plt.ylabel('Coste')
    plt.title('Evolución del coste en el tiempo')
    plt.legend()
    plt.savefig("Regresión Logística.jpg")

    
    return w, b, J_history

def predict(X, w, b):
    z = np.dot(X, w) + b
    p = sigmoid(z)
    p = p > 0.5
    return p

def regresion_logistica(X_train, y_train, X_val, y_val, X_test, y_test, lambda_, iteraciones):

    w = np.zeros(len(X_train.T))
    b = -8
    w_opt, b_opt, J_history = gradient_descent(X_train, y_train, w, b, compute_cost, compute_gradient, lambda_, iteraciones)

    p_train = predict(X_train, w_opt, b_opt)
    correct_train = (p_train == y_train).sum()
    accuracy_train = correct_train / len(y_train) * 100

    # Precisión en los datos de validación
    p_val = predict(X_val, w_opt, b_opt)
    correct_val = (p_val == y_val).sum()
    accuracy_val = correct_val / len(y_val) * 100

    # Precisión en los datos de prueba
    p_test = predict(X_test, w_opt, b_opt)
    correct_test = (p_test == y_test).sum()
    accuracy_test = correct_test / len(y_test) * 100

    print(f'porcentaje de precisión de entrenamiento: {accuracy_train}')
    print(f'porcentaje de precisión de validación: {accuracy_val}')
    print(f'porcentaje de precisión de test: {accuracy_test}')

    plot_confusion_matrix(y_test, p_test, path="logistic_regression_confusion.png", type='test')

'''
    porcentaje de precisión de entrenamiento: 91.46464646464646
    porcentaje de precisión de validación: 91.51515151515152
    porcentaje de precisión de test: 90.46898638426626
'''


#---------------------------
# SVM
#---------------------------

def SVM(X_train, y_train, X_val, y_val, X_test, y_test):

    # Definir los valores de C y sigma a probar
    C_values = [0.01, 0.03, 0.1, 0.3, 1, 3, 10, 30]
    sigma_values = [0.01, 0.03, 0.1, 0.3, 1, 3, 10, 30]

    # Inicializar variables para el mejor modelo
    best_score = 0
    best_params = {'C': 10, 'sigma': 10}

    # Inicializar matrices de coste y error
    cost_matrix = np.zeros((len(C_values), len(sigma_values)))
    error_matrix = np.zeros((len(C_values), len(sigma_values)))

    # Iterar sobre todos los valores de C y sigma
    '''
    for C in C_values:
        for sigma in sigma_values:
            # Crear una instancia de SVC con kernel RBF y los parámetros C y sigma
            svm1 = svm.SVC(kernel='rbf', C=C, gamma=1 / (2 * sigma**2))
            # Entrenar el clasificador SVM
            svm1.fit(X_train, y_train)
            # Evaluar el modelo en el conjunto de validación
            score = svm1.score(X_val, y_val)
            # Actualizar el mejor modelo si es necesario
            if score > best_score:
                best_score = score
                best_params['C'] = C
                best_params['sigma'] = sigma
    '''    

    # Iterar sobre todos los valores de C y sigma
    for i, C in enumerate(C_values):
        for j, sigma in enumerate(sigma_values):
            # Crear una instancia de SVC con kernel RBF y los parámetros C y sigma
            svm1 = svm.SVC(kernel='rbf', C=C, gamma=1 / (2 * sigma**2))
            # Entrenar el clasificador SVM
            svm1.fit(X_train, y_train)
            # Evaluar el modelo en el conjunto de validación
            score = svm1.score(X_val, y_val)
            # Calcular el coste como el error
            error = 1 - score
            
            # Guardar el error en las matrices correspondientes
            cost_matrix[i, j] = score
            error_matrix[i, j] = error
            
            # Actualizar el mejor modelo si es necesario
            if score > best_score:
                best_score = score
                best_params['C'] = C
                best_params['sigma'] = sigma

    svm_classifier = svm.SVC(kernel='rbf', C=best_params['C'], gamma=1 / (2 * best_params['sigma']**2))
    svm_classifier.fit(X_train, y_train)

    # Evaluación del modelo
    train_accuracy = svm_classifier.score(X_train, y_train)
    val_accuracy = svm_classifier.score(X_val, y_val)
    test_accuracy = svm_classifier.score(X_test, y_test)


    print("Accuracy en entrenamiento:", train_accuracy)
    print("Accuracy en validación:", val_accuracy)
    print("Accuracy en test:", test_accuracy)
    print("best_params: ", best_params)

    y_test_pred = svm_classifier.predict(X_test)
    plot_confusion_matrix(y_test, y_test_pred, path="svm_confusion.png", type='test')

    # Graficar la matriz de coste
    plt.figure(figsize=(10, 8))
    plt.imshow(cost_matrix, interpolation='nearest', cmap='viridis')
    plt.title('Matriz de coste')
    plt.xlabel('Valores de sigma')
    plt.ylabel('Valores de C')
    plt.colorbar()
    plt.xticks(np.arange(len(sigma_values)), sigma_values)
    plt.yticks(np.arange(len(C_values)), C_values)
    plt.savefig("SVM.png")

    # Graficar la matriz de error
    plt.figure(figsize=(10, 8))
    plt.imshow(error_matrix, interpolation='nearest', cmap='viridis')
    plt.title('Matriz de error')
    plt.xlabel('Valores de sigma')
    plt.ylabel('Valores de C')
    plt.colorbar()
    plt.xticks(np.arange(len(sigma_values)), sigma_values)
    plt.yticks(np.arange(len(C_values)), C_values)
    plt.savefig("SVM_error_matrix.png")

#--------------------------
# Redes Neuronales Pytorch
#-------------------------


# Define la función para el modelo complejo
def complex_reg(X_train, y_train, X_val, y_val, X_test, y_test, num_epochs, learning_rate):

    #X_train_norm = (X_train - np.mean(X_train)) / np.std(X_train)
    X_train_norm = torch.from_numpy(X_train).float()   # Crear tensor con la X
    y_train = torch.from_numpy(y_train)

    #Creamos el data set con la X y la Y
    train_ds = torch.utils.data.TensorDataset(X_train_norm, y_train)

    torch.manual_seed(1)
    batch_size = 32

    #Creamos el data louder
    train_dl = torch.utils.data.DataLoader(train_ds, batch_size, shuffle=True)

    # Define la arquitectura del modelo
    model = nn.Sequential(
        nn.Linear(len(X_train[0]), 100),
        nn.ReLU(),
        nn.Linear(100, 50),
        nn.ReLU(),
        nn.Linear(50, 25),
        nn.ReLU(),
        nn.Linear(25, 1),
        nn.Sigmoid()  # Función de activación sigmoide para la clasificación binaria
    )


    # Entrena el modelo
    loss_hist = []
    accuracy_hist = []
    loss_fn = nn.MSELoss()
    optimizer = optim.Adam(model.parameters(), lr=learning_rate, weight_decay=0.01) #usamos regularización lambda = 0.01


    for epoch in range(num_epochs):
        for x_batch, y_batch in train_dl:
            # Forward pass
            pred = model(x_batch)
            loss = loss_fn(pred.squeeze(), y_batch.float())
            
            # Backpropagation
            loss.backward()
            optimizer.step()
            optimizer.zero_grad()
            
            # Compute accuracy
            loss_hist.append(loss.item())
            is_correct = ((pred > 0.4).float() == y_batch).float()
            accuracy_hist.append(is_correct.mean())

        if epoch % (num_epochs // 10) == 0:
            print(f"Epoch {epoch} Loss {loss_hist[-1]:.4f}")

    
    # Validación del modelo
    with torch.no_grad():
        val_pred = model(torch.from_numpy(X_val).float())
        val_pred_integer = (val_pred > 0.4).float()
        val_pred_bueno = val_pred_integer.type(torch.int)

        test_pred = model(torch.from_numpy(X_test).float())
        test_pred_integer = (test_pred > 0.4).float()
        test_pred_bueno = test_pred_integer.type(torch.int)

        correct = (val_pred_bueno.numpy().flatten() == y_val)
        accuracy = correct.mean()

        correct_test = (test_pred_bueno.numpy().flatten() == y_test)
        accuracy_test = correct_test.mean()

        print(f'Accuracy on validation set: {accuracy * 100:.2f}%')
        print(f'Accuracy en test: {accuracy_test * 100:.2f}%')

    # Graficar la evolución del coste
    plt.figure(figsize=(10, 5))
    plt.plot(loss_hist, label='Loss')
    plt.xlabel('Iteration')
    plt.ylabel('Loss')
    plt.title('Evolución del coste en el tiempo')
    plt.legend()
    plt.savefig("Pytorch.jpg")

    plot_confusion_matrix(y_test, test_pred_bueno.numpy().flatten(), path="pytorch_confusion.png", type='test')


#--------------------------
# Redes Neuronales Prac 5
#-------------------------


def sigmoidGradient(z):
    return sigmoid(z) * (1 - sigmoid(z))

def one_hot_encoding(y, num_classes):
    m = len(y)
    m = int(m)
    num_classes = int(num_classes)
    y_onehot = np.zeros((m, num_classes))
    y = y.astype(int)
    y_onehot[np.arange(m), y] = 1
    return y_onehot

def initialize_weights(input_size, hidden_size1, hidden_size2, output_size):
    Einit = 0.12
    theta1 = np.random.uniform(-Einit, Einit, (hidden_size1, input_size + 1))
    theta2 = np.random.uniform(-Einit, Einit, (hidden_size2, hidden_size1 + 1))
    theta3 = np.random.uniform(-Einit, Einit, (output_size, hidden_size2 + 1))
    return theta1, theta2, theta3

def forward_propagation(X, theta1, theta2, theta3):
    m = X.shape[0]
    a1 = np.hstack([np.ones((m, 1)), X])
    
    z2 = np.dot(a1, theta1.T)
    a2 = sigmoid(z2)
    a2 = np.hstack([np.ones((m, 1)), a2])
    
    z3 = np.dot(a2, theta2.T)
    a3 = sigmoid(z3)
    a3 = np.hstack([np.ones((m, 1)), a3])
    
    z4 = np.dot(a3, theta3.T)
    h = sigmoid(z4)
    
    return a1, z2, a2, z3, a3, z4, h

def cost_function(theta1, theta2, theta3, X, y, lambda_):
    m = len(X)
    J = 0
    
    a1, z2, a2, z3, a3, z4, h = forward_propagation(X, theta1, theta2, theta3)
    
    num_classes = np.max(y) + 1
    y_onehot = one_hot_encoding(y, num_classes)
    
    J = np.sum(-y_onehot * np.log(h) - (1 - y_onehot) * np.log(1 - h))
    J /= m
    
    reg_term = (lambda_ / (2 * m)) * (np.sum(np.square(theta1[:, 1:])) + np.sum(np.square(theta2[:, 1:])) + np.sum(np.square(theta3[:, 1:])))
    J += reg_term
    
    return J


def backpropagation(theta1, theta2, theta3, X, y, lambda_):
    m = len(X)
    Delta1 = np.zeros_like(theta1)
    Delta2 = np.zeros_like(theta2)
    Delta3 = np.zeros_like(theta3)
    
    a1, z2, a2, z3, a3, z4, h = forward_propagation(X, theta1, theta2, theta3)
    
    num_classes = np.max(y) + 1
    y_onehot = one_hot_encoding(y, num_classes)
    
    delta4 = h - y_onehot
    delta3 = np.dot(delta4, theta3[:, 1:]) * sigmoidGradient(z3)
    delta2 = np.dot(delta3, theta2[:, 1:]) * sigmoidGradient(z2)
    
    Delta3 += np.dot(delta4.T, a3)
    Delta2 += np.dot(delta3.T, a2)
    Delta1 += np.dot(delta2.T, a1)
    
    grad1 = Delta1 / m
    grad2 = Delta2 / m
    grad3 = Delta3 / m
    
    grad1[:, 1:] += (lambda_ / m) * theta1[:, 1:]
    grad2[:, 1:] += (lambda_ / m) * theta2[:, 1:]
    grad3[:, 1:] += (lambda_ / m) * theta3[:, 1:]
    
    return grad1, grad2, grad3

def gradient_descent2(X, y, theta1, theta2, theta3, alpha, num_iters, lambda_=0):
    m = len(X)
    J_history = []
    
    for iter in range(num_iters):
        grad1, grad2, grad3 = backpropagation(theta1, theta2, theta3, X, y, lambda_)
        
        theta1 -= alpha * grad1
        theta2 -= alpha * grad2
        theta3 -= alpha * grad3
        
        J = cost_function(theta1, theta2, theta3, X, y, lambda_)
        J_history.append(J)
    
    plt.plot(J_history, label='Coste')
    plt.xlabel('Tiempo')
    plt.ylabel('Coste')
    plt.title('Evolución del coste en el tiempo')
    plt.legend()
    plt.savefig("Redes Neuronales.jpg")

    return theta1, theta2, theta3, J_history

def predict2(theta1, theta2, theta3, X):
    _, _, _, _, _, _, h = forward_propagation(X, theta1, theta2, theta3)
    return np.argmax(h, axis=1)

def red_neuronal(X_train, y_train, X_val, y_val, X_test, y_test, hidden_size1=100, hidden_size2=50, alpha=1, num_iters=400, lambda_=1):
    input_size = X_train.shape[1]
    output_size = len(np.unique(y_train))
    
    theta1, theta2, theta3 = initialize_weights(input_size, hidden_size1, hidden_size2, output_size)
    
    theta1_opt, theta2_opt, theta3_opt, J_history = gradient_descent2(X_train, y_train, theta1, theta2, theta3, alpha, num_iters, lambda_)
    
    predictions_train = predict2(theta1_opt, theta2_opt, theta3_opt, X_train)
    accuracy_train = np.mean(predictions_train == y_train) * 100
    print(f'Precisión en el conjunto de entrenamiento: {accuracy_train:.2f}%')
    
    predictions_val = predict2(theta1_opt, theta2_opt, theta3_opt, X_val)
    accuracy_val = np.mean(predictions_val == y_val) * 100
    print(f'Precisión en el conjunto de validación: {accuracy_val:.2f}%')
    
    predictions_test = predict2(theta1_opt, theta2_opt, theta3_opt, X_test)
    accuracy_test = np.mean(predictions_test == y_test) * 100
    print(f'Precisión en el conjunto de prueba: {accuracy_test:.2f}%')

    plot_confusion_matrix(y_test, predictions_test, path="nn_propia_confusion.png", type='test')


def plot_confusion_matrix(y_true, y_pred, path, type='train'):
    cm = confusion_matrix(y_true, y_pred)

    plt.figure(figsize=(8, 6))
    sns.heatmap(cm, annot=True, fmt="d", cmap="Blues", cbar=False)
    plt.xlabel('Predicted labels')
    plt.ylabel('True labels')
    plt.title('Confusion Matrix')
    plt.savefig(f'confusion_{type}.png')

def main():
    '''
    # Función para cargar los datos y generar los vectores de atributos
    def load_and_process_data():
        # Procesar archivos de spam
        spam_folder = "P7/data_spam/spam/"
        spam_data_file = "spam_data.pkl"

        if os.path.exists(spam_data_file):
            spam_data = load_data(spam_data_file)
        else:
            spam_data = []
            for filename in os.listdir(spam_folder):
                file_path = os.path.join(spam_folder, filename)
                if os.path.isfile(file_path):
                    with open(file_path, 'r', encoding='utf-8', errors='ignore') as file:
                        email_contents = file.read()
                        token_list = email2TokenList(email_contents)
                        spam_data.append(token_list)
            save_data(spam_data, spam_data_file)

        # Procesar archivos de hard_ham
        hard_ham_folder = "P7/data_spam/hard_ham/"
        hard_ham_data_file = "hard_ham_data.pkl"

        if os.path.exists(hard_ham_data_file):
            hard_ham_data = load_data(hard_ham_data_file)
        else:
            hard_ham_data = []
            for filename in os.listdir(hard_ham_folder):
                file_path = os.path.join(hard_ham_folder, filename)
                if os.path.isfile(file_path):
                    with open(file_path, 'r', encoding='utf-8', errors='ignore') as file:
                        email_contents = file.read()
                        token_list = email2TokenList(email_contents)
                        hard_ham_data.append(token_list)
            save_data(hard_ham_data, hard_ham_data_file)

        # Procesar archivos de easy_ham
        easy_ham_folder = "P7/data_spam/easy_ham/"
        easy_ham_data_file = "easy_ham_data.pkl"

        if os.path.exists(easy_ham_data_file):
            easy_ham_data = load_data(easy_ham_data_file)
        else:
            easy_ham_data = []
            for filename in os.listdir(easy_ham_folder):
                file_path = os.path.join(easy_ham_folder, filename)
                if os.path.isfile(file_path):
                    with open(file_path, 'r', encoding='utf-8', errors='ignore') as file:
                        email_contents = file.read()
                        token_list = email2TokenList(email_contents)
                        easy_ham_data.append(token_list)
            save_data(easy_ham_data, easy_ham_data_file)

        # Obtener el diccionario de vocabulario
        vocab_dict = getVocabDict()

        # Convertir los correos electrónicos en vectores de atributos
        spam_features = [emailToFeatureVector(email, vocab_dict) for email in spam_data]
        hard_ham_features = [emailToFeatureVector(email, vocab_dict) for email in hard_ham_data]
        easy_ham_features = [emailToFeatureVector(email, vocab_dict) for email in easy_ham_data]

        # Guardar los vectores de atributos en archivos
        save_data(spam_features, "spam_features.pkl")
        save_data(hard_ham_features, "hard_ham_features.pkl")
        save_data(easy_ham_features, "easy_ham_features.pkl")

        return spam_features, hard_ham_features, easy_ham_features

    # Función para guardar los datos en un archivo
    def save_data(data, filename):
        with open(filename, 'wb') as f:
            pickle.dump(data, f)

    # Función para cargar los datos desde un archivo
    def load_data(filename):
        with open(filename, 'rb') as f:
            return pickle.load(f)

    # Función para convertir un correo electrónico en un vector de atributos
    def emailToFeatureVector(token_list, vocab_dict):
        feature_vector = [0] * len(vocab_dict)
        for token in token_list:
            if token in vocab_dict:
                index = vocab_dict[token]
                feature_vector[index - 1] = 1
        return feature_vector

    spam_features, hard_ham_features, easy_ham_features = load_and_process_data()

    # Concatena todos los vectores de atributos y etiquetas de clase
    X = np.concatenate([spam_features, hard_ham_features, easy_ham_features])
    y = np.concatenate([np.ones(len(spam_features)), np.zeros(len(hard_ham_features) + len(easy_ham_features))])

    # División de los datos en conjuntos de entrenamiento y prueba
    X_train, X_test1, y_train, y_test1 = train_test_split(X, y, test_size=0.4)
    X_val, X_test, y_val, y_test = train_test_split(X_test1, y_test1, test_size=0.5)
    '''
    
    # Función para cargar los datos de entrenamiento y prueba, procesarlos si es necesario y guardarlos en archivos
    def load_or_process_data():
        if os.path.exists("train_data.pkl") and os.path.exists("test_data.pkl"):
            train_data = load_data("train_data.pkl")
            test_data = load_data("test_data.pkl")
        else:
            train_data, test_data = process_data()
            save_data(train_data, "train_data.pkl")
            save_data(test_data, "test_data.pkl")

        return train_data, test_data

    # Función para procesar los datos de entrenamiento y prueba
    def process_data():
        train_data = loadmat('trainset.mat') #loadmat
        test_data = loadmat('testset.mat') #loadmat
        return train_data, test_data

    # formato de texto cambio en process_data loadmat por load_text_data
    # Función para cargar datos de texto
    def load_text_data(filename):
        data = np.loadtxt(filename, delimiter=',', skiprows=1)
        X = data[:, :-1]
        y = data[:, -1].astype(int)
        return {'X': X, 'y': y}
    

    # Función para guardar los datos en un archivo
    def save_data(data, filename):
        with open(filename, 'wb') as f:
            pickle.dump(data, f, protocol=pickle.HIGHEST_PROTOCOL)

    # Función para cargar los datos desde un archivo
    def load_data(filename):
        with open(filename, 'rb') as f:
            return pickle.load(f)

    # Resto de las funciones y código sigue siendo el mismo

    # Carga o procesa los datos
    train_data, test_data = load_or_process_data()

    # Extrae los conjuntos de entrenamiento y prueba
    X_train = train_data['X']
    y_train = train_data['y'].flatten()
    X_test = test_data['Xtest'] #X cuando se utilice load_text_data
    y_test = test_data['ytest'].flatten() #y cuadno se utilice load_text_data

    # División del conjunto de entrenamiento en entrenamiento y validación
    X_train, X_val, y_train, y_val = train_test_split(X_train, y_train, test_size=0.2)
    

    #regresion_logistica(X_train, y_train, X_val, y_val, X_test, y_test, 0.001, 20000)
    SVM(X_train, y_train, X_val, y_val, X_test, y_test)
    #complex_reg(X_train, y_train, X_val, y_val, X_test, y_test, 1000, 0.0001)
    #red_neuronal(X_train, y_train, X_val, y_val, X_test, y_test, hidden_size1=100, hidden_size2=50, alpha=1, num_iters=400, lambda_=1)


if __name__ == "__main__":
    main()


'''
En esta memoria, se describen los métodos de aprendizaje automático aplicados para la clasificación de correos electrónicos en spam y no spam (ham). Se utilizaron cuatro enfoques diferentes: Regresión Logística, Máquinas de Vectores de Soporte (SVM), una Red Neuronal con PyTorch y una Red Neuronal personalizada. A continuación, se presentan los detalles de cada método, los resultados obtenidos y una evaluación de su rendimiento.

1. Regresión Logística
Descripción
La Regresión Logística es un modelo lineal utilizado para la clasificación binaria. En este caso, se utilizó para clasificar correos electrónicos como spam o no spam. La función sigmoide se emplea para mapear cualquier valor real a un valor entre 0 y 1, lo que permite interpretar la salida como una probabilidad.

Implementación
El modelo se entrenó usando descenso de gradiente, ajustando los pesos w y el sesgo b para minimizar la función de costo logística. También se implementaron versiones regularizadas de las funciones de costo y gradiente para prevenir el sobreajuste.

código de regrosion_logistica

Resultados
Precisión en entrenamiento: 91.46%
Precisión en validación: 91.51%
Precisión en test: 90.47%

2. Máquinas de Vectores de Soporte (SVM)
Descripción
Las SVM son modelos de clasificación supervisada que encuentran el hiperplano que mejor separa las clases en el espacio de características. Se utilizó un kernel RBF (Radial Basis Function) para manejar datos no linealmente separables.

Implementación
Se probaron diferentes valores de C y σ para optimizar el rendimiento del modelo. Se seleccionaron los mejores hiperparámetros basados en la precisión en el conjunto de validación.

código de SVM

Resultados
Precisión en entrenamiento: 99.84%
Precisión en validación: 98.33%
Precisión en test: 98.79%


3. Red Neuronal con PyTorch
Descripción
Se utilizó una red neuronal con PyTorch para aprovechar la capacidad de las redes profundas para aprender representaciones complejas de los datos. La red tiene tres capas ocultas con funciones de activación ReLU y una capa de salida con una función de activación sigmoide.

Implementación
El modelo se entrenó usando el optimizador Adam y la función de pérdida de error cuadrático medio (MSELoss). Se aplicó regularización para evitar el sobreajuste.

código de complex_reg

Resultados
Epoch 0 Loss: 0.2445
Epoch 100 Loss: 0.0058
Epoch 200 Loss: 0.0265
Epoch 300 Loss: 0.0047
Epoch 400 Loss: 0.0140
Epoch 500 Loss: 0.0101
Epoch 600 Loss: 0.0078
Epoch 700 Loss: 0.0140
Epoch 800 Loss: 0.0095
Epoch 900 Loss: 0.0150
Accuracy on validation set: 97.87%


4. Red Neuronal Personalizada
Descripción
Se implementó una red neuronal personalizada desde cero. Esta red tiene dos capas ocultas con tamaños configurables y utiliza la función de activación sigmoide.

Implementación
La red se entrenó utilizando propagación hacia adelante y retropropagación para calcular los gradientes. Se utilizó regularización para evitar el sobreajuste y descenso de gradiente para actualizar los pesos.

código red_neuronal

Resultados
Precisión en el conjunto de entrenamiento: 100%
Precisión en el conjunto de validación: 97.78%

Conclusiones Generales
Regresión Logística: Es fácil de implementar y da buenos resultados iniciales. Sin embargo, en problemas complejos puede no ser suficiente y otros métodos pueden superarla.
SVM: Proporciona una alta precisión y es eficaz para problemas linealmente separables o no linealmente separables usando kernels. La búsqueda de hiperparámetros es crucial para el rendimiento.
Red Neuronal con PyTorch: Ofrece alta precisión y es flexible para problemas complejos. Requiere ajuste fino de la arquitectura y los hiperparámetros.
Red Neuronal Personalizada: Puede lograr alta precisión con un buen diseño, pero es más laboriosa de implementar desde cero y puede ser propensa a sobreajuste sin una adecuada regularización.
La elección del modelo depende de los requisitos específicos del problema, la disponibilidad de recursos computacionales y el nivel de precisión deseado. En este caso, el SVM con kernel RBF se destacó por su alta precisión y consistencia en los conjuntos de datos de validación y prueba.
'''