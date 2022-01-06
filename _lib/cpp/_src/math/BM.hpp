#include "../macros.hpp"
#include "berlekamp_massey.hpp"
#include "kth_term_of_linearly_recurrent_sequence.hpp"

// BM：線形漸化式の数列Aから、その第K項を求める
template<template<typename> class FPS, typename Mint>
Mint BM(FPS<Mint> A, ll K) {
    auto bm = berlekamp_massey(A);
    bm.pop_back();
    reverse(ALL(bm));
    A.resize(bm.size());
    return kth_term_of_linearly_recurrent_sequence(A, bm, K);
}
