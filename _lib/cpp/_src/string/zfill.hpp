#include "../macros.hpp"

string zfill(string str, int len) {
    string zeros;
    int n = str.size();
    rep(i, len-n) zeros += '0';
    return zeros+str;
}
