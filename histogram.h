#ifndef HISTOGRAM_H_INCLUDED
#define HISTOGRAM_H_INCLUDED
#include <vector>

using namespace std;

void find_minmax(const vector<double>& numbers, double& min, double& max);

vector <size_t> procent (size_t number_count, const vector <size_t> bins);

#endif // HISTOGRAM_H_INCLUDED
