/*
・山登り
・とりあえず1点更新で山登りしてみた。
・rotate関数がバグってるのに後から気付いて、それ直したらめっちゃ上がった。
　最初12万ちょいで、QCFiumしたら14万5000近くまで上がった。
・今回はこれが本番中最高点。長い輪を繋げるのはうまくできなかった。
　青パフォ出たのは良かったけど、長さチェックの関数とか、
　問題文のヒントなかったら多分時間内に実装できたかも分からないくらいだし、
　やったのもとりあえずの山登りだけだから、あんまり実力って感じじゃないなー。
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#define CONSTANTS
#include "base.hpp"

constexpr long long INF = 1e18;
// constexpr long long INF = LONG_LONG_MAX;
constexpr int MOD = 1000000007;
// constexpr int MOD = 998244353;
constexpr long double EPS = 1e-10;
constexpr long double PI = M_PI;

#include "macros.hpp"

#include "common/input.hpp"
#include "common/print.hpp"
#include "common/randrange.hpp"
#include "common/Timer.hpp"
#include "common/listnd.hpp"
#include "grid/constants/directions.hpp"
#include "string/zfill.hpp"

const int TL = 1900;
const int N = 30;
// 左上右下
const vector<int> di = {0, -1, 0, 1}, dj = {-1, 0, 1, 0};
const vvi to = {
    {1, 0, -1, -1},
    {3, -1, -1, 0},
    {-1, -1, 3, 2},
    {-1, 2, 1, -1},
    {1, 0, 3, 2},
    {3, 2, 1, 0},
    {2, -1, 0, -1},
    {-1, 3, -1, 1},
};
bool used[N][N][4];

ld solve(int testcase=-1) {
    Timer timer;
    #ifdef __LOCAL
        // 入力ファイル読み込み
        string filename = "tools/in/"+zfill(tostr(testcase), 4)+".txt";
        freopen(filename.c_str(), "r", stdin);
        // 出力ファイル準備
        filename = "tools/out/"+zfill(tostr(testcase), 4)+".txt";
        ofstream ofs(filename.c_str());
        if (!ofs) {
            print(-1);
            exit(0);
        }
    #endif

    vvi tiles = list2d(N, N, 0);
    rep(i, N) {
        string S;
        cin >> S;
        rep(j, N) {
            tiles[i][j] = S[j] - '0';
        }
    }

    // (si, sj) のタイルに sd 方向のタイルから侵入した状態からスタートして環状線の長さを求める
    auto get_length = [&](int si, int sj, int sd) -> int {
        int i = si;
        int j = sj;
        int d = sd;
        int length = 0;
        while (1) {
            used[i][j][d] = true;
            int d2 = to[tiles[i][j]][d];
            if (d2 == -1) return 0;
            used[i][j][d2] = true;
            i += di[d2];
            j += dj[d2];
            if (i < 0 || i >= 30 || j < 0 || j >= 30) return 0;
            d = (d2 + 2) % 4;
            length += 1;
            if (i == si && j == sj && d == sd) return length;
        }
    };

    // スコア計算
    auto calc = [&]() -> ll {
        rep(i, N) rep(j, N) rep(d, 4) used[i][j][d] = false;
        vector<int> lens;
        rep(i, N) {
            rep(j, N) {
                rep(d, 4) {
                    if (not used[i][j][d]) {
                        lens.eb(get_length(i, j, d));
                    }
                }
            }
        }
        sort(lens.rbegin(), lens.rend());
        return lens[0] * lens[1];
    };

    // 状態dのマスを半時計回り90*r度回転
    auto rotate = [](int d, int r) {
        if (d < 4) {
            return (d+r) % 4;
        } elif (d == 4 or d == 6) {
            return d + (r%2);
        } else {
            return d - (r%2);
        }
    };

    vector<int> cur(N*N);
    ll score = calc();
    auto elapsed = timer.get_elapse();
    ll opcnt = 0;
    while (1) {
        if (opcnt%1 == 0) {
            elapsed = timer.get_elapse();
            if (elapsed >= TL) break;
        }
        ll i = randrange(0, N);
        ll j = randrange(0, N);
        ll r = randrange(1, 4);
        ll nxd = rotate(tiles[i][j], r);
        if (tiles[i][j] == nxd) continue;
        opcnt++;
        ll prevd = tiles[i][j];
        tiles[i][j] = nxd;
        ll nxscore = calc();
        if (nxscore >= score) {
            score = nxscore;
            cur[i*N+j] += r;
            cur[i*N+j] %= 4;
        } else {
            tiles[i][j] = prevd;
        }
    }
    #ifdef __LOCAL
        debug(opcnt);
    #endif

    string ans(N*N, '*');
    rep(i, N*N) ans[i] = '0' + cur[i];
    print(ans);

    return score;
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
        // 100件実施
        // vector<ll> T;
        // rep(i, 100) {
        //     T.eb(i);
        // }
        ll score = 0;
        for (ll t : T) {
            score += solve(t);
        }
        debug(score);
    #else
        solve();
    #endif

    return 0;
}
