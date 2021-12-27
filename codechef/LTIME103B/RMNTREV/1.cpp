/*
・自力AC！
・これの逆操作じゃない方は見たことある気がする。
　やってみると、リバースした部分は元indexで見ると前後交互みたいに並ぶ。
　この規則性を使って操作後の列との対応を作っておけば、
　逆にそれを復元する列も作って、当てはめればOK。
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
    string S;
    cin >> S;
    // rep(i, K, 0, -1) {
    //     reverse(S.begin(), S.begin()+i);
    // }
    // print(S);

    deque<ll> que;
    rep(i, K) {
        if ((K%2 == 0) ^ (i%2 == 0)) {
            que.push_front(i);
        } else {
            que.pb(i);
        }
    }
    rep(i, K, N) {
        que.eb(i);
    }
    vector<ll> rev(N);
    rep(i, N) {
        rev[que[i]] = i;
    }

    string ans;
    rep(i, N) {
        ans += S[rev[i]];
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
