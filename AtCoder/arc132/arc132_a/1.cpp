/*
・自力AC！でも時間かかったな…。
・真っ黒な行と列から順に、一意に確定はできる。けど陽にグリッド作るのは無理なので、
　確定する場所と色の情報だけ持っておく。クエリ先読みして、確定の情報を前から見て、
　そのクエリに対応する行か列が現れたらそのクエリの答えを確定、ってやった。
・みんな爆速だったので何で、、ってなったけど、
　結局 R[i]+C[i] <= N+1 な場所は全部黒、でいけるらしい。何でそんなん気付くんだ…。
　→この会話で言及されてた。https://twitter.com/kumakumaaaaa__/status/1475266334003187712
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
    auto R = LIST(N);
    auto C = LIST(N);
    rep(i, N) {
        R[i]--;
        C[i]--;
    }
    vector<ll> rr(N), rc(N);
    rep(i, N) {
        rr[R[i]] = i;
        rc[C[i]] = i;
    }

    deque<ll> que(N);
    iota(ALL(que), 0);
    vector<pair<ll, char>> pr, pc;
    rep(i, N) {
        ll j;
        if (i%2 == 0) {
            j = que.back(); que.pop_back();
            pr.eb(rr[j], '#');
            pc.eb(rc[j], '#');
        } else {
            j = que.front(); que.pop_front();
            pr.eb(rr[j], '.');
            pc.eb(rc[j], '.');
        }
    }

    ll Q;
    cin >> Q;
    vector<set<ll>> qsr(N), qsc(N);
    rep(i, Q) {
        ll r, c;
        cin >> r >> c;
        r--; c--;
        qsr[r].insert(i);
        qsc[c].insert(i);
    }

    string ans(Q, '*');
    rep(i, N) {
        auto [ri, c] = pr[i];
        auto [ci, _] = pc[i];
        for (auto j : qsr[ri]) {
            if (ans[j] == '*') {
                ans[j] = c;
            }
        }
        for (auto j : qsc[ci]) {
            if (ans[j] == '*') {
                ans[j] = c;
            }
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
