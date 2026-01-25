#include "CString.h"
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define CHAR_LENGTH 80
#define DEFAULT_CAPACITY 100

struct CString {
  size_t length;
  size_t capacity;
  char *data;
};

// START ===== CSTRING HELPERS =============================
CString_AllocResult CString_AllocResult_Ok() {
  return (CString_AllocResult){.tag = CString_Result_Ok};
}

CString_AllocResult CString_AllocResult_Err() {
  return (CString_AllocResult){.tag = CString_Result_Err, .error = 0};
}

CString_ConcatResult CString_ConcatResult_Ok() {
  return (CString_ConcatResult){.tag = CString_Result_Ok};
}

CString_ConcatResult CString_ConcatResult_Err() {
  return (CString_ConcatResult){.tag = CString_Result_Err, .error = 0};
}

CString_AllocResult CString_resize(
    CString *str,
    size_t min_capacity) { // resize string buffer by doubling min_capacity
  if (str == NULL || str->data == NULL) {
    return CString_AllocResult_Err();
  }
  size_t new_capacity = min_capacity * 2;
  char *temp = realloc(str->data, new_capacity);
  if (temp == NULL) {
    return CString_AllocResult_Err();
  }
  str->capacity = new_capacity;
  return CString_AllocResult_Ok();
}

// END ===== CSTRING HELPERS =============================

CString *CString_new(const char *str) {
  size_t len = str == NULL ? 0 : strlen(str);
  CString *s = malloc(sizeof(CString));
  s->length = len;
  s->capacity = len < DEFAULT_CAPACITY ? DEFAULT_CAPACITY : len * 2;
  char *data = malloc(sizeof(char) * s->capacity);
  if (data == NULL) {
    return NULL;
  }
  memcpy(data, str, len);
  s->data = data;
  return s;
}

void CString_destroy(CString *str) {
  if (str == NULL || str->data == NULL) {
    return;
  }
  free(str->data);
  str->data = NULL;
  free(str);
}

void CString_print(const CString *str) {
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

size_t CString_len(const CString *str) {
  if (str == NULL) {
    return 0;
  }
  return str->length;
}

CString_Boolean CString_isEmpty(const CString *str) {
  if (str == NULL) {
    return True;
  }
  return str->length == 0;
}

CString_ConcatResult CString_concat_cstr(CString *dest, const char *src) {
  if (dest == NULL || src == NULL) {
    return CString_ConcatResult_Err();
  }
  size_t src_len = strlen(src);
  size_t new_length = dest->length + src_len;
  if (new_length > dest->capacity) {
    if (CString_resize(dest, new_length).tag == CString_Result_Err) {
      return CString_ConcatResult_Err();
    }
  }
  memcpy(dest->data + dest->length, src, src_len);
  dest->length = new_length;
  return CString_ConcatResult_Ok();
}

CString_ConcatResult CString_concat_char(CString *dest, const char src) {
  char s[2] = {src, '\0'};
  return CString_concat_cstr(dest, s);
}

CString_ConcatResult CString_concat_CString(CString *dest, const CString *src) {
  if (dest == NULL || src == NULL) {
    return CString_ConcatResult_Err();
  }
  size_t src_len = CString_len(src);
  size_t new_length = dest->length + src_len;
  if (new_length > dest->capacity &&
      CString_resize(dest, new_length).tag == CString_Result_Err) {
    return CString_ConcatResult_Err();
  }
  memcpy(dest->data + dest->length, src->data, src_len);
  dest->length = new_length;
  return CString_ConcatResult_Ok();
}
