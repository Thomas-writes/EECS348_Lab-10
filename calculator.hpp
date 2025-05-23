#ifndef __CALCULATOR_HPP
#define __CALCULATOR_HPP

#include <string>

// this function should expect that `expression` has already been
// validated and thus throw no exceptions
double parse_number(const std::string &expression);
std::string stringadd(std::string &s, std::string &s2);
bool isValidDoubleString(const std::string& s);

#endif // __CALCULATOR_HPP
