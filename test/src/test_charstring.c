#include <charstring.h>
#include <unity.h>

void test_charstring_init(void) {
  String(69) str = {};
  TEST_ASSERT_EQUAL_UINT32(0, str.len);
}
