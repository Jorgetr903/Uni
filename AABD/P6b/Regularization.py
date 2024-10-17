import numpy as np
from sklearn.datasets import make_blobs
from sklearn.model_selection import train_test_split
import torch
import torch.nn as nn
import matplotlib.pyplot as plt

# Generar el conjunto de datos artificial
classes = 6
m = 800
std = 0.4
centers = np.array([[-1, 0], [1, 0], [0, 1], [0,-1], [-2, 1], [-2,-1]])
X, y = make_blobs(n_samples=m, centers=centers, cluster_std=std, random_state=2, n_features=2)

# Dividir el conjunto de datos en entrenamiento, validación cruzada y prueba
X_train, X_temp, y_train, y_temp = train_test_split(X, y, test_size=0.50, random_state=1)
X_cv, X_test, y_cv, y_test = train_test_split(X_temp, y_temp, test_size=0.20, random_state=1)

class ComplexModelWithRegularization(nn.Module):
    def __init__(self):
        super(ComplexModelWithRegularization, self).__init__()
        self.fc1 = nn.Linear(2, 120)
        self.fc2 = nn.Linear(120, 40)
        self.fc3 = nn.Linear(40, 6)

    def forward(self, x):
        x = torch.relu(self.fc1(x))
        x = torch.relu(self.fc2(x))
        x = self.fc3(x)
        return x

# Función para visualizar los datos
def plot_data(X, y, title):
    plt.scatter(X[:, 0], X[:, 1], c=y, cmap=plt.cm.rainbow)
    plt.title(title)
    plt.xlabel('Feature 1')
    plt.ylabel('Feature 2')
    plt.ylim(-3, 3)
    plt.show()

# Visualizar los datos de entrenamiento
plot_data(X_train, y_train, title='Training Data')

# Visualizar los datos de validación cruzada
plot_data(X_cv, y_cv, title='Cross-Validation Data')

# Convertir los datos de entrenamiento y validación cruzada a tensores de PyTorch
X_train_tensor = torch.tensor(X_train, dtype=torch.float32)
y_train_tensor = torch.tensor(y_train, dtype=torch.long)
X_cv_tensor = torch.tensor(X_cv, dtype=torch.float32)
y_cv_tensor = torch.tensor(y_cv, dtype=torch.long)

# Instanciar el modelo complejo con regularización L2
complex_model_with_regularization = ComplexModelWithRegularization()

# Definir la función de pérdida (CrossEntropyLoss) y el optimizador (Adam) con regularización L2
criterion_with_regularization = nn.CrossEntropyLoss()
optimizer_with_regularization = torch.optim.Adam(complex_model_with_regularization.parameters(), lr=0.001, weight_decay=0.1)

# Función para entrenar el modelo
def train_model(model, criterion, optimizer, X, y, X_val, y_val, epochs=1000):
    train_losses = []
    val_losses = []
    for epoch in range(epochs):
        optimizer.zero_grad()  # Reiniciar gradientes
        outputs = model(X)  # Calcular las salidas del modelo
        loss = criterion(outputs, y)  # Calcular la pérdida
        loss.backward()  # Retropropagar la pérdida
        optimizer.step()  # Actualizar los parámetros

        # Calcular la pérdida en el conjunto de validación cruzada
        with torch.no_grad():
            val_outputs = model(X_val)
            val_loss = criterion(val_outputs, y_val).item()

        # Imprimir información de la pérdida cada cierto número de épocas
        if (epoch+1) % 100 == 0:
            print(f'Epoch [{epoch+1}/{epochs}], Loss: {loss.item()}, Val Loss: {val_loss}')
        
        train_losses.append(loss.item())
        val_losses.append(val_loss)
    
    return train_losses, val_losses

# Entrenar el modelo con regularización L2
train_losses_with_regularization, val_losses_with_regularization = train_model(complex_model_with_regularization, criterion_with_regularization, optimizer_with_regularization, X_train_tensor, y_train_tensor, X_cv_tensor, y_cv_tensor, epochs=1000)

# Lista de valores de regularización (lambda) para probar
regularization_values = [0.0, 0.001, 0.01, 0.05, 0.1]

# Listas para almacenar los errores de entrenamiento y validación cruzada para cada valor de regularización
train_errors = []
cv_errors = []

# Iterar sobre los valores de regularización y entrenar el modelo para cada uno
for reg_value in regularization_values:
    # Instanciar el modelo complejo con regularización L2 para el valor actual de regularización
    complex_model_with_regularization = ComplexModelWithRegularization()

    # Definir el optimizador (Adam) con el valor actual de regularización L2
    optimizer_with_regularization = torch.optim.Adam(complex_model_with_regularization.parameters(), lr=0.001, weight_decay=reg_value)

    # Entrenar el modelo con regularización L2
    train_losses, val_losses = train_model(complex_model_with_regularization, criterion_with_regularization, optimizer_with_regularization, X_train_tensor, y_train_tensor, X_cv_tensor, y_cv_tensor, epochs=1000)

    # Guardar los errores de entrenamiento y validación cruzada para este valor de regularización
    train_errors.append(train_losses[-1])  # Usar el último valor de la lista de pérdidas de entrenamiento

    # Encontrar el error de validación cruzada más bajo durante el entrenamiento
    min_cv_loss = min(val_losses)
    cv_errors.append(min_cv_loss)

# Graficar los errores de entrenamiento y validación cruzada en función de los valores de regularización
plt.figure(figsize=(10, 6))
plt.plot(regularization_values, train_errors, marker='o', label='Train Error')
plt.plot(regularization_values, cv_errors, marker='o', label='CV Error')
plt.xlabel('Regularization (lambda)')
plt.ylabel('Error')
plt.title('Tuning Regularization: Error vs Regularization')
plt.legend()
plt.grid(True)
plt.show()
