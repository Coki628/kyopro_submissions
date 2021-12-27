template<typename T>
T floor(T a, T b) {
    if (a < 0) return (a-b+1) / b;
    else return a / b;
}
