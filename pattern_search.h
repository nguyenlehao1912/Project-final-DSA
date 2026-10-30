#ifndef PATTERN_SEARCH_H
#define PATTERN_SEARCH_H

#include <vector>
#include <string>

// Khai báo các hàm tìm kiếm từ pattern_search.cpp
std::vector<int> BinarySearch(const std::string& text, const std::string& pattern, const std::vector<int>& suffixArr);
std::vector<int> naiveSearch(const std::string& text, const std::string& pattern);

#endif