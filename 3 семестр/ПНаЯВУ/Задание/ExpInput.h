#ifndef EXPINPUT_H
#define EXPINPUT_H

#include <string>

class ExpInput 
{
public:
    static int getInt(const std::string& prompt, int min = -2147483647, int max = 2147483647);
    static double getDouble(const std::string& prompt, double min = -1.7e308, double max = 1.7e308);
    static std::string getString(const std::string& prompt, bool allowEmpty = false, bool allowNumbers = false);
    static void clearInputBuffer();
    static bool isNumber(const std::string& s);
    static bool containsOnlyLetters(const std::string& s);
    static bool containsNumbers(const std::string& s);
};

#endif 