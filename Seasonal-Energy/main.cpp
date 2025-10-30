#include "lib.hpp"
#include <fstream>
#include <ios>
#include <vector>
int main() {
  double alpha = 0.8;
  double beta = 0.1;
  double gamma = 0.3;
  double m = 12;
  std::vector<std::vector<double>> data =
      dscilib::read_csv_double("MES_0725.csv");
  std::vector<double> predicted;
  std::vector<double> level;
  double current = 0;
  std::vector<double> trend;
  std::vector<double> seasonal = {0.0};
  level.push_back(data[0][0]);
  trend.push_back(data[1][0] - data[0][0]);
  for (int i = 1; i < data.size(); i++) {
    current = data[i][0];
    level.push_back(alpha * current + (1 - alpha) * (level[i - 1]));
    trend.push_back(beta * (level[i] - level[i - 1]) +
                    (1 - beta) * trend[i - 1]);
    if (i >= m) {
      seasonal.push_back(gamma * (current - level[i]) +
                         (1 - gamma) * seasonal[i - m]);
    } else {
      seasonal.push_back(gamma * (current - level[i]));
    }
    std::cout << level[i] << "  " << trend[i] << "  " << seasonal[i]
              << std::endl;
    predicted.push_back(level[i] + trend[i] + seasonal[i - m]);
  }
  for (int i = data.size(); i < data.size() + 24; i++) {
    predicted.push_back(level.back() + trend[i - 24] + seasonal[i - 24]);
  }
  std::fstream fout;
  fout.open("results.csv", std::ios::out);
  for (int i = 0; i < predicted.size(); i++) {
    std::cout << predicted[i] << std::endl;
    fout << predicted[i] << "\n";
  }
}
