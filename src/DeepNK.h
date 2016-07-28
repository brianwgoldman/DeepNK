// Brian Goldman
#ifndef DEEPNK_H_
#define DEEPNK_H_

#include "Matrix.h"
#include "Configuration.h"
#include "OutputNode.h"

class DeepNK {
  Matrix nk_table;
  vector<OutputNode> outputs;
 public:
  DeepNK() = default;
  virtual ~DeepNK() = default;
  void build_nk_table(Configuration& config, const Matrix& inputs,
                      const vector<label_type>& labels);
};

#endif /* DEEPNK_H_ */
