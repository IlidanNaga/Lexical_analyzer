#pragma once

#include "Lex.h"
#include <vector>
#include <fstream>



class Analyzer {
private:
    std::ifstream fin;
    status current;
    bool Error_exit;
    std::vector<Lex> table;
public:
    Analyzer (std::string file_name);

    char get_next();

    void put_back (char c);
    Lex getlex ();
    void build_table();
    void Shutdown();

    void show_table();

    Lex new_getlex();

};