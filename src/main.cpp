#include <iostream>
using namespace std;
#include <fstream>
#include <sstream>
#include <optional>
#include <vector>
#include <string>
#include <cctype>
#include <cstdlib>
//#include "./tokenization.hpp"


enum class TokenType{
    exit,
    int_lit,
    semi

};
struct Token{
    TokenType type;
    std::optional<std::string> value;
};

vector<Token> tokenize(const string& str){
    vector<Token> tokens{};
    string buff{};
    for(int i=0; i<str.size(); i++){
        char c=str.at(i);
        if(isalpha(c)){
            buff.push_back(c);
            i++;
            while(i<str.size()&&isalnum(str.at(i))){
                buff.push_back(str.at(i));
                i++;
            }
            i--;
            if(buff == "exit"){
                tokens.push_back({.type =TokenType::exit});
                buff.clear();
            }
            else{ 
                cerr<<"faaaaaaaaaa you messed up (but its okay mistakes are how we grow)";
                exit(EXIT_FAILURE);
            }
        

        }
        else if (isdigit(c)){
            buff.push_back(c);
            i++;
            while(i<str.size()&&isdigit(str.at(i))){
                buff.push_back(str.at(i));
                i++;
            }
            i--;
            tokens.push_back({.type = TokenType::int_lit, .value = string(buff.begin(), buff.end())});
            buff.clear();
        }
        else if(c==';'){
            tokens.push_back({.type = TokenType::semi});
        }
        else if(isspace(c)){
            continue;
        }
        else{
            cerr<<"you messed up";
            
            exit(EXIT_FAILURE);
        }
    }
    return tokens;

}

string tokens_to_asm(const vector<Token>& tokens) {
    stringstream output;

    output << "global _start\n";
    output << "_start:\n";

    for (int i = 0; i < tokens.size(); i++) {
        const Token& token = tokens.at(i);

        if (token.type == TokenType::exit) {
            if (i + 2 < tokens.size() &&
                tokens.at(i + 1).type == TokenType::int_lit &&
                tokens.at(i + 2).type == TokenType::semi) {

                output << "    mov rax, 60\n";
                output << "    mov rdi, " << tokens.at(i + 1).value.value() << "\n";
                output << "    syscall\n";
            }
        }
    }

    return output.str();
}

int main(int argc, char* argv[]){

    if(argc!=2){
        cerr<<"Incorrect usage. Correct usage is..."<<endl;
        cerr<<"helium <input.he>"<<endl;
        return EXIT_FAILURE;
    }
    fstream input(argv[1], ios::in);
    string contents;
    {
        stringstream contents_stream;
        contents_stream << input.rdbuf();
        contents = contents_stream.str();
    }

    //cout<<contents<<endl;
    auto tokens = tokenize(contents);
    for (const auto& token : tokens) {
    cout << static_cast<int>(token.type);

    if (token.value.has_value())
        cout << " " << token.value.value();
    }
    cout<<tokens_to_asm(tokens)<<endl;
    {
        fstream file("out.asm", ios::out); //outputting to assembly
        file<<tokens_to_asm(tokens);
    }
    system("nasm -felf64 out.asm ");
    system("ld -o out out.o");
    
    return 0;

}