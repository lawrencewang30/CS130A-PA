#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <sstream>
#include <algorithm>
using namespace std;

bool duplicates(vector<string> Words) {
    sort(Words.begin(), Words.end());
    
    for (int i = 1; i < Words.size(); ++i) {
        if (Words[i-1] == Words[i]) {
            return true;
        }
    }
    
    return false;
}
int main() {
    string input;
    string temp;
    vector<string> words;
    
    getline(cin, input);
    istringstream iss(input);
    
    while (iss >> temp) {
        words.push_back(temp);
    }
    
    if (duplicates(words)) {
        cout << "no" << endl;
    }
    
    else {
        cout << "yes" << endl;
    }
    return 0;
}
    