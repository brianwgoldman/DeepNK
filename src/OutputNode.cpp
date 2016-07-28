// Brian Goldman
#include "OutputNode.h"

void OutputNode::setup(const size_t position, const size_t N, const size_t K) {
  indexes.clear();
  indexes.resize(K+1);
  for (size_t i=0; i < K+1; i++) {
    indexes[i] = (position + i) % N;
  }
}

value_type OutputNode::score(const Matrix& inputs, const vector<size_t>& active, const vector<label_type>& labels) {
  vector<size_t> selected_indexes;
  vector<value_type> selected_weights;
  for (const auto i : active) {
    selected_indexes.push_back(indexes[i]);
    selected_weights.push_back(weights[i]);
  }
  auto output_column = inputs.build_column(selected_indexes, weights);
  // TODO Make this configurable / polymorphic
  return threshold_to_label_accuracy(output_column, labels, threshold, target);
}
