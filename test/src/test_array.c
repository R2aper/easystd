#include <libestd/array.h>
#include <libestd/eerror.h>

#include <check.h>

#define array_get_(type, arr, index, err) (*(type *)array_get((arr), (index), (err)))

START_TEST(test_array_init) {
  array *arr = array_init(2);

  // should be NULL
  ck_assert_ptr_null(arr->data[0]);
  ck_assert_ptr_null(arr->data[1]);

  ck_assert_int_eq(arr->size, 2);

  array_free(arr);
}
END_TEST

START_TEST(test_array_set) {
  array *arr = array_init(2);
  int a = 5;

  // Incorrect use of fn
  ck_assert_int_eq(NULL_POINTER, array_set(NULL, 0, NULL));
  ck_assert_int_eq(INVALID_ARGUMENT, array_set(arr, 0, NULL));
  ck_assert_int_eq(INVALID_INDEX, array_set(arr, 5, &a));

  // Correct use
  ck_assert_int_eq(OK, array_set(arr, 0, &a));
  ck_assert_int_eq(5, *(int *)arr->data[0]);

  array_free(arr);
}
END_TEST

START_TEST(test_array_get) {
  array *arr = array_init(2);
  int a = 1, b = 2;
  easy_error err;

  ck_assert_ptr_null(array_get(NULL, 0, NULL));
  array_get(arr, 5, &err); // out of range
  ck_assert_int_eq(INVALID_INDEX, err);

  array_set_as(int *, arr, 0, &a);
  array_set_as(int *, arr, 1, &b);

  ck_assert_int_eq(array_get_(int, arr, 0, &err), a);
  ck_assert_int_eq(array_get_(int, arr, 1, &err), b);

  array_free(arr);
}
END_TEST

Suite *array_suite() {
  Suite *s = suite_create("Array");
  TCase *tc_array_init = tcase_create("Initialization"),
        *tc_array_set = tcase_create("Setting value"),
        *tc_array_get = tcase_create("Getting value");

  tcase_add_test(tc_array_init, test_array_init);
  tcase_add_test(tc_array_set, test_array_set);
  tcase_add_test(tc_array_get, test_array_get);

  suite_add_tcase(s, tc_array_init);
  suite_add_tcase(s, tc_array_set);
  suite_add_tcase(s, tc_array_get);

  return s;
}
