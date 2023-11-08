import csv

class model:
    def __init__(self):
        self.weight = 0.0
        self.bias = 0.0
        self.x = []
        self.y = []

    def read_data_from_csv(self, file_name):
        with open(file_name, "r") as csvfile:
            reader = csv.reader(csvfile, delimiter=',')
            next(reader)
            for row in reader:
                self.x.append(float(row[0]))
                self.y.append(float(row[1]))

    def read_model_from_csv(self, file_name):
        with open(file_name, "r") as csvfile:
            reader = csv.reader(csvfile, delimiter=',')
            next(reader)
            for row in reader:
                self.weight = float(row[0])
                self.bias = float(row[1])

    def estimate(self, x):
        normalized_x = (x - min(self.x)) / (max(self.x) - min(self.x))
        normalized_y = (normalized_x * self.weight) + self.bias
        ret = normalized_y * (max(self.y) - min(self.y)) + min(self.y)
        return ret

try:
    model = model()
    model.read_data_from_csv("data.csv")
    model.read_model_from_csv("model.csv")
    while True:
        x = float(input("x: "))
        estimated = model.estimate(x)
        print("y:", estimated)

except Exception as e:
    print("An error occurred.")
    print(e)
