#include "test_array.h"
#include "test_estring.h"
#include "test_grow.h"

#include <check.h>

int main() {
  int number_failed = 0;
  SRunner *sr = srunner_create(NULL);

  srunner_add_suite(sr, string_suit());
  srunner_add_suite(sr, array_suite());
  srunner_add_suite(sr, grow_suite());
  srunner_run_all(sr, CK_NORMAL);

  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);

  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}

