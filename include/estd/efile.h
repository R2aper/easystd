#ifndef EFILE_H
#define EFILE_H

#include <stdint.h>
#include <stdio.h>

#include "estd/eerror.h"
#include "estd/estring.h"

typedef enum FILE_MODE {
  READ,             // "r" - Only reading. File must exist.
  WRITE,            // "w" - Only writing. Create file or rewrite existing.
  APPEND,           // "a" - Only append. Create file or append into existing.
  READ_UPDATE,      // "r+" - Reading and writing. File must exist.
  WRITE_UPDATE,     // "w+" -  Reading and writing. Create file or rewrite existing.
  APPEND_UPDATE,    // "a+" - Reading and appending. Create file or open for reading and append into
                    // existing.
  READ_BIN,         // "rb" - Only reading(binary). File must exist.
  WRITE_BIN,        // "wb" -  Only writing(binary). Create file or rewrite existing
  APPEND_BIN,       // "a" - Only append(binary). Create file or append into existing.
  READ_UPDATE_BIN,  // "rb+" - Reading and writing(binary). File must exist.
  WRITE_UPDATE_BIN, // "wb+" - Reading and writing(binary). Create file or rewrite existing.
  APPEND_UPDATE_BIN // "ab+" - Reading and appending(binary. Create file or open for reading and
                    // append into existing.
} FILE_MODE;

typedef struct fwriter {
  FILE *fp;
  FILE_MODE mode;
  int64_t pos;

} fwriter;

typedef struct freader {
  FILE *fp;
  FILE_MODE mode;
  int64_t pos;

} freader;

#define file_position(io) (io)->pos
#define file_mode(io) (io)->mode

#define IS_VALID_FILE(io) ((io)->fp != NULL)
#define IS_EOF(reader) (feof((reader)->fp))

#define get_position(io) ftell((io)->fp);
#define file_seek(io, offset, origin) fseek((io->fp), (offset), (origin));
#define file_rewind(io) rewind((io)->fp)

#define file_has_error(io) (ferror((io)->fp) != 0)
#define file_clear_error(io) clearerr((io)->fp)

#define file_perror(msg, io)                                                                       \
  if (ferror((io)->fp))                                                                            \
    perror(msg);

/**
 * @brief Open file for reading
 * @note freader should be close after using
 *
 * @param filename Path to file
 * @param mode File opening mode
 * @param err Pointer to easy_error object. Pass NULL if you sure in other parameters
 * @return Pointer to opened file
 */
freader *openr(const char *filename, FILE_MODE mode, easy_error *err);

/**
 * @brief Open file for writing
 * @note fwriter should be close after using
 *
 * @param filename Path to file
 * @param mode File opening mode
 * @param err Pointer to easy_error object. Pass NULL if you sure in other parameters
 * @return Pointer to opened file
 */
fwriter *openw(const char *filename, FILE_MODE mode, easy_error *err);

/**
 * @brief Close file
 *
 * @param reader Pointer to opened file
 * @return 0 on success or easy_error
 */
easy_error closer(freader *reader);

/**
 * @brief Close file
 *
 * @param writer Pointer to opened file
 * @return 0 on success or easy_error
 */
easy_error closew(fwriter *writer);

/**
 * @brief Writes count of objects from the given array buffer to writer
 *
 * @param writer Pointer to opened file
 * @param data Name of the array to be written
 * @param size Size of each element
 * @param count Number of elements to be written
 * @param err Pointer to easy_error object. Pass NULL if you sure in other parameters
 * @return The number of objects written successfully
 */
size_t write_bytes(fwriter *writer, const void *data, size_t size, size_t count, easy_error *err);

/**
 * @brief Formatted writing into opened file
 *
 * @param writer Pointer to opened file
 * @return Number of writed arguments or easy_error
 */
int writef(fwriter *writer, const char *format, ...);

/**
 * @brief Read the given amount of data from a opened file
 *
 * @param reader Pointer to opened file
 * @param buffer Pointer to the buffer memory block where the data read will be stored
 * @param size Size of each element in bytes
 * @param count Count of elements to be read
 * @param err Pointer to easy_error object. Pass NULL if you sure in other parameters
 * @return The number of objects readed successfully
 */
size_t read_bytes(freader *reader, void *buffer, size_t size, size_t count, easy_error *err);

/**
 * @brief Formatted reading from opened file
 *
 * @param reader Pointer to opened file
 * @return Number of readed arguments or easy_error
 */
int readf(freader *reader, const char *format, ...);

/**
 * @brief Read characters in file until new line
 *
 * @param err Pointer to easy_error object. Pass NULL if you sure in other parameters
 * @return Initialized string object
 */
string *read_line(freader *reader, easy_error *err);

/**
 * @brief Read while content of file
 *
 * @param err Pointer to easy_error object. Pass NULL if you sure in other parameters
 * @return Initialized string object
 */
string *read_file(freader *reader, easy_error *err);

#endif // EFILE_H
