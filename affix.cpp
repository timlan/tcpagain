#include "affix.h"

#include <algorithm>
#include <ios>
#include <iterator>
#include <sstream>
#include <utility>

#include "split.h"
#include "vos_node.h"

namespace timlan {

affix::affix(const std::string &affix_str)
{
  std::istringstream iss{affix_str};

  iss >> *this;

  if (iss.fail())
    throw affix_format_exception{};
}

affix::~affix()
{
}

std::istream &operator>>(std::istream &is, affix &a)
{
  std::string affix_str{
      std::istreambuf_iterator<char>{is},
      std::istreambuf_iterator<char>{}};

  std::vector<std::string> affix_portions{split(affix_str, " | ")};

  if (affix_portions.size() != 10) {
    is.setstate(std::ios::failbit);
    return is;
  }

  affix new_affix;

  new_affix.timlan_ = std::move(affix_portions[0]);
  new_affix.prefix_ = std::stoi(affix_portions[1]);
  new_affix.english_ = std::move(affix_portions[2]);
  new_affix.shorthand_ = std::move(affix_portions[3]);
  new_affix.defines_type_ = std::move(affix_portions[4]);
  new_affix.syntax_type_ = get_syntax_type(affix_portions[8]);
  new_affix.short_for_str_ = std::move(affix_portions[5]);
  new_affix.description_ = std::move(affix_portions[9]);

  auto blog_ids_str = split(std::move(affix_portions[6]), ",");
  blog_ids_str.erase(
      std::remove(blog_ids_str.begin(), blog_ids_str.end(), ""),
      blog_ids_str.end());
  std::transform(
      blog_ids_str.begin(),
      blog_ids_str.end(),
      std::back_inserter(new_affix.blog_ids_),
      [] (const std::string &id) { return std::stoi(id); });

  new_affix.removed_ = std::stoi(affix_portions[7]);

  a = std::move(new_affix);

  return is;
}

std::ostream &operator<<(std::ostream &os, const affix &a)
{
  os << "T " << a.timlan_ << " | P " << a.prefix_ << " | E " << a.english_
     << " | S " << a.shorthand_ << " | D " << a.defines_type_
     << " | Sy " << a.syntax_type_ << " | Sh " << a.short_for_str_
     << " | De " << a.description_ << " | B ";

  for (auto blog_id : a.blog_ids_) {
    os << blog_id << "/";
  }

  os << " | R " << a.removed_;

  return os;
}

syntax_type get_syntax_type(const std::string &syntax_type_str)
{
  if (syntax_type_str == "supplement")
    return syntax_type::supplement;
  if (syntax_type_str == "verboid")
    return syntax_type::verboid;
  return syntax_type::none;
}

std::ostream &operator<<(std::ostream &os, syntax_type type)
{
  switch (type) {
    case syntax_type::supplement:
      os << "supplement";
      break;
    case syntax_type::verboid:
      os << "verboid";
      break;
    default:
      os << "none";
      break;
  }

  return os;
}

}
