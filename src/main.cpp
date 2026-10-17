#include "LanguageModel.h"
#include "Helper.h"

#include <iostream>
#include <string>
#include <stdexcept>

using namespace std;

int main(int argc, char* argv[]){
    try{
        double alpha = 0.0;
        int k;
        int length;
        string filename;
        //The input can vary, different ways of writig it
        //Do we include -a ?
         if (argc > 1 && string(argv[1]) == "-a") {
            if (argc != 6) {
                throw invalid_argument("Usage: ./slm [-a alpha] k filename length");
            }
            //alpha has to be a number 
            //alpha has to be positive and finite
            if(!isfinite(alpha) || alpha < 0.0) {
                throw invalid_argument("Alpha must be positive and finite");
            }
            alpha = stod(argv[2]);
            k = stoi(argv[3]);
            filename = argv[4];
            length = stoi(argv[5]);

            } else { //We don't include alpha
                if (argc != 4) {
                    throw invalid_argument("Usage: ./slm [-a alpha] k filename length");
                }

            k = stoi(argv[1]);
            filename = argv[2];
            length = stoi(argv[3]);
            }

            //Making the small language model
            LanguageModel model(k, alpha);

            //Training it with our builder
            model.Builder(filename);

            //Getting the generator
            Generator generator(model);

            //Text output
            string final_text = generator.Text_gen(length);

            cout << final_text << endl;
            } catch (const exception& error) {
                cerr << "There's been an error: " << error.what() <<endl;
                return 1;
            }
        return 0;
}
