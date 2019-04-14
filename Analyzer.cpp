#include "Analyzer.h"


Analyzer::Analyzer (std::string file_name) {
    fin.open(file_name, std::ios::in);
    current = Start;
    Error_exit = false;
    build_table();
}

char Analyzer::get_next() {
    char c;
    fin >> c;
    return c;
}

void Analyzer::put_back (char c) {
    fin.putback(c);
}

Lex Analyzer::getlex () {

    std::string hold = "";
    char buff;
    buff = get_next();
    if (buff == '\n') {
        buff = get_next();
    }

    if (buff == EOF) {
        current = End;
    } else {
        if (current == Start) {
            if (!isalpha(buff)) {
                if (buff == '/') {
                    char buff1 = get_next();
                    if (buff1 == '*')
                        current = Commentary;
                    else {
                        put_back(buff1);
                        current = Error;
                    }
                } else
                    current = Error;
            }
        } else {
            if (isalpha(buff))
                current = Const_str;
            else if (isdigit(buff))
                current = Digit;
            else {
                if (buff == '/') {
                    char buff1 = get_next();
                    if (buff1 == '*')
                        current = Commentary;
                    else {
                        put_back(buff1);
                        current = Identifier;
                    }
                } else {

                    current = Identifier;

                }
            }
        }
    }

    switch (current) {
        case Start: {
            while (isalpha(buff)) {
                hold += buff;
                buff = get_next();
            }
            put_back(buff);

            if (hold != "program") {
                std::cout << "Error: first lexeme isn't program" << std::endl;
                Error_exit = true;
            }
            break;
        }

        case Commentary: {
            buff = get_next();
            bool flag_commentary = true;

            while (flag_commentary) {
                hold += buff;
                buff = get_next();

                if (buff == '*') {
                    char buff1 = get_next();
                    if (buff1 == '/') {
                        flag_commentary = false;
                    } else {
                        put_back(buff1);
                    }
                }
            }
        }

        case Digit: {

            while (isdigit(buff)) {
                hold += buff;
                buff = get_next();
            }

            put_back(buff);

        }

            break;

        case Error:
            std::cout << "Error in defining lexems" << std::endl;
            Error_exit = true;
            break;
        case Const_str: {

            while (isalpha(buff) || isdigit(buff)) {
                hold += buff;
                buff = get_next();
            }

            put_back(buff);

        }

            break;
        case Identifier: {
            // first of all, what is identifier for me... i guess it's /, *, =, +, +=, >, <, and so on
            // so it'd be classified as not digit, not letter, not space button

            while (!isalpha(buff) && !isdigit(buff) && (buff != ' ')) {
                hold += buff;
            }

            put_back(buff);
        }
            break;
        case End: {

            std::cout << "Ending lexcemes scanning" << std::endl;

        }

            break;
        default:

            break;
    }
    Shutdown();

    Lex new_lex(hold, current);

    return new_lex;

}

void Analyzer::build_table() {
    table.push_back(getlex());
}

void Analyzer::Shutdown() {
    if (Error_exit)
        std::cout << "Analyzer stopped in case of error" << std::endl;
}

void Analyzer::show_table() {
    for (int i = 0; i < table.size(); i++) {
        std::cout << table[i].give_string() << "   " << table[i].give_status() << std::endl;

    }
}

Lex Analyzer::new_getlex() {

}