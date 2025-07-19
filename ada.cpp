/*
Medical Equipment Allocation

The objective of this project is to develop an optimized medical equipment allocation plan
that ensures efficient and effective healthcare delivery while minimizing cost and maximizing patient outcomes. 
The project will focus on optimizing the distribution of medical equipment to healthcare facilities to ensure 
equitable access to essential medical equipment and reduce the wastage of resources. 
The algorithm will be applied to the healthcare facilities network, with nodes representing healthcare
facilities and edges representing the transportation routes connecting them. 
The algorithm will find the minimum spanning tree that connects all the healthcare facilities. 
he results of the project will provide an optimized medical equipment allocation plan that
ensures efficient and effective healthcare delivery, reduces cost and wastage of resources,
and promotes patient outcomes.
*/
#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>

using namespace std;

struct Edge {
    int source, destination, weight;
};

class MedicalEquipmentAllocation {
private:
    int numFacilities;
    vector<Edge> edges;
    vector<Edge> result;

    int findSet(vector<int>& parent, int i) {
        if (parent[i] != i) {
            parent[i] = findSet(parent, parent[i]);
        }
        return parent[i];
    }

    void unionSets(vector<int>& parent, vector<int>& rank, int x, int y) {
        int rootX = findSet(parent, x);
        int rootY = findSet(parent, y);
        if (rank[rootX] < rank[rootY]) {
            parent[rootX] = rootY;
        } else if (rank[rootX] > rank[rootY]) {
            parent[rootY] = rootX;
        } else {
            parent[rootY] = rootX;
            rank[rootX]++;
        }
    }

    static bool compareEdges(const Edge& a, const Edge& b) {
        return a.weight < b.weight;
    }

    void kruskalMST() {
        result.clear();
        sort(edges.begin(), edges.end(), compareEdges);
        vector<int> parent(numFacilities);
        vector<int> rank(numFacilities, 0);
        for (int i = 0; i < numFacilities; i++) {
            parent[i] = i;
        }
        for (const Edge& edge : edges) {
            int x = findSet(parent, edge.source);
            int y = findSet(parent, edge.destination);
            if (x != y) {
                result.push_back(edge);
                unionSets(parent, rank, x, y);
            }
        }
        cout << "Optimization completed.\n";
        saveDataToFile(true); // Append optimized data
    }

    void displayMST() const {
        if (result.empty()) {
            cout << "No optimized allocation plan available. Please run the optimization first.\n";
            return;
        }
        cout << "Minimum Spanning Tree (Optimized Allocation Plan):" << endl;
        for (const Edge& edge : result) {
            cout << "Facility " << edge.source << " - Facility " << edge.destination << " : Weight = " << edge.weight << endl;
        }
    }

    void displayRoutes() const {
        if (edges.empty()) {
            cout << "No transportation routes available. Please add some routes first.\n";
            return;
        }
        cout << "All Transportation Routes:" << endl;
        for (const Edge& edge : edges) {
            cout << "Facility " << edge.source << " - Facility " << edge.destination << " : Weight = " << edge.weight << endl;
        }
    }

    void saveDataToFile(bool append = false) const {
        const string filename = "medical_equipment_allocation_data.txt";
        ofstream file(filename, append ? ios::app : ios::trunc); // Append or overwrite mode
        if (!file) {
            cerr << "Error opening file for writing!" << endl;
            return;
        }
        file << "Current Number of Facilities: " << numFacilities << endl;
        file << "All Transportation Routes:\n";
        for (const Edge& edge : edges) {
            file << "Facility " << edge.source << " - Facility " << edge.destination << " : Weight = " << edge.weight << endl;
        }
        file << "Optimized Allocation Plan (MST):\n";
        for (const Edge& edge : result) {
            file << "Facility " << edge.source << " - Facility " << edge.destination << " : Weight = " << edge.weight << endl;
        }
        file << "--------------------------------------------------\n";
        file.close();
        cout << "Data saved to " << filename << endl;
    }

    void displayStoredData() const {
        const string filename = "medical_equipment_allocation_data.txt";
        ifstream file(filename);
        if (!file) {
            cerr << "Error opening file for reading!" << endl;
            return;
        }
        string line;
        while (getline(file, line)) {
            cout << line << endl;
        }
        file.close();
    }

public:
    MedicalEquipmentAllocation(int n) : numFacilities(n) {}

    void addEdge(int u, int v, int w) {
        Edge edge = {u, v, w};
        edges.push_back(edge);
        cout << "Route added successfully and marked as new data.\n";
        saveDataToFile(true); // Append new data
    }


    void increaseFacilities(int additionalFacilities) {
        if (additionalFacilities > 0) {
            numFacilities += additionalFacilities;
            cout << "Number of facilities increased. New total: " << numFacilities << endl;
            saveDataToFile(true); // Append new data
        } else {
            cout << "Invalid number of additional facilities. Please enter a positive integer.\n";
        }
    }

    void displayMenu() const {
        cout << "\nMedical Equipment Allocation System\n";
        cout << "1. Add Transportation Route\n";
        cout << "2. Optimize Equipment Allocation (Find MST)\n";
        cout << "3. Display Optimized Allocation Plan\n";
        cout << "4. Reset Data\n";
        cout << "5. Display All Transportation Routes\n";
        cout << "6. Save Data\n";
        cout << "7. Display Stored Data\n";
        cout << "8. Increase Number of Facilities\n";
        cout << "9. Exit\n";
        cout << "Enter your choice: ";
    }

    void executeChoice(int choice) {
        int u, v, w, additionalFacilities;
        switch (choice) {
            case 1:
                cout << "Enter source facility, destination facility, and transportation cost: ";
                while (!(cin >> u >> v >> w)) {
                    cout << "Invalid input. Please enter integers for source, destination, and cost: ";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
                addEdge(u, v, w);
                break;
            case 2:
                kruskalMST();
                break;
            case 3:
                displayMST();
                break;
            case 4:
                edges.clear();
                result.clear();
                cout << "Data reset successfully.\n";
                saveDataToFile(); // Save cleared data (overwrite)
                break;
            case 5:
                displayRoutes();
                break;
            case 6:
                saveDataToFile();
                break;
            case 7:
                displayStoredData();
                break;
            case 8:
                cout << "Enter number of additional facilities to add: ";
                while (!(cin >> additionalFacilities)) {
                    cout << "Invalid input. Please enter a positive integer: ";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
                increaseFacilities(additionalFacilities);
                break;
            case 9:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    }
};

int main() {
    int numFacilities, choice;
    cout << "Enter the number of healthcare facilities: ";
    while (!(cin >> numFacilities) || numFacilities <= 0) {
        cout << "Invalid input. Please enter a positive integer for the number of facilities: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    MedicalEquipmentAllocation allocation(numFacilities);

    do {
        allocation.displayMenu();
        while (!(cin >> choice)) {
            cout << "Invalid input. Please enter an integer between 1 and 9: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        allocation.executeChoice(choice);
    } while (choice != 9);

    return 0;
}
