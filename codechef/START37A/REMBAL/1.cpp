/*
・きっちり自力AC！
・括弧列
・題意を整理すると、結局元の列で組めなかった場所はどんなにずれても
　連鎖で後から組めるようになることはなさそう、となる。
・であれば普通に括弧列の判定で消せる所を消す感じで、
　操作回数も最小化するので、まとまった場所は1回で消すとする。
　これをやるために、組めなかった場所のindexを保持しておく。
　組めなかった場所の個数がそのまま残る個数で、
　indexが隣接してない箇所の数だけ操作が必要となる。
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#define CONSTANTS
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

void solve() {
    string S;
    cin >> S;
    ll N = S.size();

    vector<pll> st;
    rep(i, N) {
        if (S[i] == '(') {
            st.eb(0, i);
        } else {
            if (st.size() and st.back().first == 0) {
                st.pop_back();
            } else {
                st.eb(1, i);
            }
        }
    }

    auto [_, ids] = zip(st);
    ids.insert(ids.begin(), -1);
    ids.eb(N);
    pll ans;
    ans.first = st.size();
    rep(i, 1, ids.size()) {
        if (ids[i-1]+1 != ids[i]) {
            ans.second++;
        }
    }
    print(ans);
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);
    cout << fixed << setprecision(15);

    // single test case
    // solve();

    // multi test cases
    int T;
    cin >> T;
    while (T--) solve();

    return 0;
}
