#include "CString.h"

int main(void) {
  CString *str = CString_new("this is some string");

  CString_pushCStr(str, ". hello me");
  CString_print(str);

  CString_pushCStr(str, "This is something you should know this i");
  CString_print(str);
  CString_destroy(str);
  return 0;
}
