/*
・きっちり自力AC！
・インタラクティブ、順列、サイクル
・同じ所で何回も聞いてサイクルを特定する。最初の並びが順番通りと分かってるので、
　通算クエリ回数も持っておけば、何がどう移動したのか逆算できる。
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

ll ask(ll i) {
    ll res;
    cout << "? " << i+1 << endl;
    cin >> res;
    res--;
    return res;
}

void answer(const vector<ll> ans) {
    cout << "! ";
    rep(i, ans.size()) {
        cout << ans[i]+1;
        if (i+1 != ans.size()) {
            cout << ' ';
        } else {
            cout << endl;
        }
    }
}

void solve() {
    ll N;
    cin >> N;

    ll cnt = 0;
    vector<bool> used(N);
    ll i = 0;
    vector<ll> ans(N);
    while (i < N) {
        while (i < N and used[i]) i++;
        if (i == N) break;
        set<ll> se;
        deque<ll> cur;
        while (1) {
            ll res = ask(i);
            if (se.count(res)) {
                break;
            } else {
                se.insert(res);
                cur.eb(res);
            }
        }
        ll m = cur.size();
        ll need = cnt%m;
        rep(_, need) {
            cur.push_front(cur.back());
            cur.pop_back();
        }
        rep(j, m) {
            ans[cur[j]] = cur[(j+1)%m];
            used[cur[j]] = true;
        }
        cnt += m+1;
    }
    answer(ans);
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
