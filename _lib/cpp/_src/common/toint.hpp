#pragma once
#include "../base.hpp"

ll toint(string s) {
    assert(s.size() < 20);
    ll res = 0;
    for (char &c : s) {
        res *= 10;
        res += c - '0';
    }
    return res;
}

int toint(char num) {
    return num - '0';
}
