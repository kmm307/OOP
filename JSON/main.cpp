
#include "json.hpp"

#include <iterator>
#include <iostream>
#include <string>

int
main(int argc, char* argv[])
{
  std::istreambuf_iterator<char> first(std::cin);
  std::istreambuf_iterator<char> last;
  std::string s(first, last);

  json::Value* val = json::parse(s);

  std::cout << *val << '\n';
}
