CXX = c++
CXXFLAGS =-Wall -std=c++17

all: slm

slm: src/main.o src/LanguageModel.o src/Helper.o
	$(CXX) $(CXXFLAGS) -o slm src/main.o src/LanguageModel.o src/Helper.o

src/main.o: src/main.cpp src/LanguageModel.h src/Helper.h
	$(CXX) $(CXXFLAGS) -c src/main.cpp -o $@

src/model.o: src/LanguageModel.cpp src/LanguageModel.h
	$(CXX) $(CXXFLAGS) -c src/model.cpp -o $@

src/TextGenerator.o: src/TextGenerator.cpp src/TextGenerator.h src/Model.h
	$(CXX) $(CXXFLAGS) -c src/TextGenerator.cpp -o $@

clean:
	rm -f src/*.o slm


.PHONY: all clean