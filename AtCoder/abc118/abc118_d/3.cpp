/*
・dojo set_e_3_1
・なんとか自力AC
・DP復元、コーナーケース
・文字列長と、マッチ何本使ったかを状態に持ってDPした。
　復元で文字列出すんだけど、これだと全然WA。
　ランダムテストいっぱい回して何とか原因が分かってきて通せた。
　同じ本数で2文字作る所で、交換した方が得する場合がある。
　結局文字種毎にカウントして、数調整してから答えの文字列作る形にまとめた。
・DP配列が1万^2=1億で結構きつめ。しかも中身ペアだし。
　vectorだと785MBで0.70秒、生配列にしたら163MBの0.40秒でやっぱり全然良くなる。
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
constexpr long double EPS = 1e-10;
constexpr long double PI = M_PI;

#include "../../../_lib/cpp/_src/macros.hpp"

#include "../../../_lib/cpp/_src/combinatorics/ModInt.hpp"
using mint = ModInt<MOD>;

#include "../../../_lib/cpp/_src/template.hpp"

#include "../../../_lib/cpp/_src/string/replace.hpp"

pair<bool, int> dp[10007][10007];

void solve() {
    ll N, M;
    cin >> N >> M;
    auto A = LIST(M);

    vector<ll> need = {
        0, 2, 5, 5, 4, 5, 6, 3, 7, 6,
    };
    vector<ll> mxd(10, -1);
    rep(i, M) {
        chmax(mxd[need[A[i]]], A[i]);
    }

    ll L = N;
    // auto dp = list2d(L+1, N+1, mkp(false, -1));
    dp[0][0] = {true, -1};
    rep(i, L) {
        rep(j, N+1) {
            if (!dp[i][j].first) continue;
            rep(cost, 2, 8) {
                if (mxd[cost] == -1) continue;
                if (j+cost <= N and !dp[i+1][j+cost].first) {
                    dp[i+1][j+cost] = {true, mxd[cost]};
                }
            }
        }
    }

    string ans;
    rep(i, L, 0, -1) {
        ll l = i;
        ll n = N;
        if (!dp[l][n].first) continue;
        string tmp;
        while (n) {
            auto [_, a] = dp[l][n];
            tmp += '0'+a;
            l--;
            n -= need[a];
        }
        auto C = Counter(tmp);
        // use 12
        if (mxd[6] == 9) {
            while (C['8'] and C['0'+mxd[5]]) {
                C['8']--;
                C['0'+mxd[5]]--;
                C['9'] += 2;
            }
        }
        // use 11
        if (mxd[6] == 9 and mxd[5] != -1) {
            while (C['8'] and C['0'+mxd[4]]) {
                C['8']--;
                C['0'+mxd[4]]--;
                C['9']++;
                C['0'+mxd[5]]++;
            }
        }
        // use 10
        if (mxd[6] == 9 and mxd[4] != -1) {
            while (C['8'] and C['0'+mxd[3]]) {
                C['8']--;
                C['0'+mxd[3]]--;
                C['9']++;
                C['0'+mxd[4]]++;
            }
        }
        // use 9
        if (mxd[6] == 9 and mxd[3] != -1) {
            while (C['8'] and C['0'+mxd[2]]) {
                C['8']--;
                C['0'+mxd[2]]--;
                C['9']++;
                C['0'+mxd[3]]++;
            }
        }
        for (auto [k, v] : C) {
            ans += string(v, k);
        }
        sort(ans.rbegin(), ans.rend());
        break;
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
