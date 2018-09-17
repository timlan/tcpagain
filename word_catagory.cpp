#include "word_catagory.h"

namespace timlan {

word_catagory get_word_catagory(const std::string &catagory_str)
{
  if (catagory_str == "noun")
    return word_catagory::noun;

  if (catagory_str == "verb")
    return word_catagory::verb;

  return word_catagory::unknown;
}

std::ostream &operator<<(std::ostream &os, word_catagory cat)
{
  switch (cat) {
    case word_catagory::noun:
      os << "noun";
      break;
    case word_catagory::verb:
      os << "verb";
      break;
    default:
      os << "unknown";
      break;
  }

  return os;
}

}
