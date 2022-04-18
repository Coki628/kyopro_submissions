#include "template.hpp"

void solve() {
    ll N, Q;
    cin >> N >> Q;
    auto A = LIST(N);

    // バケットの準備
    ll D = ceil(sqrt(N));
    ll L = N / D + 1;
    vvpll bucket(L);
    rep(i, N) {
        bucket[i/D].pb({A[i], i});
    }

    // (まとめて処理する用の何かもここで準備)

    rep(_, Q) {
        ll l, r, x;
        cin >> l >> r >> x;
        l--;

        ll ld = l / D;
        ll rd = (r-1) / D;
        // 左端と右端が同じ区間
        if (ld == rd) {
            rep(i, l, r) {
                // 愚直に何かする
            }
        } else {
            // 左右の端は愚直に見る(累積で前計算できたりする(abc223_h))
            for (auto& [a, i] : bucket[ld]) {
                if (l <= i and i < r) {
                    // 愚直に何かする
                }
            }
            for (auto& [a, i] : bucket[rd]) {
                if (l <= i and i < r) {
                    // 愚直に何かする
                }
            }
            // 全部を含む区間はまとめて処理
            rep(i, ld+1, rd) {
                // まとめて何かする
            }
        }
    }
}
