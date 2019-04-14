#include "Lex.h"

Lex::Lex(LexTypes type, std::string s, status k) {
    lex_type = type;
    lex_data = s;
    lex_status = k;
}

status Lex::give_status() {
    return lex_status;
}

std::string Lex::give_string() {
    return lex_data;
}