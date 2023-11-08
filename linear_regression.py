import sys
import csv
import numpy as np
from matplotlib import pyplot as plt

class linear_regression:
    def __init__(self):
        self.weight = 0.0
        self.bias = 0.0
        self.learning_rate = 0.01
        self.epoch = 1000
        self.m = 0
        self.x = []
        self.y = []

    def read_data_from_csv(self, file_name):
        with open(file_name, "r") as csvfile:
            reader = csv.reader(csvfile, delimiter=',')
            next(reader)
            for row in reader:
                self.x.append(float(row[0]))
                self.y.append(float(row[1]))
                self.m += 1

    def save_model_to_csv(self, file_name):
        with open(file_name, "w") as csvfile:
            writer = csv.writer(csvfile, delimiter=',')
            writer.writerow(["weight", "bias"])
            writer.writerow([self.weight, self.bias])

    def normalize_data(self, data):
        min_d = min(data)
        max_d = max(data)
        ret = []
        for d in data:
            ret.append((d - min_d) / (max_d - min_d))
        return ret

    def train_model(self):
        x = self.normalize_data(self.x)
        y = self.normalize_data(self.y)

        for _ in range(self.epoch):
            tmp_weight = (self.sigma(self.diff_weight, x, y) * self.learning_rate / self.m)
            self.bias -= (self.sigma(self.diff_bias, x, y) * self.learning_rate / self.m)
            self.weight -= tmp_weight

    def sigma(self, fn, x, y):
        sum = 0.0
        for i in range(self.m):
            sum += fn(x[i], y[i])
        return sum

    def hypothesis(self, x):
        return (x * self.weight) + self.bias

    def diff_weight(self, x, y):
        return (self.hypothesis(x) - y) * x

    def diff_bias(self, x, y):
        return (self.hypothesis(x) - y)

    def show_graph(self):
        plt.xlabel("X axis (variable)")
        plt.ylabel("Y axis (result)")
        plt.title("linear_regression")
        plt.scatter(self.x, self.y, label="data")
        min_y = min(self.y)
        max_y = max(self.y)
        line_x = [min(self.x), max(self.x)]
        line_y = [self.bias * (max_y - min_y) + min_y, (self.weight + self.bias) * (max_y - min_y) + min_y]
        plt.plot(line_x, line_y, 'r', label="model")
        plt.grid(True)
        plt.legend()
        plt.show()

try:
    lr = linear_regression()
    lr.read_data_from_csv("test.csv")
    lr.epoch = 10000
    lr.learning_rate = 0.01
    lr.train_model()
    lr.save_model_to_csv("model.csv")
    if len(sys.argv) > 1 and (sys.argv[1] == "-v" or sys.argv[1] == "--visual"):
        lr.show_graph()
except Exception as e:
    print("An error occurred.")
    print(e)