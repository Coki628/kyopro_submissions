#include "../macros.hpp"
#include "gcd.hpp"

ll lcm(ll x, ll y) { return (x * y) / gcd(x, y); }
