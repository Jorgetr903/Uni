from sklearn.datasets import make_blobs
from sklearn.model_selection import train_test_split
import torch.nn as nn
import numpy as np
import torch
from torch.utils.data import TensorDataset
from torch.utils.data import DataLoader
import matplotlib.pyplot as plt


def create_clusters():
    classes = 6
    m = 800
    std = 0.4
    centers = np.array([[-1, 0], [1, 0], [0, 1], [0, -1], [-2, 1], [-2, -1]])
    X, y = make_blobs(n_samples=m, centers=centers, cluster_std=std, random_state=2, n_features=2)
    return X, y


def complex(X, y):
    
    #Separamos en train, cv, test 50, 30, 20
    X_train, X_, y_train, y_ = train_test_split(X, y, test_size=0.50, random_state=1)
    X_cv, X_test, y_cv, y_test = train_test_split(X_, y_, test_size=0.20, random_state=1)
    
    X_train_norm = (X_train - np.mean(X_train)) / np.std(X_train)
    X_train_norm = torch.from_numpy(X_train_norm).float()   # Crear tensor con la X
    y_train = torch.from_numpy(y_train)
    
    #Creamos el data set con la X y la Y
    train_ds = TensorDataset(X_train_norm, y_train)
    
    torch.manual_seed(1)
    batch_size = 2
    
    #Creamos el data louder
    train_dl = DataLoader(train_ds, batch_size, shuffle=True)
    
    
    #COMPLEX MODEL ----------------------------------------------
    
    input_size = 120
    hiden_size = 40
    output_size = 6
    
    complexModel = nn.Sequential(
        nn.Linear(2, input_size),
        nn.ReLU(),
        nn.Linear(input_size, hiden_size),
        nn.ReLU(),
        nn.Linear(hiden_size, output_size),
    )
    
    learning_rate = 0.001
    loss_fn = nn.CrossEntropyLoss()
    optimzer = torch.optim.Adam(complexModel.parameters(), lr=learning_rate)
    
    num_epochs = 500
    
    log_epoch = num_epochs / 10
    loss_hist = [0] * num_epochs
    accuracy_hist = [0] * num_epochs
    
    #REalizamos 1000 iteraciones en las que recorremos todos los ejemplos cada vez
    
    for epoch in range(num_epochs):
        for x_batch, y_batch in train_dl:
            
            #Compute cost
            pred = complexModel(x_batch)
            loss = loss_fn(pred, y_batch.long())
            
            #Backpropagation
            loss.backward()
            optimzer.step()
            optimzer.zero_grad()
            
            # Compute accuracy
            loss_hist[epoch] += loss.item() * y_batch.size(0)
            is_correct = (torch.argmax(pred, dim=1) ==
            y_batch).float()
            accuracy_hist[epoch] += is_correct.sum()

        loss_hist[epoch] /= len(train_dl.dataset)
        accuracy_hist[epoch] /= len(train_dl.dataset)
        
        # if epoch % log_epoch == 0:
        #     print(f"Epoch {epoch} Loss {loss_hist[epoch]:.4f}")
    
    
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
    ax.set_title('Training accuracy', size=15)
    ax.set_xlabel('Epoch', size=15)
    ax.tick_params(axis='both', which='major', labelsize=15)
    plt.tight_layout()
    plt.savefig('MetricasComplex.png')


    #Calculo de la accuracy en cross validation
    X_validation_norm = (X_cv - np.mean(X_cv)) / np.std(X_cv)
    X_validation_norm = torch.from_numpy(X_validation_norm).float()
    y_cv_real = torch.from_numpy(y_cv)
    
    y_cv_predicted = complexModel(X_validation_norm)
    
    #Obtenemos vector de 1 y 0 en funcion de si el modelo acertó o no para cada ejemplo
    correct = (torch.argmax(y_cv_predicted, dim=1) == y_cv_real).float()
    accuracy = correct.mean()
    print(f'La accuracy del sistema en validación es del {accuracy} %')
    

def simple(X, y):
    
    #Separamos en train, cv, test 50, 30, 20
    X_train, X_, y_train, y_ = train_test_split(X, y, test_size=0.50, random_state=1)
    X_cv, X_test, y_cv, y_test = train_test_split(X_, y_, test_size=0.20, random_state=1)
    
    X_train_norm = (X_train - np.mean(X_train)) / np.std(X_train)
    X_train_norm = torch.from_numpy(X_train_norm).float()   # Crear tensor con la X
    y_train = torch.from_numpy(y_train)
    
    #Creamos el data set con la X y la Y
    train_ds = TensorDataset(X_train_norm, y_train)
    
    torch.manual_seed(1)
    batch_size = 2
    
    #Creamos el data louder
    train_dl = DataLoader(train_ds, batch_size, shuffle=True)
    
    
    #COMPLEX MODEL ----------------------------------------------
    
    input_size = 6
    output_size = 6
    
    complexModel = nn.Sequential(
        nn.Linear(2, input_size),
        nn.ReLU(),
        nn.Linear(input_size, output_size),
    )
    
    learning_rate = 0.001
    loss_fn = nn.CrossEntropyLoss()
    optimzer = torch.optim.Adam(complexModel.parameters(), lr=learning_rate)
    
    num_epochs = 500
    
    log_epoch = num_epochs / 10
    loss_hist = [0] * num_epochs
    accuracy_hist = [0] * num_epochs
    
    #REalizamos 1000 iteraciones en las que recorremos todos los ejemplos cada vez
    
    for epoch in range(num_epochs):
        for x_batch, y_batch in train_dl:
            
            #Compute cost
            pred = complexModel(x_batch)
            loss = loss_fn(pred, y_batch.long())
            
            #Backpropagation
            loss.backward()
            optimzer.step()
            optimzer.zero_grad()
            
            # Compute accuracy
            loss_hist[epoch] += loss.item() * y_batch.size(0)
            is_correct = (torch.argmax(pred, dim=1) ==
            y_batch).float()
            accuracy_hist[epoch] += is_correct.sum()

        loss_hist[epoch] /= len(train_dl.dataset)
        accuracy_hist[epoch] /= len(train_dl.dataset)
        
        # if epoch % log_epoch == 0:
        #     print(f"Epoch {epoch} Loss {loss_hist[epoch]:.4f}")
    
    
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
    ax.set_title('Training accuracy', size=15)
    ax.set_xlabel('Epoch', size=15)
    ax.tick_params(axis='both', which='major', labelsize=15)
    plt.tight_layout()
    plt.savefig('MetricasSimple.png')

    #Calculo de la accuracy en cross validation
    X_validation_norm = (X_cv - np.mean(X_cv)) / np.std(X_cv)
    X_validation_norm = torch.from_numpy(X_validation_norm).float()
    y_cv_real = torch.from_numpy(y_cv)
    
    y_cv_predicted = complexModel(X_validation_norm)
    
    #Obtenemos vector de 1 y 0 en funcion de si el modelo acertó o no para cada ejemplo
    correct = (torch.argmax(y_cv_predicted, dim=1) == y_cv_real).float()
    accuracy = correct.mean()
    print(f'La accuracy del sistema en validación es del {accuracy} %')


def complexBestLambda(X, y):
    
    #Separamos en train, cv, test 50, 30, 20
    X_train, X_, y_train, y_ = train_test_split(X, y, test_size=0.50, random_state=1)
    X_cv, X_test, y_cv, y_test = train_test_split(X_, y_, test_size=0.20, random_state=1)
    
    X_train_norm = (X_train - np.mean(X_train)) / np.std(X_train)
    X_train_norm = torch.from_numpy(X_train_norm).float()   # Crear tensor con la X
    y_train = torch.from_numpy(y_train)
    
    #Creamos el data set con la X y la Y
    train_ds = TensorDataset(X_train_norm, y_train)
    
    torch.manual_seed(1)
    batch_size = 2
    
    #Creamos el data louder
    train_dl = DataLoader(train_ds, batch_size, shuffle=True)
    
    
    #COMPLEX MODEL ----------------------------------------------
    
    input_size = 120
    hiden_size = 40
    output_size = 6
    
    complexModel = nn.Sequential(
        nn.Linear(2, input_size),
        nn.ReLU(),
        nn.Linear(input_size, hiden_size),
        nn.ReLU(),
        nn.Linear(hiden_size, output_size),
    )
    
    learning_rate = 0.001
    loss_fn = nn.CrossEntropyLoss()
    
    num_epochs = 100
    
    log_epoch = num_epochs / 10
    loss_hist = [0] * num_epochs
    accuracy_hist = [0] * num_epochs
    
    #REalizamos 1000 iteraciones en las que recorremos todos los ejemplos cada vez
    lambdas = [0.0, 0.001, 0.01, 0.05, 0.1, 0.2, 0.3]
    
    accuracies = []
    accuraciesCV = []
    
    for lambda_ in lambdas:
        
        optimizer = torch.optim.Adam(complexModel.parameters(), lr=learning_rate, weight_decay=lambda_)
        
        for epoch in range(num_epochs):
            for x_batch, y_batch in train_dl:
                
                #Compute cost
                pred = complexModel(x_batch)
                loss = loss_fn(pred, y_batch.long())
                
                #Backpropagation
                loss.backward()
                optimizer.step()
                optimizer.zero_grad()
                
                # Compute accuracy
                loss_hist[epoch] += loss.item() * y_batch.size(0)
                is_correct = (torch.argmax(pred, dim=1) ==
                y_batch).float()
                accuracy_hist[epoch] += is_correct.sum()

            loss_hist[epoch] /= len(train_dl.dataset)
            accuracy_hist[epoch] /= len(train_dl.dataset)
        
        #OBTENEMOS LA ACCURACY PARA ENTRENMIENTO
        y_train_pred = complexModel(X_train_norm)
        correct = (torch.argmax(y_train_pred, dim=1) == y_train).float()
        accuracy = correct.mean()
        accuracies.append(accuracy)
        
        #OBTENEMOS ACCURACY PARA CROSS VAL
        
        X_validation_norm = (X_cv - np.mean(X_cv)) / np.std(X_cv)
        X_validation_norm = torch.from_numpy(X_validation_norm).float()
        y_cv_predicted = complexModel(X_validation_norm)
        y_cv_real = torch.from_numpy(y_cv)
        
        correct = (torch.argmax(y_cv_predicted, dim=1) == y_cv_real).float()
        accuracy = correct.mean()
        accuraciesCV.append(accuracy)    
        
        
    plt.plot(lambdas, accuracies, c='b', label='Train Accuracy')
    plt.scatter(lambdas, accuracies, c='b')
    plt.plot(lambdas, accuraciesCV, c='r', label='CV Accuracy')
    plt.scatter(lambdas, accuraciesCV, c='r')
    plt.title("Accuracy with Reg")
    plt.xlabel("Lambda value")
    plt.ylabel("Accyracy")
    plt.legend()
    plt.savefig("BestLambda.png")
    

    # #Calculo de la accuracy en cross validation
    # X_validation_norm = (X_cv - np.mean(X_cv)) / np.std(X_cv)
    # X_validation_norm = torch.from_numpy(X_validation_norm).float()
    # y_cv_real = torch.from_numpy(y_cv)
    
    # y_cv_predicted = complexModel(X_validation_norm)
    
    # #Obtenemos vector de 1 y 0 en funcion de si el modelo acertó o no para cada ejemplo
    # correct = (torch.argmax(y_cv_predicted, dim=1) == y_cv_real).float()
    # accuracy = correct.mean()
    # print(f'La accuracy del sistema en validación es del {accuracy} %')
    
def trainAndSave_simple(X, y):
    #Separamos en train, cv, test 50, 30, 20
    X_train, X_, y_train, y_ = train_test_split(X, y, test_size=0.50, random_state=1)
    
    X_train_norm = (X_train - np.mean(X_train)) / np.std(X_train)
    X_train_norm = torch.from_numpy(X_train_norm).float()   # Crear tensor con la X
    y_train = torch.from_numpy(y_train)
    
    #Creamos el data set con la X y la Y
    train_ds = TensorDataset(X_train_norm, y_train)
    
    torch.manual_seed(1)
    batch_size = 2
    
    #Creamos el data louder
    train_dl = DataLoader(train_ds, batch_size, shuffle=True)
    

    #COMPLEX MODEL ----------------------------------------------
    
    input_size = 6
    output_size = 6
    
    model = nn.Sequential(
        nn.Linear(2, input_size),
        nn.ReLU(),
        nn.Linear(input_size, output_size),
    )
    
    learning_rate = 0.001
    loss_fn = nn.CrossEntropyLoss()
    optimzer = torch.optim.Adam(model.parameters(), lr=learning_rate)
    
    num_epochs = 1000
    
    #REalizamos 1000 iteraciones en las que recorremos todos los ejemplos cada vez
    
    for epoch in range(num_epochs):
        for x_batch, y_batch in train_dl:
            
            #Compute cost
            pred = model(x_batch)
            loss = loss_fn(pred, y_batch.long())
            
            #Backpropagation
            loss.backward()
            optimzer.step()
            optimzer.zero_grad()
            
    path = 'Simple(6,6).pt'
    torch.save(model, path)
    
    
def trainAndSave_regularizedComplex(X, y):
    #Separamos en train, cv, test 50, 30, 20
    X_train, X_, y_train, y_ = train_test_split(X, y, test_size=0.50, random_state=1)
    
    X_train_norm = (X_train - np.mean(X_train)) / np.std(X_train)
    X_train_norm = torch.from_numpy(X_train_norm).float()   # Crear tensor con la X
    y_train = torch.from_numpy(y_train)
    
    #Creamos el data set con la X y la Y
    train_ds = TensorDataset(X_train_norm, y_train)
    
    torch.manual_seed(1)
    batch_size = 2
    
    #Creamos el data louder
    train_dl = DataLoader(train_ds, batch_size, shuffle=True)
    
    
    #COMPLEX MODEL ----------------------------------------------
    
    input_size = 120
    hiden_size = 40
    output_size = 6
    
    complexModel = nn.Sequential(
        nn.Linear(2, input_size),
        nn.ReLU(),
        nn.Linear(input_size, hiden_size),
        nn.ReLU(),
        nn.Linear(hiden_size, output_size),
    )
    
    learning_rate = 0.001
    loss_fn = nn.CrossEntropyLoss()
    
    num_epochs = 1000
    
    optimizer = torch.optim.Adam(complexModel.parameters(), lr=learning_rate, weight_decay=0.05)
    
    for epoch in range(num_epochs):
        if epoch % 100 == 0:
            print(epoch)
        for x_batch, y_batch in train_dl:
            
            #Compute cost
            pred = complexModel(x_batch)
            loss = loss_fn(pred, y_batch.long())
            
            #Backpropagation
            loss.backward()
            optimizer.step()
            optimizer.zero_grad()
            
    path = 'ResgularizedComplex(120,40,6).pt'
    torch.save(complexModel, path)
            

def test_model(X, y, path):
    X_train, X_, y_train, y_ = train_test_split(X, y, test_size=0.50, random_state=1)
    X_cv, X_test, y_cv, y_test = train_test_split(X_, y_, test_size=0.20, random_state=1)
    
    
    X_test_norm = (X_test - np.mean(X_test)) / np.std(X_test)
    X_test_norm = torch.from_numpy(X_test_norm).float()
    y_test_real = torch.from_numpy(y_test)
    
    model = torch.load(path)
    print(model.eval())
    y_predicted = model(X_test_norm)
    error = (torch.argmax(y_predicted, dim=1) != y_test_real).float()
    error = error.mean()
    print(f'El error en test del modelo {path} es {error}')
    
    
def main():
    X, y = create_clusters()
    #complex(X, y) La accuracy del sistema en validación es del 0.8812500238418579 %
    #simple(X, y) La accuracy del sistema en validación es del 0.9281250238418579 %
    #complexBestLambda(X, y)
    # trainAndSave_simple(X, y)
    #trainAndSave_regularizedComplex(X, y)
    
    test_model(X, y, 'models/Simple(6,6).pt')
    test_model(X, y, 'models/ResgularizedComplex(120,40,6).pt')

main()

# def plot_clusters(X, y, model):
#     plt.figure(figsize=(10, 6))
#     plt.scatter(X[:, 0], X[:, 1], c=y, cmap='tab10')
#     plt.title('Clusters')
#     plt.xlabel('Feature 1')
#     plt.ylabel('Feature 2')
#     plt.colorbar(label='Cluster')
#     plt.grid(True)
#     plt.show()