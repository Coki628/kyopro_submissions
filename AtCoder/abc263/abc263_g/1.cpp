/*
参考：https://atcoder.jp/contests/abc263/editorial
・フローは間違ってなかったけどまだまだ力及ばず。
・二部マッチング
・解説を確認すると、方針はいくつかあって、これはその1つ。
　まず、素数を作るにあたって1+1=2以外全ての場合で偶奇が異なるので、ほぼ二部グラフになる。
　これがそもそも見えなかったんだけどね…。
　で、1をなるべく残すようにフローを最大限流せれば、残った1で1+1=2を作るのが最善になる。
　そのために、最大流ではなく最小費用流を使って、
　1が絡むペアだけコスト1かかるようにする。これで1がないペアを優先するようになるし、
　最終的にかかったコスト = 1を使った個数 となってとても都合がいい。
・想定解が最大流のところを最小費用流なので数値上の計算量はきつめだけど、
　実際やってみると0.02秒とかで通る…。
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

#include "numbers/is_prime.hpp"

#include "acl/mincostflow.hpp"
using namespace atcoder;

void solve() {
    ll N;
    cin >> N;
    vector<ll> A(N), B(N);
    rep(i, N) {
        cin >> A[i] >> B[i];
    }

    mcf_graph<ll, ll> mcf(N*2+2);
    ll s = N * 2;
    ll t = N * 2 + 1;
    ll cnt1 = 0;
    rep(i, N) {
        if (A[i] == 1) {
            cnt1 = B[i];
        }
        // 偶奇で二部グラフに
        if (A[i]%2 == 1) {
            mcf.add_edge(s, i, B[i], 0);
        } else {
            mcf.add_edge(N+i, t, B[i], 0);
        }
        rep(j, N) {
            if (A[i]%2 == 1 and A[j]%2 == 0) {
                if (is_prime(A[i]+A[j])) {
                    // 1を使うペアだけコスト1
                    mcf.add_edge(i, N+j, min(B[i], B[j]), A[i] == 1);
                }
            }
        }
    }
    auto [f, c] = mcf.flow(s, t);
    ll res = f + (cnt1-c) / 2;
    print(res);
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
