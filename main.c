#include "CString.h"
#include <stdio.h>

int main(void) {
  CString *str1 = CString_new(NULL);
  CString_concat_cstr(str1, "hello world");

  CString *str2 = CString_new("message number 1. This is new");
  CString_concat_CString(str1, str2);

  CString_print(str1);
  CString_destroy(str1);
  CString_destroy(str2);
  return 0;
}
