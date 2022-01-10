/*
・arc036_d
・自力AC！昔解けなかったやつぽい。嬉しいねー。
・重み付きUF、偶奇
・想定解とは違ったけど通せた。連結成分について、距離の偶奇を持っておきたい。
　そこで、重み付きUFで距離0か1で辺を繋ぐ。どっち向きに付けたかとかで、
　負になったり2以上になったりはしそうだけど、偶奇は保たれる。
　で、連結成分が木じゃなくなる時は、今までの位置関係と同じ偶奇の辺が付く時は変化なし、
　違う偶奇の辺がついたら、その連結成分内では自由に偶奇を調整できるようになるので、
　その時は何でもOKになるようにしておく。
　2点間の偶奇を聞かれたら、同じ連結成分にあるのは前提として、
　距離が偶数か、何でもOK状態になってるならOKとする。これで通った。
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

#include "../../../_lib/cpp/_src/macros.hpp"

#include "../../../_lib/cpp/_src/combinatorics/ModInt.hpp"
using mint = ModInt<MOD>;

#include "../../../_lib/cpp/_src/template.hpp"

#include "../../../_lib/cpp/_src/graph/WeightedUnionFind.hpp"

void solve() {
    ll N, Q;
    cin >> N >> Q;

    WeightedUnionFind<ll> uf(N);
    vector<bool> ok(N);
    rep(i, Q) {
        ll op, x, y, z;
        cin >> op >> x >> y >> z;
        x--; y--;
        if (op == 1) {
            z %= 2;
            if (not uf.same(x, y)) {
                ll rx = uf.find(x);
                ll ry = uf.find(y);
                ll r = uf.merge(x, y, z);
                ok[r] = ok[rx]|ok[ry];
            } elif (abs(uf.diff(x, y))%2 != z) {
                ok[uf.find(x)] = 1;
            }
        } else {
            if (uf.same(x, y) and (abs(uf.diff(x, y))%2 == 0 or ok[uf.find(x)])) {
                YES();
            } else {
                NO();
            }
        }
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
