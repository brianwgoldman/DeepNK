// Brian Goldman
#ifndef DEEPNK_H_
#define DEEPNK_H_

#include "Matrix.h"
#include "Configuration.h"
#include "OutputNode.h"

const string nn_output_key = "nn_out";

class DeepNK {
  // TODO Consider making the nk_table a non-member;
  // just something that gets handed around.
  Matrix nk_table;
  vector<OutputNode> outputs;
  size_t K=0;
  size_t N=0;
  vector<bool> selected_inputs;
  value_type estimated_quality=0;
  vector<value_type> output_scores;
 public:
  DeepNK(const Configuration& config, Random& random);
  virtual ~DeepNK() = default;
  void build_nk_table(const Matrix& inputs, const vector<label_type>& labels);
  // Find the best bitstring and record which entries in the table
  // were chosen, and how good they were
  void find_optimum_nk();
  // Inform each output node what configuration they are using
  // and build ensemble
  void configure_outputs();
  void write_as_NN(Configuration& config);
  vector<label_type> classify(const Matrix& inputs);
};

#endif /* DEEPNK_H_ */
