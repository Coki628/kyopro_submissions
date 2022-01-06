#include "../macros.hpp"

// マージソートによる転倒数取得
// ・座圧BITより速いけど、参照渡しやめるとバグるので、
// 　元の列もまだ使う場合はコピーしてからやること。
// ・座圧を二分探索ベースにしてからまだ速度比較してないので、
// 　もしかしたらそっちの座圧版だったら大差ないかも。

// 転倒数取得
ll get_inversion(vector<ll> &a) {
    int n = a.size();
    if (n <= 1) { return 0; }

    ll cnt = 0;
    vector<ll> b(a.begin(), a.begin()+n/2);
    vector<ll> c(a.begin()+n/2, a.end());

    cnt += get_inversion(b);
    cnt += get_inversion(c);

    int ai = 0, bi = 0, ci = 0;
    // mergeの処理
    while (ai < n) {
        if ( bi < b.size() && (ci == c.size() || b[bi] <= c[ci]) ) {
            a[ai++] = b[bi++];
        } else {
            cnt += n / 2 - bi;
            a[ai++] = c[ci++];
        }
    }
    return cnt;
}
