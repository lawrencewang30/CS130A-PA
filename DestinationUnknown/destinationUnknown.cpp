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
#include <set>
#include <map>
using namespace std;

int number_testCases;
set<int> possible_destinations;
int n, m, t, source, g, h, a, b, d, x;
vector<pair<int, int>> adjlist[2001];   // initialize size to max number of test cases + 1(2000 in this problem)
map<pair<int, int>, int> dist;  // key = intersection, used edge (1 if edge is where duo travelled), value = distance, will change in dijkstra algorithm
priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, greater<tuple<int, int, int>>> dijkstra_queue;
int main() {
    cin >> number_testCases;
    for (int i = 0; i < number_testCases; i++) {
        dist.clear();
        possible_destinations.clear();

        cin >> n >> m >> t;
        cin >> source >> g >> h;
        for (int i = 0; i <= n; i++) {
            adjlist[i].clear();
        }

        for (int i = 0; i < m; i++) {
            cin >> a >> b >> d;
            adjlist[a].emplace_back(b, d);
            adjlist[b].emplace_back(a, d);
        }

        for (int i = 0; i < t; i++) {
            cin >> x;
            possible_destinations.insert(x);
        }

        dist.insert({{source, 0}, 0});
        dijkstra_queue.emplace(0, source, 0);
        
        while (dijkstra_queue.empty() != true) {
            auto [d, u, traveled_edge] = dijkstra_queue.top();  //traveled_edge value is 1 if duo traveled there, 0 otherwise
            dijkstra_queue.pop();
            
            if (d > dist[{u, traveled_edge}]) {
                continue;
            }
            
            for (auto [v, w] : adjlist[u]) {
                if (max(u, v) == max(g, h) && min(u, v) == min(g, h)) {
                    if (dist.count({v, 1}) && dist[{v, 1}] < d + w) {
                        continue;
                    }
                    dist[{v, 1}] = d + w;
                    dijkstra_queue.emplace(d + w, v, 1);
                }
                else {
                    if (dist.count({v, traveled_edge}) && dist[{v, traveled_edge}] < d + w) {
                        continue;
                    }
                    dist[{v, traveled_edge}] = d + w;
                    dijkstra_queue.emplace(d + w, v, traveled_edge);
                }
            }
        }
            
            for (auto i : possible_destinations) {
                if (dist.count({i, 1}) && (dist.count({i, 0}) == 0 || dist[{i, 1}] <= dist[{i, 0}])) {  //first statement asks if there is a path from i to the traveled edge duo took, 
                    cout << i << " ";                                                                   //second statement states either there is no other path to go to destination that duo did not travel too or distance going through the duo's traveled edge is shorter than going through non traveled edges
                }
            }
            cout << endl;
    }
    
    return 0;
}