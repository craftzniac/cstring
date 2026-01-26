#include "CString.h"
#include <stdio.h>

int main(void) {
  CString *str1 = CString_new("HELLO");
  CString *str2 = CString_new("hello");

  CString_Boolean isEqual = CString_equals(str1, str2);
  printf("isEQual: %d", isEqual);

  CString_destroy(str1);
  CString_destroy(str2);
  return 0;
}
