#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib> 
#include "Image.hpp"
#include "processing.hpp"

using namespace std;

static void print_usage_and_return_nonzero() {
  cout << "Usage: resize.exe IN_FILENAME OUT_FILENAME WIDTH [HEIGHT]\n"
       << "WIDTH and HEIGHT must be less than or equal to original" << endl;
}

int main(int argc, char *argv[]) {
    if (argc != 4 && argc != 5) {
        print_usage_and_return_nonzero();
        return 1;
    }

    string in_filename = argv[1];
    string out_filename = argv[2];
    int new_width = atoi(argv[3]);

    ifstream input(in_filename);
    if (!input.is_open()) {
        cout << "Error opening file: " << in_filename << endl;
        return 1;
    }

    Image img;
    Image_init(&img, input);
    int orig_width = Image_width(&img);
    int orig_height = Image_height(&img);

    int new_height = orig_height;
    if (argc == 5) {
        new_height = atoi(argv[4]);
    }

    if (new_width <= 0 || new_width > orig_width || 
        new_height <= 0 || new_height > orig_height) {
            print_usage_and_return_nonzero();
            return 1;
        }

    seam_carve(&img, new_width, new_height);
    ofstream output(out_filename);
    if (!output.is_open()) {
        cout << "Error opening file: " << out_filename << endl;
        return 1;
    }

    Image_print(&img, output);
    return 0;
}