#include <utils.h>

using namespace std;


namespace utils
{
    vector<string> splitCSVLine(const string &line)
    {
        vector<string> result;
        stringstream ss(line);
        string cell;
        while (getline(ss, cell, ','))
        {
            // trim spaces
            cell.erase(cell.find_last_not_of(" \n\r\t") + 1);
            cell.erase(0, cell.find_first_not_of(" \n\r\t"));
            result.push_back(cell);
        }
        return result;
    }
}