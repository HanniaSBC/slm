#pragma once

#include <string>
#include <vector>
#include <map>
#include <random>

class LanguageModel{
    public:
    // Constructors
    LanguageModel(int k, double alpha);

    //Method to build the model from text file
    void Builder(const std::string& filename);

    //For the probabilities
    //Next character "c"
    double Probability(const std::string& word, char next_kchar) const;

    //For the first kgram according to frequency
    std::string pickStartK(std::mt19937& rndm_numb) const; //here otherwise we cant access the private elements in helper.

    //For the next charactrer
    char pickNextChar(const std::string& word, std::mt19937& rndm_numb) const;
 
    private:
    int k;
    double alpha;

    //frequencies
    std::map<std::string, int> kgram_freq;
    //which character follows
    std::map<std::string, std::map<char, int>> next_k;
    std::vector<char> alphabet;

};