/*
参考：https://twitter.com/koboshi_kyopro/status/1496705355254239233
・概要イメージは小星さんのツイートから。
・区画を3行3列構成にした。両側で並行して動いて、真ん中も一発で仕留めるようにしてる。
　まだこれは叩き台って感じで荒く組んだだけ。それでもかなり伸びて、これで16億5000万くらい。
・バグって半分くらい働いてなかったので直した。これだけで27億5000万くらい！
・余ってる奇数番目に働いてもらうようにしたり。手元ではちょい上がったんだけど、投げたら26億9000万。。
・左右チェックを先、中央チェックを後ろに。
・構築済の最大行と最小行を持っておいて、その範囲外は探索しないようにした。
・探索パートのペア組みを、位置によって順位付けするようにした。
・探索パートのペア組みを初期位置で決めても意味なかったので、構築パートでの位置でソートするようにした。
・構築パートの方の位置決めも、初期位置でソートして近い所に行くようにした。
　手元だと結構伸びたんだけど、投げたらベスト更新はならずで26億7900万。
・向きを交互にして、それぞれ近い方から探索位置についたりとか。
　それに伴って、固定値ベタ打ちをだいぶ変数にした。結構伸びて、これで29億5500万！
・ペアなしのやつの行動を整えた。悪くなる要素はないはずなんだけど、ちょい下げて29億4300万。
・構築がせっかく左右からできるようになったので、
　同じ位置の担当が2人いたら必ず左右それぞれからやるようにした。
　交差した判定も入れて、なるべく早く探索作業に回れるようにもした。
　これで結構変わって、30億9600万！ついに30億乗ったね！！
・左右先と中央先、入れ替えて中央のチェックを優先したらちょい伸びた。31億7500万。
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
#include "grid/constants/directions.hpp"
#include "string/zfill.hpp"
#include "common/listnd.hpp"
#include "common/ceil.hpp"
#include "common/chmax.hpp"
#include "common/chmin.hpp"

const int GRID_SIZE = 32;
const int TURN_COUNT = 300;
bitset<20> pets[GRID_SIZE][GRID_SIZE];
bitset<10> people[GRID_SIZE][GRID_SIZE];
bool done[3][GRID_SIZE];
bool used[3][GRID_SIZE];
bool goatedrow[2][GRID_SIZE];
bool goated[10];

// block
const string udlr = "udlr";
map<char, int> udlrrev = {
    {'u', 0}, {'d', 1}, {'l', 2}, {'r', 3},
};
// move
const string UDLR = "UDLR";
map<char, int> UDLRrev = {
    {'U', 0}, {'D', 1}, {'L', 2}, {'R', 3},
};

struct Pet {
    ll h, w, type;
};
struct Human {
    ll h, w, phase, targetrow, targetrow2, pair, tci3;
    bool down, started;
};

ld solve(int testcase=-1) {
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

    ll N, M;
    cin >> N;
    vector<Pet> P(N);
    auto blocked = list2d(GRID_SIZE, GRID_SIZE, false);
    vector<array<ll, 3>> nxpeople;
    vector<ll> targetcol = {10, 21};
    vvl tradj(GRID_SIZE);
    ll dogcnt = 0, readycnt = 0, mnrow = INF, mxrow = -INF;
    bool goat = false, ready = false;

    rep(i, N) {
        cin >> P[i].h >> P[i].w >> P[i].type;
        if (P[i].type == 4) dogcnt++;
        pets[P[i].h][P[i].w].set(i);
    }
    cin >> M;
    vector<Human> H(M);
    string action(M, '.');
    rep(i, M) {
        cin >> H[i].h >> H[i].w;
        people[H[i].h][H[i].w].set(i);
    }
    #ifdef __LOCAL
        ll seed;
        cin >> seed;
    #endif

    // 番兵
    rep(i, GRID_SIZE) {
        blocked[0][i] = true;
        blocked[i][0] = true;
        blocked[GRID_SIZE-1][i] = true;
        blocked[i][GRID_SIZE-1] = true;
    }

    // 到達可能範囲内のマス数とペット数を集計
    auto bfs = [&](ll sh, ll sw) -> array<ll, 4> {
        auto visited = list2d(GRID_SIZE, GRID_SIZE, false);
        queue<pii> que;
        que.push({sh, sw});
        array<ll, 4> res = {0, 0, 0, 0};
        while (!que.empty()) {
            auto [h, w] = que.front(); que.pop();
            res[0]++;
            res[1] += pets[h][w].count();
            rep(i, 20) {
                if (pets[h][w][i] and P[i].type == 4) {
                    res[3]++;
                }
            }
            rep(i, 10) {
                if (people[h][w][i] and not goated[i]) {
                    res[2]++;
                }
            }
            for (auto [dh, dw] : dir4) {
                int nh = h+dh, nw = w+dw;
                if (blocked[nh][nw]) continue;
                if (not visited[nh][nw]) {
                    visited[nh][nw] = true;
                    que.push({nh, nw});
                }
            }
        }
        return res;
    };
    // ブロック可能なマスか判定
    auto can_block = [&](ll h, ll w) -> bool {
        if (blocked[h][w] or pets[h][w].count() or people[h][w].count()) {
            return false;
        }
        for (auto [dh, dw] : dir4) {
            ll nh = h+dh, nw = w+dw;
            if (pets[nh][nw].count()) {
                return false;
            }
        }
        return true;
    };
    // 基本行動
    auto base_act = [&](ll i) -> char {
        ll h = P[i].h, w = P[i].w;
        while (1) {
            ll d = randrange(0, 4);
            auto [dh, dw] = dir4[d];
            int nh = h+dh, nw = w+dw;
            if (blocked[nh][nw]) continue;
            // この行動に確定
            pets[P[i].h][P[i].w].reset(i);
            P[i].h += dh, P[i].w += dw;
            pets[P[i].h][P[i].w].set(i);
            return UDLR[d];
        }
    };
    // ペットの移動
    auto move_pet = [&](ll i, string& action) -> void {
        pets[P[i].h][P[i].w].reset(i);
        for (auto c : action) {
            auto [dh, dw] = dir4[UDLRrev[c]];
            P[i].h += dh;
            P[i].w += dw;
        }
        pets[P[i].h][P[i].w].set(i);
    };
    // 最終スコア計算
    auto calc_score = [&]() -> ld {
        ll M = H.size();
        ld res = 0;
        rep(i, M) {
            auto [ri, ni, _, __] = bfs(H[i].h, H[i].w);
            res += ri/900.0*pow(2.0, -ni);
        }
        return round(1e8*res/M);
    };
    // 人の移動
    auto move_human = [&](ll i, char c) -> void {
        action[i] = c;
        nxpeople.pb({H[i].h, H[i].w, i});
        auto [dh, dw] = dir4[UDLRrev[c]];
        H[i].h += dh, H[i].w += dw;
        nxpeople.pb({H[i].h, H[i].w, i});
    };
    // ブロック
    auto block = [&](ll h, ll w, ll i, char c) -> void {
        action[i] = c;
        auto [dh, dw] = dir4[udlrrev[c]];
        blocked[h+dh][w+dw] = true;
    };
    // この行に探索作業開始前の人が残っていないかチェック
    auto is_saferow = [&](ll h) -> bool {
        for (ll i : tradj[h]) {
            if (not H[i].started) {
                return false;
            }
        }
        return true;
    };
    // ターン終了時にまとめてやりたい処理を適用
    auto apply = [&]() {
        // 作業開始準備完了判定
        if (readycnt == M) {
            ready = true;
        }
        // 人の位置情報更新
        rep(i, nxpeople.size()) {
            auto [h, w, j] = nxpeople[i];
            if (i%2 == 0) {
                people[h][w].reset(j);
            } else {
                people[h][w].set(j);
            }
        }
        nxpeople.clear();
        // 各区画の完成判定
        auto bk = blocked;
        rep(i, 10) {
            ll h = i*3;
            rep(j, 3) {
                ll lw = j*11;
                if (not done[j][h+1]) {
                    ll rw = lw+9;
                    blocked[h+1][lw] = true;
                    blocked[h+1][rw] = true;
                    bool ok = true;
                    rep(cw, lw+1, rw) {
                        if (not blocked[h][cw] or not blocked[h+3][cw]) {
                            ok = false;
                            break;
                        }
                    }
                    rep(ch, h+1, h+3) {
                        if (not blocked[ch][lw] or not blocked[ch][rw]) {
                            ok = false;
                            break;
                        }
                    }
                    if (ok) {
                        done[j][h+1] = true;
                        chmax(mxrow, h+1);
                        chmin(mnrow, h+1);
                    }
                }
            }
        }
        blocked = bk;
    };
    // 構築中に対面側と交差したか判定
    auto check_across = [&](ll i) -> bool {
        // そもそも1人作業
        if (tradj[H[i].targetrow].size() == 1) {
            return false;
        }
        // もう1人との位置関係をチェックする
        ll j = tradj[H[i].targetrow][0] != i ? tradj[H[i].targetrow][0] : tradj[H[i].targetrow][1];
        if (
            H[i].tci3 < H[j].tci3 and H[i].w > H[j].w or
            H[i].tci3 > H[j].tci3 and H[i].w < H[j].w
        ) {
            return true;
        } else {
            return false;
        }
    };

    // 構築時の基準行
    vector<ll> targetrows;
    rep(i, M) {
        targetrows.eb((i%5)*6+4);
    }
    sort(ALL(targetrows));
    // 縦の初期位置順で担当行を決める
    vector<pll> AI;
    rep(i, M) {
        AI.eb(H[i].h, i);
    }
    sort(ALL(AI));
    rep(i, M) {
        auto [_, j] = AI[i];
        H[j].targetrow = targetrows[i];
    }
    rep(i, M) {
        // 基準行毎に人番号を持っておく(安全チェック用)
        tradj[H[i].targetrow].eb(i);
    }
    // 構築パートの担当縦位置でソートして探索のペア組み
    AI.clear();
    rep(i, M) {
        AI.eb(H[i].targetrow, i);
    }
    sort(ALL(AI));
    rep(i, 0, M/2*2, 2) {
        auto [_, j1] = AI[i];
        auto [__, j2] = AI[i+1];
        H[j1].pair = j2;
        H[j2].pair = j1;
    }

    vector<char> back = {'L', 'R'};
    vector<char> fore = {'R', 'L'};
    vector<char> lr = {'l', 'r'};
    vector<ll> dw = {-1, 1};
    vector<ll> start = {1, 30};
    vector<ll> end = {30, 1};
    // 探索時の左右決め
    rep(h, 1, GRID_SIZE) {
        // この行担当が1人なら適当に
        if (tradj[h].size() == 1) {
            ll i = tradj[h][0];
            H[i].tci3 = randrange(0, 2);
        // 2人なら左右に振り分ける
        } elif (tradj[h].size() == 2) {
            ll i1 = tradj[h][0];
            ll i2 = tradj[h][1];
            H[i1].tci3 = 0;
            H[i2].tci3 = 1;
        }
    }
    rep(i, M) {
        ll pi = H[i].pair;
        ll tr = H[i].targetrow;
        ll ptr = H[pi].targetrow;
        // 探索時の基準行(index小さい方に合わせる)
        H[i].targetrow2 = i < pi ? tr : ptr;
        if (H[i].w == start[H[i].tci3]) {
            H[i].phase++;
        }
    }
    rep(turn, TURN_COUNT, 0, -1) {
        // Human's action
        // ".": none, "udlr": block, "UDLR": move
        action.assign(M, '.');
        vector<bool> pairdone(M);
        // 探索パートのペア左右決めの順位付け
        auto comp_tci = [](ll tci3, ll ptci3, ll i, ll pi) -> bool {
            // 構築パートの左右が異なればそれを使う
            if (tci3 != ptci3) {
                return tci3 > ptci3;
            } else {
                // 同じ方なら適当にindexで
                return i < pi;
            }
        };
        rep(i, M) {
            ll pi = H[i].pair;
            ll h = H[i].h, w = H[i].w;
            ll tr = H[i].targetrow;
            ll ptr = H[pi].targetrow;
            ll tr2 = H[i].targetrow2;
            // targetcol index (構築時左右どっちか)
            ll tci3 = H[i].tci3;
            ll ptci3 = H[pi].tci3;
            // targetcol index (通路左右どっちか)
            ll tci = comp_tci(tci3, ptci3, i, pi) ? 0 : 1;
            ll ptci = comp_tci(ptci3, tci3, pi, i) ? 0 : 1;
            // targetcol index (領域3つの左右どっちか)
            ll tci2 = comp_tci(tci3, ptci3, i, pi) ? 0 : 2;
            ll ptci2 = comp_tci(ptci3, tci3, pi, i) ? 0 : 2;
            // まず左右へ集合
            if (H[i].phase == 0) {
                move_human(i, back[tci3]);
                if (w+dw[tci3] == start[tci3]) {
                    H[i].phase++;
                }
            // 担当する行へ移動
            } elif (H[i].phase == 1) {
                if (h == tr) {
                    H[i].phase++;
                    readycnt++;
                } elif (h < tr) {
                    move_human(i, 'D');
                } else {
                    move_human(i, 'U');
                }
            // 壁構築
            } elif (H[i].phase == 2) {
                // まだ全員集まってない
                if (not ready) continue;
                // 対面側と交差した
                if (h == tr and check_across(i)) {
                    H[i].phase++;
                    continue;
                }
                // 1つずらす位置
                if (w == 9 or w == 11 or w == 20 or w == 22) {
                    // 下
                    if (blocked[tr+1][w]) {
                        // 上
                        if (blocked[tr-2][w]) {
                            if (h == tr) {
                                move_human(i, fore[tci3]);
                            } else {
                                move_human(i, 'D');
                            }
                        } else {
                            if (h == tr) {
                                move_human(i, 'U');
                            } else {
                                if (can_block(tr-2, w)) {
                                    block(h, w, i, 'u');
                                }
                            }
                        }
                    } else {
                        if (can_block(tr+1, w)) {
                            block(h, w, i, 'd');
                        }
                    }
                // 縦の通路
                } elif (w == 10 or w == 21) {
                    move_human(i, fore[tci3]);
                // その他全部
                } else {
                    // 基準行に戻って次の列へ
                    if (blocked[tr-1][w] and blocked[tr+2][w]) {
                        if (h == tr) {
                            // 最後
                            if (w == end[tci3]) {
                                H[i].phase++;
                            } else {
                                move_human(i, fore[tci3]);
                            }
                        } else {
                            move_human(i, 'U');
                        }
                    // 上壁 → 下移動 → 下壁 → 上移動
                    } else {
                        if (h == tr) {
                            if (blocked[tr-1][w]) {
                                move_human(i, 'D');
                            } else {
                                if (can_block(tr-1, w)) {
                                    block(h, w, i, 'u');
                                }
                            }
                        } else {
                            if (blocked[tr+2][w]) {
                                move_human(i, 'U');
                            } else {
                                if (can_block(tr+2, w)) {
                                    block(h, w, i, 'd');
                                }
                            }
                        }
                    }
                }
            // 通路列へ移動
            } elif (H[i].phase == 3) {
                if (w < targetcol[tci]) {
                    move_human(i, 'R');
                } elif (w > targetcol[tci]) {
                    move_human(i, 'L');
                } elif (h < tr2) {
                    move_human(i, 'D');
                } elif (h > tr2) {
                    move_human(i, 'U');
                }
                // 完了
                if (H[i].w == targetcol[tci] and H[i].h == tr2) {
                    H[i].phase++;
                    H[i].started = true;
                }
            // 巡回
            } elif (H[i].phase == 4) {
                // 相方なし
                if (M%2 == 1 and i == AI.back().second) {
                    if (h%3 == 1) {
                        // この行の安全確認
                        if (is_saferow(h)) {
                            // 左右チェック
                            if (done[tci2][h] and not used[tci2][h]) {
                                if (can_block(h, targetcol[tci]+dw[tci])) {
                                    blocked[h][targetcol[tci]+dw[tci]] = true;
                                    auto [cellcnt, petcnt, mancnt, dcnt] = bfs(h, targetcol[tci]+dw[tci]*2);
                                    blocked[h][targetcol[tci]+dw[tci]] = false;
                                    if (mancnt == 0 and petcnt > 0) {
                                        // ペットをこの行に閉じ込める
                                        dogcnt -= dcnt;
                                        used[tci2][h] = true;
                                        block(h, targetcol[tci], i, lr[tci]);
                                        continue;
                                    }
                                }
                            }
                        }
                    }
                    // 次の行を見にいく
                    if (h == 1) {
                        H[i].down = true;
                        move_human(i, 'D');
                    } elif (h == 30) {
                        H[i].down = false;
                        move_human(i, 'U');
                    } else {
                        move_human(i, H[i].down ? 'D' : 'U');
                    }
                } else {
                    // 相方にまとめて決めてもらう
                    if (pairdone[i]) continue;
                    // 相方が来るまで待つ
                    if (!people[h][targetcol[ptci]][pi]) continue;

                    pairdone[pi] = true;
                    if (h%3 == 1) {
                        // この行の安全確認
                        if (is_saferow(h)) {
                            // 中央チェック
                            if (action[i] == '.' and action[pi] == '.' and done[1][h] and not used[1][h]) {
                                if (can_block(h, targetcol[tci]-dw[tci]) and can_block(h, targetcol[ptci]-dw[ptci])) {
                                    blocked[h][targetcol[tci]-dw[tci]] = true;
                                    blocked[h][targetcol[ptci]-dw[ptci]] = true;
                                    auto [cellcnt, petcnt, mancnt, dcnt] = bfs(h, targetcol[tci]-dw[tci]*2);
                                    blocked[h][targetcol[tci]-dw[tci]] = false;
                                    blocked[h][targetcol[ptci]-dw[ptci]] = false;
                                    if (mancnt == 0 and petcnt > 0) {
                                        // ペットをこの行に閉じ込める
                                        dogcnt -= dcnt;
                                        used[1][h] = true;
                                        block(h, targetcol[tci], i, lr[ptci]);
                                        block(h, targetcol[ptci], pi, lr[tci]);
                                    }
                                }
                            }
                            // 左右チェック
                            if (action[i] == '.' and done[tci2][h] and not used[tci2][h]) {
                                if (can_block(h, targetcol[tci]+dw[tci])) {
                                    blocked[h][targetcol[tci]+dw[tci]] = true;
                                    auto [cellcnt, petcnt, mancnt, dcnt] = bfs(h, targetcol[tci]+dw[tci]*2);
                                    blocked[h][targetcol[tci]+dw[tci]] = false;
                                    if (mancnt == 0 and petcnt > 0) {
                                        // ペットをこの行に閉じ込める
                                        dogcnt -= dcnt;
                                        used[tci2][h] = true;
                                        block(h, targetcol[tci], i, lr[tci]);
                                    }
                                }
                            }
                            if (action[pi] == '.' and done[ptci2][h] and not used[ptci2][h]) {
                                if (can_block(h, targetcol[ptci]+dw[ptci])) {
                                    blocked[h][targetcol[ptci]+dw[ptci]] = true;
                                    auto [cellcnt, petcnt, mancnt, dcnt] = bfs(h, targetcol[ptci]+dw[ptci]*2);
                                    blocked[h][targetcol[ptci]+dw[ptci]] = false;
                                    if (mancnt == 0 and petcnt > 0) {
                                        // ペットをこの行に閉じ込める
                                        dogcnt -= dcnt;
                                        used[ptci2][h] = true;
                                        block(h, targetcol[ptci], pi, lr[ptci]);
                                    }
                                }
                            }
                        }
                    }
                    if (action[i] == '.' and action[pi] == '.' and mnrow < INF) {
                        for (ll j : {i, pi}) {
                            // 次の行を見にいく
                            if (h <= mnrow) {
                                H[j].down = true;
                                move_human(j, 'D');
                            } elif (h >= mxrow) {
                                H[j].down = false;
                                move_human(j, 'U');
                            } else {
                                move_human(j, H[j].down ? 'D' : 'U');
                            }
                        }
                    }
                }
            }
        }
        apply();
        #ifdef __LOCAL
            ofs << action << endl;
        #else
            cout << action << endl;
        #endif

        // Pets' action
        rep(i, N) {
            #ifdef __LOCAL
                // ペットの行動をシミュレート
                action = "";
                // 犬・猫はとりあえず面倒なので仮で2回行動
                if (P[i].type >= 4) {
                    rep(_, 2) action += base_act(i);
                // 他はタイプ番号 = 行動回数でOK
                } else {
                    rep(_, P[i].type) action += base_act(i);
                }
                ofs << action;
                if (i != N-1) ofs << ' ';
                else ofs << endl;
            #else
                cin >> action;
                move_pet(i, action);
            #endif
        }
    }

    ld score = calc_score();
    return score;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);
    cout << fixed << setprecision(15);

    #ifdef __LOCAL
        // 実施テスト番号
        vector<ll> T = {
            12,
        };
        // 100件実施
        // vector<ll> T;
        // rep(i, 100) {
        //     T.eb(i);
        // }
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
