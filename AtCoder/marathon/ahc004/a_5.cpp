/*
・マラソン精進
・山登り、高速化、焼きなまし
・山登りで最高点出たやつを焼きなました。
　スコアは大きく下がって21億点台くらい…。
*/

#pragma region mytemplate

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#define _USE_MATH_DEFINES
#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ull = unsigned long long;
using ld = long double;
using pll = pair<ll, ll>;
using pii = pair<int, int>;
using pil = pair<int, ll>;
using vvl = vector<vector<ll>>;
using vvi = vector<vector<int>>;
using vvpll = vector<vector<pll>>;
using vvpil = vector<vector<pil>>;
#define name4(i, a, b, c, d, e, ...) e
#define rep(...) name4(__VA_ARGS__, rep4, rep3, rep2, rep1)(__VA_ARGS__)
#define rep1(i, a) for (ll i = 0, _aa = a; i < _aa; i++)
#define rep2(i, a, b) for (ll i = a, _bb = b; i < _bb; i++)
#define rep3(i, a, b, c) for (ll i = a, _bb = b; (c > 0 && a <= i && i < _bb) or (c < 0 && a >= i && i > _bb); i += c)
#define rrep(i, a, b) for (ll i=(a); i>(b); i--)
#define pb push_back
#define eb emplace_back
#define mkp make_pair
#define ALL(A) A.begin(), A.end()
#define UNIQUE(A) sort(ALL(A)), A.erase(unique(ALL(A)), A.end())
#define elif else if
#define tostr to_string
constexpr ll INF = 1e18;
// constexpr ll INF = LONG_LONG_MAX;
constexpr int MOD = 1000000007;
// constexpr int MOD = 998244353;

template<typename T> vector<vector<T>> list2d(int N, int M, T init) { return vector<vector<T>>(N, vector<T>(M, init)); }
template<typename T> vector<vector<vector<T>>> list3d(int N, int M, int L, T init) { return vector<vector<vector<T>>>(N, vector<vector<T>>(M, vector<T>(L, init))); }
template<typename T> vector<vector<vector<vector<T>>>> list4d(int N, int M, int L, int O, T init) { return vector<vector<vector<vector<T>>>>(N, vector<vector<vector<T>>>(M, vector<vector<T>>(L, vector<T>(O, init)))); }

template<typename T=ll> vector<T> LIST(ll N) { vector<T> A(N); rep(i, N) cin >> A[i]; return A; }

void print() { cout << '\n'; }
template<typename T> void print(T out) { cout << out << '\n'; }
template<typename T1, typename T2> void print(const pair<T1, T2> &p) { cout << p.first << ' ' << p.second << '\n'; }
template<typename T1, typename T2, typename T3> void print(const tuple<T1, T2, T3> &tp) { cout << get<0>(tp) << ' ' << get<1>(tp) << ' ' << get<2>(tp) << '\n'; }
template<typename T1, typename T2, typename T3, typename T4> void print(const tuple<T1, T2, T3, T4> &tp) { cout << get<0>(tp) << ' ' << get<1>(tp) << ' ' << get<2>(tp) << ' ' << get<3>(tp) << '\n'; }
template<typename T> void print(const vector<T> &V) { rep(i, V.size()) { cout << V[i]; if (i != V.size()-1) cout << ' '; } cout << '\n'; }
template<typename T, size_t SZ> void print(const array<T, SZ> &arr) { rep(i, arr.size()) { cout << arr[i]; if (i != arr.size()-1) cout << ' '; } cout << '\n'; }
template<typename T> void print(const deque<T> &que) { vector<T> V(ALL(que)); print(V); }
template<typename T> void print(const set<T> &se) { vector<T> V(ALL(se)); print(V); }
#define debug(x) (cout << #x << ": ", print(x));

void Yes() { print("Yes"); }
void No() { print("No"); }
void YES() { print("YES"); }
void NO() { print("NO"); }

ll ceil(ll a, ll b) { if (a >= 0) return (a+b-1) / b; else return a / b; }
template<typename T> bool chmax(T &x, T y) { return (y > x) ? x = y, true : false; }
template<typename T> bool chmin(T &x, T y) { return (y < x) ? x = y, true : false; }

const vector<pii> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

string zfill(string str, int len) { string zeros; int n = str.size(); rep(i, len-n) zeros += '0'; return zeros+str; }

#pragma endregion

// [l,r)の範囲で乱数生成
mt19937_64 mt(chrono::steady_clock::now().time_since_epoch().count());
ll randrange(ll l, ll r) {
    uniform_int_distribution<ll> rand(l, r-1);
    return rand(mt);
}

// 環境に依存せずミリ秒単位で時間取得するクラス
struct Timer {

    chrono::_V2::system_clock::time_point start_time;
    
    Timer() {
        start_time = this->now();
    }

    chrono::_V2::system_clock::time_point now() {
        return chrono::high_resolution_clock::now();
    }

    int64_t get_diff() {
        return chrono::duration_cast<chrono::milliseconds>(this->now() - start_time).count();
    }
};

const int L = 8;
const string letters = "ABCDEFGH.";
const int N = 20;
vector<string> S;
vector<string> mat(N, string(N, '.'));

unordered_map<string, int> C;

void count_all() {
    rep(i, N) {
        rep(j, N) {
            string cur;
            rep(k, j, N) {
                cur += mat[i][k];
                C[cur]++;
            }
        }
    }
    rep(j, N) {
        rep(i, N) {
            string cur;
            rep(k, i, N) {
                cur += mat[k][j];
                C[cur]++;
            }
        }
    }
}

void count(ll h, ll w, char c) {
    rep(j, N) {
        string cur;
        rep(k, j, N) {
            cur += mat[h][k];
            C[cur]--;
        }
    }
    rep(i, N) {
        string cur;
        rep(k, i, N) {
            cur += mat[k][w];
            C[cur]--;
        }
    }
    mat[h][w] = c;
    rep(j, N) {
        string cur;
        rep(k, j, N) {
            cur += mat[h][k];
            C[cur]++;
        }
    }
    rep(i, N) {
        string cur;
        rep(k, i, N) {
            cur += mat[k][w];
            C[cur]++;
        }
    }
}

ld calc_all(ll M, ll d=N*N) {
    ll cnt = 0;
    for (auto& s : S) {
        if (C[s]) cnt++;
    }
    if (cnt < M) {
        return round(10e8*cnt/M);
    } else {
        return round(10e8*2*N*N/(2*N*N-d));
    }
}

const ll TL = 2500;

const ld T0 = 10e6;
const ld T1 = 10e2;

// 焼きなましに使う温度の計算
ld calc_temp(ll elapsed) {
    ld t = elapsed / (ld)TL;
    if (t >= 1) {
        return -1;
    }
    // return T0 + (T1-T0)*t;
    return pow(T0, (1-t))*pow(T1, t);
}

// 焼きなましを踏まえた採用確率の計算
ld calc_prob(ld score, ld temp) {
    if (score > 0) {
        return 1;
    }
    return exp(score/temp);
}

void solve(int t=-1) {
    Timer timer;
    C.reserve(10e6);
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

    ll _, M;
    cin >> _ >> M;
    S.resize(M);
    rep(i, M) {
        cin >> S[i];
    }

    // 初期解(貪欲)
    sort(ALL(S));
    ll k = 0;
    rep(i, N) {
        ll j = 0;
        while (j < N) {
            if (j+S[k].size() < N) {            
                rep(l, S[k].size()) {
                    mat[i][j+l] = S[k][l];
                }
                j += S[k].size();
                k++;
            } else {
                break;
            }
        }
    }
    count_all();
    ld score = calc_all(M);
    #ifdef __LOCAL
        debug(score);
    #endif

    // 焼きなまし
    auto elapsed = timer.get_diff();
    auto temp = calc_temp(elapsed);
    ll opcnt = 0;
    ld mxdiff = 0;
    while (1) {
        // 温度の更新
        if (opcnt%1 == 0) {
            elapsed = timer.get_diff();
            temp = calc_temp(elapsed);
            if (temp == -1) break;
        }
        opcnt++;

        ll h = randrange(0, N);
        ll w = randrange(0, N);
        ll c = randrange(0, L);
        char prevc = mat[h][w];
        count(h, w, letters[c]);
        ld nxt = calc_all(M);
        ld diff = nxt-score;
        chmax(mxdiff, abs(diff));
        if (diff >= 0 or calc_prob(diff, temp)*100 >= randrange(0, 100)) {
            score = nxt;
        } else {
            count(h, w, prevc);
        }
    }
    #ifdef __LOCAL
        debug(score);
        debug(opcnt);
        debug(mxdiff);
        debug(C.size());
    #endif

    rep(i, N) {
        #ifdef __LOCAL
            ofs << mat[i] << endl;
        #else
            print(mat[i]);
        #endif
    }
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
