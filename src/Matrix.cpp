// Brian Goldman
#include "Matrix.h"
#include <cassert>

Matrix::Matrix(const size_t rows, const size_t columns) : data(columns, vector<value_type>(rows)), nrows(rows), ncols(columns) {

}

void load_csv(string filename, Matrix& inputs, vector<label_type>& labels) {
  // TODO Implement this code
  assert(false);
  inputs.clear();
  labels.clear();
}

void Matrix::resize(const size_t rows, const size_t columns) {
  data.clear();
  data.resize(columns, vector<value_type>(rows));
  nrows = rows;
  ncols = columns;
}

vector<value_type> Matrix::build_column(const vector<size_t>& column_indexes, const vector<value_type>& weights) const {
  assert(column_indexes.size() == weights.size());
  vector<value_type> result(nrows, 0);
  for (size_t i=0; i < column_indexes.size(); i++) {
    const auto& column = data[column_indexes[i]];
    const auto weight = weights[i];
    for (size_t r=0; r < nrows; r++) {
      result[r] += column[r] * weight;
    }
  }
  return result;
}

Matrix multiply(const Matrix& lhs, const Matrix& rhs) {
  assert(lhs.ncols == rhs.nrows);
  Matrix result(lhs.nrows, rhs.ncols);
  for (size_t row=0; row < result.nrows; row++) {
    for (size_t col=0; col < result.ncols; col++) {
      value_type sum = 0;
      for (size_t i=0; i < lhs.ncols; i++) {
        // TODO consider making this direct access instead of through function
        sum += lhs.value(row, i) * rhs.value(i, col);
      }
      result.value(row, col) = sum;
    }
  }
  return result;
}

void Matrix::fill_with_random_weights(Random& random) {
  for (size_t row = 0; row < nrows; row++) {
    auto weights = random_log_weights(ncols, random);
    for (size_t col = 0; col < ncols; col++) {
      // TODO Consider direct access
      value(row, col) = weights[col];
    }
  }
}
