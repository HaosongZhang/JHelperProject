#include "../tasks/Task.cpp"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cctype>
#include <ctime>

namespace Color {
    enum Code {
        FG_RED = 31,
        FG_GREEN = 32,
        FG_YELLOW = 33,
        FG_BLUE = 34,
        FG_PURPLE = 35,
        FG_ORANGE = 208,
        FG_DEFAULT = 39,
        BG_RED = 41,
        BG_GREEN = 42,
        BG_BLUE = 44,
        BG_DEFAULT = 49
    };
    class Modifier {
        Code code;
    public:
        Modifier(Code pCode) : code(pCode) {}
        friend std::ostream&
        operator<<(std::ostream& os, const Modifier& mod) {
            return os << "\033[" << mod.code << "m";
        }
    };
}

Color::Modifier red(Color::FG_RED);
Color::Modifier green(Color::FG_GREEN);
Color::Modifier yellow(Color::FG_YELLOW);
Color::Modifier blue(Color::FG_BLUE);
Color::Modifier orange(Color::FG_ORANGE);
Color::Modifier purple(Color::FG_PURPLE);
Color::Modifier def(Color::FG_DEFAULT);

namespace jhelper {

    struct Test {
        std::string input;
        std::string output;
        bool active;
        bool has_output;
    };

    bool check(std::string expected, std::string actual) {
        while(!expected.empty() && isspace(*--expected.end()))
            expected.erase(--expected.end());
        while(!actual.empty() && isspace(*--actual.end()))
            actual.erase(--actual.end());
        return expected == actual;
    }

} // namespace jhelper

int main() {
    std::vector<jhelper::Test> tests = {

    };
    bool allOK = true;
    int testID = 0;
    std::cout << std::fixed;
    double maxTime = 0.0;
    for (const jhelper::Test& test : tests) {
        std::cout << "Test #" << ++testID << std::endl;
        std::cout << "Input: \n" << test.input << std::endl;
        if (test.has_output) {
            std::cout << "Expected output: \n" << test.output << std::endl;
        }
        else {
            std::cout << "Expected output: \n" << "N/A" << std::endl;
        }
        if (test.active) {
            std::stringstream in(test.input);
            std::ostringstream out;
            std::clock_t start = std::clock();
            std::streambuf *oldcin, *oldcout;
            oldcin = std::cin.rdbuf(in.rdbuf());
            oldcout = std::cout.rdbuf(out.rdbuf());
            Task solver;
            solver.solve();
            std::cin.rdbuf(oldcin);
            std::cout.rdbuf(oldcout);
            std::clock_t finish = std::clock();
            double currentTime = double(finish - start) / CLOCKS_PER_SEC;
            maxTime = std::max(currentTime, maxTime);
            std::cout << "Actual output: \n" << out.str() << std::endl;
            if (test.has_output) {
                bool result = jhelper::check(test.output, out.str());
                allOK = allOK && result;
                std::cout << "Result: " << (result ? "OK" : "Wrong answer") << std::endl;
            }
            std::cout << "Time: " << currentTime << std::endl;
        }
        else {
            std::cout << "SKIPPED\n";
        }

        std::cout << std::endl;

    }
    if (allOK) {
        std::cout << green << "All OK" << def << std::endl;
    }
    else {
        std::cout << red << "Some cases failed" << def << std::endl;
    }
    std::cout << purple << "Maximal time: " << maxTime << "s." << def << std::endl;
    return 0;
}
