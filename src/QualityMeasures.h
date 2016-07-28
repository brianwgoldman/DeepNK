// Brian Goldman
#ifndef QUALITYMEASURES_H_
#define QUALITYMEASURES_H_

#include "Utilities.h"

value_type threshold_to_label_accuracy(const vector<value_type>& output_column, const vector<label_type>& labels, const value_type threshold, const label_type target);

#endif /* QUALITYMEASURES_H_ */
