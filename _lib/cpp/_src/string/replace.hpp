#include "../base.hpp"

string replace(string str, const string& replace, const string& with) {
    if(!replace.empty()) {
        size_t pos = 0;
        while ((pos = str.find(replace, pos)) != string::npos) {
            str.replace(pos, replace.length(), with);
            pos += with.length();
        }
    }
    return str;
}
