/*
参考：https://codeforces.com/blog/entry/98942
・自力ならず…。でもこれは出なかっただろうな。
・考察がむずいDP、DP復元
・重要な考察があって、長さ2,3の部分列を使うと、
　4以上の任意の部分列を表現できる。言われてみると確かにそうかも！
　じゃあ2だけでいいんじゃあとか思ったけど、2だけだと奇数長は表現できないもんね。
　3も組み合わせると、全部できる訳だ。まじかー、ってなった。
・で、これを使うと、長さ2か3ずつ到達可能かチェックしていくDPが作れる。
　でも今回これの復元も要るんだよね。ちょっと面倒。
・dp[i] := {位置iに到達可能か, {使った部分列の位置, 長さ}}
　みたいに情報を持たせた。やってみればまあ、出来ることの積み重ねで出来る。
　やっぱり要点は、長さ2,3の部分列だけ組み合わせるDPを着想できるかどうかだな…。
・ちなみに自力では、グラフに帰着で経路みたいにならないかとかで、
　色々こねくり回してたけど全然ハズレ方針だったっぽい…。
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

#include "../../../_lib/cpp/_src/graph/Dijkstra.hpp"

void solve() {
    ll N, M;
    cin >> N >> M;
    vector<string> nums(N);
    rep(i, N) {
        cin >> nums[i];
    }
    string S;
    cin >> S;

    map<string, ll> mp;
    rep(len, 2, 4) {
        rep(i, N) {
            rep(j, M-len+1) {
                auto sub = nums[i].substr(j, len);
                mp[sub] = i*M+j;
            }
        }
    }

    vector<pair<bool, pll>> dp(M+1, {false, {-1, -1}});
    dp[0] = {true, {-1, -1}};
    rep(i, M) {
        if (not dp[i].first) continue;
        rep(len, 2, 4) {
            if (i+len <= M) {
                auto sub = S.substr(i, len);
                if (not dp[i+len].first and mp.count(sub)) {
                    dp[i+len] = {true, {mp[sub], len}};
                }
            }
        }
    }
    if (not dp[M].first) {
        print(-1);
        return;
    }
    vector<array<ll, 3>> ans;
    ll m = M;
    while (m) {
        auto [ok, p] = dp[m];
        auto [ij, len] = p;
        auto [i, j] = divmod(ij, M);
        ans.pb({j+1, j+len, i+1});
        m -= len;
    }
    reverse(ALL(ans));
    print(ans.size());
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
