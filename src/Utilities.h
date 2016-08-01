// Brian Goldman
#ifndef UTILITIES_H_
#define UTILITIES_H_
#include <string>
using std::string;
#include <vector>
using std::vector;
using std::size_t;
#include <cassert>
#include <random>

using value_type=float;
// TODO This is basically a stub until I know what the labels look like
using label_type=string;
const label_type NO_CLASS = "NA";

using Random=std::mt19937;

// Return the list of bits set to 1 in "number"
vector<size_t> list_of_one_bits(size_t number);

// Converts values to sum to one
void scale_to_one(vector<value_type>& values);

// These two functions should behave identically. Both are methods to generate
// random numbers between 0 and 1 that sum to 1.
vector<value_type> random_log_weights(const size_t N, Random& random);
vector<value_type> random_exp_weights(const size_t N, Random& random);

#endif /* UTILITIES_H_ */
