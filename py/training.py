import numpy as np
from matplotlib import pyplot as plt

class linear_regression:
    def __init__(self):
        self.weight = 1.0
        self.bias = 0.0
        self.mse = 0.0
        self.learning_rate = 1.0
        self.datas = []

    def read_data_from_csv(self, file_name):
        file = open(file_name, 'r')
        lines = file.readlines()
        file.close()
        for i in lines[1:]:
            temp = i[:-1].split(',')
            for idx in range(len(temp)):
                if type (temp[idx]) != float:
                    temp[idx] = float(temp[idx])
            self.datas.append(temp)

    def save_model_to_csv(self, file_name):
        file = open(file_name, 'w')
        line = "%f,%f\n" % (self.weight, self.bias)
        file.write(line)
        file.close()

    def show_graph(self):
        x = np.array(self.datas).T[0]
        y = np.array(self.datas).T[1]
        plt.xlabel("X")
        plt.ylabel("Y")
        plt.scatter(x, y)
        plt.plot(x, (self.weight * x) + self.bias)
        plt.show()

    def training(self, learning_rate, epoch):
        self.learning_rate = learning_rate

        for _ in range(epoch):
            self.weight -= self.sigma(self.pd_weight) * self.learning_rate / len(self.datas)
            self.bias -= self.sigma(self.pd_bias) * self.learning_rate / len(self.datas)
        self.mse = self.sigma(self.mean_sqaured_error)

    def hypothesis(self, x):
        return (x * self.weight) + self.bias

    def sigma(self, fn):
        sum = 0.0
        for data in self.datas:
            sum += fn(data[0], data[1])
        return sum

    def mean_sqaured_error(self, x, y):
        return (self.hypothesis(x) - y) ** 2

    def pd_weight(self, x, y):
        return (((x ** 2) * self.weight) + (x * self.bias) - (x * y)) * 2

    def pd_bias(self, x, y):
        return ((x * self.weight) - y + self.bias) * 2

    def get_weight(self):
        return self.weight

    def get_bias(self):
        return self.bias

    def get_mse(self):
        return self.mse

    def get_precision(self):
        sum = 0
        for data in self.datas:
            estimated = round(self.hypothesis(data[0]))
            actual = round(data[1])
            sum += (estimated == actual)
        return "%s%%" % (sum / (len(self.datas)) * 100)

try:
    lr = linear_regression()
    file_path = input("data csv file: ")
    lr.read_data_from_csv(file_path)
    print("done.")
    learning_rate = float(input("learning_rate: "))
    epoch = int(input("epoch: "))
    lr.training(learning_rate, epoch)
    lr.save_model_to_csv("model.csv")
    print("done.")
    print(lr.get_precision())
    lr.show_graph()
except:
    print("something went wrong.")
    exit(1)
