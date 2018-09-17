#include "dictionary.h"
#include "fixionary.h"
#include "parser.h"

#include <iostream>

int main(int argc, char **argv)
{
  timlan::dictionary dict;
  dict.load_words("DB.dat");

  timlan::fixionary fix;
  fix.load_affixes("afixes.dat");

  if (argc == 1) {
    std::cout << dict << "\n" << fix << "\nPASS SENTENCE AS ARG\n";
    return 1;
  }

  timlan::parser p{std::move(fix), std::move(dict)};
  std::cout << p.parse(argv[1]) << "\n";
}
