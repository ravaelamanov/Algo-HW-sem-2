#include <iostream>
#include <fstream>
#include <vector>
#include <utility>
#include <climits>

using namespace std;

int extractMin(long long dist[], bool used[], int vertexes) {
    int min = -1;
    for (int i = 1; i <= vertexes; i++) {
        if (!used[i] && (min == -1 || dist[i] < dist[min]))
            min = i;
    }
    return min;
}

long long dijkstra(vector<pair<int, int>> graph[], int vertexes, int start, int finish) {
    long long dist[vertexes + 1];
    bool used[vertexes + 1];
    for (int i = 1; i <= vertexes; i++) {
        dist[i] = LONG_LONG_MAX;
        used[i] = false;
    }
    dist[start] = 0;
    for (int i = 1; i <= vertexes; i++) {
        int min = extractMin(dist, used, vertexes);
        if (dist[min] == LONG_LONG_MAX || min == finish) {
            break;
        }
        used[min] = true;
        for (int j = 0; j < graph[min].size(); j++) {
            if (dist[graph[min][j].first] > dist[min] + graph[min][j].second) {
                dist[graph[min][j].first] = dist[min] + graph[min][j].second;
            }
        }
    }
    return dist[finish] == LONG_LONG_MAX ? -1 : dist[finish];
}

int main() {
    ifstream fin("pathmgep.in");
    ofstream fout("pathmgep.out");
    int vertexes, start, finish;
    fin >> vertexes >> start >> finish;
    vector<pair<int, int>> graph[vertexes + 1];
    int weight;
    for (int i = 1; i <= vertexes; i++) {
        for (int j = 1; j <= vertexes; j++) {
            fin >> weight;
            if (weight != -1 && i != j) {
                graph[i].emplace_back(j, weight);
            }
        }
    }
    fout << dijkstra(graph, vertexes, start, finish);
    return 0;
}
