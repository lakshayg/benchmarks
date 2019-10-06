#include "libc/ctype.h"

namespace lg {

bool isnum(char c) {
  return c >= '0' && c <= '9';
}

bool isspace(char c) {
  return c == ' ';
}

} // namespace lg
