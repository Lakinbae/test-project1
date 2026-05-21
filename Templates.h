#ifndef TEMPLATES_H
#define TEMPLATES_H

#include <vector>
#include <algorithm>
#include <functional>

using namespace std;

// We no longer need custom Repository, LinkedList, Stack, or Queue classes
// because we can use the built-in:
// std::map<string, T> (for Repository)
// std::list<T> (for LinkedList)
// std::stack<T> (for Stack)
// std::queue<T> (for Queue)

// We only keep specialized helper functions that make your main code cleaner:

// Simple wrapper for sorting
template<typename T>
void sortItems(vector<T>& arr, function<bool(const T&, const T&)> cmp) {
    sort(arr.begin(), arr.end(), cmp);
}

// Simple wrapper for searching
template<typename T>
int findItem(const vector<T>& arr, function<bool(const T&)> pred) {
    auto it = find_if(arr.begin(), arr.end(), pred);
    return (it != arr.end()) ? distance(arr.begin(), it) : -1;
}

#endif
