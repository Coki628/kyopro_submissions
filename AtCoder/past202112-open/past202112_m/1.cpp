/*
参考：https://hogloid.hatenablog.com/entry/2014/09/23/132440
・自力AC！
・座圧BIT、平衡二分探索木
・座圧BITだけだと、同じ名前の中で順序を探せない。
　隣接リストにsetみたいなでかつ、indexが探せるようなやつがあればなぁ、
　って調べてたらg++拡張が出てきた。聞いたことあったtreeってこれか。
・あと文字列で座圧みたいにしたのも多分初めてやったけど、
　ちゃんとうまく動いてよかった。
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

constexpr long long INF = 1e18;
// constexpr long long INF = LONG_LONG_MAX;
constexpr int MOD = 1000000007;
// constexpr int MOD = 998244353;

#include "../../../_lib/cpp/_src/base.hpp"

#include "../../../_lib/cpp/_src/macros.hpp"

#include "../../../_lib/cpp/_src/combinatorics/ModInt.hpp"
using mint = ModInt<MOD>;

#include "../../../_lib/cpp/_src/template.hpp"

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/tag_and_trait.hpp>
using namespace __gnu_pbds;

void solve() {
    ll N, Q;
    cin >> N >> Q;
    vector<string> S(N);
    vector<string> tmp;
    rep(i, N) {
        cin >> S[i];
        tmp.eb(S[i]);
    }
    vector<ll> X(Q);
    vector<string> T(Q);
    rep(i, Q) {
        cin >> X[i] >> T[i];
        tmp.eb(T[i]);
    }

    Compress<string> cp(tmp);
    ll L = cp.size();
    auto A = cp.zip(S);
    auto B = cp.zip(T);
    BIT<ll> bit(L);
    auto f = [](int a, int b) { return min(a, b); };
    vector<tree<int, null_type,less<int>, rb_tree_tag, tree_order_statistics_node_update>> ids(L);
    rep(i, N) {
        bit.add(A[i], 1);
        ids[A[i]].insert(i);
    }
    rep(i, Q) {
        ll j = bit.bisearch_fore(0, L-1, X[i]);
        ll rest = X[i]-bit.query(0, j);
        if (j == B[i]) continue;
        auto itr = ids[j].find_by_order(rest-1);
        ids[B[i]].insert(*itr);
        ids[j].erase(itr);
        bit.add(j, -1);
        bit.add(B[i], 1);
    }

    vector<string> ans(N);
    rep(i, L) {
        for (ll id : ids[i]) {
            ans[id] = cp.unzip(i);
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
