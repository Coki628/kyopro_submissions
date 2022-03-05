/*
参考：https://twitter.com/brthyyjp/status/1499801853454073857
・自力ならず。。これは解けるべきだったな。
　Dに張り付く前にもうちょいちゃんと考えるべきだった。
・工夫してビット全探索
・2冪を組み合わせていけば任意の数が表せるのは知られる所だけど、
　今回はそれに加えて使える数として階乗がある。
　この階乗の候補はかなり少ないので、ここをビット全探索して、
　残りは2冪で貪欲に減らす、としても、複数テストケース100件が十分間に合う。
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#define CONSTANTS
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
#include "template.hpp"

const ll MX = 1e12;
vector<ll> pows = {1}, facts;
void prep() {
    ll cur = 1;
    while (cur*2 <= MX) {
        cur *= 2;
        pows.eb(cur);
    }
    cur = 2;
    ll i = 3;
    while (cur*i <= MX) {
        cur *= i;
        i++;
        facts.eb(cur);
    }
}

void solve() {
    ll N;
    cin >> N;

    ll M = facts.size();
    ll L = pows.size();
    ll ans = INF;
    rep(bit, 1LL<<M) {
        ll cur = 0, cnt = 0;
        rep(i, M) {
            if (bit>>i & 1 and cur+facts[i] <= N) {
                cur += facts[i];
                cnt++;
            }
        }
        rep(i, L-1, -1, -1) {
            if (cur+pows[i] <= N) {
                cur += pows[i];
                cnt++;
            }
        }
        chmin(ans, cnt);
    }
    print(ans);
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);
    cout << fixed << setprecision(15);

    prep();

    // single test case
    // solve();

    // multi test cases
    int T;
    cin >> T;
    while (T--) solve();

    return 0;
}
