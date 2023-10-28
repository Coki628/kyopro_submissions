/*
・終了後自力AC！本番中間に合わず。。
・縦横独立、半分全列挙、復元
・方針は立ってたけど、時間内に実装詰め切れず。
　復元の方法がぱっと浮かばなかった。
　どの向きからどの向きに変わるかをキーにして、
　答えにどの文字を使うかを値に持ったmapを予め準備したら上手くいった。
・半分全列挙4回も書いたので、これまとめられないかなぁとは思うんだけど、
　半分全列挙って毎回中身でやること微妙に違うし、
　ライブラリ化もしづらくて何だかなぁという感じ。
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
// constexpr int MOD = 1000000007;
constexpr int MOD = 998244353;
constexpr long double EPS = 1e-10;
constexpr long double PI = M_PI;

#include "macros.hpp"
#include "combinatorics/ModInt.hpp"
using mint = ModInt<MOD>;
#include "template.hpp"

void solve() {
    ll N, X, Y;
    cin >> N >> X >> Y;
    vector<ll> A(N);
    cin >> A;

    ll H = ceil(N, 2LL);
    ll W = N / 2;
    vector<ll> B, C;
    rep(i, N) {
        if (i % 2 == 0) {
            B.eb(A[i]);
        } else {
            C.eb(A[i]);
        }
    }
    assert(B.size() == H);
    assert(C.size() == W);

    ll H1 = ceil(H, 2LL);
    ll H2 = H / 2;
    vector<pair<ll, vector<char>>> vech1, vech2;
    rep(bit, 1LL << H1) {
        ll sm = 0;
        vector<char> op;
        rep(i, H1) {
            if (bit >> i & 1) {
                sm += B[i];
                op.eb('U');
            } else {
                sm -= B[i];
                op.eb('D');
            }
        }
        vech1.eb(sm, op);
    }
    rep(bit, 1LL << H2) {
        ll sm = 0;
        vector<char> op;
        rep(i, H2) {
            if (bit >> i & 1) {
                sm += B[H1 + i];
                op.eb('U');
            } else {
                sm -= B[H1 + i];
                op.eb('D');
            }
        }
        vech2.eb(sm, op);
    }
    sort(ALL(vech2));
    vector<char> yans;
    for (auto [sm, li] : vech1) {
        ll i = bisect_left(vech2, {Y - sm, {}});
        if (i < vech2.size() and sm + vech2[i].first == Y) {
            yans = concat(li, vech2[i].second);
            break;
        }
    }

    ll W1 = ceil(W, 2LL);
    ll W2 = W / 2;
    vector<pair<ll, vector<char>>> vecw1, vecw2;
    rep(bit, 1LL << W1) {
        ll sm = 0;
        vector<char> op;
        rep(i, W1) {
            if (bit >> i & 1) {
                sm += C[i];
                op.eb('R');
            } else {
                sm -= C[i];
                op.eb('L');
            }
        }
        vecw1.eb(sm, op);
    }
    rep(bit, 1LL << W2) {
        ll sm = 0;
        vector<char> op;
        rep(i, W2) {
            if (bit >> i & 1) {
                sm += C[W1 + i];
                op.eb('R');
            } else {
                sm -= C[W1 + i];
                op.eb('L');
            }
        }
        vecw2.eb(sm, op);
    }
    sort(ALL(vecw2));
    vector<char> xans;
    for (auto [sm, li] : vecw1) {
        ll i = bisect_left(vecw2, {X - sm, {}});
        if (i < vecw2.size() and sm + vecw2[i].first == X) {
            xans = concat(li, vecw2[i].second);
            break;
        }
    }

    map<string, char> mp = {
        {"RU", 'L'},
        {"UL", 'L'},
        {"LD", 'L'},
        {"DR", 'L'},
        {"RD", 'R'},
        {"DL", 'R'},
        {"LU", 'R'},
        {"UR", 'R'},
    };
    if (yans.size() + xans.size() == N) {
        Yes();
        ll i = 0, j = 0;
        char cur = 'R';
        string ans;
        rep(k, N) {
            if (k % 2 == 0) {
                char nxt = yans[i];
                i++;
                assert(mp.count({cur, nxt}));
                ans += mp[{cur, nxt}];
                cur = nxt;
            } else {
                char nxt = xans[j];
                j++;
                assert(mp.count({cur, nxt}));
                ans += mp[{cur, nxt}];
                cur = nxt;
            }
        }
        print(ans);
    } else {
        No();
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
