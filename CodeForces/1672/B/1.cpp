/*
・なんとか自力AC…。
・ランレングス。A..BA..Bの形は必須として、後ろからBの数だけやるとすると、
　余らせたAを前に任せて、最後に余らなければOK。
・なんかBが連続するとダメだと思ってて、間に差し込めば増やせることに気付くのに結構時間かかった。
　その後もAの数より多くできないと思って、各A..B区間は独立に見てたんだけど、
　これも違って、余ったAは前に回せるみたいな感じだったんだよね。色々考察外してた。
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

    if (S[0] == 'B' or S[N-1] == 'A') {
        NO();
        return;
    }

    auto rle = RLE(S);
    ll M = rle.size();
    ll rest = 0;
    rep(i, M-2, -1, -2) {
        assert(rle[i].first == 'A' and rle[i+1].first =='B');
        if (rle[i].second < rle[i+1].second) {
            rest += rle[i+1].second - rle[i].second;
        } else {
            rest = max(rest - (rle[i].second - rle[i+1].second), 0LL);
        }
    }
    if (rest > 0) {
        NO();
    } else {
        YES();
    }
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
