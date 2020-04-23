#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

bool dfs(int x, vector<int> graph[], vector<int>& px, vector<int>& py, vector<bool>& visited) {
    if (visited[x]) return false;
    visited[x] = true;
    for (int i = 0; i < graph[x].size(); i++) {
        int y = graph[x][i];
        if (py[y] == -1) {
            py[y] = x;
            px[x] = y;
            return true;
        }
        else {
            if (dfs(py[y], graph, px, py, visited)) {
                py[y] = x;
                px[x] = y;
                return true;
            }
        }
    }
    return false;
}

int fordFulkerson(vector<int> graph[], int n, int m) {
    vector<int> px(n, -1);
    vector<int> py(m, -1);
    bool existsPath = true;
    while (existsPath) {
        existsPath = false;
        vector<bool> visited(n, false);
        for (int i = 0; i < n; i++) {
            if (px[i] == -1) {
                if (dfs(i, graph, px, py, visited))
                    existsPath = true;
            }
        }
    }
    int result = 0;
    for (int i = 0; i < n; i++) {
        if (px[i] != -1)
            result++;
    }
    return result;
}

int main() {
    ifstream fin("matching.in");
    ofstream fout("matching.out");
    int n, m, k;
    fin >> n >> m >> k;
    vector<int> graph[n];
    int from, to;
    for (int i = 0; i < k; i++) {
        fin >> from >> to;
        graph[from - 1].push_back(to - 1);
    }
    fout << fordFulkerson(graph, n, m);
    return 0;
}
