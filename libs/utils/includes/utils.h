#ifndef UTILS_H
#define UTILS_H

#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>

using namespace std;

namespace utils
{
    vector<string> splitCSVLine(const string &line);
}
#endif
