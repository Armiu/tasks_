#include <vector>
#include <cstring>
#include <iostream> 
#include <fstream>
#include "MyString.hpp"
#include "BlockString.hpp"
#include "BlockSelection.hpp"
#include "Selection.hpp"
#include "Ostream.hpp"

int main() {
    
    //strings::BlockSelection q = s1 * 1 + 2 * s1 ;
    std :: string s = "abc" ;
    strings :: MyString a , b = "a" , c = s ;
    strings :: BlockString bstr = a + b * 1 + 2 * c ;
    //std :: cout << bstr << std :: endl ;

    strings :: cout << strings :: array << bstr << "\n"; 
    strings :: cout << strings :: plain << bstr << "\n"; // Prints aabcabc
    strings :: cout << bstr (3) << ' ' << bstr [3] << "\n"; // c abc
    
    std :: ofstream z("a.txt");
    strings :: output fout ( z );
    fout << strings :: plain << bstr << "\n"; // Prints aabcabc to file a . txt
    //fout . close (); // Closes file a . txt

    std :: vector < std :: vector < int > > v = {{4 , 3 , 2 , 1 , 0} , {3 , 5 , 10} , {0}};
    strings :: BlockSelection f(v);
    strings :: cout << strings :: array << f(bstr) << "\n"; // {" acbaa " , " cb ?" , " a "}
    strings :: cout << strings :: plain << f(bstr) << "\n"; // acbaacb ? a

    v = {{1 , 2 , 1} , {4 , 5 , 5}};
    strings :: BlockSelection g(v);
    strings :: cout << strings :: array << g(bstr) << "\n"; // {" aba " , " abb "}
    strings :: cout << strings :: plain << g(bstr) << "\n"; // abaabb

    strings :: BlockSelection fg = f ( g ); // fg = {{5 , 4 , 1 , 2 , 1} , {4 , 5 , -1} , {1}}
    //std:: cout << fg<< "\n";
    strings :: cout << f << "\n" << g << "\n" << fg << "\n";
    // Prints {" baaba " , " ab ?" , " a "}:
    strings :: cout << strings :: array << fg ( bstr ) << "\n";
    strings :: cout << strings :: plain << fg ( bstr ) << "\n"; // baabaab ? a

    strings :: Selection shift_left ( std :: vector < int >({1 , 2 , 3 , 4 , 5 , 6 , 7 , 8 , 0}));
    strings :: BlockSelection h = shift_left ( fg );
    // h = {{4 , 1 , 2 , 1 , 4 , 5 , -1 , 1 , 5}}
    strings :: cout << strings :: array << h ( c ) << '\n'; // {"? bcb ??? b ?"}
    strings :: cout << strings :: plain << h ( c ) << '\n'; // ? bcb ??? b ?


    shift_left = std :: vector < int >({1 , 2 , 0});
    strings :: Selection shift_right ( std :: vector < int >({2 , 0 , 1}));
    f = shift_left * 1 + 2 * shift_right ;
    // f = {{1 , 2 , 0} , {2 , 0 , 1} , {2 , 0 , 1}}
    strings :: cout << strings :: array << f(s) << '\n'; // {" bca " , " cab " , " cab "}
    strings :: cout << strings :: plain << f(s) << '\n'; // bcacabcab
    a = "b";
    bstr = ( shift_right + shift_left ( shift_right ))( a + b * 2);
    strings :: cout << strings :: array << bstr << '\n'; // {" aba " , " baa "}
    strings :: cout << strings :: plain << bstr << '\n'; // ababaa
    return 0;
}        