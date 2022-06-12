/*
・きっちり自力AC！
・辞書順最小、貪欲
・とりあえずソートしておく。で、カウントがKに達してしまったら他方とする。
　それ以外は常に今出せる小さい方を出す。
　両側で同じ文字が来るみたいな厄介っぽい状況は問題設定で排除されているので、やる。
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
    ll N, M, K;
    cin >> N >> M >> K;
    string S[2];
    cin >> S[0] >> S[1];

    string ans;
    ll cnt = 0, prv = -1;
    sort(S[0].rbegin(), S[0].rend());
    sort(S[1].rbegin(), S[1].rend());
    while (S[0].size() and S[1].size()) {
        if (cnt == K) {
            ans += S[1-prv].back();
            S[1-prv].pop_back();
            prv = 1 - prv;
            cnt = 1;
        } elif (S[0].back() < S[1].back()) {
            ans += S[0].back();
            S[0].pop_back();
            if (prv == 0) {
                cnt++;
            } else {
                cnt = 1;
            }
            prv = 0;
        } else {
            ans += S[1].back();
            S[1].pop_back();
            if (prv == 1) {
                cnt++;
            } else {
                cnt = 1;
            }
            prv = 1;
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
