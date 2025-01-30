#include "scanner.hpp"

const char* Scanner::TW[] = {
    "", // 0 позиция 0 не используется
    "and", // 1
    "begin", // 2
    "bool", // 3
    "do", // 4
    "else", // 5
    "end", // 6
    "if", // 7
    "false", // 8
    "int", // 9
    "not", // 10
    "or", // 11
    "program", // 12
    "read", // 13
    "then", // 14
    "true", // 15
    "var", // 16
    "while", // 17
    "write", // 18
    "type",//19
    "record",//20
    NULL
};

table_ident TID(100);

const char* Scanner::TD[] = {
    "", // 0 позиция 0 не используется
    "@", // 1
    ";", // 2
    ",", // 3
    ":", // 4
    ":=", // 5
    "(", // 6
    ")", // 7
    "=", // 8
    "<", // 9
    ">", // 10
    "+", // 11
    "-", // 12
    "*", // 13
    "/", // 14
    "<=", // 15
    "!=", // 16
    ">=", // 17
    ".", // 18
    NULL
};

type_of_lex Scanner::words[] = {
    LEX_NULL,
    LEX_AND,
    LEX_BEGIN,
    LEX_BOOLEAN,
    LEX_DO,
    LEX_ELSE,
    LEX_END,
    LEX_IF,
    LEX_FALSE,
    LEX_INT,
    LEX_NOT,
    LEX_OR,
    LEX_PROGRAM,
    LEX_READ,
    LEX_THEN,
    LEX_TRUE,
    LEX_VAR,
    LEX_WHILE,
    LEX_WRITE,
    LEX_TYPE,
    LEX_RECORD,
};

type_of_lex Scanner::dlms[] = {
    LEX_NULL,
    LEX_EOF,
    LEX_SEMICOLON,
    LEX_COMMA,
    LEX_COLON,
    LEX_ASSIGN,
    LEX_LPAREN,
    LEX_RPAREN,
    LEX_EQ,
    LEX_LSS,
    LEX_GTR,
    LEX_PLUS,
    LEX_MINUS,
    LEX_TIMES,
    LEX_SLASH,
    LEX_LEQ,
    LEX_NEQ,
    LEX_GEQ,
    LEX_DOT,
};

void Scanner::clear() {
    buf_top = 0;
    for (int j = 0; j < 80; ++j)
        buf[j] = '\0';
}

void Scanner::add() {                
    buf[buf_top++] = c;
}
int Scanner::look(const char* buf, const char** list) {
    int i = 0;
    while (list[i]) {
        if (!strcmp(buf, list[i]))
            return i;
        ++i;
    }
    return 0;
}

void Scanner::gc() {
    c = fgetc (fp);
    std::cout<<c;
}

Lex Scanner::get_lex() {
    int d, j;
    CS = H;
    do {
        switch (CS) {
            case H:
                if(c ==' ' || c =='\n' || c=='\r' || c =='\t')
                    gc ();
                else if(isalpha(c)) {
                    clear();
                    add();
                    gc();
                    CS = IDENT;
                }
                else if (isdigit(c)) {
                    d = c - '0';
                    gc();
                    CS = NUMB;
                }
                else if (c== '{') {
                    gc();
                    CS = COM;
                }
                else if (c== ':' || c== '<' || c== '>') {
                    clear();
                    add();
                    gc();
                    CS = ALE;
                }
                else if ((int)c == EOF)
                    return Lex(LEX_EOF);
                else if (c == '!') {
                    clear();
                    add();
                    gc();
                    CS = NEQ;
                }
                else
                    CS = DELIM;
                break;
            case IDENT:
                if (isalpha(c) || isdigit(c)) {
                    add();
                    gc();
                }
                else if ((j = look(buf, TW))) {
                        return Lex(words[j], j);
                    }
                else {
                    j = TID.put(buf);
                    return Lex(LEX_ID, j);
                }
                break;
            case NUMB:
                if (isdigit(c)) {
                    d = d * 10 + (c - '0');
                    gc();
                }
                else
                    return Lex(LEX_NUM, d);
                break;
            case COM:
                if (c == '}') {
                    gc();
                    CS = H;
                }
                else if (c == '@' || c == '{')
                    throw c;
                else
                    gc();
                break;
            case ALE:
                if ( c == '=' ) {
                    add();
                    gc();
                    j = look(buf, TD);
                    return Lex(dlms[j], j);
                }
                else {
                    j = look(buf, TD);
                    return Lex(dlms[j], j);
                }
                break;
            case NEQ:
                if ( c == '=' ) {
                    add();
                    gc();
                    j = look(buf, TD);
                    return Lex(LEX_NEQ, j);
                }
                else
                    throw '!';
                break;
            case DELIM:
                clear();
                add();
                if ((j = look(buf, TD))) {
                    gc();
                    return Lex(dlms[j], j);
                }
                else
                    throw c;
                break;
        } 
    } while(true);
}
Scanner::Scanner(const char* program) {
    fp = fopen(program, "r");
    CS = H;
    clear();
    gc();
}

