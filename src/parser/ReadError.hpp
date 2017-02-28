#pragma once
#include <string>
#include <stdexcept>



class ReadError: public std::exception {
public:
    ReadError(const std::string& file, const std::string& error):
        text {"Error occured while reading file "+file+": "+error} {}

    virtual const char* what() const noexcept {
        return text.c_str();
    }

private:
    std::string text;
};
