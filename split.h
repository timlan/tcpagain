#pragma once

#include <string>
#include <vector>

namespace timlan {

std::vector<std::string> split(
    const std::string &input,
    const std::string &delimiter,
    int num = -1);

}
