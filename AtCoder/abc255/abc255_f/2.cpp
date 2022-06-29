/*
参考：https://www.youtube.com/watch?v=fR3W5IcBGLQ
・時間外で色々考えても自力ならず。これむずくないか…。
・木グラフ、行きがけ順、通りがけ順、再帰探索
・構築方法の考察も思いつかなかったし、実装もまあまあむずい。
・考察は、行きがけ順ベースで考えたのがそもそも悪手だったぽい。
　通りがけ順ベースで見て、そこで部分木の根から左右に分けて、さらに部分木を見ていく、
　みたいにする。行きがけ順は次に見る部分木の根がどれなのかのチェックに使う。
　(行きがけ順の先頭が根と分かるので)
・実装は、PとI両方の添字と頂点番号が出てくるので、この変数は何を指してたんだっけ？
　みたいに添字で頭がつらくなってくる。頑張る。
・頂点1からスタートできないのは論外として、途中で話が合わなくなったらNG、
　みたいにしたら無事通った…。ところでassertってtry/catchできないのね。
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
    ll N;
    cin >> N;
    auto P = LIST(N);
    auto I = LIST(N);
    rep(i, N) P[i]--;
    rep(i, N) I[i]--;

    if (P[0] != 0) {
        print(-1);
        return;
    }

    try {
        vector<ll> pretoi(N), intoi(N);
        rep(i, N) {
            pretoi[P[i]] = i;
            intoi[I[i]] = i;
        }
        vector<pll> ans(N);
        auto rec = [&](auto&& f, ll inl, ll inr, ll r) -> void {
            ll ini = intoi[r];
            // assert(inl <= ini and ini < inr);
            if (not (inl <= ini and ini < inr)) {
                throw -1;
            }
            ll llen = ini - inl;
            ll rlen = inr - (ini+1);
            if (llen > 0) {
                // assert(pretoi[r]+1 < N);
                if (not (pretoi[r]+1 < N)) {
                    throw -1;
                }
                ans[r].first = P[pretoi[r]+1] + 1;
                f(f, inl, ini, P[pretoi[r]+1]);
            }
            if (rlen > 0) {
                // assert(pretoi[r]+llen+1 < N);
                if (not (pretoi[r]+llen+1 < N)) {
                    throw -1;
                }
                ans[r].second = P[pretoi[r]+llen+1] + 1;
                f(f, ini+1, inr, P[pretoi[r]+llen+1]);
            }
        };
        rec(rec, 0, N, P[0]);
        print(ans, '\n');
    } catch (int e) {
        print(e);
    }
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
