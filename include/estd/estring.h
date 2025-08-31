#ifndef ESTRING_H
#define ESTRING_H

#if __STDC_VERSION__ < 202311L // <C23
#include <stdbool.h>
#endif
#include <stddef.h>

#include "estd/eerror.h"

/**
 * @brief Implementation of boyer moore search algorithm
 * @note If F is not in T, then fn return -1
 *
 * @param T Cstring
 * @param F subCstring
 * @return Positon or easy_error code
 */
int boyer_moore_search(const char *T, const char *F);

/// string is struct for easier usage of strings type
typedef struct string {
  char *data;
  size_t length;   // Size of string
  size_t capacity; // Size of allocate memory

} string;

// Macros for getting fields of string struct
#define string_length(string) (string)->length
#define string_capacity(string) (string)->capacity

/**
 * @def is_empty(string)
 * @brief Checks if string is empty
 * @warning Make sure string object is not NULL
 */
#define is_empty(string) ((string)->length == 0)

/// @defgroup String Functions relative to string type
/// @{

/**
 * @brief Create empty string
 * @note str should be freed after using
 *
 * @return Initialized string object or NULL if alocation failed
 */
string *string_init_empty(void);

/**
 * @brief Create string from Cstring
 * @note str should be freed after using
 *
 * @param cstr Cstring
 * @return Initialized string object or NULL if alocation failed
 */
string *string_from_cstr(const char *cstr);

/**
 * @brief Create string. If cstr is empty, return empty string
 * @note str should be freed after using
 * @note use this function if you sure cstr is not NULL
 *
 * @param cstr Pointer to Cstring
 * @return Initialized string object or NULL if alocation failed
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
 * @brief Add char to end of str
 *
 * @param str Pointer to string object
 * @param ch Character
 * @return 0 on success or easy_error
 */
easy_error string_appendc(string *str, const char ch);

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
bool string_compare_bool(string *str1, string *str2, easy_error *err);

/**
 * @brief Compare two string
 *
 * @param str1,str2 Pointers to string objects
 * @return  -1 if str1 < str2, 1 if str1 > str2, 0 if str1 == str2, or a easy_error code
 */
int string_compare(const void *str1, const void *str2);

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
