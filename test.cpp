#include <iostream>
#include <string>

int main()
{
    std::string line(80, '-');
    std::string str = "Centered Text";

    if (str.length() < line.length())
    {
        int padding = (line.length() - str.length()) / 2;
        line.replace(padding, str.length(), str);
    }
    else
    {
        // String is too long, truncate it
        str = str.substr(0, line.length());
        line.replace(0, str.length(), str);
    }

    std::cout << line << std::endl;

    return 0;
}
