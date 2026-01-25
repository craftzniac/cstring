#include "CString.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define CHAR_LENGTH 80

struct CString {
  size_t length;
  size_t capacity;
  char *data;
};

CString *CString_new(const char *str) {
  size_t len = str == NULL ? 0 : strlen(str);
  CString *s = malloc(sizeof(CString));
  s->length = len;
  s->capacity = len < 100 ? 100 : len * 2;
  char *data = malloc(sizeof(char) * s->capacity);
  memcpy(data, str, len);
  s->data = data;

  return s;
}

void CString_destroy(CString *str) {
  if (str == NULL) {
    return;
  }
  if (str->data == NULL) {
    return;
  }
  free(str->data);
  str->data = NULL;
  free(str);
  str = NULL;
}

void CString_print(CString *str) {
  if (str == NULL) {
    printf("NULL");
    return;
  }
  size_t len = str->length;
  printf("CString(");
  if (len == 0) {
    printf("\"\")\n");
    return;
  }

  if (len > CHAR_LENGTH) {
    printf("\n  \"");
  } else {
    printf("\"");
  }

  for (size_t i = 0; i < len; i++) {
    printf("%c", str->data[i]);
  }

  if (len > CHAR_LENGTH) {
    printf("\"\n)\n");
  } else {
    printf("\")\n");
  }
}

size_t CString_len(CString *str) {
  if (str == NULL) {
    return 0;
  }
  return str->length;
}

Boolean CString_isEmpty(CString *str) {
  if (str == NULL) {
    return True;
  }
  return str->length == 0;
}

void CString_clear(CString *str) {
  if (str == NULL || str->data == NULL)
    return;
  str->length = 0;
  free(str->data);
  str->data = NULL;
}

void CString_pushCStr(CString *dest, const char *src) {
  if (dest == NULL || src == NULL) {
    return;
  }
  size_t src_len = strlen(src);
  size_t new_length = dest->length + src_len;
  if (new_length >= dest->capacity) {
    dest->capacity = new_length * 2;
    dest->data = realloc(dest->data, dest->capacity);
    if (dest->data == NULL) {
      dest->length = 0;
      dest->capacity = 0;
      return;
    }
  }

  char *start_write = dest->data + dest->length;
  memcpy(start_write, src, src_len);
  dest->length += src_len;
}
