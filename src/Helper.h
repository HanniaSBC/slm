#pragma once

#include "LanguageModel.h"
#include <string>

class Generator {
    public:
    //Constructor
    Generator(const LanguageModel& model);

    private:
    //referencing the trained model
    const LanguageModel& model;
};