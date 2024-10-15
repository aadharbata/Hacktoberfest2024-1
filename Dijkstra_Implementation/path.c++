#include <iostream>
#include <string>
#include <climits>
#include <vector>
#include <iomanip>

using namespace std;

int mindistance(int distance[], bool stat[], int n) {
    int minimum = INT_MAX, index;
    for (int k = 0; k < n; k++) {
        if (!stat[k] && distance[k] <= minimum) {
            minimum = distance[k];
            index = k;
        }
    }
    return index;
}

void dijkstra(int graph[53][53], int source, string stations[], int n) {
    int distance[53];
    bool stat[53];
    int parent[53]; // To store the path

    for (int k = 0; k < n; k++) {
        distance[k] = INT_MAX;
        stat[k] = false;
        parent[k] = -1; // Initialize parent array
    }

    distance[source] = 0;

    for (int k = 0; k < n; k++) {
        int m = mindistance(distance, stat, n);
        stat[m] = true;

        for (int i = 0; i < n; i++) {
            if (!stat[i] && graph[m][i] && distance[m] != INT_MAX && 
                (distance[m] + graph[m][i] < distance[i])) {
                distance[i] = distance[m] + graph[m][i];
                parent[i] = m; // Update parent
            }
        }
    }

    cout << "Minimum distance from " << stations[source] << " to every station:\n\n";
    for (int k = 0; k < n; k++) {
        cout << "Minimum distance from " << stations[source] << " to " << stations[k] 
             << " is " << distance[k] << " via path: ";

        // Reconstruct path
        if (distance[k] == INT_MAX) {
            cout << "No path";
        } else {
            vector<int> path;
            for (int v = k; v != -1; v = parent[v]) {
                path.push_back(v);
            }
            // Print the path in reverse order
            for (int j = path.size() - 1; j >= 0; j--) {
                cout << stations[path[j]];
                if (j > 0) cout << " -> ";
            }
        }
        cout << endl;
    }
}

int main() {
    int n = 53; // Number of stations
    int graph[53][53] = {0}; // Adjacency matrix
    string stations[53]; // Station names

    // Input station names
    cout << "Enter names of 53 stations:\n";
    for (int i = 0; i < n; i++) {
        cout << "Station " <<
