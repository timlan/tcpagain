#pragma once

#include <exception>
#include <string>
#include <vector>

#include "dictionary.h"
#include "fixionary.h"
#include "vos_node.h"
#include "word_node.h"

namespace timlan {

class parser {
public:
  parser(fixionary fix, dictionary dict);

  std::vector<vos_node> parse(const std::string &input);

private:
  fixionary fix_;
  dictionary dict_;

  std::vector<std::string> tokenise(const std::string &input);

  template <typename iterator>
  vos_node parse_tokens(iterator &begin, const iterator &end);

  word_node parse_word(std::string word_str);
};

class parse_error : public std::exception {
public:
  parse_error(const std::string& what);

  std::string what_;

  const char *what() const noexcept override;
};

template <typename iterator>
vos_node parser::parse_tokens(iterator &begin, const iterator &end)
{
  if (begin == end)
    throw parse_error{"Too many verbs!"};

  std::unique_ptr<word_node> word, prev_word;
  do {
    word = std::make_unique<word_node>(parse_word(*begin++));
    if (prev_word) {
      word->supplement_ = std::move(prev_word);
    }
    prev_word = std::move(word);
  }
  while (prev_word->is_supplement_ && begin != end);

  if (begin == end && prev_word->is_supplement_)
    throw parse_error{"Spurious supplement"};

  // OK, after that minor chaos, we now have prev_word containing a
  // non-supplement which now owns its supplement (if any). Now we should
  // figure out if our current word is a verboid or not.

  vos_node node;
  node.word_node_ = std::move(*prev_word);
  if (prev_word->is_verboid_) {
    node.object_ = std::make_unique<vos_node>(parse_tokens(begin, end));
    node.subject_ = std::make_unique<vos_node>(parse_tokens(begin, end));
  }

  return node;
}

}
