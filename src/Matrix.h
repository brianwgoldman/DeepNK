// Brian Goldman
#ifndef MATRIX_H_
#define MATRIX_H_

#include "Utilities.h"

class Matrix {
  // Stored as data[column][row] since most of the time you want
  // to look at entire columns
  vector<vector<value_type>> data;
  size_t nrows, ncols;
 public:
  Matrix(const size_t rows=0, const size_t columns=0);
  virtual ~Matrix() = default;

  inline const value_type value(const size_t row, const size_t column) const {
    assert(column < data.size() and row < data[column].size());
    return data[column][row];
  }
  inline value_type& value(const size_t row, const size_t column) {
    assert(column < data.size() and row < data[column].size());
    return data[column][row];
  }

  const vector<value_type>& column(const size_t col) const {
    return data[col];
  }
  const size_t rows() const {
    return nrows;
  }
  const size_t cols() const {
    return ncols;
  }
  void resize(const size_t rows, const size_t columns);
  void clear() {
    data.clear();
  }
  // Selects columns and does a weighted sum of their values using weights
  vector<value_type> build_column(const vector<size_t>& column_indexes, const vector<value_type>& weights) const;

  friend Matrix multiply(const Matrix& lhs, const Matrix& rhs);
};

Matrix multiply(const Matrix& lhs, const Matrix& rhs);
void load_csv(const string filename, Matrix& inputs, vector<label_type>& labels);

#endif /* MATRIX_H_ */
