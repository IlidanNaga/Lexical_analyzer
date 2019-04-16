#include "Lex.h"

Lex::Lex(status stat, std::string name, std::string data, int val) {
    lex_status = stat;
    lex_name = name;
    lex_data = data;
    lex_value = val;
}

Lex::Lex(const Lex &other) {
    lex_status = other.lex_status;
    lex_name = other.lex_name;
    lex_data = other.lex_data;
    lex_value = other.lex_value;
}

void Lex::show_item() {
    switch (lex_status) {
        case Null:
            std::cout << "Null ";
            break;
        case Init:
            std::cout << "Init ";
            break;
        case Error:
            std::cout << "Error ";
            break;
        case Variable:
            std::cout << "Variable ";
            break;
        case Int:
            std::cout << "Int ";
            break;
        case String:
            std::cout << "String ";
            break;
        case Const_Int:
            std::cout << "Const_Int ";
            break;
        case Const_Str:
            std::cout << "Const_Str ";
            break;
        case If:
            std::cout << "If ";
            break;
        case Else:
            std::cout << "Else ";
            break;
        case While:
            std::cout << "While ";
            break;
        case Read:
            std::cout << "Read ";
            break;
        case Write:
            std::cout << "Write ";
            break;
        case End:
            std::cout << "End ";
            break;
        case FB_L:
            std::cout << "{ ";
            break;
        case FB_R:
            std::cout << "} ";
            break;
        case Commentary:
            std::cout << "Commentary ";
            break;
        default:
            std::cout << "Undeclared ";
            break;
    }

    std::cout << lex_name << " " << lex_data << " " << lex_value << std::endl;
}

status Lex::show_status() {
    return lex_status;
}