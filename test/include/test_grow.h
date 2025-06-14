#ifndef TEST_GROW_H
#define TEST_GROW_H

#include "estd/eerror.h"
#include <check.h>
#include <estd/grow.h>

#include "test_array.h"

void fill_rn_grow(grow *gr, size_t size);
bool is_sort_grow(grow *gr);

Suite *grow_suite();

#endif // TEST_GROW_H

