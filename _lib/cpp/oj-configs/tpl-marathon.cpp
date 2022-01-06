/*
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
constexpr ld EPS = 1e-10;
constexpr ld PI = M_PI;

#include "../../../_lib/cpp/_src/macros.hpp"

#include "../../../_lib/cpp/_src/common/listnd.hpp"
#include "../../../_lib/cpp/_src/common/input.hpp"
#include "../../../_lib/cpp/_src/common/print.hpp"
#include "../../../_lib/cpp/_src/common/ceil.hpp"
#include "../../../_lib/cpp/_src/common/chmin.hpp"
#include "../../../_lib/cpp/_src/common/chmax.hpp"
#include "../../../_lib/cpp/_src/common/randrange.hpp"
#include "../../../_lib/cpp/_src/common/Timer.hpp"
#include "../../../_lib/cpp/_src/grid/constants/directions.hpp"
#include "../../../_lib/cpp/_src/string/zfill.hpp"

void solve() {
    #ifdef __LOCAL
        // 入力ファイル読み込み
        string filename = "tools/in/"+zfill(tostr(t), 4)+".txt";
        freopen(filename.c_str(), "r", stdin);
        // 出力ファイル準備
        filename = "tools/out/"+zfill(tostr(t), 4)+".txt";
        ofstream ofs(filename.c_str());
        if (!ofs) {
            print(-1);
            return;
        }
    #endif

}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);
    cout << fixed << setprecision(15);

    #ifdef __LOCAL
        // 実施テスト番号
        vector<ll> T = {
            0,
        };
        for (ll t : T) {
            solve(t);
        }
    #else
        solve();
    #endif

    return 0;
}
