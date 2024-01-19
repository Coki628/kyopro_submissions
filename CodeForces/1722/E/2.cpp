/*
・なんとか自力AC。。
・Rectagle Sum、重み付きWavelet Matrix
・結局うしさん版のRectagle Sumで通した。
　X座標を予め一意にしておくみたいな下準備は要るが、まあそれは何回かやってるし。
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#define CONSTANTS
#define __LOCAL
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

#include "datastructure/SuccinctIndexableDictionary.hpp"

// 重み付きWavelet Matrix
template<typename T, int MAXLOG, typename D> struct WaveletMatrixRectangleSum {
    size_t length;
    SuccinctIndexableDictionary matrix[MAXLOG];
    vector<D> ds[MAXLOG];
    int mid[MAXLOG];

    WaveletMatrixRectangleSum() = default;

    WaveletMatrixRectangleSum(const vector<T> &v, const vector<D> &d)
        : length(v.size()) {
        assert(v.size() == d.size());
        vector<int> l(length), r(length), ord(length);
        iota(begin(ord), end(ord), 0);
        for (int level = MAXLOG - 1; level >= 0; level--) {
            matrix[level] = SuccinctIndexableDictionary(length + 1);
            int left = 0, right = 0;
            for (int i = 0; i < length; i++) {
                if (((v[ord[i]] >> level) & 1)) {
                    matrix[level].set(i);
                    r[right++] = ord[i];
                } else {
                    l[left++] = ord[i];
                }
            }
            mid[level] = left;
            matrix[level].build();
            ord.swap(l);
            for (int i = 0; i < right; i++) {
                ord[left + i] = r[i];
            }
            ds[level].resize(length + 1);
            ds[level][0] = D();
            for (int i = 0; i < length; i++) {
                ds[level][i + 1] = ds[level][i] + d[ord[i]];
            }
        }
    }

    pair<int, int> succ(bool f, int l, int r, int level) {
        return {
            matrix[level].rank(f, l) + mid[level] * f,
            matrix[level].rank(f, r) + mid[level] * f
        };
    }

    // count d[i] s.t. (l <= i < r) && (v[i] < upper)
    D rect_sum(int l, int r, T upper) {
        D ret = 0;
        for (int level = MAXLOG - 1; level >= 0; level--) {
            bool f = ((upper >> level) & 1);
            if (f)
                ret += ds[level][matrix[level].rank(false, r)] -
                       ds[level][matrix[level].rank(false, l)];
            tie(l, r) = succ(f, l, r, level);
        }
        return ret;
    }

    D rect_sum(int l, int r, T lower, T upper) {
        return rect_sum(l, r, upper) - rect_sum(l, r, lower);
    }
};

template<typename T, int MAXLOG, typename D>
struct CompressedWaveletMatrixRectangleSum {
    WaveletMatrixRectangleSum<int, MAXLOG, D> mat;
    vector<T> ys;

    CompressedWaveletMatrixRectangleSum(const vector<T> &v, const vector<D> &d)
        : ys(v) {
        sort(begin(ys), end(ys));
        ys.erase(unique(begin(ys), end(ys)), end(ys));
        vector<int> t(v.size());
        for (int i = 0; i < v.size(); i++) t[i] = get(v[i]);
        mat = WaveletMatrixRectangleSum<int, MAXLOG, D>(t, d);
    }

    inline int get(const T &x) {
        return lower_bound(begin(ys), end(ys), x) - begin(ys);
    }

    D rect_sum(int l, int r, T upper) {
        return mat.rect_sum(l, r, get(upper));
    }

    D rect_sum(int l, int r, T lower, T upper) {
        return mat.rect_sum(l, r, get(lower), get(upper));
    }
};

void solve() {
    ll N, Q;
    cin >> N >> Q;
    vector<pll> rect;
    Compress<pll> cp;
    rep(i, N) {
        ll h, w;
        cin >> h >> w;
        rect.eb(h, w);
        cp.add({w, i});
    }
    cp.build();
    ll L = cp.size();
    vector<ll> vec1(L), vec2(L);
    rep(i, N) {
        auto [h, w] = rect[i];
        vec1[cp[{w, i}]] = h;
        vec2[cp[{w, i}]] = h * w;
    }

    WaveletMatrixRectangleSum<ll, 18, ll> rectsm(vec1, vec2);
    rep(i, Q) {
        ll hs, ws, hb, wb;
        cin >> hs >> ws >> hb >> wb;
        ll res = rectsm.rect_sum(cp[{ws, INF}], cp[{wb, -INF}], hs + 1, hb);
        print(res);
    }
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
