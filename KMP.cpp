#include <iostream>
#include<vector>
using namespace std;

//preprocessing function
//abcabc
vector<int> prefixFunction(string &pat)
{
    int m = pat.size();
    vector<int> arr(m);

    int k = -1;
    arr[0] = -1;
    for (int i = 1; i < m; i++)
    {
        while (k >= 0 && pat[k + 1] != pat[i])
        {
            k = arr[k];
        }

        if (pat[k + 1] == pat[i])
            k++;
        arr[i] = k;
    }

    return arr;
}

void KMP_Algo(string &pat, string &txt)
{
    int n = txt.size();
    int m = pat.size();

    vector<int> arr = prefixFunction(pat);

    int q = -1;
    for (int i = 0; i < n; i++)
    {
        while (q >= 0 && pat[q + 1] != txt[i])
            q = arr[q];

        if (pat[q + 1] == txt[i])
            q++;

        if (q == m - 1)
        {
            cout<<"Index is : " << i-m+1 << endl;
            cout<<"Text is : ";
            for (int j = m - 1; j >= 0; j--)
                cout << txt[i - j];
            cout << endl;
            q = arr[q];
        }
    }
}

int main()
{
    string pat, txt;
    cout << "Enter the string Pattern :";
    cin >> pat;
    cout << "Enter the string Text :";
    cin >> txt;

    KMP_Algo(pat, txt);
}