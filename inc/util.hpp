#ifndef UTIL_HPP
#define UTIL_HPP

#include <fstream>
#include <string>
#include <vector>
#include <map>


class FileReader {
  private:
    std::string& ltrim(std::string &s);
    std::string& rtrim(std::string &s);
    std::string& trim(std::string &s);
    std::vector<std::string> split(std::string& s, std::string delim);
    void read_file(const std::string &file_name, std::vector<std::string>& data);

  protected:

  public:
    std::map<std::string, std::vector<double>> read_csv_d(const std::string file_name);
};

#endif
