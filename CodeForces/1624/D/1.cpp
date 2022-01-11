/*
・なんとか自力AC！
・回文、決め打ち二分探索
・決め打ちにぶたんしたけど実装こじらせてタイムロス…。
　判定する文字列長が奇数の時真ん中に割り当てるやつをどうするかで、
　まずは偶数個だけ使って余った分で真ん中に割り当てようとしたけど、
　余りが少なかったら既に作った分切り崩さないといけないなーとか考えてたらぐちゃぐちゃに…。
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#define CONSTANTS
#include "../../../_lib/cpp/_src/base.hpp"

constexpr long long INF = 1e18;
// constexpr long long INF = LONG_LONG_MAX;
constexpr int MOD = 1000000007;
// constexpr int MOD = 998244353;
constexpr long double EPS = 1e-10;
constexpr long double PI = M_PI;

#include "../../../_lib/cpp/_src/macros.hpp"

#include "../../../_lib/cpp/_src/combinatorics/ModInt.hpp"
using mint = ModInt<MOD>;

#include "../../../_lib/cpp/_src/template.hpp"

void solve() {
    ll N, K;
    cin >> N >> K;
    string S;
    cin >> S;

    auto C = Counter(S);
    ll res = bisearch_max(1, N+1, [&](ll m) {
        bool odd = false;
        if (m%2 == 1) {
            odd = true;
            m--;
        }
        ll cnt = 0;
        vector<ll> rest;
        for (auto [k, v] : C) {
            cnt += v/m;
            rest.eb(v%m);
        }
        ll sm = 0;
        ll oddcnt = 0;
        for (ll a : rest) {
            if (a%2 == 1) {
                oddcnt++;
                a--;
            }
            sm += a;
        }
        cnt += sm/m;
        sm = sm%m;
        sm += oddcnt;

        ll res = 0;
        if (odd) {
            ll use = min(cnt, sm);
            res += use;
            cnt -= use;
            sm -= use;
            while (cnt) {
                sm = m;
                cnt--;
                use = min(cnt, sm);
                res += use;
                cnt -= use;
                sm -= use;
            }
        } else {
            res = cnt;
        }
        return res >= K;
    });
    print(res);
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
