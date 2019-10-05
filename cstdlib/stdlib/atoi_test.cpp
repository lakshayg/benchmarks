#include <cassert>

#include "atoi.h"

void tdd_test() {
  assert(lg::atoi("") == 0);
  assert(lg::atoi(nullptr) == 0);

  assert(lg::atoi("0") == 0);
  assert(lg::atoi("1") == 1);
  assert(lg::atoi("2") == 2);

  assert(lg::atoi("10") == 10);
  assert(lg::atoi("23467814") == 23467814);

  assert(lg::atoi("c") == 0);
  assert(lg::atoi("1c") == 1);

  assert(lg::atoi("-1") == -1);
  assert(lg::atoi("+1") == 1);

  assert(lg::atoi(" 1") == 1);
  assert(lg::atoi("-2147483648") == -2147483648);
}

void test() {
  assert(lg::atoi("  -1") == -1);
  assert(lg::atoi("   -1   ") == -1);
  assert(lg::atoi("123x123") == 123);
  assert(lg::atoi("1345.3") == 1345);
  assert(lg::atoi("0034") == 34);
  assert(lg::atoi("2147483647") == 2147483647);
}

int main() {
  tdd_test();
  test();
}
