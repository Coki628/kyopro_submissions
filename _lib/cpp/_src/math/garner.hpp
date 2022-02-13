#include "../combinatorics/ModInt.hpp"

// MOD復元
// ・int超ll以内みたいな数え上げをFPSやBMで殴る時に使う。
// ・FPS配列を2つ用意してそれぞれのmodで答えを出して、garnerに突っ込む。
// ・mint -> ll の型変換を一時的に有効にして使う。

constexpr int m1 = 998244353;
constexpr int m2 = 1004535809;
constexpr int inv_m1_mod_m2 = 669690699;
using mint1 = ModInt<m1>;
using mint2 = ModInt<m2>;

long long garner(long long r1, long long r2) {
    long long t = (r2 - r1) * inv_m1_mod_m2;
    while (t < 0) t += m2;
    t %= m2;
    r1 += t * m1;
    return r1;
}
