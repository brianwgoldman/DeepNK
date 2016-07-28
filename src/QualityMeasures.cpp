// Brian Goldman
#include "QualityMeasures.h"

value_type threshold_to_label_accuracy(const vector<value_type>& output_column, const vector<label_type>& labels, const value_type threshold, const label_type target) {
  assert(output_column.size() == labels.size());
  size_t correct=0;
  for (size_t r=0; r < output_column.size(); r++) {
    bool estimated = output_column[r] > threshold;
    bool actual = labels[r] == target;
    correct += estimated == actual;
  }
  return static_cast<value_type>(correct) / labels.size();
}
