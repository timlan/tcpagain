#pragma once
#include <istream>
#include <memory>
#include <ostream>
#include <string>
#include <vector>

namespace timlan {

struct vos_node;

enum class syntax_type {
  none,
  verboid,
  supplement
};

struct affix {
  std::string timlan_;
  bool prefix_;
  std::string english_;
  std::string shorthand_;
  std::string defines_type_;
  syntax_type syntax_type_;
  std::string short_for_str_;
    // used temporarily, since properly parsing would require an otherwise
    // fully loaded fixionary
  std::unique_ptr<vos_node> short_for_;
  std::string description_;
  std::vector<unsigned int> blog_ids_;
  bool removed_;

  affix(const std::string &affix_str);
  affix() = default;

  ~affix(); // required because of the incomplete type of vos_node

  // now because of that we need to specify default copy/assignment/etc., sigh

  affix(const affix &) = delete;
  affix(affix &&) = default;
  affix &operator=(const affix &) = delete;
  affix &operator=(affix &&) = default;

  friend std::istream &operator>>(std::istream &is, affix &a);
  friend std::ostream &operator<<(std::ostream &os, const affix &a);

};

syntax_type get_syntax_type(const std::string &syntax_type_str);

std::ostream &operator<<(std::ostream &os, syntax_type type);

class affix_format_exception : public std::exception { };

}
