/*
    Written by Jtaim
    Date 24 Nov 2019
    Stroustrup, Bjarne. Programming: Principles and Practice Using C++ . Pearson Education. Kindle Edition.

    Section 11 Exercise 11
    Write a function vector<string> split(const string& s, const string& w)
    that returns a vector of whitespace-separated substrings from the argument s,
    where whitespace is defined as �ordinary whitespace� plus the characters in w.
*/

#include"ppp.h"

std::vector<std::string> split(const std::string& s, const std::string& w);

int main()
try {
    std::string_view str{"Stroustrup, Bjarne. Programming: Principles and Practice Using C++ . Pearson Education. Kindle Edition."};
    std::string_view remove{R"(.,?/;"\:)"};
    auto white_space{split(str.data(), remove.data())};

    for(auto s : white_space) {
        std::cout << s << '\n';
    }

    ppp::keep_window_open();
    return 0;
} catch(std::exception & e) {
    std::cerr << "exception: " << e.what() << std::endl;
    ppp::keep_window_open();
    return 1;
} catch(...) {
    std::cerr << "exception\n";
    ppp::keep_window_open();
    return 2;
}

std::vector<std::string> split(const std::string& s, const std::string& w)
{
    std::string str{s};
    for(auto& ch : str) {
        for(const auto space : w) {
            if(space == ch) {
                ch = ' ';
                break;
            }
        }
    }
    std::vector<std::string> sub_strings;
    std::istringstream is{str};
    for(std::string sub; is >> sub; ) {
        sub_strings.push_back(sub);
    }
    return sub_strings;
}
