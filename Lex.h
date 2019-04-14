#pragma once

#include <iostream>
#include <string>

enum LexTypes {
    Lex_NULL,
    Lex_Program, Lex_LFB, Lex_RFB, Lex_int, Lex_str,  // 1-5
    Lex_int_const, Lex_str_const, Lex_if, Lex_else, Lex_while,  //6-10
    Lex_read, Lex_write,  //11-12
};

enum status {
    Start, // 0
    Digit, Const_str, Identifier, Error, End,  // 1-5
    Commentary

    Null,


    // Identifier is =, /, *, and so on
};


class Lex {
private:
    LexTypes lex_type;
    status lex_status;
    std::string lex_data;
public:
    Lex(LexTypes, std::string, status);
    status give_status ();
    std::string give_string ();
};
