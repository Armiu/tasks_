#ifndef ENUM_HPP
#define ENUM_HPP

enum type_of_lex {
	LEX_NULL, // 0
	LEX_AND, // 1
	LEX_BOOLEAN, // 2
	LEX_DO, // 3
	LEX_ELSE, // 4
	LEX_IF, // 5
	LEX_FALSE, // 6
	LEX_INT, // 7
	LEX_NOT, // 8 
	LEX_OR, // 9
	LEX_PROGRAM, // 10
	LEX_READ, // 11
	LEX_TRUE, // 12
	LEX_WHILE, // 13
	LEX_WRITE, // 14
	LEX_STR, // 15
	LEX_GOTO, // 16
	LEX_SEMICOLON, // 17
	LEX_COMMA, // 18
	LEX_ASSIGN, // 19
	LEX_LPAREN, // 20
	LEX_RPAREN, // 21
	LEX_LBRACE, // 22
	LEX_RBRACE, // 23
	LEX_EQ, // 24
	LEX_LSS, // 25
	LEX_GTR, // 26
	LEX_PLUS, // 27
	LEX_MINUS, // 28
	LEX_MULT, // 29
	LEX_DIV, // 30
	LEX_MOD, // 31
	LEX_FRONTSLASH, // 32
	LEX_BACKSLASH, // 33
	LEX_LEQ, // 34
	LEX_NEQ, // 35
	LEX_GEQ, // 36
	LEX_PLUSEQ, // 37
	LEX_MINUSEQ, // 38
	LEX_QUOTE, //39
	LEX_COLON, // 40
	LEX_NUM, // 41
	LEX_ID, //42
	POLIZ_LABEL, // 43 | нужен для ссылок на номера элементов ПОЛИЗа
	POLIZ_GO, // 44 | для реализации goto, ссылка на конкретную лексему в ПОЛИЗе
	POLIZ_FGO, // 45 | условный переход по false
	LEX_EOF,//46
    LEX_BEGIN,//47
    LEX_BOOL,//48
    LEX_THEN,//49
    LEX_VAR,//50
    LEX_END,//51
    LEX_TIMES,//52
    LEX_SLASH,//53
    POLIZ_ADDRESS,//54
	LEX_RECORD,//55
    LEX_TYPE,//56
    LEX_DOT//57
};
#endif