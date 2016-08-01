// Brian Goldman
#include "DeepNK.h"

void DeepNK::build_nk_table(Configuration& config, const Matrix& inputs,
                            const vector<label_type>& labels) {
  // Each output node depends on exactly "K+1" columns from "inputs".
  N = inputs.cols();
  K = config.get<size_t>("K");
  assert(N == outputs.size());
  const size_t patterns = 2 << K;
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
  assert(nk_table.cols() == (static_cast<size_t>(2) << K));
  assert(nk_table.rows() == N);
  assert(K > 0);
  const size_t dependencies = 2 * K;
  assert(N >= dependencies);
  const size_t patterns = 1 << dependencies;
  const size_t function_mask = (1 << (K + 1)) - 1;
  // These are used to build and store the functions created
  // by removing a bit.
  vector<float> previous_function(patterns, 0);
  vector<float> next_function(patterns, 0);
  // Records how the removed bit should be set given its dependencies
  vector<vector<char>> best_bit_choice(N, vector<char>(patterns));
  const char TIE = 2;
  // Creates a function to mimic all NK functions that wrap
  for (size_t f = N - K; f < N; f++) {
    // Used to strip off bits not used by this function
    const size_t shift_size = N - f - 1;
    for (size_t pattern = 0; pattern < patterns; pattern++) {
      // Leaves only the k+1 bits used by this function
      size_t relevant_bits = (pattern >> shift_size) & function_mask;
      previous_function[pattern] += nk_table.value(f, relevant_bits);
    }
  }
  const size_t powk = 1 << K;
  const size_t created_function_mask = (1 << dependencies) - 1;
  // "n" is the bit position we are currently trying to remove.
  // You could also say at the end of this loop the problem size will be n.
  for (size_t n = N - 1; n >= dependencies; n--) {
    for (size_t left = 0; left < powk; left++) {
      for (size_t right = 0; right < powk; right++) {
        // quality of setting bit "n" to zero and one.
        float zero_quality = 0, one_quality = 0;
        // The pattern the dependent bits take
        const size_t zero_pattern = (left << (K + 1)) | right;
        const size_t one_pattern = zero_pattern | powk;
        // bit "n" only depends on two functions at this point:
        // NK function_{n-k} and the "previous_function"
        zero_quality += nk_table.value(n - K, zero_pattern >> K);
        one_quality += nk_table.value(n - K, one_pattern >> K);
        zero_quality += previous_function[zero_pattern & created_function_mask];
        one_quality += previous_function[one_pattern & created_function_mask];
        // put the results into "next_function"
        const size_t hammer_pattern = (left << K) | right;
        if (zero_quality > one_quality) {
          // Zero was better
          next_function[hammer_pattern] = zero_quality;
          best_bit_choice[n][hammer_pattern] = 0;
        } else if (zero_quality == one_quality) {
          // tie
          next_function[hammer_pattern] = zero_quality;
          best_bit_choice[n][hammer_pattern] = TIE;
          std::cout << "A tie happened" << std::endl;
        } else {
          // One was better
          next_function[hammer_pattern] = one_quality;
          best_bit_choice[n][hammer_pattern] = 1;
        }
      }
    }
    previous_function.swap(next_function);
  }

  // previous_function is now wide enough to score all remaining patterns
  // so we can just copy in the remaining NK functions
  const size_t k_bits = (1 << K) - 1;
  for (size_t f = 0; f < K; f++) {
    // Used to strip off bits not used by this function
    size_t shift_size = K - f - 1;
    for (size_t pattern = 0; pattern < patterns; pattern++) {
      // Leaves only the k+1 bits used by this function
      size_t relevant_bits = (pattern >> shift_size) & function_mask;
      // TODO Simplify this, perhaps with 2 loops
      // The handedness of this flips
      size_t previous_function_pattern = ((pattern >> K) & k_bits) |
          ((pattern & k_bits) << K);
      previous_function[previous_function_pattern] += nk_table.value(f, relevant_bits);
    }
  }

  // Whichever previous_function entry has the highest quality
  // is the true best pattern
  size_t best_pattern = 0;
  for (size_t pattern=0; pattern < patterns; pattern++) {
    if (previous_function[pattern] > previous_function[best_pattern]) {
      // TODO Probably need a list of patterns to deal with ties
      best_pattern = pattern;
    }
  }
  // Extract a global optimum
  selected_inputs.resize(N);
  size_t left = best_pattern >> K;
  size_t right = best_pattern & k_bits;
  // First "dependencies" bits comes from "best_pattern", but flipped
  const size_t dependency_pattern = right << K | left;
  for (size_t i = 0; i < dependencies; i++) {
    selected_inputs[i] = (dependency_pattern >> (dependencies - i - 1)) & 1;
  }
  // Use the previous "left" and "right" to recover the way to set bit i
  for (size_t i = dependencies; i < N; i++) {
    auto best_bit = best_bit_choice[i][left << K | right];
    if (best_bit == TIE) {
      // TODO Handle this better
      best_bit = 0;
    }
    selected_inputs[i] = best_bit;
    // shift out old bit information, add in new bit
    left = ((left << 1) & k_bits) | best_bit;
  }
  estimated_quality = previous_function[best_pattern];
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
