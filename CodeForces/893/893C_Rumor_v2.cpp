#include <bits/stdc++.h>

#define N 100000
#define M 100000

int c[N];
int graph[N];

int find(int x)
{
    return x==graph[x] ? x :  graph[x]=find(graph[x]);
}

int main()
{
    long long min = 0;
    int n, m;
    int x, y;

    std::cin >> n >> m;

    for (int i=1; i<=n; ++i) {
        std::cin >> c[i];
        graph[i] = i;
    }

    for (int i=1; i<=m; ++i) {
        std::cin >> x >> y;
        graph[find(x)] = find(y);
    }

    for (int i=1; i<=n; ++i) {
        graph[i] = find(i);
        c[graph[i]] = std::min(c[graph[i]], c[i]);
    }

    for (int i=1; i<=n; ++i) {
        if (graph[i] == i)
            min += c[i];
    }

    std::cout << min << "\n";

    return 0;
}
