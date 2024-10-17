import os
import pickle
import torch
import torch.nn as nn
import torch.optim as optim
from torch.utils.data import DataLoader, TensorDataset
import numpy as np
import matplotlib.pyplot as plt
from sklearn.model_selection import train_test_split
import numpy as np
import matplotlib.pyplot as plt
import pickle
import os
import torch
import torch.nn as nn
from sklearn import svm
from sklearn.svm import SVC
from utils import*
from sklearn.model_selection import train_test_split
from sklearn.linear_model import LogisticRegression
from sklearn.metrics import classification_report, confusion_matrix

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



# Carga y procesamiento de datos
spam_features, hard_ham_features, easy_ham_features = load_and_process_data()

# Concatena todos los vectores de atributos y etiquetas de clase
X = np.concatenate([spam_features, hard_ham_features, easy_ham_features])
y = np.concatenate([np.ones(len(spam_features)), np.zeros(len(hard_ham_features) + len(easy_ham_features))])

# División de los datos en conjuntos de entrenamiento y prueba
X_train, X_test1, y_train, y_test1 = train_test_split(X, y, test_size=0.4)
X_val, X_test, y_val, y_test = train_test_split(X_test1, y_test1, test_size=0.5)
# Define la función para cargar y procesar los datos


# Define la función para el modelo complejo
def complex_reg(X_train, y_train, X_val, y_val, X_test, y_test):
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
        nn.Linear(len(X_train[0]), 200),
        nn.ReLU(),
        nn.Linear(200, 100),
        nn.ReLU(),
        nn.Linear(100, 50),
        nn.ReLU(),
        nn.Linear(50, 1),
        nn.Sigmoid()  # Función de activación sigmoide para la clasificación binaria
    )


    # Entrena el modelo
    num_epochs = 300
    log_epoch = num_epochs / 10
    loss_hist = [0] * num_epochs
    accuracy_hist = [0] * num_epochs

    learning_rate = 0.01
    loss_fn = nn.MSELoss()
    optimzer = optim.Adam(model.parameters(), lr=learning_rate, weight_decay=0.1) #usamos regularización lambda = 0.1


    for epoch in range(num_epochs):
        for x_batch, y_batch in train_dl:
            
            #Compute cost
            pred = model(x_batch)
            loss = loss_fn(pred.squeeze(), y_batch.float())  # Squeeze para asegurar que las dimensiones sean compatibles
            
            #Backpropagation
            loss.backward()
            optimzer.step()
            optimzer.zero_grad()
            
            # Compute accuracy
            loss_hist[epoch] += loss.item() * y_batch.size(0)
            is_correct = ((torch.max(pred, dim=1).values > 0.5) == y_batch).float()
            accuracy_hist[epoch] += is_correct.sum()
            
        loss_hist[epoch] /= len(train_dl.dataset)
        accuracy_hist[epoch] /= len(train_dl.dataset)
        
        if epoch % log_epoch == 0:
            print(f"Epoch {epoch} Loss {loss_hist[epoch]:.4f}")

    print("Accuracy:", accuracy_hist[num_epochs - 1])
        
    #Pintamos el training loss
    fig = plt.figure(figsize=(12, 5))
    ax = fig.add_subplot(1, 2, 1)
    ax.plot(loss_hist, lw=3)
    ax.set_title('Training loss', size=15)
    ax.set_xlabel('Epoch', size=15)
    ax.tick_params(axis='both', which='major', labelsize=15)
    
    #Pintamos el training accuracy
    ax = fig.add_subplot(1, 2, 2)
    ax.plot(accuracy_hist, c='b')
    ax.set_title('Test accuracy', size=15)
    ax.set_xlabel('Epoch', size=15)
    ax.tick_params(axis='both', which='major', labelsize=15)
    plt.tight_layout()
    plt.savefig('MetricasSimple.png')

# Entrena y evalúa el modelo complejo
complex_reg(X_train, y_train, X_val, y_val, X_test, y_test)

'''
Epoch 0 Loss 0.1929
Epoch 30 Loss 0.1526
Epoch 60 Loss 0.1544
Epoch 90 Loss 0.1535
Epoch 120 Loss 0.1538
Epoch 150 Loss 0.1525
Epoch 180 Loss 0.1532
Epoch 210 Loss 0.1531
Epoch 240 Loss 0.1527
Epoch 270 Loss 0.1537
Accuracy: 0.8455
'''