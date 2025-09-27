#include<iostream>
#include<string>

using namespace std;

int main()
{
    string s;
    getline(cin, s);

    while (s[0] != '#')
    {
        int value = 0;
        for (int i = 0; i < s.length(); ++i)
        {
            if (s[i] >= 'A' && s[i] <= 'Z')
                value += (s[i] - 'A' + 1) * (i + 1);
        }
        cout << value << endl;
        getline(cin, s);
    }

    return 0;
}