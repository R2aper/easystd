#ifndef ESTRING_H
#define ESTRING_H

#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#include "estd/eerror.h"

/**
 * @brief Create bad char table for boyer moore search algorithm
 * @note Table should be freed after using
 * @note If F is NULL then fn return NULL
 *
 * @param F Cstring
 * @return bad char table
 */
int *bad_char_table(const char *F);

/**
 * @brief Implementation of boyer moore search algorithm
 * @note If F is not in T, then fn return -1
 *
 * @param T Cstring
 * @param F subCstring
 * @return Positon or easy_error code
 */
int boyer_moore_search(const char *T, const char *F);

/**
 * @def IS_EMPTY(string)
 * @brief Checks if string is empty
 * @warning Make sure string object is not NULL
 */
#define IS_EMPTY(string) ((string)->length == 0)

/// string is struct for easier usage of strings type
typedef struct string {
  char *data;
  size_t length;   // Size of string
  size_t capacity; // Size of allocate memory
} string;

/// @defgroup String Functions relative to string type
/// @{

/**
 * @brief Create empty string
 * @note str should be freed after using
 *
 * @return Initialized string object
 */
string *string_init_empty(void);

/**
 * @brief Create string from Cstring
 * @note str should be freed after using
 *
 * @param cstr Cstring
 * @return Initialized string object
 */
string *string_from_cstr(const char *cstr);

/**
 * @brief Create string. If cstr is empty, return empty string
 * @note str should be freed after using
 * @note use this function if you sure cstr is not NULL
 *
 * @param cstr Pointer to Cstring
 * @return Initialized string object
 */
string *string_create(const char *cstr);

/// @brief Freed string object
void string_free(string *str);

/// @brief Same as string_free, just with void* argument
void string_free_abs(void *str);

/**
 * @brief Changes the size of the buffer
 * @note If (new_capacity <= str->capacity) then will return OK;
 *
 * @param str Pointer to string object
 * @param new_capacity Size of new buffer
 * @return 0 on success or easy_error
 */
easy_error string_reserve(string *str, size_t new_capacity);

/**
 * @brief Add Cstring to end of str
 *
 * @param str Pointer to string object
 * @param cstr Cstring
 * @return 0 on success or easy_error
 */
easy_error string_append(string *str, const char *cstr);

/**
 * @brief Get char by index
 *
 * @param str Pointer to string object
 * @param index Index of char
 * @param err Pointer to easy_error object. Pass NULL if you sure in other parameters
 * @return Char by index or '\0'
 */
char string_at(string *str, size_t index, easy_error *err);

/// @brief string as Cstring or NULL if str is bad
const char *string_cstr(const string *str);

/**
 * @brief Find fragment in string and return positon of it
 * @note Use boyer moore algorithm for finding positon
 *
 * @param str Pointer to string object
 * @param fragment Fragment to find in str
 * @return Position of fragment or -1
 */
int string_find(string *str, const char *fragment);

/**
 * @brief Compare two string
 *
 * @param str1,str2 Pointers to string objects
 * @param err Pointer to easy_error object. Pass NULL if you sure in other parameters
 * @return result of comparing. If one of string is NULL return false
 */
bool string_compare(string *str1, string *str2, easy_error *err);

/**
 * @brief Insert Cstring to given positon
 *
 * @param str Pointer to string object
 * @param pos Position to insert
 * @param cstr Cstring
 * @return 0 on success or easy_error
 */
easy_error string_insert(string *str, size_t pos, const char *cstr);

/**
 * @brief Erases all chars from the string
 *
 * @param str Pointer to string object
 * @return 0 on success or easy_error
 */
easy_error string_clear(string *str);

/**
 * @brief Reduce str->capacity to str->length
 *
 * @param str Pointer to string object
 * @return 0 on success or easy_error
 */
easy_error string_shrink_to_fit(string *str);

///@}

#endif // ESTRING_H
