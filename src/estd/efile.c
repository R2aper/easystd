#include "estd/efile.h"
#include <stdarg.h>
#include <stdlib.h>

#define is_mode_reader(mode) (mode == READ || mode == READ_BIN)
#define is_mode_writer(mode)                                                                       \
  (mode == WRITE || mode == WRITE_BIN || mode == APPEND || mode == APPEND_BIN ||                   \
   mode == READ_UPDATE || mode == READ_UPDATE_BIN || mode == WRITE_UPDATE ||                       \
   mode == WRITE_UPDATE_BIN || mode == APPEND_UPDATE || mode == APPEND_UPDATE_BIN)

static inline easy_error update_position_r(freader *reader) {
  reader->pos = get_position(reader);
  return (reader->pos < 0) ? FILE_TELL_ERROR : OK;
}

static inline easy_error update_position_w(fwriter *writer) {
  writer->pos = get_position(writer);
  return (writer->pos < 0) ? FILE_TELL_ERROR : OK;
}

static const char *mode_to_string(FILE_MODE mode) {
  switch (mode) {
  case READ:
    return "r";
  case WRITE:
    return "w";
  case APPEND:
    return "a";
  case READ_UPDATE:
    return "r+";
  case WRITE_UPDATE:
    return "w+";
  case APPEND_UPDATE:
    return "a+";
  case READ_BIN:
    return "rb";
  case WRITE_BIN:
    return "wb";
  case APPEND_BIN:
    return "ab";
  case READ_UPDATE_BIN:
    return "rb+";
  case WRITE_UPDATE_BIN:
    return "wb+";
  case APPEND_UPDATE_BIN:
    return "ab+";
  default:
    return NULL;
  }
}

freader *openr(const char *filename, FILE_MODE mode, easy_error *err) {
  // Check for NULL
  if (!filename) {
    SET_CODE_ERROR(err, INVALID_ARGUMENT);
    return NULL;
  }

  // Check mode
  const char *mode_str = mode_to_string(mode);
  if (!is_mode_reader(mode) || !mode_str) {
    SET_CODE_ERROR(err, FILE_INVALID_MODE);
    return NULL;
  }

  freader *reader = (freader *)malloc(sizeof(freader));
  if (!reader) {
    SET_CODE_ERROR(err, ALLOCATION_FAILED);
    free(reader);
    return NULL;
  }

  reader->mode = mode;
  reader->fp = fopen(filename, mode_str);

  // Check if file is open
  if (!IS_VALID_FILE(reader)) {
    SET_CODE_ERROR(err, FILE_OPEN_ERROR);
    free(reader);
    return NULL;
  }

  // Get position
  easy_error e = update_position_r(reader);
  if (e != OK) {
    SET_CODE_ERROR(err, e);
    closer(reader);
    return NULL;
  }

  SET_CODE_ERROR(err, OK);
  return reader;
}

fwriter *openw(const char *filename, FILE_MODE mode, easy_error *err) {
  // Check for NULL
  if (!filename) {
    SET_CODE_ERROR(err, INVALID_ARGUMENT);
    return NULL;
  }

  // Check mode
  const char *mode_str = mode_to_string(mode);
  if (!is_mode_writer(mode) || !mode_str) {
    SET_CODE_ERROR(err, FILE_INVALID_MODE);
    return NULL;
  }

  fwriter *writer = (fwriter *)malloc(sizeof(fwriter));
  if (!writer) {
    SET_CODE_ERROR(err, ALLOCATION_FAILED);
    return NULL;
  }

  writer->mode = mode;
  writer->fp = fopen(filename, mode_str);

  // Check if file is open
  if (!IS_VALID_FILE(writer)) {
    SET_CODE_ERROR(err, FILE_OPEN_ERROR);
    return NULL;
  }

  // Get position
  easy_error e = update_position_w(writer);
  if (e != OK) {
    SET_CODE_ERROR(err, e);
    return NULL;
  }

  SET_CODE_ERROR(err, OK);
  return writer;
}

easy_error closer(freader *reader) {
  CHECK_NULL_PTR((reader && reader->fp));

  fclose(reader->fp);
  reader->fp = NULL;

  free(reader);

  return OK;
}

easy_error closew(fwriter *writer) {
  CHECK_NULL_PTR((writer && writer->fp));

  fclose(writer->fp);
  writer->fp = NULL;

  free(writer);

  return OK;
}

size_t write_bytes(fwriter *writer, const void *data, size_t size, size_t count, easy_error *err) {
  if (!writer || !writer->fp) {
    SET_CODE_ERROR(err, NULL_POINTER);
    return 0;
  }

  if (!data) {
    SET_CODE_ERROR(err, INVALID_ARGUMENT);
    return 0;
  }

  size_t written = fwrite(data, size, count, writer->fp);

  /* NOTE: Probably shouldn't be a error

  if (written != count)
    return FILE_WRITE_FAILED;
*/

  easy_error e = update_position_w(writer);
  if (e != OK) {
    SET_CODE_ERROR(err, e);
    return 0;
  }

  SET_CODE_ERROR(err, OK);
  return written;
}

int writef(fwriter *writer, const char *format, ...) {
  CHECK_NULL_PTR((writer && writer->fp && format));

  // Parse arguments
  va_list args;
  va_start(args, format);
  int result = vfprintf(writer->fp, format, args);
  va_end(args);

  // If vfprintf return error
  if (result < 0)
    return FILE_WRITE_FAILED;

  easy_error e = update_position_w(writer);
  if (e != OK)
    return e;

  return result;
}

size_t read_bytes(freader *reader, void *buffer, size_t size, size_t count, easy_error *err) {
  if (!reader || !reader->fp) {
    SET_CODE_ERROR(err, NULL_POINTER);
    return 0;
  }

  if (!buffer) {
    SET_CODE_ERROR(err, INVALID_ARGUMENT);
    return 0;
  }

  size_t read_size = fread(buffer, size, count, reader->fp);

  /*  NOTE: Probably shouldn't be a error

  if (read_size != count) {
    SET_CODE_ERROR(err, FILE_READ_FAILED);
    return 0;
  }
  */

  easy_error e = update_position_r(reader);
  if (e != OK)
    return e;

  SET_CODE_ERROR(err, OK);
  return read_size;
}

int readf(freader *reader, const char *format, ...) {
  if (!reader || !reader->fp)
    return NULL_POINTER;

  if (!format)
    return INVALID_ARGUMENT;

  // Parse arguments
  va_list args;
  va_start(args, format);
  int result = vfscanf(reader->fp, format, args);
  va_end(args);

  // if vfscanf return error
  if (result < 0)
    return FILE_READ_FAILED;

  easy_error e = update_position_r(reader);
  if (e != OK)
    return e;

  return result;
}

string *read_line(freader *reader, easy_error *err) {
  if (!reader || !reader->fp) {
    SET_CODE_ERROR(err, NULL_POINTER);
    return NULL;
  }

  string *line = string_init_empty();
  if (!line) {
    SET_CODE_ERROR(err, ALLOCATION_FAILED);
    return NULL;
  }

  int ch;
  while ((ch = fgetc(reader->fp)) != EOF) {
    if (ch == '\n')
      break;
    easy_error e = string_appendc(line, (char)ch); // Append string with character
    if (e != OK) {
      string_free(line);
      SET_CODE_ERROR(err, e);
      return NULL;
    }
  }

  if (is_empty(line) && ch == EOF) { // If file is emtpy
    string_free(line);
    return NULL;
  }

  easy_error e = update_position_r(reader);
  if (e != OK) {
    SET_CODE_ERROR(err, e);
    return NULL;
  }

  SET_CODE_ERROR(err, OK);
  return line;
}

string *read_file(freader *reader, easy_error *err) {
  if (!reader || !reader->fp) {
    SET_CODE_ERROR(err, NULL_POINTER);
    return NULL;
  }

  if (fseek(reader->fp, 0, SEEK_END) != 0) {
    SET_CODE_ERROR(err, FILE_SEEK_ERROR);
    return NULL;
  }

  int64_t filesize = ftell(reader->fp);
  if (filesize < 0) {
    SET_CODE_ERROR(err, FILE_TELL_ERROR);
    return NULL;
  }

  file_rewind(reader);

  string *text = (string *)malloc(sizeof(string));
  if (!text) {
    SET_CODE_ERROR(err, ALLOCATION_FAILED);
    return NULL;
  }

  text->data = (char *)malloc(filesize + 1); // +1 for '\0'
  if (!text->data) {
    free(text);
    SET_CODE_ERROR(err, ALLOCATION_FAILED);
    return NULL;
  }

  size_t readsize = fread(text->data, 1, filesize, reader->fp);
  text->data[readsize] = '\0';
  text->length = readsize;
  text->capacity = readsize + 1;

  easy_error e = update_position_r(reader);
  if (e != OK) {
    SET_CODE_ERROR(err, e);
    return NULL;
  }

  SET_CODE_ERROR(err, OK);
  return text;
}
