#include "Helper.h"
#include <iostream>
#include <stdexcept>
#include <vector>

using namespace std;

//Constructor
Generator::Generator(const LanguageModel& model): model(model), rdnm_numb(random_device{}()) {
}

//Generating text
string Generator::Text_gen(int k_lenght){
    string final_word = "";

    //1. Choosing starting kgram
    string kword = model.pickStartK(rdnm_numb);

    if (kword.empty()){
        throw invalid_argument("No starting kgram found");
        //return final_word;
    } else {
        final_word += kword;
    }
    //For the following character
    while(final_word.size() < static_cast<size_t>(k_lenght)) {
        //Pick the next character
        char next_char = model.pickNextChar(kword, rdnm_numb);
        final_word += next_char;
        kword = kword.substr(1) + next_char;
    }
    return final_word.substr(0, k_lenght); 
}



