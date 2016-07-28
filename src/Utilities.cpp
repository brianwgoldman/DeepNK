// Brian Goldman
#include "Utilities.h"

vector<size_t> list_of_one_bits(size_t number) {
  vector<size_t> active;
  // Each loop increase i and strip a bit off of "number"
  // stop when number reaches 0
  for (size_t i = 0; number; i++, number >>= 1) {
    // If the lowest bit of "number" is set to one
    if (number & 1) {
      active.push_back(i);
    }
  }
  return active;
}
