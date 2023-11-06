#include "../inc/training.hpp"

int main(int argc, char** argv) {
  if (argc != 4) {
    std::cerr << "Usage: " << argv[0] << " (csv-file-path) (x_column) (y_column)" << std::endl;
    return 0;
  }

  std::vector<std::pair<int, int>> data;
  try {
    std::map<std::string, std::vector<double>> data_map;
    data_map = FileReader().read_csv_d(argv[1]);
    if (data_map.find(argv[2]) == data_map.end() || data_map.find(argv[3]) == data_map.end()) {
      std::cerr << "Column not exist." << std::endl;
      return 0;
    }
    std::vector<double>& x = data_map[argv[2]];
    std::vector<double>& y = data_map[argv[3]];
    for (size_t i = 0; i < x.size(); ++i)
      data.push_back({x[i], y[i]});
  } catch (std::exception& e) {
    std::cerr << e.what() << std::endl;
    return 0;
  }

  std::pair<double, double> ret = gradient_descent(data, 0.001, 100000);
  double weight = ret.first;
  double bias = ret.second;

  std::string filename = "result.csv";
  std::ofstream file_out(filename, std::ofstream::out | std::ofstream::trunc);
  if (!file_out.good()) std::cerr << "File written error occured\n";
  file_out << "weight, bias\n";
  file_out << weight << "," << bias << "\n";
  file_out.close();

  return 0;
}

double hypothesis(double weight, double bias, double data) {
  return (data * weight) + bias;
}

double loss_fn(std::vector<std::pair<int, int>>& data, double weight, double bias) {
  double sum = 0;

  for (const std::pair<int, int>& p: data)
    sum += pow(hypothesis(weight, bias, p.first) - p.second, 2);
  sum /= data.size();

  return sum;
}


double pd_weight(std::vector<std::pair<int, int>>& data, double weight, double bias) {
  double sum = 0;

  for (const std::pair<int, int>& p: data)
    sum += ((pow(p.first, 2)) * weight) + (p.first * bias) - (p.first * p.second);
  sum *= 2;
  sum /= static_cast<double>(data.size());

  return sum;
}

double pd_bias(std::vector<std::pair<int, int>>& data, double weight, double bias) {
  double sum = 0;

  for (const std::pair<int, int>& p: data)
    sum += (p.first * weight) - p.second + bias;
  sum *= 2;
  sum /= static_cast<double>(data.size());

  return sum;
}

std::pair<double, double> gradient_descent(std::vector<std::pair<int, int>>& data, double learning_rate, int epoch) {
  double weight = 1, bias = 0;

  //const double epsilon = 0.00000000001;
  for (int i = 0; i < epoch ; ++i) {
    //loss = loss_fn(data, weight, bias);
    //if (std::fabs(loss - 0.0) < epsilon) break;
    weight -= pd_weight(data, weight, bias) * learning_rate;
    bias -= pd_bias(data, weight, bias) * learning_rate;
  }
  std::cout << "Loss: " << loss_fn(data, weight, bias) << std::endl;
  std::cout << "Weight: " << weight << std::endl;
  std::cout << "Bias: " << bias << std::endl;

  return {weight, bias};
}
