#include <iostream>
using namespace std;
#include <fstream>
#include <sstream>
#include <optional>
#include <vector>
#include <string>
#include <cctype>
#include <cstdlib>
#include "./tokenization.hpp"




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
    tokenizer tokenizer(contents);
    vector<Token> tokens = tokenizer.tokenize();
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