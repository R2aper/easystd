#include <libestd/eerror.h>
#include <libestd/estring.h>

#include <check.h>
#include <stdio.h>

START_TEST(test_bad_char_table) {
  ck_assert_ptr_eq(bad_char_table(NULL), NULL);

  int *table = bad_char_table("ABA");
  ck_assert_int_eq(table['A'], 2);
  ck_assert_int_eq(table['B'], 1);

  free(table);
}
END_TEST

START_TEST(test_boyer_moore) { ck_assert_int_eq(boyer_moore_search("ABCDE", "CD"), 2); }
END_TEST

START_TEST(test_string_init) {
  string *str1 = string_init_emtpy();
  ck_assert_str_eq(string_cstr(str1), "");

  ck_assert_ptr_eq(string_from_cstr(NULL), NULL);

  string *str2 = string_from_cstr("Hello world");
  ck_assert_str_eq(string_cstr(str2), "Hello world");

  string *str3 = string_create(""), *str4 = string_create("Hello world");
  ck_assert_str_eq(string_cstr(str3), "");
  ck_assert_str_eq(string_cstr(str4), "Hello world");

  string_free(str1);
  string_free(str2);
  string_free(str3);
  string_free(str4);
}
END_TEST

START_TEST(test_string_reserve) {
  string *str = string_create("Hello world");

  ck_assert_int_eq(OK, string_reserve(str, str->capacity - 1));
  ck_assert_int_eq(OK, string_reserve(str, str->capacity + 1));

  string_free(str);
}
END_TEST

START_TEST(test_string_append) {
  ck_assert_int_eq(NULL_POINTER, string_append(NULL, "Hello world"));

  string *str = string_create("Foo");
  ck_assert_int_eq(INVALID_ARGUMENT, string_append(str, NULL));

  string_append(str, "Foo2");
  ck_assert_str_eq(string_cstr(str), "FooFoo2");

  string_free(str);
}
END_TEST

START_TEST(test_string_at) {
  ck_assert_int_eq((int)string_at(NULL, 0, NULL), (int)'\0');
  easy_error err;
  string_at(NULL, 0, &err);
  ck_assert_int_eq(err, NULL_POINTER);

  string *str = string_create("Foo");
  string_at(str, str->capacity, &err);
  ck_assert_int_eq(err, INVALID_INDEX);

  ck_assert_int_eq((int)string_at(str, 1, &err), (int)'o');
  ck_assert_int_eq(err, OK);

  string_free(str);
}
END_TEST

START_TEST(test_string_insert) {
  ck_assert_int_eq(string_insert(NULL, 0, NULL), NULL_POINTER);
  string *str = string_create("Foo");

  ck_assert_int_eq(string_insert(str, 0, NULL), INVALID_ARGUMENT);

  ck_assert_int_eq(string_insert(str, str->length + 1, "Foo2"), INVALID_INDEX);

  ck_assert_int_eq(string_insert(str, 0, "Foo2"), OK);
  ck_assert_str_eq(string_cstr(str), "Foo2Foo");

  string_free(str);
}
END_TEST

START_TEST(test_string_compare) {
  ck_assert_int_eq(string_compare(NULL, NULL, NULL), 0);

  easy_error err;
  ck_assert_int_eq(string_compare(NULL, NULL, &err), 0);
  ck_assert_int_eq(err, NULL_POINTER);

  string *str1 = string_create("Foo"), *str2 = string_create("Foo"), *str3 = string_create("Foo2");

  ck_assert_int_eq(string_compare(str1, str2, &err), 1);
  ck_assert_int_eq(string_compare(str1, str3, &err), 0);
  ck_assert_int_eq(err, OK);

  string_free(str1);
  string_free(str2);
  string_free(str3);
}
END_TEST

START_TEST(test_string_clear) {
  ck_assert_int_eq(NULL_POINTER, string_clear(NULL));

  string *str = string_create("foo");
  ck_assert_int_eq(string_clear(str), OK);
  ck_assert_str_eq(string_cstr(str), "");

  string_free(str);
}
END_TEST

START_TEST(test_string_shrink_to_fit) {
  string *str = string_create("");
  string_append(str, "Hello world");
  string_shrink_to_fit(str);

  ck_assert_int_eq(str->length + 1, str->capacity);

  string_free(str);
}
END_TEST

Suite *string_suit() {
  Suite *s = suite_create("Easy string");
  TCase *tc_boyer_moore = tcase_create("Boyer Moore search algorithm"),
        *tc_string_init = tcase_create("Initialitation"),
        *tc_string_append = tcase_create("Append"), *tc_string_reserve = tcase_create("Reserve"),
        *tc_string_clear = tcase_create("Clear"),
        *tc_string_shrink_to_fit = tcase_create("Shrink to fit"),
        *tc_string_at = tcase_create("At index"), *tc_string_insert = tcase_create("Insert"),
        *tc_string_compare = tcase_create("Compare");

  tcase_add_test(tc_boyer_moore, test_bad_char_table);
  tcase_add_test(tc_boyer_moore, test_boyer_moore);
  tcase_add_test(tc_string_init, test_string_init);
  tcase_add_test(tc_string_append, test_string_append);
  tcase_add_test(tc_string_reserve, test_string_reserve);
  tcase_add_test(tc_string_at, test_string_at);
  tcase_add_test(tc_string_insert, test_string_insert);
  tcase_add_test(tc_string_clear, test_string_clear);
  tcase_add_test(tc_string_shrink_to_fit, test_string_shrink_to_fit);
  tcase_add_test(tc_string_compare, test_string_compare);

  suite_add_tcase(s, tc_boyer_moore);
  suite_add_tcase(s, tc_string_init);
  suite_add_tcase(s, tc_string_append);
  suite_add_tcase(s, tc_string_reserve);
  suite_add_tcase(s, tc_string_at);
  suite_add_tcase(s, tc_string_insert);
  suite_add_tcase(s, tc_string_clear);
  suite_add_tcase(s, tc_string_shrink_to_fit);
  suite_add_tcase(s, tc_string_compare);

  return s;
}
