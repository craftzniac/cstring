#include "CString.h"
#include <stdio.h>
#include <string.h>

int main(void) {
  CString *str1 =
      CString_new("THE FIRST RANDOM TEXT. THE SECOND RANDOM TEXT. THE THIRD "
                  "RANDOM TEXT. THE FOURTH RANDOM TEXT. THE FIFTH RANDOM TEXT. "
                  "THE SIXTH RANDOM TEXT.");
  char *name = "let all that is in me praise";

  printf("cap: %lu\n", CString_capacity(str1));

  CString_InsertResult res = CString_insert_cstr(str1, name, 17, strlen(name));
  switch (res.tag) {
  case CString_Result_Err:
    printf("insert err: %s", res.error);
    break;
  case CString_Result_Ok:
    CString_print(str1);
    break;
  }
  printf("cap: %lu\n", CString_capacity(str1));
  printf("len: %lu\n", CString_len(str1));

  CString_destroy(str1);
  return 0;
}
