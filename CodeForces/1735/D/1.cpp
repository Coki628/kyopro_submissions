/*
参考：https://twitter.com/AllDirections4/status/1576616716054171649
　　　https://codeforces.com/blog/entry/107533
・自力ならず。。
・数え上げの考察自体は最初に考えたやつでほぼ合ってた…。
　mod 3で対になるやつを求めるパートで、6-a-bじゃなくて3-a-bってやってたせいで、
　負数modになってバグってた。まじでしょーもない…。
・結局、5つ組は3つ組2つで真ん中軸にしたやつでしか作れない、で合ってた。
　答え合わないからこの前提が違うんじゃないか、って疑ってた時間がもったいない。
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
    ll N, K;
    cin >> N >> K;
    vvl cards(N);
    set<vector<ll>> exists;
    rep(i, N) {
        cards[i] = LIST(K);
        exists.insert(cards[i]);
    }

    auto f = [&](vector<ll>& a, vector<ll>& b) {
        vector<ll> res(K);
        rep(i, K) {
            res[i] = (6-a[i]-b[i]) % 3;
        }
        return res;
    };

    map<vector<ll>, ll> C;
    rep(i, N) {
        rep(j, i+1, N) {
            auto res = f(cards[i], cards[j]);
            if (exists.count(res)) {
                C[cards[i]]++;
                C[cards[j]]++;
                C[res]++;
            }
        }
    }
    ll ans = 0;
    for (auto& [k, v] : C) {
        assert(v%3 == 0);
        v /= 3;
        ans += nC2(v);
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
