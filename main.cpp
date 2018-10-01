#include <string>
#include <iostream>
#include <filesystem>
#include <vector>
#include <map>
#include <ncurses.h>

namespace fs = std::filesystem;

std::vector<std::string> get_all_targets()
{
  std::string current_path = fs::current_path().string();
  std::vector<std::string> directories;
  std::vector<std::string> all_files;
  
  // Initialize to current path
  directories.push_back(current_path);

  int i = 0;
  while (i < directories.size())
  {
    current_path = directories.at(i);
    std::cout << directories.at(i) << "\n";
    for (const auto & p : fs::directory_iterator(current_path)){
      if (fs::is_directory(p)) {
        directories.push_back(p.path().string());
      }
      all_files.push_back(p.path().string());
    }

    i++;
  }

  return all_files;
}

int main()
{
  std::vector<std::string> all_targets = get_all_targets();
  for (const auto &c: all_targets)
    std::cout << c << '\n';
}
