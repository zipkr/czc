#include <vector>
#include <string>

using namespace std;

#ifndef UTILS_H
#define UTILS_H

vector<string> get_all_targets();
void println(string out);
int min(int x, int y, int z);
int find_edit_distance(string str1, string str2, int m, int n);

#endif
