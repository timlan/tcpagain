#pragma once
#include <memory>
#include <ostream>

#include "word_node.h"

namespace timlan {

struct vos_node {
  word_node word_node_;

  std::unique_ptr<vos_node> object_;
  std::unique_ptr<vos_node> subject_;
};

std::ostream &operator<<(std::ostream &os, const vos_node &v_n);

std::ostream &operator<<(std::ostream &os, const std::vector<vos_node> &nodes);

}
