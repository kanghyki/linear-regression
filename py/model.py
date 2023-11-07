class Model:
    def __init__(self):
        self.weight = 1.0
        self.bias = 0.0

    def read_model_from_csv(self, file_name):
        file = open(file_name, 'r')
        lines = file.readlines()
        file.close()
        temp = lines[0][:-1].split(',')
        self.weight = float(temp[0])
        self.bias = float(temp[1])

    def estimate(self, x):
        return (x * self.weight) + self.bias

try:
    model = Model()
    file_path = input("model csv file: ")
    model.read_model_from_csv(file_path)
    while True:
        x = float(input("x: "))
        print(model.estimate(x))
except:
    print("something went wrong.")
    exit(1)
