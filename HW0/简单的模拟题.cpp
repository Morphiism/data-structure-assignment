#include<iostream>

using namespace std;

void counter(int n);

int main()
{
    int n;
    cin >> n;

    while (n != -1)
    {
        counter(n);
        cin >> n;
    }

    return 0;
}

void counter(int n)
{
    long long female = 1, male = 0;
    long long new_female, new_male;

    for (int i = 0; i < n; ++i)
    {
        new_female = 1 + male;
        new_male = male + female;

        female = new_female;
        male = new_male;
    }

    cout << male << " " << female + male << endl;
}