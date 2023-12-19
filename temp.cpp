#include <iostream>

using namespace std;

#define hello(i) \
i("asdf", 0, for (int j = 0; j < 5; j++) cout << "HI\n";) \
i("asdf", 1, for (int j = 0; j < 5; j++) cout << "Hello\n";) 

int main()
{
    #define i(st, f, p) if (f) {p}
    hello(i) {}

    {
        cout << "HI";
    }
    return 0;
}