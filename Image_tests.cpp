#include "Matrix.hpp"
#include "Image_test_helpers.hpp"
#include "unit_test_framework.hpp"
#include <iostream>
#include <string>
#include <sstream>
#include <cassert>

using namespace std;

// Here's a free test for you! Model yours after this one.
// Test functions have no interface and thus no RMEs, but
// add a comment like the one here to say what it is testing.
// -----
// Sets various pixels in a 2x2 Image and checks
// that Image_print produces the correct output.
TEST(test_print_basic) {
  Image img;
  const Pixel red = {255, 0, 0};
  const Pixel green = {0, 255, 0};
  const Pixel blue = {0, 0, 255};
  const Pixel white = {255, 255, 255};

  Image_init(&img, 2, 2);
  Image_set_pixel(&img, 0, 0, red);
  Image_set_pixel(&img, 0, 1, green);
  Image_set_pixel(&img, 1, 0, blue);
  Image_set_pixel(&img, 1, 1, white);

  // Capture our output
  ostringstream s;
  Image_print(&img, s);

  // Correct output
  ostringstream correct;
  correct << "P3\n2 2\n255\n";
  correct << "255 0 0 0 255 0 \n";
  correct << "0 0 255 255 255 255 \n";
  ASSERT_EQUAL(s.str(), correct.str());
}

// Tests that Image_init correctly sets width/height
// and initializes all pixels to black (0,0,0)
TEST(test_image_init) {
  Image img;
  
  Image_init(&img, 3, 2);

  ASSERT_EQUAL(Image_width(&img), 3);
  ASSERT_EQUAL(Image_height(&img), 2);

  Pixel black = {0, 0, 0};

  for (int i = 0; i < Image_height(&img); ++i) {
    for (int j = 0; j < Image_width(&img); ++j) {
      Pixel p = Image_get_pixel(&img, i, j);
      ASSERT_EQUAL(p.r, black.r);
      ASSERT_EQUAL(p.g, black.g);
      ASSERT_EQUAL(p.b, black.b);
    }
  }
}

//tests that image_init correctly itializes the image
// by reading in PPM format
TEST(test_image_init_PPM) {
  stringstream ss;
  ss << "P3\n";
  ss << "2 2\n";
  ss << "255\n";
  ss << "255 0 0   0 255 0\n";
  ss << "0 0 255   255 255 255\n";

  Image img;
  Image_init(&img, ss);

  ASSERT_EQUAL(img.width, 2);
  ASSERT_EQUAL(img.height, 2);

  ASSERT_EQUAL(*Matrix_at(&img.red_channel, 0, 0), 255);
  ASSERT_EQUAL(*Matrix_at(&img.green_channel, 0, 0), 0);
  ASSERT_EQUAL(*Matrix_at(&img.blue_channel, 0, 0), 0);

  ASSERT_EQUAL(*Matrix_at(&img.red_channel, 0, 1), 0);
  ASSERT_EQUAL(*Matrix_at(&img.green_channel, 0, 1), 255);
  ASSERT_EQUAL(*Matrix_at(&img.blue_channel, 0, 1), 0);

  ASSERT_EQUAL(*Matrix_at(&img.red_channel, 1, 0), 0);
  ASSERT_EQUAL(*Matrix_at(&img.green_channel, 1, 0), 0);
  ASSERT_EQUAL(*Matrix_at(&img.blue_channel, 1, 0), 255);

  ASSERT_EQUAL(*Matrix_at(&img.red_channel, 1, 1), 255);
  ASSERT_EQUAL(*Matrix_at(&img.green_channel, 1, 1), 255);
  ASSERT_EQUAL(*Matrix_at(&img.blue_channel, 1, 1), 255);
}

// Tests that Image_print outputs a correct P3 PPM file
// with proper header, spacing, and pixel order.
TEST(test_image_print) {
  Image img;
  Pixel red   = {255, 0, 0};
  Pixel green = {0, 255, 0};
  Pixel blue  = {0, 0, 255};
  Pixel white = {255, 255, 255};
  Image_init(&img, 2, 2);

  Image_set_pixel(&img, 0, 0, red);
  Image_set_pixel(&img, 0, 1, green);
  Image_set_pixel(&img, 1, 0, blue);
  Image_set_pixel(&img, 1, 1, white);

  ostringstream out;
  Image_print(&img, out);
  
  ostringstream correct;
  correct << "P3" << endl;
  correct << "2 2" << endl;
  correct << "255" << endl;
  correct << "255 0 0 0 255 0 " << endl;
  correct << "0 0 255 255 255 255 " << endl;

  ASSERT_EQUAL(out.str(), correct.str());
}

// Tests that Image_width returns the correct height after initialization
TEST(test_image_width) {
  Image img;

  Image_init(&img, 1, 1);
  ASSERT_EQUAL(Image_width(&img), 1);

  Image_init(&img, 10, 5);
  ASSERT_EQUAL(Image_width(&img), 10);

  Image_init(&img, 7, 9);
  ASSERT_EQUAL(Image_width(&img), 7);
}

// Tests that Image_height returns the correct height after initialization
TEST(test_image_height) {
 Image img;

  Image_init(&img, 1, 1);
  ASSERT_EQUAL(Image_height(&img), 1);

  Image_init(&img, 10, 5);
  ASSERT_EQUAL(Image_height(&img), 5);

  Image_init(&img, 7, 9);
  ASSERT_EQUAL(Image_height(&img), 9);
}

// Tests that Image_get_pixel returns the correct Pixel values
TEST(test_image_get_pixel) {
  Image img;

  Image_init(&img, 2, 2);
  Pixel p = Image_get_pixel(&img, 0, 0);

  ASSERT_EQUAL(p.r, 0);
  ASSERT_EQUAL(p.g, 0);
  ASSERT_EQUAL(p.b, 0);

  Pixel white = {255, 255, 255};
  Image_set_pixel(&img, 0, 0, white);
  p = Image_get_pixel(&img, 0, 0);

  ASSERT_EQUAL(p.r, 255);
  ASSERT_EQUAL(p.g, 255);
  ASSERT_EQUAL(p.b, 255);
}

// Tests that Image_set_pixel correctly sets RGB values
TEST(test_image_set_pixel) {
  Image img;
  
  Image_init(&img, 2, 2);
  Pixel purple = {128, 0, 128};
  Image_set_pixel(&img, 0, 1, purple);
  Pixel p = Image_get_pixel(&img, 0, 1);

  ASSERT_EQUAL(p.r, 128);
  ASSERT_EQUAL(p.g, 0);
  ASSERT_EQUAL(p.b, 128);
}

// Tests that Image_fill sets all pixels to the same color
TEST(test_image_fill_basic) {
  Image img;
  
  Image_init(&img, 3, 2);
  Pixel gray = {100, 100, 100};
  Image_fill(&img, gray);

  for (int i = 0; i < Image_height(&img); ++i) {
    for (int j = 0; j < Image_width(&img); ++j) {
      Pixel p = Image_get_pixel(&img, i, j);
      ASSERT_EQUAL(p.r, 100);
      ASSERT_EQUAL(p.g, 100);
      ASSERT_EQUAL(p.b, 100);
    }
  }
}
// IMPLEMENT YOUR TEST FUNCTIONS HERE
// You are encouraged to use any functions from Image_test_helpers.hpp as needed.

TEST_MAIN() // Do NOT put a semicolon here
