#include "word.h"

#include <ios>
#include <iterator>
#include <sstream>
#include <vector>

#include "split.h"

namespace timlan {

word::word(const std::string &word_str)
{
  std::istringstream iss{word_str};

  iss >> *this;

  if (iss.fail())
    throw word_format_exception{};
}

word::word(
    const std::string &english,
    const std::string &timlan,
    const std::string &description,
    word_catagory catagory,
    const std::string &definition,
    const std::string &syntax,
    bool is_real)
  : english_{english},
    timlan_{timlan},
    description_{description},
    catagory_{catagory},
    definition_{definition},
    syntax_{syntax},
    is_real_{is_real}
{
}

std::istream &operator>>(std::istream &is, word &w)
{
  std::string word_str{
      std::istreambuf_iterator<char>{is},
      std::istreambuf_iterator<char>{}};

  std::string::size_type equals = word_str.find(" = ");
  std::string::size_type equals_r = equals + 3;
  if (equals == std::string::npos)
  {
    is.setstate(std::ios::failbit);
    return is;
  }

  std::string timlan{word_str, 0, equals};

  std::string::size_type left_bracket = word_str.find(" (", equals_r);
  std::string::size_type left_bracket_r = left_bracket + 2;
  if (left_bracket == std::string::npos)
  {
    is.setstate(std::ios::failbit);
    return is;
  }

  std::string english{word_str, equals_r, left_bracket - equals_r};

  std::string::size_type right_bracket = word_str.find(") : ");
  std::string::size_type right_bracket_r = right_bracket + 4;
  if (right_bracket == std::string::npos)
  {
    is.setstate(std::ios::failbit);
    return is;
  }

  std::string catagory{
      word_str,
      left_bracket_r,
      right_bracket - left_bracket_r};

  std::vector<std::string> remainder = split(
      {word_str, right_bracket_r},
      " | ");
  if (remainder.size() != 3)
  {
    is.setstate(std::ios::failbit);
    return is;
  }

  word_catagory catagory_e = get_word_catagory(catagory);

  w = {english, timlan, remainder[0], catagory_e, remainder[1], remainder[2]};

  return is;
}

std::ostream &operator<<(std::ostream &os, const word &w)
{
  os << "T " << w.timlan_ << " | E " << w.english_
     << " | C " << w.catagory_ << " | D " << w.description_
     << " | De " << w.definition_ << " | S " << w.syntax_ << " | END";

  return os;
}

}
