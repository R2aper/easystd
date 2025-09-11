#ifndef ARGPARSER_H
#define ARGPARSER_H

#include "estd/eerror.h"
#include "estd/grow.h"
#include "estring.h"

typedef enum { FLAG, SINGLE_OPTION, MULTIPLE_OPTION } arg_type;

typedef struct cmd_parser {
  // TODO: Maybe should use hash table?
  grow *args;        // cmd_arg*
  grow *pos_args;    // string*
  string *arg_error; // If error appears, it would be invalid arg

} cmd_parser;

#define arg_error(parser) (parser)->arg_error

/**
 * @brief Creates a new command parser.
 *
 * @return A pointer to the new cmd_parser struct.
 */
cmd_parser *cmd_parser_create();

/**
 * @brief Frees the memory allocated for the command parser.
 *
 * @param p A pointer to the cmd_parser to be freed.
 */
void cmd_parser_free(cmd_parser *p);

/**
 * @brief Adds a new argument to the parser.
 *
 * @param p A pointer to the cmd_parser.
 * @param short_name The short name of the argument (e.g., "-h").
 * @param long_name The long name of the argument (e.g., "--help").
 * @param type The type of the argument (FLAG, SINGLE_OPTION, or MULTIPLE_OPTION).
 *
 * @return OK on success, or an error code on failure.
 */
easy_error cmd_parser_add(cmd_parser *p, const char *short_name, const char *long_name,
                          arg_type type);

/**
 * @brief Parses the command-line arguments.
 *
 * @param p A pointer to the cmd_parser.
 * @param argc The number of command-line arguments.
 * @param argv An array of command-line arguments.
 *
 * @return OK on success, or an error code on failure.
 */
easy_error cmd_parser_parse(cmd_parser *p, int argc, char *argv[]);

/**
 * @brief Checks if a flag or option was set.
 *
 * @param p A pointer to the cmd_parser.
 * @param name The name of the argument to check (short or long name).
 * @param err A pointer to an easy_error variable to store any error that occurs.
 *
 * @return True if the argument was set, false otherwise.
 */
bool cmd_is_set(cmd_parser *p, const char *name, easy_error *err);

/**
 * @brief Gets the value of a single option.
 *
 * @param p A pointer to the cmd_parser.
 * @param name The name of the argument to get the value of (short or long name).
 * @param err A pointer to an easy_error variable to store any error that occurs.
 *
 * @return A pointer to the value of the option, or NULL if the option was not set or an error
 * occurred.
 */
const string *cmd_get_value(cmd_parser *p, const char *name, easy_error *err);

/**
 * @brief Gets the values of a multiple option.
 *
 * @param p A pointer to the cmd_parser.
 * @param name The name of the argument to get the values of (short or long name).
 * @param err A pointer to an easy_error variable to store any error that occurs.
 *
 * @return A pointer to a growable array of strings containing the values of the option, or NULL if
 * the option was not set or an error occurred.
 */
const grow *cmd_get_values(cmd_parser *p, const char *name, easy_error *err);

/**
 * @brief Gets the positionals args.
 *
 * @param p A pointer to the cmd_parser.
 * @param err A pointer to an easy_error variable to store any error that occurs.
 *
 * @return A pointer to a growable array of strings containing the positionals args, or NULL if
 * error accured.
 */
const grow *cmd_get_pos_args(cmd_parser *p, easy_error *err);

/*
#ifdef DEBUG
void cmd_parser_print_result(cmd_parser *p);
#endif
*/

#endif // ARGPARSER_H
