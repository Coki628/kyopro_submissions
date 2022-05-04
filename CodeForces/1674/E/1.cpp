/*
参考：https://twitter.com/AllDirections4/status/1521169010762559488
・自力ならず…。
・DPしようとして沼った。影響のあるのが隣接3つだけなので、うまく状態持てばいけると踏んだけど、
　隣接2つならまだしも3つの状態管理はゴチャゴチャしすぎた。
　しかも、それでうまくやったとして、「どこか1箇所を連続で1つ目消し切るまでやるのがいい」
　というDP遷移の前提がそもそも誤っていたため、何やっても無理だった。
　これならF見といた方がまだ良かったな…。
・前述のDPでやりたかったことは、1箇所決め打って1つ目消し切るまで減らす、
　その時残ってる最小位置を2つ目として消す。を全てのiで試せればよくて、これはセグ木でできた。
・で、これでダメなケースは隣接2項をうまく減らす方法で、
　こうやると、2箇所を3ずつ減らすことができる。ここまではサンプルにあるので行ったかもしれない。
　がしかしこれだけだとシステス後半のケースで落ちる。何か今回の結果見たらやたら
　このEでシステス落ちとかハックになってる人多かったので、まあ自分もここまでだっただろう…。
・さらによく考えると、これも気付けばそれはそうなんだけど、
　この隣接2項でceil(sm, 3)が通用するのは、比較的2項の差分が小さい場合のみ。
　(例えば、0,6とかだったら明らかに2手で終わりにはできない。)
　具体的には、差分が2倍以下ならOKといった感じなので、これを条件に加える。これで無事AC。。
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#define CONSTANTS
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
    auto A = LIST(N);

    A.insert(A.begin(), INF);
    A.eb(INF);
    auto seg = get_segment_tree(A, [](ll a, ll b) { return min(a, b); }, INF);
    ll ans = INF;
    rep(i, 1, N+1) {
        ll mncnt = min({A[i-1], ceil(A[i], 2LL), A[i+1]});
        seg.update(i-1, A[i-1]-mncnt);
        seg.update(i, A[i]-mncnt*2);
        seg.update(i+1, A[i+1]-mncnt);
        ll okcnt = 0;
        ll oki = -1;
        rep(j, i-1, i+2) {
            if (seg[j] <= 0) {
                okcnt++;
                oki = j;
            }
        }
        assert(okcnt >= 1);
        if (okcnt >= 2) {
            chmin(ans, mncnt);
        } else {
            seg.update(oki, INF);
            ll othermn = seg.query(1, N+1);
            chmin(ans, mncnt+ceil(othermn, 2LL));
        }
        seg.update(i-1, A[i-1]);
        seg.update(i, A[i]);
        seg.update(i+1, A[i+1]);
    }
    rep(i, 1, N) {
        ll a1 = A[i], a2 = A[i+1];
        if (a1 > a2) swap(a1, a2);
        if (a1*2 >= a2) {
            chmin(ans, ceil(a1+a2, 3LL));
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
