#include <bits/stdc++.h>
#define LL long long
using namespace std;

const int EXIT_AC = 42;
const int EXIT_WA = 43;

const int mina = 1, maxa = 1000000000;

int wa() {
    exit(EXIT_WA);
}

int ac() {
    exit(EXIT_AC);
}

int main(int argc, char* argv[]) {
    ifstream tc_in(argv[1]);
    ifstream tc_out(argv[2]);
    string feedback_path = argv[3];
    feedback_path += "/judgeerror.txt";
    ofstream feedback(feedback_path);

    int n;
    tc_in >> n;
    int ans;
    if (!(cin >> ans)) {
        feedback << "no answer" << endl;
        return wa();
    }
    int impossible;
    tc_out >> impossible;
    if (impossible == -1) {
        if (ans != -1) {
            feedback << "contestant has solution while judge doesn't" << endl;
            return wa();
        } else {
            return ac();
        }
    }

    if (ans % n == 0 && ans >= mina && ans <= maxa) return ac();
    else return wa();

    return ac();
}