/*
・自力ならず。。惜しい所まで来てたのにな。
　最終的にWAが取れずに時間切れだったんだけど、
　速度のために途中でintにしたansがオーバーフローしてただけだった…。
・使わない1文字を固定して、残りの25種を全て奇数にするとすると、
　ペアの片方で奇数のものが決まれば、他方で奇数にする必要がある文字種も定まる。
　それぞれ奇数個ある文字の集合をmapに詰めておけば、ペアになりうる個数が分かる。
　なんだけど、使わない文字と偶数個カウントは気をつけないと同一視してしまいそうだし、
　途中で数値とcharを切り替えたりで実装ガチャガチャするし、
　まあとにかくうまくまとまらなくてしんどいコードになってしまった。
　あとペア組ませた時の長さが奇数ってのも大分後で気付いたし…。
・なんかTLがきつくて、map撃墜用hackケースが仕込まれてるらしい。
　mapだと3.04秒、HashMapにしたら1.56秒だった。(TL4秒だからまあセーフだけども)
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
// constexpr int MOD = 1000000007;
constexpr int MOD = 998244353;
constexpr long double EPS = 1e-10;
constexpr long double PI = M_PI;

#include "macros.hpp"
#include "combinatorics/ModInt.hpp"
using mint = ModInt<MOD>;
#include "template.hpp"

#include "common/HashMap.hpp"

void solve() {
    int N;
    cin >> N;
    vector<string> S(N);
    cin >> S;

    int M = 26;
    HashMap<string, int> mp[M];
    vector<string> T(N);
    auto none = listnd(N, M, true);
    rep(i, N) {
        vector<int> cnt(M);
        for (auto c : S[i]) {
            cnt[c - 'a']++;
            none[i][c - 'a'] = false;
        }
        string odd;
        rep(j, M) {
            if (cnt[j] % 2 == 1) {
                odd += 'a' + j;
            }
        }
        T[i] = odd;
        rep(j, M) {
            if (none[i][j] and S[i].size() % 2 == 1) {
                mp[j][odd]++;
            }
        }
    }

    ll ans = 0;
    rep(j, M) {
        char nonec = 'a' + j;
        rep(i, N) {
            if (not none[i][j] or S[i].size() % 2 == 1) continue;
            assert(not count(ALL(T[i]), nonec));
            string target;
            rep(k, M) {
                char c = 'a' + k;
                if (c != nonec and not count(ALL(T[i]), c)) {
                    target += c;
                }
            }
            if (mp[j].count(target)) {
                ans += mp[j][target];
            }
        }
    }
    print(ans);
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);
    cout << fixed << setprecision(15);

    // single test case
    solve();

    // multi test cases
    // int T;
    // cin >> T;
    // while (T--) solve();

    return 0;
}
