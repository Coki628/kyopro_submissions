/*
参考：https://www.terry-u16.net/entry/ahc006-for-beginners
　　　https://qiita.com/thun-c/items/058743a25c37c87b8aa4
　　　https://chokudai.hatenablog.com/entry/2017/04/12/055515
・なんか良い方針が生えず、最初から解説見ちゃった…。
・貪欲、二分探索、chokudaiサーチ
・近い方から取る。それだけ。現在位置からの距離を毎回N箇所全部と取っても、
　Nが1000で回数が50回くらいなので全然問題ない。
・距離が遠すぎる場所を予め候補から外しておく。
・レストランと配達先をまとめて処理する。
・候補を絞る距離の閾値を二分探索でギリギリに設定する。
・初めてのビームサーチ。なんかうまくできてるのかは微妙。
　終了周りの条件がいけてない感じはする。。
・始めむしろ貪欲よりダメで、ビーム幅10とかだったのを時間使って1000まで増やしたら
　いくらかマシになって129万点くらいに。
・にぶたんの判定部分をterryさんのとちゃんと合わせた。
　両方の和じゃなくて、両方個別に閾値以下か見る。
　これやったら大きく上がって148万点くらい。
　ちなみに同じにぶたんの改善を貪欲コードに当てたら138万点くらいだったので、
　ビームサーチも一応意味があったのかな、となってる。
・状態を作る時、setは絶対遅いだろうなと思ったので、
　条件同じでsetを生配列に変えたら1.7秒くらいかかってたのが1.2秒くらいになったので、
　その分ビーム幅を1000から1300まで増やした。
　あんま変わんなくて、148万点くらい。(5000点くらい伸びた。)
・座圧でN=1000回してた所を50くらいに減らしたんだけど、速度ほぼ変わらず。。
・ビームサーチをちょっといじってchokudaiサーチもやってみた。
　ちょっと上がって、149万点くらい。
・ローカルでテスト100個やってスコア出せるように作った。
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
#include "string/zfill.hpp"

#include "common/sum.hpp"
#include "common/listnd.hpp"
#include "common/bisearch.hpp"
#include "common/chmin.hpp"
#include "common/Compress.hpp"
#include "geometry/Point.hpp"

ld calc(ll t) {
    return round(1e8/(1000+t));
}

const int N = 1000;
const int K = 50;
Point<ll> XY[2][N];
bool used[2][N];

const int BEAM_WIDTH = 1;
const int TL = 1900;

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

    Point<ll> s = {400, 400};
    rep(i, N) {
        cin >> XY[0][i].x >> XY[0][i].y >> XY[1][i].x >> XY[1][i].y;
    }

    // K箇所回れる閾値を二分探索
    ll DIST_MAX = bisearch_min(0, 600, [&](ll m) {
        ll res = N;
        rep(i, N) {
            if (s.manhattan(XY[0][i]) > m or s.manhattan(XY[1][i]) > m) {
                res--;
            }
        }
        return res >= K;
    });
    // 閾値より大きい距離の注文を予め省いておく
    vector<ll> tmp;
    rep(i, N) {
        if (s.manhattan(XY[0][i]) <= DIST_MAX and s.manhattan(XY[1][i]) <= DIST_MAX) {
            tmp.eb(i);
        }
    }
    // 座圧して必要な注文だけ見れるようにしておく
    Compress<ll> cp(tmp);
    int L = tmp.size();
    #ifdef __LOCAL
        debug(L);
    #endif

    // state[d, v[p, i]] = 距離d, 通ったルートv[レストランor配達先p=0/1, 注文番号i]
    using state = pair<ll, vector<pair<bool, int>>>;
    vector<priority_queue<state, vector<state>, greater<state>>> beam(L*2+1);
    beam[0].push({0, {}});
    ll opcnt = 0;
    while (timer.get_elapse() < TL) {
        opcnt++;
        rep(i, L*2) {
            auto& cur_beam = beam[i];
            auto& nxt_beam = beam[i+1];
            rep(_, BEAM_WIDTH) {
                if (cur_beam.empty()) break;
                auto [d, v] = cur_beam.top();
                auto cur = v.empty() ? s : XY[v.back().first][cp.unzip(v.back().second)];
                // 現在の使用状態を作る
                rep(i, L) {
                    used[0][i] = false;
                    used[1][i] = false;
                }
                ll abcnt = 0, cdcnt = 0;
                for (auto& [p, i] : v) {
                    used[p][i] = true;
                    if (p) cdcnt++;
                    else abcnt++;
                }
                // 既に終了状態
                if (cdcnt == K) continue;
                cur_beam.pop();
                rep(i, L) {
                    if (not used[0][i] and abcnt < K) {
                        ll nxd = cur.manhattan(XY[0][cp.unzip(i)]);
                        v.eb(0, i);
                        nxt_beam.push({d+nxd, v});
                        v.pop_back();
                    }
                    if (used[0][i] and not used[1][i]) {
                        ll nxd = cur.manhattan(XY[1][cp.unzip(i)]);

                        v.eb(1, i);
                        nxt_beam.push({d+nxd, v});
                        v.pop_back();
                    }
                }
            }
            if (nxt_beam.empty()) break;
        }
    }

    // キューの中身から一番いいものを探す
    ll mn = INF;
    vector<ll> route;
    vector<ll> xy;
    rep(i, K, L*2+1) {
        while (beam[i].size()) {
            ll cdcnt = 0;
            auto [d, v] = beam[i].top(); beam[i].pop();
            // 始点に戻る前の時点でmnより大きいなら見る必要ない
            if (d > mn) break;
            for (auto& [p, _] : v) {
                if (p) cdcnt++;
            }
            // K箇所回りきってたら答えに使えるかチェック
            if (cdcnt == K) {
                auto cur = XY[v.back().first][cp.unzip(v.back().second)];
                d += cur.manhattan(s);
                if (chmin(mn, d)) {
                    vector<ll> tmp_route;
                    vector<ll> tmp_xy = {s.x, s.y};
                    for (auto& [p, j] : v) {
                        if (!p) tmp_route.eb(cp.unzip(j)+1);
                        cur = XY[p][cp.unzip(j)];
                        tmp_xy.eb(cur.x);
                        tmp_xy.eb(cur.y);
                    }
                    // 答えを更新
                    tmp_xy.eb(s.x);
                    tmp_xy.eb(s.y);
                    route = tmp_route;
                    xy = tmp_xy;
                }
            }
        }
    }
    #ifdef __LOCAL
        debug(opcnt);
        debug(mn);
        debug(calc(mn));
    #endif
    cout << route.size() << ' ';
    print(route);
    cout << xy.size()/2 << ' ';
    print(xy);
    return calc(mn);
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);
    cout << fixed << setprecision(15);

    #ifdef __LOCAL
        // 実施テスト番号
        // vector<ll> T = {
        //     0
        // };
        vector<ll> T;
        rep(i, 100) {
            T.eb(i);
        }
        ld score = 0;
        for (ll t : T) {
            score += solve(t);
        }
        debug(score);
    #else
        solve();
    #endif

    return 0;
}
