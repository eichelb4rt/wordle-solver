#include <map>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

map<string, vector<string>> read_csv(string filename, int& n_items) {
    // Reads a CSV file into a vector of <string, vector<int>> pairs where
    // each pair represents <column name, column values>

    // Create a vector of <string, int vector> pairs to store the result
    map<string, vector<string>> result;
    vector<string> column_names;

    // Create an input filestream
    ifstream input_file(filename);

    // Helper vars
    string line, colname, item;

    // Read the column names
    // Extract the first line in the file
    getline(input_file, line);

    // Create a stringstream from line
    stringstream ss(line);

    // Extract each column name
    while (getline(ss, colname, ',')) {
        // Initialize and add <colname, int vector> pairs to result
        result[colname] = {};
        column_names.push_back(colname);
    }

    // Read data, line by line
    n_items = 0;
    while (getline(input_file, line)) {
        // Create a stringstream of the current line
        stringstream ss(line);
        int column_id = 0;
        while (getline(ss, item, ',')) {
            // Initialize and add <colname, int vector> pairs to result
            result[column_names[column_id++]].push_back(item);
        }
        ++n_items;
    }

    // Close file
    input_file.close();

    return result;
}