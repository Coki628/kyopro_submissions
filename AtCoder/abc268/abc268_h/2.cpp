/*
参考：https://atcoder.jp/contests/abc268/editorial
・公式解説の別解より
・ロリハ、種類数が√になる典型
・右端を固定して、必要な左端を全探索できればその位置を重複なく置けるか分かる。
　まともにやると2乗オーダーだけど、文字列長の種類として存在するのが最大でも
　「√文字列長の総和」個しかないので、これを予め見ておけば、確認する必要のある左端を減らせる。
・Tの文字列長の総和をMとして、ループだけでもO(|S|√M)かかって、
　ここにロリハのクエリとsetが乗るのでまあ計算量はきつい。けど無事AC1.47秒。(制約4秒)
　HashSet使ったけど、今回は純正setで試しても変わらなかった…。(unordered_setは遅かった。)
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

#include "string/RollingHash.hpp"

void solve() {
    string S;
    cin >> S;
    ll L = S.size();
    ll N;
    cin >> N;
    RollingHash rh;
    vector<HashSet<uint64_t>> adj(500007);
    rep(i, N) {
        string t;
        cin >> t;
        ll sz = t.size();
        auto hash = rh.get_hash(t, 0, t.size());
        adj[sz].insert(hash);
    }
    auto table = rh.build(S);

    // 存在する文字列長だけでループを回せるように準備しておく
    vector<ll> ids;
    rep(i, 500007) {
        if (adj[i].size()) {
            ids.eb(i);
        }
    }

    // lは調べる左端の左限
    ll ans = 0, l = 0;
    rep(r, 1, L+1) {
        bool ok = true;
        for (auto sz : ids) {
            // 存在する文字列長に対応する左端だけ見る
            ll i = r - sz;
            if (l <= i) {
                if (adj[sz].count(rh.query(table, i, r))) {
                    ok = false;
                    break;
                }
            }
        }
        if (not ok) {
            ans++;
            // 区切ったら左限を更新
            l = r;
        }
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
