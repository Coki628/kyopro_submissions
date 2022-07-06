/*
・JOI埋め
・きっちり自力AC！
・セグ木2本、座圧
・真ん中の人を固定して両側に適した2人を探す。
　自分よりバトンが速い人用のセグ木と遅い人用のセグ木をそれぞれ用意する。
　こうすることで、前者には後から自分のB[i]を追加、後者には予めその人のB[i]を
　セグ木の値に織り込んでおく、としておけば、それぞれから速い2人を取れる。
　2人目を取る時には1人目の値をINFにしておく。Bの値をindexとして使うけど、
　これは取り得る範囲が大きいし同値もあり得るので、座圧+一意キーにしておく。
　これで候補が最大4人取れるので、ここから良い2人を選べばいい。
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
    vector<ll> A(N), B(N);
    rep(i, N) {
        cin >> A[i] >> B[i];
    }

    vector<pii> cptmp;
    rep(i, N) {
        cptmp.eb(B[i], i);
    }
    Compress<pii> cp(cptmp);
    assert(cp.size() == N);
    vector<ll> itocp(N);
    rep(i, N) {
        itocp[i] = cp[{B[i], i}];
    }

    auto sega = get_segment_tree(N, [](ll a, ll b) { return min(a, b); }, INF);
    auto segb = get_segment_tree(N, [](ll a, ll b) { return min(a, b); }, INF);
    rep(i, N) {
        sega.set(itocp[i], A[i]);
        segb.set(itocp[i], A[i]+B[i]);
    }
    sega.build();
    segb.build();

    ll ans = INF;
    rep(i, N) {
        vector<ll> cur;
        ll mn = sega.query(0, itocp[i]);
        if (mn < INF) {
            cur.eb(mn+B[i]);
            ll j = sega.find_first(0, [&](ll x) { return x <= mn; });
            assert(j != -1);
            sega.update(j, INF);
            ll mn2 = sega.query(0, itocp[i]);
            if (mn2 < INF) {
                cur.eb(mn2+B[i]);
            }
            sega.update(j, mn);
        }
        mn = segb.query(itocp[i]+1, N);
        if (mn < INF) {
            cur.eb(mn);
            ll j = segb.find_first(itocp[i]+1, [&](ll x) { return x <= mn; });
            assert(j != -1);
            segb.update(j, INF);
            ll mn2 = segb.query(itocp[i]+1, N);
            if (mn2 < INF) {
                cur.eb(mn2);
            }
            segb.update(j, mn);
        }
        sort(ALL(cur));
        chmin(ans, A[i]+cur[0]+cur[1]);
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
