/*
・自力ならず。。バグが取れなかった。
・multiset2本持ってシミュ。なんだけど1TLE。。
　結局原因は、空なのに先頭の値触ってたからだった。
　こんな空チェック、いつも絶対やるのに何で今日は見落としたんだ。。
　REが出てくれれば真っ先に疑ったと思うんだけどTLEだったんだよな。
　後から色々実験して分かったけど、*se.begin()は空でやってもWAになるだけっぽくて、
　se.erase(se.begin())を空でやるとTLEするっぽい。
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

#include "mystl/my_multiset.hpp"

void solve() {
    ll N, M, K;
    cin >> N >> M >> K;
    vector<ll> A(N);
    cin >> A;

    my_multiset<ll> left, right;
    rep(i, M) {
        right.insert(A[i]);
    }
    ll cur = 0;
    rep(i, K) {
        cur += right.front();
        left.insert(right.pop_front());
    }
    vector<ll> ans;
    ans.eb(cur);
    rep(i, M, N) {
        ll nxta = A[i];
        ll prva = A[i - M];
        if (left.count(prva)) {
            left.erase(left.find(prva));
            cur -= prva;
            // M=Kの時、rightは空
            if (right.size() and right.front() < nxta) {
                cur += right.front();
                left.insert(right.pop_front());
                right.insert(nxta);
            } else {
                cur += nxta;
                left.insert(nxta);
            }
        } else {
            assert(right.count(prva));
            right.erase(right.find(prva));
            if (left.back() > nxta) {
                cur -= left.back();
                cur += nxta;
                right.insert(left.pop_back());
                left.insert(nxta);
            } else {
                right.insert(nxta);
            }
        }
        ans.eb(cur);
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
