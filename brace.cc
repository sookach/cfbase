#include <algorithm>
#include <execution>
#include <fstream>
#include <iostream>
#include <ranges>
#include <string>

int main(int argc, char **argv) {
  if (argc != 2) {
    std::cout << "usage: brace <filename>\n";
    exit(EXIT_FAILURE);
  }

  std::fstream f{argv[1]};

  for (std::string s{}; std::getline(f, s);) {
    std::ranges::transform(s, begin(s), [](auto &&x) -> char {
      switch (x) {
      default:
        return x;
      case '[':
        return '{';
      case ']':
        return '}';
      }
    });
    std::cout << s << std::endl;
  }
}