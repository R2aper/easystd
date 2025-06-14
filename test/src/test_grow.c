#include <check.h>
#include <estd/global.h>
#include <estd/grow.h>
#include <stdbool.h>
#include <time.h>

#include "test_grow.h"

void fill_rn_grow(grow *gr, size_t size) {
  srand(time(0));
  for (size_t i = 0; i < size; i++) {
    int *tmp = (int *)malloc(sizeof(int));
    *tmp = rand() % 100;
    grow_push(gr, tmp);
  }
}

bool is_sort_grow(grow *gr) {
  for (size_t i = 0; i < gr->size - 1; i++) {
    if (grow_get_as(int, gr, i, NULL) > grow_get_as(int, gr, i + 1, NULL))
      return false;
  }

  return true;
}

// Tests:
START_TEST(test_grow_init) {
  grow *gr = grow_init(2);

  // should be NULL
  ck_assert_ptr_null(gr->data[0]);
  ck_assert_ptr_null(gr->data[1]);

  ck_assert_int_eq(gr->size, 0);
  ck_assert_int_eq(gr->capacity, 2);

  grow_free(gr, NULL);
}
END_TEST

START_TEST(test_grow_qsort) {
  grow *gr = grow_init(15);
  fill_rn_grow(gr, 10);

  grow_qsort(gr, int_compare);
  ck_assert_int_eq(true, is_sort_grow(gr));

  grow_free(gr, free);
}
END_TEST

START_TEST(test_grow_push) {
  grow *gr = grow_init(2);
  int a = 5;

  ck_assert_int_eq(NULL_POINTER, grow_push(NULL, NULL));
  ck_assert_int_eq(INVALID_ARGUMENT, grow_push(gr, NULL));

  ck_assert_int_eq(OK, grow_push(gr, &a));
  ck_assert_int_eq(a, *(int *)gr->data[0]);

  a = 10;
  ck_assert_int_eq(OK, grow_push(gr, &a));
  ck_assert_int_eq(a, *(int *)gr->data[1]);

  grow_free(gr, NULL);
}
END_TEST

START_TEST(test_grow_set) {
  grow *gr = grow_init(2);
  int a = 5, b = 10;

  ck_assert_int_eq(NULL_POINTER, grow_set(NULL, 0, NULL));
  ck_assert_int_eq(INVALID_INDEX, grow_set(gr, 0, &a));

  grow_push(gr, &a);
  ck_assert_int_eq(INVALID_ARGUMENT, grow_set(gr, 0, NULL));

  grow_set(gr, 0, &b);
  ck_assert_int_eq(b, *(int *)gr->data[0]);

  grow_free(gr, NULL);
}
END_TEST

Suite *grow_suite() {
  Suite *s = suite_create("Grow");
  TCase *tc_grow_init = tcase_create("Initialization"), *tc_grow_push = tcase_create("Push"),
        *tc_grow_set = tcase_create("Setting"), *tc_grow_qsort = tcase_create("Qsort");

  tcase_add_test(tc_grow_init, test_grow_init);
  tcase_add_test(tc_grow_push, test_grow_push);
  tcase_add_test(tc_grow_set, test_grow_set);
  tcase_add_test(tc_grow_qsort, test_grow_qsort);

  suite_add_tcase(s, tc_grow_init);
  suite_add_tcase(s, tc_grow_push);
  suite_add_tcase(s, tc_grow_set);
  suite_add_tcase(s, tc_grow_qsort);

  return s;
}

