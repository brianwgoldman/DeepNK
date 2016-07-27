// Brian Goldman

#include <iostream>
using namespace std;
#include "Configuration.h"

int main(int argc, char * argv[]) {
  Configuration config;
  config.parse(argc, argv);
  config.dump();
  return 0;
}
