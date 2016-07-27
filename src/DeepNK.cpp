// Brian Goldman
#include "DeepNK.h"

vector<size_t> number_to_active(size_t number) {
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

value_type build_nk_entry(Configuration& config, const Matrix& inputs,
                          const vector<value_type>& labels,
                          const vector<size_t>& indexes,
                          const vector<value_type>& weights) {
  assert(indexes.size() == weights.size());
  auto column = inputs.build_column(indexes, weights);
  value_type result;
  return result;
}

void DeepNK::build_nk_table(Configuration& config, const Matrix& inputs,
                            const vector<value_type>& labels, Matrix& weights) {
  // Each output node depends on exactly "K+1" columns from "inputs".
  const size_t K = config.get<size_t>("K");
  const size_t patterns = 2 << K;
  const size_t N = inputs.cols();
  nk_table.resize(N, patterns);

  for (size_t i = 0; i < patterns; i++) {
    // Creates the indexes relative to this node
    auto relative_indexes = number_to_active(i);
    // Create a version of the indexes in the global positions.
    auto absolute_indexes = relative_indexes;
    for (auto& index : absolute_indexes) {
      index += (N + index) % N;
    }
    // TODO Allow for weights to be set using regression

  }
}
