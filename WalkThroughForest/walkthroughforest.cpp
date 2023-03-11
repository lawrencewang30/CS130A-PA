#include <iostream>
#include <math.h>
#include <iomanip>
#include <string>
#include <vector>
#include <unordered_map>
#include <sstream>
#include <cmath>
#include <algorithm>
#include <queue>
using namespace std;

vector<vector<pair<int, int>>> adjacent_list;
vector<vector<int>> adjacent_list2;
vector<int> dist;   // vector holding distance
vector<int> topological_sort;
priority_queue<tuple<int, int>, vector<tuple<int, int>>, greater<tuple<int, int>>> dijkstra_queue;

void topologicalSort(int a) {
    dist[a] = 1;
    for (auto b : adjacent_list2[a]) {
        if (dist[b] == 0) {
            topologicalSort(b);
        }
    }
    topological_sort.push_back(a);
}

int main() {
    while (1) {
        int n, m;
        cin >> n;
        if (n == 0) {
            break;
        }
        cin >> m;
        
        adjacent_list.assign(n, vector<pair<int, int>>());
        adjacent_list2.assign(n, vector<int>());
        dist.assign(n, 1e9);
        
        int a, b, d;
        
        for (int i = 0; i < m; ++i) {
            cin >> a >> b >> d;
            a--;        //these 2 lines match up with number of intersections (paths = intersections + 1, which is why we decrement the individual intersections to match n
            b--;
            adjacent_list[a].push_back({d, b});
            adjacent_list[b].push_back({d, a});
        }
        
        int office = 1;
        dist[office] = 0;
        dijkstra_queue.push({0, office});
        while (dijkstra_queue.empty() != true) {     //find shortest distance between house and each intersection
            auto [u, a] = dijkstra_queue.top();
            dijkstra_queue.pop();
            
            if (u > dist[a]) {
                continue;
            }
            for (auto &[d, b] : adjacent_list[a]) {
                if (dist[b] > dist[a] + d) {
                    dist[b] = dist[a] + d;
                    dijkstra_queue.push({dist[b], b});
                }
            }
        }
        
        //DAG construction connecting adjacent nodes with shorter paths to house
        for (int i = 0; i < n; ++i) {
            for (auto &[d, b] : adjacent_list[i]) {
                if (dist[b] < dist[i]) {
                    adjacent_list2[i].push_back(b);
                }
            }
        }
        
        //topological sorting by calling function
        dist.assign(n, 0);
        topological_sort.clear();
        for (int i = 0; i < n; ++i) {
            if (dist[i] == 0) {
                topologicalSort(i);
            }
        }
         //counting total paths Jimmy can take
        
        reverse(topological_sort.begin(), topological_sort.end());   //reverse vector since recursive function call will put original topo. order vector in reversed order
        
        dist.assign(n, 0);
        dist[0] = 1; 
        for (int i = 0; i < topological_sort.size(); ++i) {
            for (auto v : adjacent_list2[topological_sort[i]]) {
                dist[v] += dist[topological_sort[i]];
            }
        }
        
        cout << dist[office] << endl;
    }
    
    return 0;
}