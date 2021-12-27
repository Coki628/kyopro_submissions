/*
・きっちり自力AC！これは結構早く済んだ。
・桁毎に見る
・制約があからさまに桁毎に何とかしないとダメって言ってる。
　各桁が足される値がどれくらいか検討すると、
　うまいこと累積和取ったやつがそのまま使える感じになってる。
　なので桁毎に使う数を先に集めておいて、後は繰り上がりみたいにやって下から決めてく。
　どのくらい繰り上がってくるか見積もりの自信がなかったので、
　かなり多めに大きい桁まで見た。いずれにしろ、最後に余分な0は全部外す。
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

constexpr long long INF = 1e18;
// constexpr long long INF = LONG_LONG_MAX;
constexpr int MOD = 1000000007;
// constexpr int MOD = 998244353;

#include "../../../_lib/cpp/template.hpp"

const ll M = 2000000;
ll B[M];

void solve() {
    string S;
    cin >> S;
    ll N = S.size();

    vector<ll> A(N);
    rep(i, N) {
        A[i] = toint(S[i]);
    }
    Accumulate<ll> acc(A);

    rep(i, N) {
        B[N-i-1] = acc.query(0, i+1);
    }
    string ans;
    rep(i, M) {
        if (B[i] >= 10) {
            B[i+1] += B[i]/10;
            B[i] %= 10;
        }
        ans += tochar(B[i]);
    }
    while (ans.back() == '0') {
        ans.pop_back();
    }
    reverse(ALL(ans));
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
