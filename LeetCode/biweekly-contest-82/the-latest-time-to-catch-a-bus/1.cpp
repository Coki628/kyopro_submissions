/*
・自力AC。
・イベントソート
・ソートしてシミュしてうまいこと見るんだけど、
　他の人と同じ位置ダメとか地味にめんどくて時間食ってしまった…。
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
    int latestTimeCatchTheBus(vector<int>& A, vector<int>& B, int cap) {
        ll N = A.size();
        ll M = B.size();
        sort(ALL(A));
        sort(ALL(B));
        vector<pll> events;
        rep(i, N) {
            events.eb(A[i], 2);
        }
        rep(i, M) {
            events.eb(B[i], 1);
        }
        set<ll> se(ALL(B));
        sort(ALL(events));
        deque<ll> que;
        ll ans = 0;
        for (auto [t, op] : events) {
            if (op == 1) {
                que.pb(t);
            } elif (op == 2) {
                if (que.size() < cap) {
                    que.clear();
                    ll val = t;
                    while (se.count(val)) val--;
                    chmax(ans,val);
                } else {
                    ll last = -1;
                    rep(_, cap) {
                        if (que.empty()) break;
                        last = que.front();
                        que.pop_front();
                    }
                    assert(last != -1);
                    ll val = last - 1;
                    while (se.count(val)) val--;
                    chmax(ans, val);
                }
            }
        }
        return (int)ans;
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
