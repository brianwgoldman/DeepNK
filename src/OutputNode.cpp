// Brian Goldman
#include "OutputNode.h"

void OutputNode::setup(const Configuration& config, const size_t position, const size_t N, const size_t K, Random& random) {
  target = config.get<label_type>("target_label");
  threshold = config.get<value_type>("fire_threshold");
  indexes.clear();
  indexes.resize(K+1);
  for (size_t i=0; i < K+1; i++) {
    indexes[i] = (position + i) % N;
  }
  weights = random_log_weights(K+1, random);
}

value_type OutputNode::score(const Matrix& inputs, const vector<size_t>& active, const vector<label_type>& labels) {
  vector<size_t> selected_indexes;
  vector<value_type> selected_weights;
  for (const auto i : active) {
    selected_indexes.push_back(indexes[i]);
    selected_weights.push_back(weights[i]);
  }
  // Rescale the weights to sum to 1
  scale_to_one(selected_weights);
  auto output_column = inputs.build_column(selected_indexes, selected_weights);
  // TODO Make this configurable / polymorphic
  return threshold_to_label_accuracy(output_column, labels, threshold, target);
}

vector<label_type> OutputNode::test(const Matrix& inputs) const {
  auto output_column = inputs.build_column(indexes, weights);
  vector<label_type> labels(output_column.size());
  for (size_t row=0; row < output_column.size(); row++) {
    if (output_column[row] > threshold) {
      labels[row] = target;
    } else {
      labels[row] = NO_CLASS;
    }
  }
  return labels;
}

void OutputNode::configure(const vector<size_t>& active) {
  vector<size_t> new_indexes;
  vector<value_type> new_weights;
  for (const auto i : active) {
    new_indexes.push_back(indexes[i]);
    new_weights.push_back(weights[i]);
  }
  scale_to_one(new_weights);
  swap(new_indexes, indexes);
  swap(new_weights, weights);
}
