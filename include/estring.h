#ifndef ESTRING_H
#define ESTRING_H

#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>

#include "eerror.h"

/// string is struct for easier usage of strings type
typedef struct string {
  char *data;
  size_t length;   // Size of string
  size_t capacity; // Size of allocate memory
} string;

/// @defgroup String Functions relative to string type
/// @{

/**
 * @brief Create emtpy string
 * @note str should be freed after using
 *
 * @param str Pointer to string object
 * @return 0 on success or easy_error
 */
easy_error string_init_emtpy(string *str);

/**
 * @brief Create string from Cstring
 * @note str should be freed after using
 *
 * @param str Pointer to string object
 * @param cstr Cstring
 * @return 0 on success or easy_error
 */
easy_error string_from_cstr(string *str, const char *cstr);

/**
 * @brief Create string. If cstr is empty, return emtpy string
 * @note str should be freed after using
 * @note use this function if you sure cstr is not NULL
 *
 * @param cstr Pointer to Cstring
 * @return String object
 */
string string_create(const char *cstr);

/// @brief Freed string object
void string_free(string *str);

/// @brief Same as string_free, just with void* argument
void string_free_abs(void *str);

/**
 * @brief Changes the size of the buffer
 *
 * @note if (new_capacity <= str->capacity) then will return OK;
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

///@}

#endif // ESTRING_H
