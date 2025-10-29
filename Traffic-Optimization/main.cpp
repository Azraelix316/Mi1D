#include "lib.hpp"
#include <chrono>
#include <iostream>
#include <numeric>
#include <ostream>
#include <vector>
std::vector<std::vector<double>> makeIdentity(int n) {
  std::vector<std::vector<double>> I(n, std::vector<double>(n, 0.0));
  for (int i = 0; i < n; ++i)
    I[i][i] = 1.0;
  return I;
}
std::vector<std::vector<double>>
addMatrices(const std::vector<std::vector<double>> &A,
            const std::vector<std::vector<double>> &B) {
  int n = A.size(), m = A[0].size();
  std::vector<std::vector<double>> R(m, std::vector<double>(n));
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      R[i][j] = A[i][j] + B[i][j];
    }
  }
  return R;
}
std::vector<std::vector<double>>
multiplyScalar(const std::vector<std::vector<double>> &M, double scalar) {
  int n = M.size(), m = M[0].size();
  std::vector<std::vector<double>> R(n, std::vector<double>(m));
  for (int i = 0; i < n; ++i)
    for (int j = 0; j < m; ++j)
      R[i][j] = M[i][j] * scalar;
  return R;
}
int main() {
  std::vector<std::vector<double>> transition_matrix;
  std::vector<double> state = {50, 50, 0};
  std::vector<double> capacity = {30, 50, 20};
  double alpha = 0.9;
  int n = capacity.size();
  std::vector<double> vec(n);
  std::vector<std::vector<double>> ones;
  for (int i = 0; i < n; i++) {
    ones.push_back({1});
  }
  // Step 1: normalize capacity to get π
  double sum = std::accumulate(capacity.begin(), capacity.end(), 0.0);
  std::vector<std::vector<double>> pi;
  for (int i = 0; i < n; ++i)
    capacity[i] = capacity[i] / sum;
  pi.push_back(capacity);
  auto I = makeIdentity(n);
  dscilib::transpose(pi);
  dscilib::transpose(ones);
  std::vector<std::vector<double>> input1 = multiplyScalar(I, alpha);
  std::vector<std::vector<double>> input2 =
      multiplyScalar(dscilib::matrix_mult(pi, ones), 1 - alpha);
  transition_matrix = addMatrices(input1, input2);
  dscilib::detail::printArr(pi);
  dscilib::detail::printArr(transition_matrix);
  for (int i = 0; i < 100; i++) {
    state = dscilib::matrix_vec_mult(transition_matrix, state);
    dscilib::detail::printVec(state);
  }
}
