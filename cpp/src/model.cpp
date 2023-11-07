#include "../inc/model.hpp"

double weight, bias;

double estimatePrice(unsigned long long n) {
  return bias + (weight * n);
}

int main(int argc, char** argv) {
  std::map<std::string, std::vector<double>> data_map;
  std::map<std::string, std::vector<double>>::iterator weight_iter;
  std::map<std::string, std::vector<double>>::iterator bias_iter;
  std::string line;

  if (argc < 2) {
    std::cerr << "Usage: " << argv[0] << " (model-cvs-file-path)" << std::endl;
    return 0;
  }

  try {
    data_map = FileReader().read_csv_d(argv[1]);
    weight_iter = data_map.find("weight");
    bias_iter = data_map.find("bias");
    if (weight_iter == data_map.end() || bias_iter == data_map.end()
        || weight_iter->second.size() != 1 || bias_iter->second.size() != 1) {
      std::cerr << "Model data is wrong." << std::endl;
      return 0;
    }
    weight = weight_iter->second[0];
    bias = bias_iter->second[0];
  } catch (std::exception& e) {
    std::cerr << e.what() << std::endl;
    return 0;
  }

  for (std::cout << "prompt: "; std::getline(std::cin, line).eof() == false; std::cout << "prompt: ") {
    if (std::find_if(line.begin(), line.end(),
          [](const char& c)->bool{ return !std::isdigit(c); }) != line.end()) {
      std::cout << "Not positive integer." << std::endl;
      continue;
    }
    if (line.length() > 10) {
      std::cout << "out of range. (0 <= n < 10^11)" << std::endl;
      continue;
    }
    std::cout << "price: " << std::to_string(estimatePrice(std::atoll(line.c_str()))) << std::endl;
  }

  return 0;
}
