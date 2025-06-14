#ifndef TEST_ARRAY_H
#define TEST_ARRAY_H

#include <check.h>
#include <estd/array.h>
#include <estd/eerror.h>
#include <estd/global.h>
#include <stdbool.h>

bool is_sort_array(array *arr);
void fill_rn_array(array *arr);

Suite *array_suite();

#endif // TEST_ARRAY_H

