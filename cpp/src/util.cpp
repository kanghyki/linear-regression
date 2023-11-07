#include "../inc/util.hpp"

std::map<std::string, std::vector<double>> FileReader::read_csv_d(const std::string file_name) {
  std::map<std::string, std::vector<double>> cvs_map;
  std::map<std::string, std::vector<double>>::iterator iter;
  std::vector<std::string> columns;
  std::vector<std::string> data;

  if (file_name.substr(file_name.find_last_of(".") + 1) != "csv") {
    throw std::invalid_argument("It is not csv file.");
  }
  this->read_file(file_name, data);
  if (data.size() == 0) return cvs_map;
  columns = this->split(data.front(), ",");
  for (const std::string& column: columns) {
    cvs_map.insert({column, std::vector<double>(0)});
  }
  for (size_t i = 1; i < data.size(); ++i) {
    std::vector<std::string> sp = this->split(data[i], ",");
    for (size_t j = 0; j < columns.size(); ++j) {
      if (j >= sp.size()) {
        throw std::invalid_argument("Bad csv file.");
      }
      else {
        cvs_map[columns[j]].push_back(std::stod(sp[j]));
      }
    }
  }

  return cvs_map;
}

void FileReader::read_file(const std::string &file_name, std::vector<std::string>& data) {
  std::string line;
  std::ifstream file_in(file_name, std::ifstream::in);

  if (!file_in.is_open()) {
    throw std::invalid_argument("Could not open file.");
  }
  while (!std::getline(file_in, line).eof()) {
    data.push_back(line);
  }
  file_in.close();
}

std::vector<std::string> FileReader::split(std::string& s, std::string delim) {
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

std::string& FileReader::ltrim(std::string &s) {
  std::string::iterator iter;

  iter = std::find_if(s.begin(), s.end(), [](char &c) {
      return !std::iswspace(c);
      });
  s.erase(s.begin(), iter);

  return s;
}

std::string& FileReader::rtrim(std::string &s) {
  std::string::reverse_iterator iter;

  iter = std::find_if(s.rbegin(), s.rend(), [](char &c) {
      return !std::iswspace(c);
      });
  s.erase(iter.base(), s.end());

  return s;
}

std::string& FileReader::trim(std::string &s) {
  this->rtrim(s);
  this->ltrim(s);

  return s;
}
