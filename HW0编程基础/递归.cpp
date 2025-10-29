#include<iostream>

using namespace std;

int main()
{
    int n, m;
    cin >> n >> m;

    int f = 0;
    for (int i = 0; i < n; i++)
    {
        f = (f + m) % (i + 1);
    }
    cout << f << endl;

    return 0;
}