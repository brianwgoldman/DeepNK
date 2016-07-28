// Brian Goldman
#ifndef QUALITYMEASURES_H_
#define QUALITYMEASURES_H_

#include "Utilities.h"

value_type threshold_to_label_accuracy(const vector<value_type>& output_column, const vector<label_type>& labels, const value_type threshold, const label_type target);

// Returns a 2x2 table where result[0][1] is False positives
vector<vector<size_t>> single_target_confusion_matrix(const vector<label_type>& estimated, const vector<label_type>& actual, const label_type target);
#endif /* QUALITYMEASURES_H_ */
