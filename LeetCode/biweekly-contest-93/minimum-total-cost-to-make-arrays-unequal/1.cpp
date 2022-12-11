/*
・なんとか自力AC。。
・こんなんどうせ無理だよーって言いながらガチャガチャやってたら通った。。
　まず、基本的に最初からA[i]=B[i]になってる場所だけで回せる。
　偶数なら自明にOKだし、A[0]を使うとコスト0なので奇数でもうまいことやれる(と信じる)。
　これが無理なのは同じ数がたくさんある時。具体的には、
　変えるべき場所の数の半分超くらい同じ値だったらその分は余分に連れてくる。
　index小さい方が低コストなので前から順に、未使用でA[i]もB[i]もその最大個数の値と被らない所を使う。
　こんなん絶対何かしら考慮漏れてるだろーって言いながらも、
　適当にぶん投げてしょうもないバグ直したら無事AC…。
・こういう系は通せてもマグレ感しかないのでそんなに嬉しくないよなー。。
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#define CONSTANTS
#define __LOCAL
// #define CAST_MINT_TO_LL
#include "base.hpp"

constexpr long long INF = 1e18;
// constexpr long long INF = LONG_LONG_MAX;
constexpr int MOD = 1000000007;
// constexpr int MOD = 998244353;
constexpr long double EPS = 1e-10;
constexpr long double PI = M_PI;

#include "macros.hpp"
#include "combinatorics/ModInt.hpp"
using mint = ModInt<MOD>;
#include "template.hpp"

class Solution {
public:
    long long minimumTotalCost(vector<int> &A, vector<int> &B) {
        int N = A.size();
        HashMap<ll, ll> C;
        ll diffsm = 0;
        ll cost = 0;
        vector<int> used(N);
        rep(i, N) {
            if (A[i] == B[i]) {
                used[i] = true;
                C[A[i]]++;
                diffsm++;
                cost += i;
            }
        }
        if (C.empty()) {
            return 0;
        }
        auto [v, k] = most_common(C)[0];
        if (v <= diffsm / 2) {
            return cost;
        } else {
            ll rest = v - (diffsm - v);
            bool done = false;
            rep(i, N) {
                if (not used[i] and A[i] != k and B[i] != k) {
                    cost += i;
                    rest--;
                    if (rest == 0) {
                        done = true;
                        break;
                    }
                }
            }
            if (done) {
                return cost;
            } else {
                return -1;
            }
        }
    }
};

#ifdef __LOCAL
int main() {
    // Solution sol;
    // auto res = sol.funcName();
    // print(res);
    return 0;
}
#endif
