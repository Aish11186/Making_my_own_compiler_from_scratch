#pragma once
using namespace std;
#include <fstream>
#include <vector>
#include <string>
#include <optional>
#include <sstream>


class tokenizer{
    public:
        inline Tokenizer (const string& src):
        {
            :m_src(move(src)); //initializing the source code to be tokenized
        }
        inline vector<Token> tokenize(){

        }

    private:
    
        const string m_src;
}