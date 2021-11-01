#include "../library/lib.hpp"

class Task {
public:
    void solveOne() {
        return;
    }

    void solve() {
        int nt = 1;
        //cin >> nt;
        for (int it = 0; it < nt; ++it) {
            solveOne();
        }
        return;
    }
};