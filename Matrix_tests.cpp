#include "Matrix.hpp"
#include "Matrix_test_helpers.hpp"
#include "unit_test_framework.hpp"

using namespace std;

// Here's a free test for you! Model yours after this one.
// Test functions have no interface and thus no RMEs, but
// add a comment like the one here to say what it is testing.
// -----
// Fills a 3x5 Matrix with a value and checks
// that Matrix_at returns that value for each element.
TEST(test_fill_basic) {
  Matrix mat;
  const int width = 3;
  const int height = 5;
  const int value = 42;
  Matrix_init(&mat, 3, 5);
  Matrix_fill(&mat, value);

  for(int r = 0; r < height; ++r){
    for(int c = 0; c < width; ++c){
      ASSERT_EQUAL(*Matrix_at(&mat, r, c), value);
    }
  }
}

// Tests that Matrix_init initializes correctly and overwrites old data
TEST(test_matrix_init) {
  Matrix mat;
  
  Matrix_init(&mat, 2, 2);
  ASSERT_EQUAL(mat.width, 2);
  ASSERT_EQUAL(mat.height, 2);
  ASSERT_EQUAL(mat.data.size(), 4);

  for (int i = 0; i < 4; ++i) {
    ASSERT_EQUAL(mat.data[i], 0);
  }

  mat.data[0] = 99;
  mat.data[3] = 42;
  Matrix_init(&mat, 3, 1);

  ASSERT_EQUAL(mat.width, 3);
  ASSERT_EQUAL(mat.height, 1);
  ASSERT_EQUAL(mat.data.size(), 3);
  for (int i = 0; i < 3; i++) {
    ASSERT_EQUAL(mat.data[i], 0);
  }
}

// Tests that Matrix_print outputs the correct format
TEST(test_matrix_print) {
  Matrix mat;
  Matrix_init(&mat, 3, 2); 

  mat.data[0] = 1;
  mat.data[1] = 2;
  mat.data[2] = 3;
  mat.data[3] = 4;
  mat.data[4] = 5;
  mat.data[5] = 6;

  ostringstream out;
  Matrix_print(&mat, out);

  ostringstream correct;
  correct << "3 2 " << endl;
  correct << "1 2 3 " << endl;
  correct << "4 5 6 " << endl;
  ASSERT_EQUAL(out.str(), correct.str());
}

// Tests that Matrix_width returns the correct width
TEST(test_matrix_width) {
  Matrix mat;

  Matrix_init(&mat, 4, 3);
  int w = Matrix_width(&mat);
  ASSERT_EQUAL(w, 4);
}

// Tests that Matrix_height returns the correct height
TEST(test_matrix_height) {
  Matrix mat;

  Matrix_init(&mat, 5, 4);
  int h = Matrix_height(&mat);
  ASSERT_EQUAL(h, 4);
}

TEST(test_matrix_at) {
  Matrix mat;

  Matrix_init(&mat, 3, 3);

  *Matrix_at(&mat, 0, 0) = 5;
  *Matrix_at(&mat, 1, 2) = 17;
  *Matrix_at(&mat, 2, 1) = -3;

  ASSERT_EQUAL(*Matrix_at(&mat, 0, 0), 5);
  ASSERT_EQUAL(*Matrix_at(&mat, 1, 2), 17);
  ASSERT_EQUAL(*Matrix_at(&mat, 2, 1), -3);
}

TEST(test_matrix_at_const) {
  Matrix mat;
  Matrix_init(&mat, 3, 2);
  *Matrix_at(&mat, 1, 2) = 99;

  const Matrix* cmat = &mat;
  const int* p = Matrix_at(cmat, 1, 2);
  ASSERT_EQUAL(*p, 99);

  int expected_index = 1 * mat.width + 2;
  ASSERT_EQUAL(p, &mat.data[expected_index]);
}

// Tests Matrix_fill initializes and overwrites all elements correctly
TEST(test_matrix_fill) {
  Matrix mat;
  Matrix_init(&mat, 3, 2);
  Matrix_fill(&mat, 5);

  for (int i = 0; i < mat.height; ++i) {
    for (int j = 0; j < mat.width; ++j) {
      ASSERT_EQUAL(*Matrix_at(&mat, i, j), 5);
    }
  }

  *Matrix_at(&mat, 0, 0) = 1;
  *Matrix_at(&mat, 0, 1) = 2;
  *Matrix_at(&mat, 0, 2) = 3;
  *Matrix_at(&mat, 1, 0) = 4;
  *Matrix_at(&mat, 1, 1) = 5;
  *Matrix_at(&mat, 1, 2) = 6;
  Matrix_fill(&mat, 0);

  for (int i = 0; i < mat.height; ++i) {
    for (int j = 0; j < mat.width; ++j) {
      ASSERT_EQUAL(*Matrix_at(&mat, i, j), 0);
    }
  }
}

TEST(test_matrix_fill_border) {
  Matrix mat1;
  Matrix_init(&mat1, 4, 3);
  Matrix_fill(&mat1, 7);
  Matrix_fill_border(&mat1, 1);

  for (int i = 0; i < mat1.height; ++i) {
    for (int j = 0; j < mat1.width; ++j) {
      bool isBorder = (i == 0 || i == mat1.height - 1 ||
         j == 0 || j == mat1.width - 1);
      if (isBorder) {
                ASSERT_EQUAL(*Matrix_at(&mat1, i, j), 1);
      }
      else {
                ASSERT_EQUAL(*Matrix_at(&mat1, i, j), 7);
      }
    }
  }
  Matrix_fill_border(&mat1, 9);
  for (int i = 0; i < mat1.height; ++i) {
    for (int j = 0; j < mat1.width; ++j) {
      bool isBorder = (i == 0 || i == mat1.height - 1 ||
        j == 0 || j == mat1.width - 1);
      if (isBorder) {
        ASSERT_EQUAL(*Matrix_at(&mat1, i, j), 9);
      }
      else {
        ASSERT_EQUAL(*Matrix_at(&mat1, i, j), 7);
      }
    }
  }

  Matrix mat2;
  Matrix_init(&mat2, 1, 1);
  Matrix_fill(&mat2, 4);
  Matrix_fill_border(&mat2, 8);
  ASSERT_EQUAL(*Matrix_at(&mat2, 0, 0), 8);

  Matrix mat3;
  Matrix_init(&mat3, 5, 1);
  Matrix_fill(&mat3, 2);
  Matrix_fill_border(&mat3, 6);
  for (int i = 0; i < mat3.width; ++i) {
    ASSERT_EQUAL(*Matrix_at(&mat3, 0, i), 6);
  }

  Matrix mat4;
  Matrix_init(&mat4, 1, 5);
  Matrix_fill(&mat4, 3);
  Matrix_fill_border(&mat4, 7);
  for (int i = 0; i < mat4.height; ++i) {
    ASSERT_EQUAL(*Matrix_at(&mat4, i, 0), 7);
  }
}

TEST(test_matrix_max) {
  Matrix mat1;
  Matrix_init(&mat1, 3, 2);
  *Matrix_at(&mat1, 0, 0) = 1;
  *Matrix_at(&mat1, 0, 1) = 5;
  *Matrix_at(&mat1, 0, 2) = 3;
  *Matrix_at(&mat1, 1, 0) = 4;
  *Matrix_at(&mat1, 1, 1) = 2;
  *Matrix_at(&mat1, 1, 2) = 0;
  ASSERT_EQUAL(Matrix_max(&mat1), 5);

  Matrix mat2;
  Matrix_init(&mat2, 4, 4);
  Matrix_fill(&mat2, 7);
  ASSERT_EQUAL(Matrix_max(&mat2), 7);

  Matrix mat3;
  Matrix_init(&mat3, 2, 2);
  *Matrix_at(&mat3, 0, 0) = -5;
  *Matrix_at(&mat3, 0, 1) = -9;
  *Matrix_at(&mat3, 1, 0) = -3;
  *Matrix_at(&mat3, 1, 1) = -7;
  ASSERT_EQUAL(Matrix_max(&mat3), -3);

  Matrix mat4;
  Matrix_init(&mat4, 1, 1);
  *Matrix_at(&mat4, 0, 0) = 42;
  ASSERT_EQUAL(Matrix_max(&mat4), 42);

  Matrix mat5;
  Matrix_init(&mat5, 3, 3);
  Matrix_fill(&mat5, 1);
  *Matrix_at(&mat5, 0, 2) = 99;
  ASSERT_EQUAL(Matrix_max(&mat5), 99);
}


TEST(test_matrix_column_of_min_value_in_row) {
  Matrix mat;
  Matrix_init(&mat, 6, 3);
  *Matrix_at(&mat, 0, 0) = 5;
  *Matrix_at(&mat, 0, 1) = 2;
  *Matrix_at(&mat, 0, 2) = 7;
  *Matrix_at(&mat, 0, 3) = 2;
  *Matrix_at(&mat, 0, 4) = 9;
  *Matrix_at(&mat, 0, 5) = 1;

  *Matrix_at(&mat, 1, 0) = -4;
  *Matrix_at(&mat, 1, 1) = -4;
  *Matrix_at(&mat, 1, 2) = -2;
  *Matrix_at(&mat, 1, 3) = -9;
  *Matrix_at(&mat, 1, 4) = -9;
  *Matrix_at(&mat, 1, 5) = 0;

  for (int c = 0; c < 6; ++c) {
    *Matrix_at(&mat, 2, c) = 3;
  }

  ASSERT_EQUAL(Matrix_column_of_min_value_in_row(&mat, 0, 0, 6), 5);
  ASSERT_EQUAL(Matrix_column_of_min_value_in_row(&mat, 1, 0, 6), 3);
  ASSERT_EQUAL(Matrix_column_of_min_value_in_row(&mat, 0, 1, 4), 1);
  ASSERT_EQUAL(Matrix_column_of_min_value_in_row(&mat, 0, 3, 4), 3);
  ASSERT_EQUAL(Matrix_column_of_min_value_in_row(&mat, 2, 0, 6), 0);
  ASSERT_EQUAL(Matrix_column_of_min_value_in_row(&mat, 2, 2, 5), 2);
}

TEST(test_matrix_min_value_in_row) {
  Matrix mat;
  Matrix_init(&mat, 6, 3);

  *Matrix_at(&mat, 0, 0) = 5;
  *Matrix_at(&mat, 0, 1) = 2;
  *Matrix_at(&mat, 0, 2) = 7;
  *Matrix_at(&mat, 0, 3) = 2;
  *Matrix_at(&mat, 0, 4) = 9;
  *Matrix_at(&mat, 0, 5) = 1;

  *Matrix_at(&mat, 1, 0) = -4;
  *Matrix_at(&mat, 1, 1) = -4;
  *Matrix_at(&mat, 1, 2) = -2;
  *Matrix_at(&mat, 1, 3) = -9;
  *Matrix_at(&mat, 1, 4) = -9;
  *Matrix_at(&mat, 1, 5) = 0;

  for (int c = 0; c < 6; ++c) {
    *Matrix_at(&mat, 2, c) = 3;
  }

  ASSERT_EQUAL(Matrix_min_value_in_row(&mat, 0, 0, 6), 1);
  ASSERT_EQUAL(Matrix_min_value_in_row(&mat, 1, 0, 6), -9);
  ASSERT_EQUAL(Matrix_min_value_in_row(&mat, 0, 1, 4), 2);
  ASSERT_EQUAL(Matrix_min_value_in_row(&mat, 0, 3, 4), 2);
  ASSERT_EQUAL(Matrix_min_value_in_row(&mat, 2, 0, 6), 3);
  ASSERT_EQUAL(Matrix_min_value_in_row(&mat, 2, 2, 5), 3);
}
// ADD YOUR TESTS HERE
// You are encouraged to use any functions from Matrix_test_helpers.hpp as needed.

TEST_MAIN() // Do NOT put a semicolon here
