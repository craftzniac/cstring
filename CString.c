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
CString_InsertResult cstring_InsertResult_Err(char *msg) {
  return (CString_InsertResult){.tag = CString_Result_Err, .error = msg};
}

CString_InsertResult cstring_InsertResult_Ok() {
  return (CString_InsertResult){.tag = CString_Result_Ok, .error = NULL};
}

CString_CharOption CString_CharOption_None() {
  return (CString_CharOption){.tag = CString_Option_None};
}

CString_CharOption CString_CharOption_Some(char c) {
  return (CString_CharOption){.tag = CString_Option_Some, .value = c};
}

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

  if (str->capacity >= min_capacity) {
    return CString_AllocResult_Ok();
  }

  size_t new_capacity = min_capacity * 2;
  char *temp = realloc(str->data, new_capacity);
  if (temp == NULL) {
    return CString_AllocResult_Err();
  }
  str->data = temp;
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

CString_Boolean CString_equals(const CString *str1, const CString *str2) {
  if (str1 == NULL || str2 == NULL) {
    return False;
  }

  size_t str1_len = CString_len(str1);
  size_t str2_len = CString_len(str2);
  if (str1_len != str2_len) {
    return False;
  }

  for (size_t i = 0; i < str1_len; i++) { // compare the corresponding chars
    CString_CharOption char_str1_opt = CString_charAt(str1, i);
    CString_CharOption char_str2_opt = CString_charAt(str2, i);
    if (char_str1_opt.tag == CString_Option_Some &&
        char_str2_opt.tag == CString_Option_Some) {
      if (char_str1_opt.value != char_str2_opt.value) {
        return False;
      }
    } else {
      return False;
    }
  }

  return True;
}

/** Insert characters from a string buffer {src} into a cstring starting at
 * {startIndex}.
 * {src} is NOT assumed to be nullterminated, and therefore a {count} is used to
 * decide how many chars are collected from the buffer
 * */
CString_InsertResult CString_insert_cstr(CString *dest, const char *src,
                                         size_t startIndex, size_t count) {
  if (dest == NULL || dest->data == NULL || src == NULL) {
    return cstring_InsertResult_Err("encountered a NULL pointer");
  }

  size_t dest_len = CString_len(dest);
  if (startIndex >= dest_len) {
    char buf[93];
    snprintf(buf, sizeof(buf),
             "startIndex is out of bounds of string buffer. startIndex was %lu "
             "but dest string length was %lu",
             startIndex, dest_len);
    // FIX: once this function returns, buf becomes a dangling pointer. I have
    // to fix this without using CString since it is heap-allocated
    return cstring_InsertResult_Err(buf);
  }

  size_t min_capacity = count + dest->length;
  if (min_capacity > dest->capacity) { // resize dest to be able to fit src
    CString_AllocResult res = CString_resize(dest, min_capacity);
    if (res.tag == CString_Result_Err) {
      return cstring_InsertResult_Err("resize failed");
    }
  }

  size_t tail_len = dest->length - startIndex;

  // copy the tail elements in dest->data to the end of the buffer.
  // Do this first before copying the elements from src to
  // dest->data, so that elements between startIndex and dest->len don't get
  // overriden
  memmove(dest->data + startIndex + count, dest->data + startIndex, tail_len);

  // then copy the elements of src into dest->data
  memmove(dest->data + startIndex, src, count);
  dest->length = min_capacity;
  return cstring_InsertResult_Ok();
}

// get char at a specific index in the string
CString_CharOption CString_charAt(const CString *str, size_t index) {
  if (str == NULL) {
    return CString_CharOption_None();
  }

  // bounds check
  if (index >= CString_len(str)) {
    return CString_CharOption_None();
  }

  return CString_CharOption_Some(str->data[index]);
}

size_t CString_capacity(const CString *str) {
  if (str == NULL) {
    return 0;
  }
  return str->capacity;
}
