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

int main()
{
  initscr();
  noecho();
  keypad(stdscr, TRUE);
  scrollok(stdscr, TRUE);

  vector<string> all_targets = get_all_targets();
  for (const auto &c: all_targets) {
    println(c);
  }

  map<string, int> target_map;
  for (const auto &c: all_targets) {
    target_map.insert(pair<string, int>(c, 0));
  }
  
  vector<pair<string, int>> sorted_pairs;

  char input;
  string buffer = "";
  string search_buffer = "";
  bool is_input_mode = false;
  int x = 0;
  int y = 0;
  while (input = getch()) {
    if (input == '\n' && buffer == ":q") {
      return 0;
    }

    if (input == 27) {
      search_buffer = "";
      buffer = "";
      is_input_mode = false;
      println(buffer);
      continue;
    }

    buffer += input;

    if (is_input_mode) {
      search_buffer += input;
    }

    if (buffer == "i") {
      buffer = "";
      search_buffer = "";
      is_input_mode = true;
      continue;
    }

    if (!is_input_mode) {
      if (input == 'k') {
        y++;
        move(y, 0);
      }
    }


    sorted_pairs = {};

    for (const auto &[key, value]: target_map)
    {
      sorted_pairs.push_back(pair<string,int>(key, value));
    }

    sort(sorted_pairs.begin(), sorted_pairs.end(), [](auto &left, auto &right) {
      return left.second > right.second;
    });

    for (const auto &c: sorted_pairs)
    {
      println(c.first);
    }

    for (const auto &c: target_map) {
      int edit_distance = find_edit_distance(search_buffer, c.first, search_buffer.length(), c.first.length());
      target_map[c.first] = edit_distance;
    }

    println("sb: " + search_buffer);
    println("b: " + buffer);
    refresh();
  }
  return 0;
}
