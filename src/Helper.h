#pragma once

#include "LanguageModel.h"
#include <string>
#include <random>

class Generator {
    public:
    //Constructor
    Generator(const LanguageModel& model);

    std::string Text_gen(int k_lenght);

    private:
    //referencing the trained model
    const LanguageModel& model;

    std::mt19937 rdnm_numb;

};