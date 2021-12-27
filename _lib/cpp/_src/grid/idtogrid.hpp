#include "../macros.hpp"
#include "../common/divmod.hpp"

// 列⇒グリッド変換
pll idtogrid(ll id, ll W) { return divmod(id, W); }
