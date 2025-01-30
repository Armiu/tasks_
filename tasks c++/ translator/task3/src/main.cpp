#include <iostream>
#include "interpretator.hpp"

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <filename>\n";
        return 1;
    }
    const char* filename = argv[1];
    try {
        Interpretator I(filename);
        I.interpretation();
        return 0;
    }
    catch (char c) {
        std::cout << "unexpected symbol " << c << std::endl;
        return 1;
    }
    catch (Lex l) {
        std::cout << "unexpected lexeme";
        std::cout << l;
        return 1;
    }
    catch (const char *source) {
        std::cout << source << std::endl;
        return 1;
    }
}
