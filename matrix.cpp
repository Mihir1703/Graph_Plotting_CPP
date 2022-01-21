#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
#include "library/pbPlots.cpp"
#include "library/supportLib.cpp"
using namespace std;
#define FastIO                        \
    ios_base::sync_with_stdio(false); \
    cin.tie(NULL);                    \
    cout.tie(NULL);
#define endl '\n'
typedef long long ll;
typedef long double ld;
const int mod = 1e9 + 7;
ll _count = 0;

// Graph Plotting

set<pair<ll, ld>> plot;

void plot_graph()
{
    StringReference *errorMessage = new StringReference();
    RGBABitmapImageReference *graph = CreateRGBABitmapImageReference();
    vector<double> x, y;
    for (auto point : plot)
    {
        x.push_back(double(point.first));
        y.push_back(double(point.second));
    }
    DrawScatterPlot(graph, 2000, 1200, &x, &y, errorMessage);
    vector<double> *png_data = ConvertToPNG(graph->image);
    WriteToFile(png_data, "multiply.png");
    DeleteImage(graph->image);
}

// Modern C++ random number generator

random_device dev;
mt19937 range(dev());
uniform_int_distribution<mt19937::result_type> gen(1, 100);

void solve()
{
    _count = 0;
    ll n;
    cin >> n;
    auto fill_matrix = [](ll n) -> vector<vector<ll>>
    {
        vector<vector<ll>> l(n, vector<ll>(n));
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                l[i][j] = gen(range);
                cout << l[i][j] << " ";
            }
            cout << endl;
        }
        return l;
    };
    cout << "Matrix A\n";
    vector<vector<ll>> a(fill_matrix(n));
    cout << "Matrix B\n";
    vector<vector<ll>> b(fill_matrix(n));
    chrono::high_resolution_clock::time_point start = chrono::high_resolution_clock::now();
    auto multiply = [](vector<vector<ll>> &a, vector<vector<ll>> &b) -> vector<vector<ll>>
    {
        ll space = a.size();
        vector<vector<ll>> res(space, vector<ll>(space));
        for (int i = 0; i < space; i++)
        {
            for (int j = 0; j < space; j++)
            {
                for (int k = 0; k < space; k++)
                {
                    _count++;
                    res[i][j] += a[i][k] * b[k][j];
                }
            }
        }
        return res;
    };
    vector<vector<ll>> ans = multiply(a, b);
    chrono::high_resolution_clock::time_point end = chrono::high_resolution_clock::now();
    chrono::duration<ld> timeElapsed = chrono::duration_cast<chrono::duration<ld>>(end - start);
    plot.insert({n, ld(timeElapsed.count() * 1e6)});
    cout << "\nResultant Matrix on Multiplication.\n";
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cout << ans[i][j] << " ";
        }
        cout << endl;
    }
    cout << "For n = " << n << " count = " << _count << " and time taken = " << ld(timeElapsed.count() * 1e6) << " microseconds for multiplication." << endl;
};

int main()
{
    int tc;
    cin >> tc;
    while (tc--)
    {
        solve();
    }
    plot_graph();
    return 0;
}