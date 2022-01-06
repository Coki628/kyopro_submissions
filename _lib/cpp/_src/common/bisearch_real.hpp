#include "../macros.hpp"

// 条件を満たす最小値を見つける二分探索(実数)
template<typename F>
ld bisearch_min(ld mn, ld mx, const F &func, ll times) {
    ld ok = mx;
    ld ng = mn;
    rep(_, times) {
        ld mid = (ok+ng) / 2;
        if (func(mid)) {
            // 下を探しに行く
            ok = mid;
        } else {
            // 上を探しに行く
            ng = mid;
        }
    }
    return ok;
}

// 条件を満たす最大値を見つける二分探索(実数)
template<typename F>
ld bisearch_max(ld mn, ld mx, const F &func, ll times) {
    ld ok = mn;
    ld ng = mx;
    rep(_, times) {
        ld mid = (ok+ng) / 2;
        if (func(mid)) {
            // 上を探しに行く
            ok = mid;
        } else {
            // 下を探しに行く
            ng = mid;
        }
    }
    return ok;
}
