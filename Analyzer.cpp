#include "Analyzer.h"

Analyzer::Analyzer (char * file_name) {
    current = Null;
    Error_exit = false;


    fin = fopen(file_name, "r");

    Init_flag = true;

    build_table();
}

char Analyzer::get_next() {
    char c;
    c = getc(fin);
    return c;
}

void Analyzer::put_back (char c) {
    ungetc(c, fin);
}

void Analyzer::build_table() {
    bool flag = true;

    while (flag) {

        Lex new_lex = new_getlex();

        status stat = new_lex.show_status();

        switch (stat) {
            case Init:
                if (Init_flag) {
                    Init_flag = false;
                } else {
                    Error_exit = true;
                    flag = false;
                    std::cout << "test, we're here";
                }
                break;
            case Error:
                flag = false;
                Error_exit = true;
                break;
            case End:
                flag = false;
                break;
            case Null:
                break;
            default:
                if (new_lex.show_status() != Null)
                    table.push_back(new_lex);
                break;
        }

    }

    if (Error_exit) {
        std::cout << "An error occured during parsing" << std::endl;
    } else
        std::cout << "Input file ended, all okay, down you'll get contained \n" << std::endl;
}

void Analyzer::Shutdown() {
    if (Error_exit)
        std::cout << "Analyzer stopped in case of error" << std::endl;
}

void Analyzer::show_table() {
    for (int i = 0; i < table.size(); i++) {
        table[i].show_item();

    }
}

char Analyzer::skip_spaces(char buff) {
    while ((buff == ' ') || (buff == '\n') || (buff == '\t') || (buff == '/')) {

        while ((buff == ' ') || (buff == '\n') || (buff == '\t'))
            buff = get_next();

        if (buff == '/') {
            buff = get_next();
            if (buff == '*') {
                bool inner_flag = true;
                while (inner_flag) {
                    buff = get_next();
                    if (buff == '*') {
                        buff = get_next();
                        if (buff == '/')
                            inner_flag = false;
                    }
                }
                buff = get_next();
            }
        }

    }
    return buff;
}


Lex Analyzer::new_getlex() {
    char buff = get_next();

    std::string hold_name = "";
    std::string hold_data = "";
    int hold_value = 0;
    status hold_status = Null;

    buff = skip_spaces(buff);
    if (buff == EOF) {
            //End part
            hold_status = End;
    } else {


        switch(current) {

            case Commentary: {

                bool comm_flag = true;
                hold_status = Commentary;

                while (comm_flag) {
                    hold_data += buff;
                    buff = get_next();

                    if (buff == '*') {
                        char buff1 = get_next();
                        if (buff1 == '/')
                            comm_flag = false;
                        else
                            put_back(buff1);
                    }

                    if (buff == EOF) {
                        comm_flag = false;
                        hold_status = Error;
                    }
                }
            }
                break;
            case Int: {
                buff = skip_spaces(buff);

                while (isalpha(buff)) {
                    hold_name += buff;
                    buff = get_next();
                }
                put_back(buff);

                buff = skip_spaces(buff);

                if (buff == '=') {
                    hold_status = Const_Int;

                    buff = get_next();
                    buff = skip_spaces(buff);

                    std::string inner_hold = "";

                    while (isdigit(buff)) {

                        //число собирается нормально

                        hold_value = hold_value * 10 + (buff - '0');

                        buff = get_next();

                    }

                } else {
                    hold_status = Int;
                }

                buff = skip_spaces(buff);

                if (buff == ',') {
                    current = Int;
                } else if (buff == ';') {
                    current = Null;
                } else {
                    // can't be anything else but these 2 symbols
                    current = Null;
                    hold_status = Error;
                }
            }
                break;
            case String: {
                buff = skip_spaces(buff);

                while (isalpha(buff)) {
                    hold_name += buff;
                    buff = get_next();
                }
                put_back(buff);

                buff = skip_spaces(buff);

                if (buff == '=') {
                    hold_status = Const_Str;

                    buff = get_next();

                    buff = skip_spaces(buff);

                    if (buff == '"') {
                        buff = get_next();
                        while (buff != '"') {
                            hold_data += buff;
                            buff = get_next();
                        }
                    } else {
                        // no string starting
                        hold_status = Error;
                    }

                    buff = get_next();

                } else {
                    hold_status = String;
                }

                buff = skip_spaces(buff);

                if (buff == ',') {
                    current = String;
                } else if (buff == ';') {
                    current = Null;
                } else {
                    // can't be anything else but these 2 symbols
                    current = Error;
                }

            }
                break;
            case Null: {
                // default status at a new command after ;

                buff = skip_spaces(buff);

                if (isalpha(buff)) {
                    //a letter
                    std::string inner_hold = "";
                    while (isalpha(buff)) {
                        inner_hold += buff;
                        buff = get_next();
                    }

                    put_back(buff);
                    hold_status = Null;
                    if (inner_hold == "int") {
                        current = Int;
                    } else if (inner_hold == "string") {
                        current = String;
                    } else if (inner_hold == "if") {
                        current = If;
                    } else if (inner_hold == "while") {
                        current = While;
                    } else if (inner_hold == "read") {
                        current = Read;
                    } else if (inner_hold == "write") {
                        current = Write;
                    } else if (inner_hold == "else") {
                        current = Null;
                        hold_status = Else;
                    } else if (inner_hold == "program") {
                        current = Null;
                        hold_status = Init;
                    }else {
                        current = Null;
                        hold_status = Undeclared;
                    }
                } else {
                    if (buff == '{') {
                        current = Null;
                        hold_status = FB_L;
                    } else if (buff == '}') {
                        current = Null;
                        hold_status = FB_R;
                    }
                }




            }
                break;
            default: {
                // default state will work with If, Read, Write, While - all operators, whose commands are inside ()


                    buff = skip_spaces(buff);

                    if (buff != '(') {
                        hold_status = Error;
                        current = Error;
                    } else {
                        hold_status = current;

                        buff = get_next();

                        while(buff != ')') {
                            hold_data += buff;
                            buff = get_next();
                            if (buff == EOF) {
                                hold_status = Error;
                                current = Error;
                                break;
                            }
                        }
                    }
                    current = Null;
                    buff = skip_spaces(buff);
                    if (buff == ';') {
                        buff = get_next();
                    }

            }
                break;
        }


    }

    Lex New_lex(hold_status, hold_name, hold_data, hold_value);

    return New_lex;


}