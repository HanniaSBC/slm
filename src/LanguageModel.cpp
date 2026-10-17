#include "LanguageModel.h"
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <sstream>

using namespace std;

LanguageModel::LanguageModel(int k0, double alpha0) {
    k = k0;
    alpha = alpha0;

    if (k <= 0) {
        throw invalid_argument("k must be a positive integer");
    }
    if (alpha < 0 ) {
        throw invalid_argument("alpha must be positive");
    }


}

void LanguageModel::Builder(const std::string& filename) {
    kgram_freq.clear();
    next_k.clear();
    alphabet.clear();

    ifstream file(filename);

    if (!file) { // can't open file
        throw runtime_error("Couldn't open file");
    }
    
    //Reading the text into a string, keeping the whole of it including spaces.
    //getline(file, text, '\0'); //this doesnt keep the \n
    string text((std::istreambuf_iterator<char>(file)),
                 std::istreambuf_iterator<char>());
    //is the text long enough?
    if (text.length() < static_cast<size_t>(k)) {
        throw runtime_error("The text size is smaller than k");
    }
    //Build an alphabet with all the unique characters in the text
    for (char c : text) {
        alphabet.push_back(c);

    }

    //Iterating through every possible kgram on the text up to the last one
    for (size_t i= 0; i <= text.length() - static_cast<size_t>(k); ++i){
        //current kgram
        string word = text.substr(i, k);
        //getting the frequency of the kgram
        kgram_freq[word]++;

        //for the character that follows, n(w,c)
        if (i + k < text.length()) {
            char next_kchar = text[i + k];

            next_k[word][next_kchar]++;
        }

    }
}

//Calculating the probabilities 
//for a character following the kgram
double LanguageModel::Probability(const string& word, char next_kchar) const {
    //the transitions following this k
    int total_char = 0; //all characters that follow it
    auto word_n = next_k.find(word); // the transition

    if (word_n != next_k.end()) {
        for (const auto& item : word_n->second) {
            total_char += item.second;
        }
    }
    int count_nchar = 0; //for the requested next character
    if (word_n != next_k.end()) {
        auto nchar = word_n->second.find(next_kchar);
        if (nchar != word_n -> second.end()){
            count_nchar = nchar->second;
        }
    }

    //Now for the formulas
    //if alpha is = 0, P=n(w,c)/n(w)
    if (alpha == 0.0) {
        if (total_char == 0.0) {
            return 0.0;
        }

        return static_cast<double>(count_nchar) / total_char;
    } 
     // if we have a value for alpha P=n(w,c)=alpha /n(w) +alpha*alphabet
        return (count_nchar + alpha) / (total_char + (alpha * alphabet.size()));
    
}

string LanguageModel::pickStartK(std::mt19937& rndm_numb) const {
    
    vector<string> word;
    vector<double> probs;

     for (const auto& pairs : kgram_freq) { //accessing the map for the freq
        word.push_back(pairs.first);
        probs.push_back(pairs.second);
    }

    // Choose a k-gram based on its frequency
    discrete_distribution<size_t> distribution(
        probs.begin(), probs.end()
    );

    size_t index = distribution(rndm_numb);

    return word[index];
}

char LanguageModel::pickNextChar(const string& word, mt19937& rndm_numb) const {
//the possible next characters and their posibilities:
    vector<char> character;
    vector<double> probs2;

    for(char c : alphabet) {
        double p = Probability(word, c);
        if (p > 0.0) {
            character.push_back(c);
            probs2.push_back(p);
        }
    }
    if (character.empty()) {
        throw runtime_error("No next character available");
    }
    //picking a character
    discrete_distribution<size_t> distribution(probs2.begin(), probs2.end());
    size_t index = distribution(rndm_numb);
    return character[index]; 
}

    