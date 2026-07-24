#pragma once
using namespace std;
#include <fstream>
#include <vector>
#include <string>
#include <optional>
#include <sstream>
#include <iostream>
#include <cctype>
#include <cstdlib>

enum class TokenType{
    exit,
    int_lit,
    semi

};
struct Token{
    TokenType type;
    std::optional<std::string> value;
};

class tokenizer{
    public:
        inline explicit tokenizer (string& src)
        
            : m_src(std::move(src)), m_index(0)
        { //initializing the source code to be tokenized
        }
        inline vector<Token> tokenize(){
            string buf{};
            vector<Token> tokens;
             while(peak().has_value()){
                if(isalpha(peak().value())){
                    buf.push_back(consume());
                    while(peak().has_value() && isalnum(peak().value())){
                        buf.push_back(consume());
                    }
                    if(buf=="exit"){
                        tokens.push_back({.type =TokenType::exit});
                        buf.clear();
                    }
                    else {
                        cerr<<"faaaaaaaaaa you messed up (but its okay mistakes are how we grow)";
                        exit(EXIT_FAILURE);
                    }
                }
                else if(isdigit(peak().value())){
                    buf.push_back(consume());
                    while(peak().has_value()&&isdigit(peak().value())){
                        buf.push_back(consume());
                    }
                    tokens.push_back({.type = TokenType::int_lit, .value = string(buf.begin(), buf.end())});
                    buf.clear();
                }
                else if(peak().value()==';'){
                    consume();
                    tokens.push_back({.type = TokenType::semi});

                }
                else if(isspace(peak().value())) consume();
                else{
                    cerr<<"you messed up";
            
                    exit(EXIT_FAILURE);
                }
                

            }
            m_index=0;
            return tokens;
  
    
        }

    private:
    
        [[nodiscard]]optional<char> peak() const{ // optional for if eof 
            if(m_index>=m_src.length()) return {};
            else{
                return m_src[m_index];
            }

        }
        char consume(){
            return m_src[m_index++];

        }
    
        string m_src;
        int m_index;
};