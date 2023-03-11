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
// Kahn's algorithm using BFS, modified it to suit the correct data types for user made queues, vectors, and maps
unordered_map<string, int> skepticism_total;
vector<int> heard;
vector<int> skepticism_value;
vector<vector<int>> adjacent_connections;
priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> bfs_queue;  // min heap
int main() {
    int n, m, d;
    cin >> n >> m >> d;
    adjacent_connections.assign(n, vector<int>());
    skepticism_value.assign(n, 0);
    heard.assign(n, 0);

    for (int i = 0; i < n; i++) {
        string name;
        cin >> name >> skepticism_value[i];
        skepticism_total[name] = i;                   // implement integer values for each name, used in next for loop
    }
    for (int i = 0; i < m; i++) {
        string friend1, friend2;
        cin >> friend1 >> friend2;
        adjacent_connections[skepticism_total[friend1]].emplace_back(skepticism_total[friend2]);        // these two lines put pairs of connections in adjust_connections vector using integer values from previous loop
        adjacent_connections[skepticism_total[friend2]].emplace_back(skepticism_total[friend1]);
    }

    string source;
    cin >> source;

    int answer = 0;
    bfs_queue.push({0, skepticism_total[source]});
    heard[skepticism_total[source]] = 1;
    
    while (bfs_queue.empty() == false) {  // Kahn's algorithm that starts at in-degree node of 0, which is always the last line of user input since it is the source of the rumour
        auto [day, v] = bfs_queue.top();  // data type format for queue implemented, use day which value changes based on key of the queue
        bfs_queue.pop();
        if (day >= d) {     // this avoids possible repeated connections to be added to answer (ex: Bob Dan and Dan Bob should be just 1), also keeps track of # days
            break;
        }
        for (int i : adjacent_connections[v]) {
            if (heard[i] == 0) {
                heard[i] = 1;
                answer++;
            }
            skepticism_value[i]--;
            if (skepticism_value[i] == 0) {
                bfs_queue.push({day + 1, i});
            }
        }
    }
    
    cout << answer << endl;
    
    return 0;
}