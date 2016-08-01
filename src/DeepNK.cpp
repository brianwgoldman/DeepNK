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
  const size_t K_plus_1_bits = (1 << (K + 1)) - 1;
  const size_t powk = 1 << K;
  // These are used to build and store the functions created
  // by removing a bit.
  vector<float> previous_function(patterns, 0);
  vector<float> next_function(patterns, 0);
  // Records how the removed bit should be set given its dependencies
  vector<vector<char>> best_bit_choice(N, vector<char>(patterns));
  const char TIE = 2;
  // Creates a function to mimic all NK functions that wrap
  for (size_t i = 0; i < K; i++) {
    // Used to strip off bits not used by this function
    const size_t f = N - K + i;
    for (size_t pattern = 0; pattern < patterns; pattern++) {
      // Leaves only the k+1 bits used by this function
      size_t relevant_bits = (pattern >> i) & K_plus_1_bits;
      previous_function[pattern] += nk_table.value(f, relevant_bits);
    }
  }

  // "n" is the bit position we are currently trying to remove.
  // You could also say at the end of this loop the problem size will be n.
  for (size_t n = N - 1; n >= dependencies; n--) {
    for (size_t before_wrap = 0; before_wrap < powk; before_wrap++) {
      for (size_t after_wrap = 0; after_wrap < powk; after_wrap++) {
        // quality of setting bit "n" to zero and one.
        float zero_quality = 0, one_quality = 0;
        // The pattern the dependent bits take
        const size_t zero_pattern = before_wrap | (after_wrap << (K + 1));
        const size_t one_pattern = zero_pattern | powk;
        // bit "n" only depends on two functions at this point:
        // NK function_{n-k} which uses the first K+1 bits and the "previous_function"
        zero_quality += nk_table.value(n - K, zero_pattern & K_plus_1_bits);
        one_quality += nk_table.value(n - K, one_pattern & K_plus_1_bits);
        // previous_function doesn't use the lowest index bit
        zero_quality += previous_function[zero_pattern >> 1];
        one_quality += previous_function[one_pattern >> 1];
        // put the results into "next_function"
        const size_t next_function_entry = before_wrap | (after_wrap << K);
        if (zero_quality > one_quality) {
          // Zero was better
          next_function[next_function_entry] = zero_quality;
          best_bit_choice[n][next_function_entry] = 0;
        } else if (zero_quality == one_quality) {
          // tie
          next_function[next_function_entry] = zero_quality;
          best_bit_choice[n][next_function_entry] = TIE;
          std::cout << "A tie happened" << std::endl;
        } else {
          // One was better
          next_function[next_function_entry] = one_quality;
          best_bit_choice[n][next_function_entry] = 1;
        }
      }
    }
    previous_function.swap(next_function);
  }

  // previous_function is now wide enough to score all remaining patterns
  // so we can just copy in the remaining NK functions
  for (size_t f = 0; f < K; f++) {
    // Used to strip off bits not used by this function
    for (size_t before_wrap = 0; before_wrap < powk; before_wrap++) {
      for (size_t after_wrap = 0; after_wrap < powk; after_wrap++) {
        const size_t previous_function_pattern = before_wrap | (after_wrap << K);
        const size_t in_order = after_wrap | (before_wrap << K);
        const size_t in_use = (in_order >> f) & K_plus_1_bits;
        previous_function[previous_function_pattern] += nk_table.value(f, in_use);
      }
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
  const size_t k_bits = (1 << K) - 1;
  size_t after_wrap = best_pattern >> K;
  size_t before_wrap = best_pattern & k_bits;
  // First "dependencies" bits comes from "best_pattern"
  const size_t dependency_pattern = after_wrap | (before_wrap << K);
  for (size_t i = 0; i < dependencies; i++) {
    selected_inputs[i] = (dependency_pattern >> i) & 1;
  }
  // Use the previous "left" and "right" to recover the way to set bit i
  for (size_t i = dependencies; i < N; i++) {
    auto best_bit = best_bit_choice[i][before_wrap | (after_wrap << K)];
    if (best_bit == TIE) {
      // TODO Handle this better
      best_bit = 0;
    }
    selected_inputs[i] = best_bit;
    // shift out old bit information, add in new bit
    before_wrap = (before_wrap >> 1) | (best_bit << (K-1));
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
