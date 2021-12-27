#pragma once
#include "../base.hpp"

// シード生成
mt19937_64 mt(chrono::steady_clock::now().time_since_epoch().count());
