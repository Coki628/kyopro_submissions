template<typename T>
T ceil(T a, T b) {
    if (a >= 0) return (a+b-1) / b;
    else return a / b;
}
