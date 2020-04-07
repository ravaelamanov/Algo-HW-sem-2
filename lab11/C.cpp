#include <iostream>
#include <fstream>
#include <vector>
#include <utility>
#include <climits>
#include <queue>

using namespace std;

ifstream fin("pathbgep.in");
ofstream fout("pathbgep.out");

int extractMin(long long dist[], bool used[], int vertexes) {
    int min = -1;
    for (int i = 1; i <= vertexes; i++) {
        if (!used[i] && (min == -1 || dist[i] < dist[min]))
            min = i;
    }
    return min;
}

void dijkstra(vector<pair<int, int>> graph[], int vertexes, int start) {
    vector<long long> dist(vertexes);
    bool used[vertexes];
    for (int i = 0; i < vertexes; i++) {
        dist[i] = LONG_LONG_MAX;
        used[i] = false;
    }
    dist[start] = 0;
    priority_queue<pair<long long, int>> q;
    q.push(make_pair(0, 0));
    while (!q.empty()) {
        long long minDist = -q.top().first;
        int min = q.top().second;
        q.pop();
        if (minDist > dist[min])
            continue;
        used[min] = true;
        for (int j = 0; j < graph[min].size(); j++) {
            if (dist[graph[min][j].first] > dist[min] + graph[min][j].second) {
                dist[graph[min][j].first] = dist[min] + graph[min][j].second;
                q.push(make_pair(-dist[graph[min][j].first], graph[min][j].first));
            }
        }
    }
    for (int i = 0; i < vertexes; i++) {
        fout << dist[i] << " ";
    }
}

int main() {
    int vertexes, edges, n1, n2, weight;
    fin >> vertexes >> edges;
    vector<pair<int, int>> graph[vertexes];
    while (edges--) {
        fin >> n1 >> n2 >> weight;
        graph[n1 - 1].emplace_back(n2 - 1, weight);
        graph[n2 - 1].emplace_back(n1 - 1, weight);
    }
    dijkstra(graph, vertexes, 0);
    return 0;
}
