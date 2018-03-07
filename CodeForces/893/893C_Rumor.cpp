#include <iostream>

#include <list>
#include <vector>
#include <limits>
#include <cstring>

#define N 100000
#define M 100000


struct character
{
    long long cost;
    bool is_visit;
};

int n, m;
struct character c[N];
std::vector< std::list<int> > graph;

void graph_by_adjlist(int x, int y)
{
    graph.at(x).push_back(y);
    graph.at(y).push_back(x);
}

long long DFS(int v, long long cur_min)
{
    long long min = (c[v].cost > cur_min) ? cur_min : c[v].cost;

    for (std::list<int>::iterator it=graph[v].begin(); it!=graph[v].end(); ++it) {
        if (true == c[(*it)].is_visit)
            continue;

        c[(*it)].is_visit = true;
        min = DFS(*it, min);
    }

    return min;
}

long long get_min_gold()
{
    long long sum = 0;
    long long min;

    for(int i=0; i<n; ++i) {
        if (true == c[i].is_visit)
            continue;

        min = std::numeric_limits<long long>::max();     // reset

        c[i].is_visit = true;
        min = DFS(i, min);

        sum += min;
    }

    return sum;
}

int main()
{
    int x, y;

    std::cin >> n >> m;

    graph.resize(n);
    memset(c, 0, N*sizeof(struct character));

    for (int i=0; i<n; ++i) {
        std::cin >> c[i].cost;
    }    

    for (int i=0; i<m; ++i) {
        std::cin >> x >> y;
        graph_by_adjlist(x-1, y-1);     // bacause character starts from 1, shifting to 0
    }

    std::cout << get_min_gold() << "\n";

    return 0;
}
