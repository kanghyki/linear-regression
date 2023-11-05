#include "../inc/main.cpp"
#include <unistd.h>

std::vector<std::string> read_file(const std::string &file_name) {
  std::vector<std::string> ret;
  std::string line;
  std::ifstream file_in(file_name, std::ifstream::in);

  if (!file_in.is_open())
    throw std::invalid_argument("Could not open file.");
  while (!std::getline(file_in, line).eof())
    ret.push_back(line);
  file_in.close();

  return ret;
}

std::vector<std::string> split(std::string& s, std::string delim) {
  std::vector<std::string> ret;
  size_t pos = 0;
  int npos;

  if (delim.empty()) return ret;
  while (pos < s.length()) {
    npos = s.find(delim, pos);
    if (npos == -1) npos = s.length();
    if (npos - pos > 0) ret.push_back(s.substr(pos, npos - pos));
    pos = npos + delim.length();
  }

  return ret;
}

std::vector<std::pair<int, int>> to_data(std::vector<std::string>& file_data) {
  std::vector<std::pair<int, int>> data;

  for (size_t i = 1; i < file_data.size(); ++i) {
    std::string& line = file_data[i];
    std::vector<std::string> sp = split(line, ",");
    if (sp.size() != 2) continue;
    std::pair<int, int> tmp(atoi(sp[0].c_str()), atoi(sp[1].c_str()));
    data.push_back(tmp);
  }

  return data;
}

double hypothesis(double weight, double bias, double data) {
  return (data * weight) + bias;
}

double loss_fn(std::vector<std::pair<int, int>>& data, double weight, double bias) {
  double sum = 0;

  double h;
  for (const std::pair<int, int>& p: data) {
    h = hypothesis(weight, bias, p.first);
    sum += pow(h - p.second, 2);
  }
  sum /= data.size();

  return sum;
}


double pd_weight(std::vector<std::pair<int, int>>& data, double weight, double bias) {
  double sum = 0;

  for (const std::pair<int, int>& p: data) {
    sum += ((pow(p.first, 2)) * weight) + (p.first * bias) - (p.first * p.second);
  }
  sum *= 2;
  sum /= static_cast<double>(data.size());

  return sum;
}

double pd_bias(std::vector<std::pair<int, int>>& data, double weight, double bias) {
  double sum = 0;

  for (const std::pair<int, int>& p: data) {
    sum += (p.first * weight) - p.second + bias;
  }
  sum *= 2;
  sum /= static_cast<double>(data.size());

  return sum;
}

std::string print_var(double d) {
  std::string ret = "(";

  if (d >= 0) ret += '+';
  ret += std::to_string(d);
  ret += ')';

  return ret;
}

void print(double loss, double w_d, double b_d, double bias, double weight, double learning_rate) {
  std::cout.fill('-');
  std::cout << "+" << std::right << std::setw(40) << "" << "+" << "\n";
  std::cout.fill(' ');
  std::cout << "|"
    << std::setw(10) << std::right << "Loss: "
    << std::setw(30) << std::left << std::to_string(loss)
    << "|\n";
  std::cout << "|"
    << std::setw(10) << std::right << "Weight: "
    << std::setw(15) << std::left << weight
    << std::setw(15) << print_var(-1 * w_d * learning_rate)
    << "|\n";
  std::cout << "|"
    << std::setw(10) << std::right << "Bias: "
    << std::setw(15) << std::left << bias
    << std::setw(15) << print_var(-1 * b_d  * learning_rate)
    << "|\n";
  std::cout.fill('-');
  std::cout << "+" << std::right << std::setw(40) << "" << "+" << "\n";
  std::cout.fill(' ');
}

std::pair<double, double> gradient_descent(std::vector<std::pair<int, int>>& data, double learning_rate, int epoch) {
  double weight = 1, bias = 0, w_d, b_d, loss;

  std::cout.precision(7);
  //const double epsilon = 0.00000000001;
  for (int i = 0; i < epoch ; ++i) {
    loss = loss_fn(data, weight, bias);
    //if (std::fabs(loss - 0.0) < epsilon) break;
    w_d = pd_weight(data, weight, bias);
    weight -= (w_d * learning_rate);
    b_d = pd_bias(data, weight, bias);
    bias -= (b_d * learning_rate);
    //print(loss, w_d, b_d, bias, weight, learning_rate);
    //usleep(5000);
  }
  print(loss, w_d, b_d, bias, weight, learning_rate);

  return {weight, bias};
}

int main(int argc, char** argv) {
  if (argc < 2) {
    std::cerr << "Usage: " << argv[0] << " (csv-file-path)" << std::endl;
    return 0;
  }

  std::vector<std::string> file_data = read_file(argv[1]);
  std::vector<std::pair<int, int>> data = to_data(file_data);

  std::pair<double, double> ret = gradient_descent(data, 0.001, 100000);
  double weight = ret.first;
  double bias = ret.second;

  int n;
  while(1) {
    std::cout << "Input number: ";
    std::cin >> n;
    std::cout << hypothesis(weight, bias, n) << std::endl;
  }
}
