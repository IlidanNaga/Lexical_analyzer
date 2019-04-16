#pragma once

#include <iostream>
#include <string>

enum status {
    Null,
    Init, Error, Variable,// 1-3
    Int, String, Const_Int, Const_Str, // 4-7
    If, Else, While, Read, Write, // 8-12
    End, FB_L, FB_R, Commentary,  // 13-16
    Undeclared

    // Identifier is =, /, *, and so on
};


class Lex {
private:
    status lex_status;

    std::string lex_name;
    std::string lex_data;
    int lex_value;
public:
    Lex(status, std::string, std::string, int);

    Lex(const Lex &);

    void show_item();
    status show_status();
};
