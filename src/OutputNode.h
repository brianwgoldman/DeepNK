// Brian Goldman
#ifndef OUTPUTNODE_H_
#define OUTPUTNODE_H_

#include "Matrix.h"

// This is a default OutputNode. I'll likely end up subclassing it to make it polymorphic
class OutputNode {
  vector<size_t> indexes;
  vector<value_type> weights;
 public:
  OutputNode(const size_t position=-1, const size_t n=-1, const size_t k=-1) {
    setup(position, n, k);
  }
  void setup(const size_t position, const size_t n, const size_t k);
  virtual ~OutputNode() = default;
  value_type score(const Matrix& inputs, const vector<size_t>& active, const vector<label_type>& labels);

};

#endif /* OUPUTNODE_H_ */
