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
    WriteToFile(png_data, "transpose.png");
    DeleteImage(graph->image);
}

// Random Number Generator C++

random_device dev;
mt19937 range(dev());
uniform_int_distribution<mt19937::result_type> gen(1, 100);

void solve()
{
    _count = 0;
    ll n, k;
    cin >> n;
    k = n;
    auto fill_matrix = [](ll n, ll k) -> vector<vector<ll>>
    {
        vector<vector<ll>> l(n, vector<ll>(k));
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < k; j++)
            {
                l[i][j] = gen(range);
                cout << l[i][j] << " ";
            }
            cout << endl;
        }
        return l;
    };
    cout << "Matrix\n\n";
    vector<vector<ll>> a(fill_matrix(n, k));
    chrono::high_resolution_clock::time_point start = chrono::high_resolution_clock::now();
    auto transpose = [](vector<vector<ll>> &a, int n, int k) -> vector<vector<ll>>
    {
        vector<vector<ll>> res(k, vector<ll>(n));
        for (int i = 0; i < k; i++)
        {
            for (int j = 0; j < n; j++)
            {
                res[i][j] = a[j][i];
            }
        }
        return res;
    };
    vector<vector<ll>> ans(transpose(a, n, k));
    chrono::high_resolution_clock::time_point end = chrono::high_resolution_clock::now();
    chrono::duration<ld> timeElapsed = chrono::duration_cast<chrono::duration<ld>>(end - start);
    cout << "\nResultant Matrix on Transpose.\n\n";
    plot.insert({n, ld(timeElapsed.count() * 1e6)});
    for (int i = 0; i < k; i++)
    {
        for (int j = 0; j < n; j++)
        {
            _count++;
            cout << ans[i][j] << " ";
        }
        cout << endl;
    }
    cout << "For n = " << n << " count = " << _count << " and time taken = " << ld(timeElapsed.count() * 1e6) << " microseconds for Transpose." << endl;
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
    for(auto x:plot){
        cout<<x.first<<"\t\t"<<x.second<<endl;
    }
    return 0;
}
