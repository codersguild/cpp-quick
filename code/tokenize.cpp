#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include <stdlib.h>
using namespace std;
/* Read, Tokenize, Write CSV */
std::vector<string> SplitWordsTokenizerCSVRead (string input_string)
{
    /* Remove extra white spaces between words in a string with comma. Unique puts it to the back of the string. */
    string::iterator str_end_iter = unique(input_string.begin(), input_string.end(), [](const char& x, const char& y){
        return x == y && x == ' ';
    });
    /* Remove all extra white spaces from the end of the string. */
    input_string.erase(str_end_iter, input_string.end());
    while(input_string[input_string.length() - 1] == ' '){
        input_string.pop_back();
    }
    std::vector<string> split_tokens;
    char delimiter = ',';
    size_t pos, i = 0;
    /* Find white spaces and tokenized the string by slicing into substrings at comma. Push back the substrings. */
    pos = input_string.find(delimiter);
    while(pos != string::npos){
        auto temp = input_string.substr(i, pos - i);
        if(temp.front() == ' ') temp.erase(0, 1);
        /* Erase that one space, if left out */
        split_tokens.push_back(temp);
        i = pos + 1;
        pos = input_string.find(delimiter, i);
        /* Find the next token and push it back. */
    }
    /* Last part of the string is still left out. */
    auto temp = input_string.substr(i, std::min(pos, input_string.length()));
    temp.erase(0, 1);
    split_tokens.push_back(temp);
    /* Return vector of tokens */
    return split_tokens;
}

int main(int argc, char **argv)
{
    if(argc < 2) {
        fprintf(stdout,"Usage: %s file_name\n",argv[0]);
        exit(EXIT_FAILURE);
    }    
    std::string input = "";
    // atoi(argv[0]), atof(argv[1])
    std::vector<std::vector<std::string> > CSVTokens;
    std::fstream fileCSVReader(argv[1], std::fstream::in);
    while(fileCSVReader.good() && std::getline(cin, input))
    {
        auto dump = SplitWordsTokenizerCSVRead(input);
        CSVTokens.push_back(dump);
    }
    fileCSVReader.close();
    for(const auto& a : CSVTokens){
        std::cout << "Fileline :" << std::endl;
        for(const auto& b : a){
            std::cout << "Token :" << b << std::endl; 
        }
    }
    std::cout << "Done" << std::endl;
    return 0;
}
