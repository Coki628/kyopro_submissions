/*
参考：https://twitter.com/kyopro_friends/status/1474738164401340420
・あー、これだよね、やっぱり。ってなった。
・累積和して、前から進めて自身が終わったら出現済としてmapに詰めれば、
　自分より後ろをやる時には左端の候補として数えられる。
・初手で総和0にするがどうとか思ったのが思いっきりハズレ方針だったな。。
　そういう意味ではそこに固執しないでさっさとWM使ったのはむしろ良かったんだけど、
　それにしてもこれは見たことあり過ぎる方針なので、自分で出なかったのはダメ過ぎる…。
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

constexpr long long INF = 1e18;
// constexpr long long INF = LONG_LONG_MAX;
constexpr int MOD = 1000000007;
// constexpr int MOD = 998244353;

#include "../../../_lib/cpp/template.hpp"

void solve() {
    ll N, K;
    cin >> N >> K;
    auto A = LIST(N);

    vector<ll> acc(N+1);
    rep(i, N) {
        acc[i+1] = acc[i]+A[i];
    }
    ll ans = 0;
    map<ll, ll> C;
    rep(i, N+1) {
        if (C.count(acc[i]-K)) {
            ans += C[acc[i]-K];
        }
        C[acc[i]]++;
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
