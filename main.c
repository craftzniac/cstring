#include "CString.h"
#include <assert.h>
#include <stdio.h>

int main(void) {
  CString *str = CString_new("God is good");

  CString_SubstringResult res = CString_substring(str, 0, 6);

  switch (res.tag) {
  case CString_Result_Err:
    printf("%s", res.error);
    break;
  case CString_Result_Ok: {
    CString *substring = res.value;
    printf("substring: ");
    CString_print(substring);

    CString *temp = CString_new("God is");
    assert(CString_equals(substring, temp) == True);
    CString_destroy(temp);

    CString_destroy(substring);
  } break;
  }

  CString_destroy(str);
  return 0;
}
