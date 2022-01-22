/*
・自力ならず。。
・回文
・さんざん悩んだ後、これ4文字以上取っとく必要ないんじゃあ、って所まで感づいたのに、
　3文字以下だけ持っての判定方法がミスってて通せず。。
・反転したやつで判定するとして、取っておく必要のある文字列は、
　そのまま、1字減らし、に加えて、任意の1文字増やしたやつも必要だった。
・途中、今見てる方も削ってみたりしたんだけど、両方加工するとバグる感じだったから、
　持っておく方をいじって、今見てる方はそのままにした。
　でもこれ逆の方が、setに持っておく要素数が明らかに少ないので速いかも。
・やってみた。やっぱ全然速い。AC0.48秒→0.17秒。
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#define CONSTANTS
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
    ll N;
    cin >> N;
    vector<string> S(N);
    rep(i, N) cin >> S[i];

    set<string> se;
    rep(i, N) {
        if (S[i][0] == S[i].back()) {
            YES();
            return;
        }
        auto rev = S[i];
        reverse(ALL(rev));
        if (se.count(rev) or se.count(rev.substr(0, rev.size()-1))) {
            YES();
            return;
        }
        for (auto c : ascii_lowercase) {
            if (se.count(rev+c)) {
                YES();
                return;
            }
        }
        se.insert(S[i]);
    }
    NO();
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
