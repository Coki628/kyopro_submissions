/*
参考：https://codeforces.com/blog/entry/76352
　　　https://discord.com/channels/920351976712200234/920971145879113761/963966872708067338
・dojo set_e_6_7
・自力ならず。むずい。
・まず問題ちゃんと読めてなかったよね。与えられる区間は、
　左端は任意だけど、(どれがそうなのかは分からないものの)右端は決まっていて、それぞれ2～Nになる。
　で、そうなると、適当な1つを先頭として選ぶと、それを各区間から削除して、
　要素が1つだけになったものが、次で右端になるものと分かるので、一意に定めていける。
　でもこれだけだと、必要だけど十分ではなくて、実際にOKかチェックする必要がある。
　これは、各区間について、その区間内の要素が連続している箇所がちゃんと
　答えの数列に存在しているか、をチェックしたら通った。
・Mikeさん、Div.3でこういうねっとり系出すの好きだよな…。
　こういうの通せるべきなんだけど、あんま好きじゃないんだよね。。
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
#include "template.hpp"

void solve() {
    ll N;
    cin >> N;
    vector<set<ll>> P(N-1);
    rep(i, N-1) {
        ll k;
        cin >> k;
        auto tmp = LIST(k);
        P[i] = set<ll>(ALL(tmp));
    }

    rep(a, 1, N+1) {
        ll cur = a;
        auto curp = P;
        vector<ll> ans = {cur};
        bool ok = true;
        rep(_, N-1) {
            // curを削除
            rep(i, N-1) {
                curp[i].erase(cur);
            }
            // 要素が1つだけになっている所を見つけて、次のcurとする
            bool found = false, okok = false;
            rep(i, N-1) {
                if (curp[i].size() == 1) {
                    if (not found) {
                        cur = *curp[i].begin();
                        found = true;
                        okok = true;
                    } else {
                        // 1つだけが複数個所見つかったらNG
                        okok = false;
                        break;
                    }
                } 
            }
            if (not okok) {
                ok = false;
                break;
            }
            ans.eb(cur);
        }
        if (ok) {
            bool okok = true;
            rep(i, N-1) {
                // 区間P[i]内の全要素が連続している箇所が答えの列に存在しているか
                ll sz = P[i].size();
                bool okokok = false;
                rep(l, N-sz+1) {
                    ll r = l + sz;
                    set<ll> cur(ans.begin()+l, ans.begin()+r);
                    if (P[i] == cur) {
                        okokok = true;
                        break;
                    }
                }
                if (not okokok) {
                    okok = false;
                    break;
                }
            }
            if (okok) {
                print(ans);
                return;
            }
        }
    }
    assert(0);
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
