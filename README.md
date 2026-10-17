# sml

The project serves as a Small language model, an alternative to Artificial Intelligence being an "Artificial Idiot" since the text generated is not necessarily correct. \
The model works from a given input, it receives a text and then it trains on it to generate new text based on the frequency of the _"k-grams"_ (words) in the text.

## How to compile
Requisites: A compiler compatible with C++17\
Use `make` and `make clean` to remove generated files.

## How to use
```
Usage: ./slm [-a alpha] k filename length
```
Where:\
**_alpha_** corresponds to the pseudocount, it is optional and when not inputted it defaults to 0.\
A small alpha adds a little “creativity” to the output, while a large drowns the information in the training text and gives random characters.\
**_k_** corresponds to the size of the kgrams.\
**_filename_** corresponds to the text it will train with.\
**_length_** corresponds to the output in length in characters.\


_Examples_
```
./slm 2 moby_dick.txt 5
it we

./slm -a 0.01 3 moby_dick.txt 40
n bow not is a next in only means hearli
```
Here we can see it works as intended

