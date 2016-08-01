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

using Random=std::mt19937;

// Return the list of bits set to 1 in "number"
vector<size_t> list_of_one_bits(size_t number);


#endif /* UTILITIES_H_ */
