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

X, y = create_clusters()
complex(X, y) 
#La accuracy del sistema en validación es del 0.8812500238418579 %