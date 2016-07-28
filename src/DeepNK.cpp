// Brian Goldman
#include "DeepNK.h"

void DeepNK::build_nk_table(Configuration& config, const Matrix& inputs,
                            const vector<label_type>& labels) {
  // Each output node depends on exactly "K+1" columns from "inputs".
  const size_t K = config.get<size_t>("K");
  const size_t patterns = 2 << K;
  const size_t N = inputs.cols();
  nk_table.resize(N, patterns);

  for (size_t o = 0; o < N; o++) {
    for (size_t i = 0; i < patterns; i++) {
      // Creates the indexes relative to this node
      // TODO Consider building all of the patterns once instead of N times
      auto relative_indexes = list_of_one_bits(i);
      // Finds how good this pattern is for that output
      nk_table.value(o, i) = outputs[o].score(inputs, relative_indexes, labels);
    }
  }
}

void DeepNK::find_optimum_nk() {
  // TODO Copy over existing C++ code and augment it using Francisco's code
  assert(false);
}

void DeepNK::configure_outputs() {
  // TODO Finish implementing this
  assert(false);
}

void DeepNK::write_as_NN(Configuration& config) {
  if (not config.has(nn_output_key)) {
    return;
  }
  string filename = config.get<string>(nn_output_key);
  if (filename == "none") {
    return;
  }
  // TODO Finish implementing this
  assert(false);
}

vector<label_type> DeepNK::classify(const Matrix& inputs) {
  // TODO Finish implementing this
  assert(false);
}
