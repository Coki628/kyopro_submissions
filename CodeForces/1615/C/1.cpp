/*
・自力ならず。。
・なんか偶奇場合分けで貪欲みたくいけるみたいだけど、DPどうなんだろう。
　いけそうな気がするんだけど通らない。
　てか、謎の無理なはずのケースが正解はできるでWAになったので、
　根本的に何か理解が間違ってる可能性がある。。
・色々詰めた。なんかcharの型変換でミスってるのとかあってそれは直したけど、
　それでもダメで、結局、1の場所でないと反転の軸にして止めておく場所にできないのが
　多分条件としてきつくて、その部分がこのDPだと考慮できないっぽい。。
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
    ll N;
    cin >> N;
    string S, T;
    cin >> S >> T;
    vector<ll> A(N), B(N);
    rep(i, N) {
        A[i] = S[i]-'0';
        B[i] = T[i]-'0';
    }

    ll cnt0 = count(ALL(S), '0');
    ll cnt1 = N-cnt0;
    if (cnt0 == N) {
        print(-1);
        return;
    }
    ll need1 = count(ALL(T), '1');
    if (need1 != cnt1 and need1 != cnt0+1) {
        print(-1);
        return;
    }

    // dp[i][j][k] := i番目まで見て、決めた部分が反転状態j=0/1, 実際に反転した回数の偶奇k=0/1
    auto dp = list3d(N+1, 2, 2, INF);
    dp[0][0][0] = dp[0][1][0] = 0;
    rep(i, N) {
        rep(j, 2) {
            rep(k, 2) {
                if (((A[i]^k) == B[i]) ^ j) {
                    chmin(dp[i+1][j][k], dp[i][j][k]);
                } else {
                    chmin(dp[i+1][1-j][1-k], dp[i][j][k]+1);
                }
            }
        }
    }
    ll ans = min(dp[N][0][0], dp[N][0][1]);
    if (ans == INF) ans = -1;
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
