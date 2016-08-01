// Brian Goldman
#include "Utilities.h"

vector<size_t> list_of_one_bits(size_t number) {
  vector<size_t> active;
  // Each loop increase i and strip a bit off of "number"
  // stop when number reaches 0
  for (size_t i = 0; number; i++, number >>= 1) {
    // If the lowest bit of "number" is set to one
    if (number & 1) {
      active.push_back(i);
    }
  }
  return active;
}

void scale_to_one(vector<value_type>& values) {
  value_type sum = 0;
  for (const auto value : values) {
    sum += value;
  }
  for (auto & value : values) {
    value /= sum;
  }
}

vector<value_type> random_log_weights(const size_t N, Random& random) {
  vector<value_type> result(N);
  std::uniform_real_distribution<value_type> dist(0, 1);
  for (size_t i=0; i < N; i++) {
    result[i] = -log2(dist(random));
  }
  scale_to_one(result);
  return result;
}

vector<value_type> random_exp_weights(const size_t N, Random& random) {
  vector<value_type> result(N);
  std::exponential_distribution<value_type> dist(1);
  for (size_t i=0; i < N; i++) {
   result[i] = dist(random);
  }
  scale_to_one(result);
  return result;
}
