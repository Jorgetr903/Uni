import numpy as np

def load_data():
    data = np.loadtxt("C:/Users/jorge/source/repos/AABD/P1/data/ex1data1.txt", delimiter=',')
    X = data[:,0]
    y = data[:,1]
    return X, y

def load_data_multi():
    data = np.loadtxt("C:/Users/jorge/source/repos/AABD/P2/data/houses.txt", delimiter=',')
    X = data[:,:2]
    y = data[:,2]
    return X, y
