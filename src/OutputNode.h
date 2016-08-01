// Brian Goldman
#ifndef OUTPUTNODE_H_
#define OUTPUTNODE_H_


#include "Configuration.h"
#include "Matrix.h"
#include "QualityMeasures.h"

// This is a default OutputNode. I'll likely end up subclassing it to make it polymorphic
class OutputNode {
  vector<size_t> indexes;
  vector<value_type> weights;
  label_type target;
  value_type threshold;
 public:
  OutputNode() = default;
  void setup(const Configuration& config, const size_t position, const size_t n, const size_t k, Random& random);
  virtual ~OutputNode() = default;
  value_type score(const Matrix& inputs, const vector<size_t>& active, const vector<label_type>& labels);
  void configure(const vector<size_t>& active);
  vector<label_type> test(const Matrix& inputs) const;

};

#endif /* OUPUTNODE_H_ */
