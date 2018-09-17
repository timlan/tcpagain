#include "split.h"

namespace timlan {

std::vector<std::string> split(
    const std::string &input,
    const std::string &delimiter,
    int num)
{
  std::string::size_type start = 0;
  std::string::size_type end;
  std::vector<std::string> result;

  while ((end = input.find(delimiter, start)) != std::string::npos) {
    result.emplace_back(input, start, end - start);
    start = end + delimiter.size();
    if (num >= 0 && result.size() >= static_cast<decltype(result.size())>(num))
      break;
  }

  if (num < 0 || result.size() < static_cast<decltype(result.size())>(num))
    result.emplace_back(input, start);

  return result;
}

}
