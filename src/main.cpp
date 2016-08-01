// Brian Goldman

#include <iostream>
#include "Configuration.h"
#include "Matrix.h"
#include "DeepNK.h"
#include "QualityMeasures.h"

using std::cout;
using std::endl;

// TODO Include timing and logging.
int main(int argc, char * argv[]) {
  // Parse and (if configured to) save complete configuration
  Configuration config;
  config.parse(argc, argv);
  string training_file = config.get<string>("training_input");
  string testing_file = config.get<string>("testing_input");
  Random random;
  int seed = config.get<int>("seed");
  if (seed == -1) {
    std::random_device rd;
    seed = rd();
    config.set("seed", seed);
  }
  random.seed(seed);

  config.dump();

  // Read in CSV file encoding the training data
  Matrix inputs;
  vector<label_type> labels;
  load_csv(training_file, inputs, labels);

  // TODO any preprocessing you want to do on the data,
  // e.g. introduction of another layer
  // Note if you do add a layer, you'll need to write it to a file.

  // Construct a DeepNK classifier
  DeepNK nk_classifier(config, random);
  nk_classifier.build_nk_table(inputs, labels);

  // Use the training data to configure the classifier
  nk_classifier.find_optimum_nk();
  nk_classifier.configure_outputs();

  // If configured to do so, this will dump the classifier to a file,
  // and it will look like a standard layer of a Neural Network.
  nk_classifier.write_as_NN(config);

  // Load the test data over the training data keep memory usage down
  load_csv(testing_file, inputs, labels);
  auto predictions = nk_classifier.classify(inputs);

  // TODO Create more general report of how accurate the classification was
  auto confusion = single_target_confusion_matrix(predictions, labels, config.get<label_type>("target_label"));
  for (const auto& row : confusion) {
    for (const auto entry : row) {
      cout << "| " << entry << " ";
    }
    cout << "|" << endl;
  }
  return 0;
}
