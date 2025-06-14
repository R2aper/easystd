#include <check.h>
#include <estd/array.h>
#include <estd/eerror.h>
#include <estd/global.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "test_array.h"

bool is_sort_array(array *arr) {
  for (size_t i = 0; i < arr->size - 1; i++) {
    if (array_get_as(int, arr, i, NULL) > array_get_as(int, arr, i + 1, NULL))
      return false;
  }

  return true;
}

void fill_rn_array(array *arr) {
  srand(time(0));
  for (size_t i = 0; i < arr->size; i++) {
    int *value = (int *)malloc(sizeof(int));
    *value = rand() % 100;
    array_set(arr, i, value);
  }
}

// All tests:
START_TEST(test_array_init) {
  array *arr = array_init(2);

  // should be NULL
  ck_assert_ptr_null(arr->data[0]);
  ck_assert_ptr_null(arr->data[1]);

  ck_assert_int_eq(arr->size, 2);

  array_free(arr, free);
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

  array_free(arr, NULL);
}
END_TEST

START_TEST(test_array_get) {
  array *arr = array_init(2);
  int a = 1, b = 2;
  easy_error err;

  ck_assert_ptr_null(array_get(NULL, 0, NULL));
  array_get(arr, 5, &err); // out of range
  ck_assert_int_eq(INVALID_INDEX, err);

  array_set(arr, 0, &a);
  array_set(arr, 1, &b);

  ck_assert_int_eq(array_get_as(int, arr, 0, &err), a);
  ck_assert_int_eq(array_get_as(int, arr, 1, &err), b);

  array_free(arr, NULL);
}
END_TEST

START_TEST(test_array_qsort) {
  array *arr = array_init(10);
  fill_rn_array(arr);

  ck_assert_int_eq(NULL_POINTER, array_qsort(NULL, NULL));
  ck_assert_int_eq(INVALID_ARGUMENT, array_qsort(arr, NULL));

  array_qsort(arr, int_compare);
  ck_assert_int_eq(is_sort_array(arr), true);

  array_free(arr, NULL);
}
END_TEST

Suite *array_suite() {
  Suite *s = suite_create("Array");
  TCase *tc_array_init = tcase_create("Initialization"),
        *tc_array_set = tcase_create("Setting value"),
        *tc_array_get = tcase_create("Getting value"), *tc_array_qsort = tcase_create("Sorting");

  tcase_add_test(tc_array_init, test_array_init);
  tcase_add_test(tc_array_set, test_array_set);
  tcase_add_test(tc_array_get, test_array_get);
  tcase_add_test(tc_array_qsort, test_array_qsort);

  suite_add_tcase(s, tc_array_init);
  suite_add_tcase(s, tc_array_set);
  suite_add_tcase(s, tc_array_get);
  suite_add_tcase(s, tc_array_qsort);

  return s;
}

