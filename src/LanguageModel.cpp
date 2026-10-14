#include "LanguageModel.h"
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <sstream>

using namespace std;

LanguageModel::LanguageModel(int k0, double alpha) {
    k = k0;
    alpha = alpha;

    if (k <= 0) {
        throw invalid_argument("k must be a positive integer");
    }
    if (alpha < 0 ) {
        throw invalid_argument("alpha must be ");
    }


}

void LanguageModel::builder(const std::string& filename) {
    kgram_freq.clear();
    next_k.clear();

    ifstream file(filename);

    if (!file) { // can't open file
        throw runtime_error("Couldn't open file");
    }
    
    //Reading the text into a string
    //getline(file, text, '\0');
    string text((std::istreambuf_iterator<char>(file)),
                 std::istreambuf_iterator<char>());
    //is the text long enough?
    if (text.length() < k) {
        throw runtime_error("The text size is smaller than k");
    }




}
