#include "parser.h"

#include <optional>
#include <utility>

#include "affix.h"
#include "split.h"
#include "word.h"
#include "word_catagory.h"

namespace timlan {

parser::parser(fixionary fix, dictionary dict)
  : fix_{std::move(fix)},
    dict_{std::move(dict)}
{
}

std::vector<vos_node> parser::parse(const std::string &input)
{
  auto tokens = tokenise(input);

  auto begin_it = tokens.cbegin();

  std::vector<vos_node> sentences;

  while (begin_it != tokens.cend())
    sentences.emplace_back(parse_tokens(begin_it, tokens.cend()));
  return sentences;
}

std::vector<std::string> parser::tokenise(const std::string &input)
{
  // TODO make this handle more than just words
  return split(input, " ");
}

word_node parser::parse_word(std::string word_str)
{
  word_node result;

  while (auto a = fix_.find_prefix(word_str)) {
    const affix &ref_a = *a;
    word_str = word_str.substr(ref_a.timlan_.size());
    if (ref_a.syntax_type_ == syntax_type::supplement)
      result.is_supplement_ = true;
    if (ref_a.syntax_type_ == syntax_type::verboid)
      result.is_verboid_ = true;
    result.prefixes_.emplace_back(ref_a);
  }

  while (auto a = fix_.find_suffix(word_str)) {
    const affix &ref_a = *a;
    word_str = word_str.substr(0, word_str.size() - ref_a.timlan_.size());
    if (ref_a.syntax_type_ == syntax_type::supplement)
      result.is_supplement_ = true;
    if (ref_a.syntax_type_ == syntax_type::verboid)
      result.is_verboid_ = true;
    result.suffixes_.emplace_back(ref_a);
  }

  auto maybe_word = dict_.find_word(word_str);

  if (maybe_word) {
    result.word_ = *maybe_word;
  }
  else {
    result.word_ = {
        word_str,
        word_str,
        "Not found",
        word_catagory::unknown,
        "Not found",
        "Not found",
        false};
  }

  return result;
}

parse_error::parse_error(const std::string &what)
  : what_{what}
{
}

const char *parse_error::what() const noexcept
{
  return what_.c_str();
}

}
