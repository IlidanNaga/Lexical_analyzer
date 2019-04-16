#pragma once

#include "Lex.h"
#include <vector>
#include <fstream>



class Analyzer {
private:

    FILE *fin;

    status current;
    bool Error_exit;
    std::vector<Lex> table;

    bool Init_flag;
public:
    Analyzer (char * file_name);

    char get_next();

    void put_back (char c);
    void build_table();
    void Shutdown();

    void show_table();

    Lex new_getlex();

    char skip_spaces(char buff);

};