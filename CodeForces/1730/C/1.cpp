/*
・なんとか自力AC！
・辞書順最小の貪欲
・辞書順最小を求めるので、小さい文字はなるべく操作せずそのまま残すようにする。
　よって、小さい文字から決めていくとして、邪魔な文字を後ろに送る感じにする。
　一度動かそうとしたやつは+1した状態で好きな場所に置けるとして別にして取っておく。
　今見ている文字が出現する末尾indexより手前にあるものは移動、後ろはそのまま。
　これを0から順にやっていけばOK。
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

void solve() {
    string S;
    cin >> S;
    ll N = S.size();

    string ans;
    vector<ll> cnt(10);
    for (char c : digits) {
        ll mxi = -1;
        string nxt;
        rep(i, S.size()) {
            if (S[i] == c) {
                mxi = i;
                cnt[c-'0']++;
            }
        }
        if (mxi != -1) {
            rep(i, S.size()) {
                if (S[i] != c) {
                    if (i < mxi) {
                        cnt[min(char(S[i]+1), '9')-'0']++;
                    } else {
                        nxt += S[i];
                    }
                }
            }
            S = nxt;
        }
        ans += string(cnt[c-'0'], c);
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
