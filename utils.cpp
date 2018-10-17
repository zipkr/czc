#include <string>
#include <iostream>
#include <filesystem>
#include <vector>
#include <map>
#include <curses.h>
#include <bits/stdc++.h>

using namespace std;
namespace fs = filesystem;

void println(string out) {
  printw(out.c_str());
  printw("\n");
}

vector<string> get_all_targets()
{
  string current_path = fs::current_path().string();
  vector<string> directories;
  vector<string> all_files;
  
  // Initialize to current path
  directories.push_back(current_path);

  int i = 0;
  while (i < directories.size())
  {
    current_path = directories.at(i);
    for (const auto & p : fs::directory_iterator(current_path))
    {
      if (fs::is_directory(p))
      {
        directories.push_back(p.path().string());
      }
      all_files.push_back(p.path().string());
    }
    i++;
  }

  return all_files;
}

int min(int x, int y, int z) 
{ 
    return min(min(x, y), z); 
}

int find_edit_distance(string str1, string str2, int m, int n) 
{ 
    int dp[m+1][n+1]; 
    for (int i=0; i<=m; i++) 
    { 
        for (int j=0; j<=n; j++) 
        { 
            if (i==0) 
                dp[i][j] = j;
  
            else if (j==0) 
                dp[i][j] = i;
  
            else if (str1[i-1] == str2[j-1]) 
                dp[i][j] = dp[i-1][j-1]; 
  
            else
                dp[i][j] = 1 + min(dp[i][j-1], dp[i-1][j], dp[i-1][j-1]);
        } 
    } 
  
    return dp[m][n]; 
} 

