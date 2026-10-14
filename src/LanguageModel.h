#pragma once

#include <string>
#include <vector>
#include <map>

class LanguageModel{
    public:
    // Constructors
    LanguageModel(int k, double alpha);

    //Method
    void builder(const std::string& filename);
 
    private:
    int k;
    double alpha;

    //frequencies
    std::map<std::string, int> kgram_freq;
    //which character follows
    std::map<std::string, std::map<char, int>> next_k;
    std::vector<char> alphabet;

};