#include <string>
#include <iostream>
#include <filesystem>
#include <vector>
#include <map>
#include <curses.h>
#include <bits/stdc++.h>
#include "utils.h"

using namespace std;
namespace fs = filesystem;

string EXIT_BUFFER = ":q";
int ESC_KEY = 27;

vector<pair<string, int>> recompute_targets(string search_buffer, map<string, int> target_map)
{
  vector<pair<string, int>> sorted_pairs;

  // assign edit distances
  for (const auto &c: target_map)
  {
    int edit_distance = find_edit_distance(search_buffer, c.first, search_buffer.length(), c.first.length());
    target_map[c.first] = edit_distance;
  }

  // add elements to list
  for (const auto &[key, value]: target_map)
  {
    sorted_pairs.push_back(pair<string,int>(key, value));
  }

  // sort the array
  sort(sorted_pairs.begin(), sorted_pairs.end(), [](auto &left, auto &right) {
    return left.second > right.second;
  });

  return sorted_pairs; 
}

int main()
{
  initscr();
  noecho();
  keypad(stdscr, TRUE);
  scrollok(stdscr, TRUE);

  // get all targets, and insert into ordering map
  vector<string> all_targets = get_all_targets();
  map<string, int> target_map;
  for (const auto &c: all_targets) {
    target_map.insert(pair<string, int>(c, 0));
  }

  // initialize main loop variables
  bool is_input_mode = false;
  string buffer = "";
  string search_buffer = "";
  vector<pair<string, int>> sorted_pairs = recompute_targets(search_buffer, target_map);
  int y = sorted_pairs.size() - 1;

  // print first screen
  for (const auto &c: sorted_pairs)
  {
    println(c.first);
  }

  char input;
  while (input = getch()) {
    // if input == enter and buffer is exit_buffer exit program
    if (input == '\n' && buffer == EXIT_BUFFER) {
      return 0;
    }

    if (input == ESC_KEY) {
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

    if (!is_input_mode)
    {
      if (input == 'k')
      {
        if (y > 0)
        {
          y--;
        }
      } 
      else if (input == 'j')
      {
        if (y < sorted_pairs.size() - 1)
        {
          y++;
        }
      }
      else if (input == '\n')
      {
        string vim_cmd = "$EDITOR ";
        string cmd = vim_cmd + sorted_pairs.at(y).first;
        system(cmd.c_str());
        return 0;
      }
    }

    sorted_pairs = recompute_targets(search_buffer, target_map);
    int i = 0;
    for (const auto &c: sorted_pairs)
    {
      if (i == y) {
        println(c.first + "<<<<< targeted");
      } else {
        println(c.first);
      }
      i++;
    }
    println("sb: " + search_buffer);
    println("b: " + buffer);
    refresh();
  }
  return 0;
}
