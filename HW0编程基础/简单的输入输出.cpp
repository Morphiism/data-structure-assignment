#include<iostream>

using namespace std;

int main()
{
    double income, total = 0;

    for (int i = 0; i < 12; ++i)
    {
        cin >> income;
        total += income;
    }

    cout << "¥" << total / 12.0 << endl;

    return 0;
}