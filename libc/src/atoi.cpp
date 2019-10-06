#include "libc/ctype.h"
#include "libc/stdlib.h"

namespace lg {

int atoi(const char* str) {
  if (str == nullptr) {
    return 0;
  }

  // skip all space
  while (isspace(*str))
    ++str;

  // deal with signs at the beginning
  bool negative = str[0] == '-';
  bool positive = str[0] == '+';
  if (negative || positive)
    ++str;

  // construct the number
  int n = 0;
  for (int i = 0; isnum(str[i]); ++i) {
    n = 10 * n + (negative ? -1 : 1) * (str[i] - '0');
  }
  return n;
}

} // namespace lg
