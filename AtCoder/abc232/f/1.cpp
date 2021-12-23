/*
・自力ならず。これは解けるべきだったな…。
・bitDP、転倒数
・制約がbitDPって言ってるのは知ってた。なのに時間少ないのとかで焦ってちゃんと考察せずに進んでしまった。
　まあ終了後考えても、自力でうまい状態と遷移には落とせなかったんだけど。。
・数列Aの使用済要素の集合、を状態に持つとよかった。
　この使用済は、Bの要素と値を合わせるために、既に必要な位置にスワップとかをさせ終わった状態を指す。
　これを数列Bの先頭の方から確定させていくとすると、うまくいく。
　立ってるビットから、使用済のAの要素だけでなく、どの位置までBと合わせ終わっていて
　次に見るBの要素がどれなのかも分かるようになってる。
　残っているAの要素が今どの位置にあるのかも分かる。
　(実際に適当に使用済要素を前に詰めた状態をシミュして毎回作っておけばいい。
　これは使用済の順序がどうでもいいのでO(N)でできる。)
・あとはこれらの情報を使って、使用済個数より後ろに残っている要素を、
　次に決める要素として持ってくる遷移を全部試せばいい。
・スワップは転倒数なんだけど、この方針だと単に1つの要素をある場所まで
　引っ張ってくるだけなので、難しく考えず移動距離と同値でOK。
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
    ll N, X, Y;
    cin >> N >> X >> Y;
    auto A = LIST(N);
    auto B = LIST(N);

    vector<ll> dp(1LL<<N, INF);
    dp[0] = 0;
    rep(bit, (1LL<<N)-1) {
        if (dp[bit] == INF) continue;
        vector<ll> cur;
        // 確定済(順番はどうでもいい)
        rep(i, N) {
            if (bit>>i & 1) {
                cur.eb(i);
            }
        }
        ll n = cur.size();
        // 未確定
        rep(i, N) {
            if (!(bit>>i & 1)) {
                cur.eb(i);
            }
        }
        // 今位置iにある要素を位置nに持ってくる
        rep(i, n, N) {
            chmin(dp[bit|1LL<<cur[i]], dp[bit]+(i-n)*Y+abs(B[n]-A[cur[i]])*X);
        }
    }
    ll ans = dp[(1LL<<N)-1];
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
