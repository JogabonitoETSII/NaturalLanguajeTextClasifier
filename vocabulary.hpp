#ifndef VOCABULARY_H
#define VOCABULARY_H
#include <math.h>
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <regex>
#include <algorithm>
#define ERROR_OPEN_FILE -1
#define WORD_NUMBER "Número de palabras:"
#define WORD "Palabra:"
#define OUT_FILE "vocabulario.txt"
#define REGEX_WORD \w
using namespace std;

class Vocabulary {
private:
	regex textTag_ = regex ("(?:Texto:)(REGEX_WORD|\b|.)+");
	regex spaceSeparator_ = regex (" ");
	vector <string> words;
	ifstream file;
public:
	Vocabulary ();
	~Vocabulary();
	vector<string> dontWordRepeat();
	int learning(string input,string output);
	int parseFile (string fileName);
	float countWordsAppear(std::vector<string> learnWords,int j);
	bool checkFileExist (string fileName);

};

#endif