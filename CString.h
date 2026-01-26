#include <stddef.h>

typedef struct CString CString;

typedef enum { False = 0, True = 1 } CString_Boolean;

enum ResultTag { CString_Result_Ok = 1, CString_Result_Err = 0 };
enum OptionTag { CString_Option_Some = 1, CString_Option_None = 0 };

#define CSTRING_RESULT(T, E)                                                   \
  struct {                                                                     \
    enum ResultTag tag;                                                        \
    union {                                                                    \
      T value;                                                                 \
      E error;                                                                 \
    };                                                                         \
  }

#define CSTRING_RESULT_VOID(E)                                                 \
  struct {                                                                     \
    enum ResultTag tag;                                                        \
    E error;                                                                   \
  }

#define CSTRING_OPTION(T)                                                      \
  struct {                                                                     \
    enum OptionTag tag;                                                        \
    T value;                                                                   \
  }

#define CSTRING_OK(val) {.tag = CString_Result_Ok, .value = (val)}
#define CSTRING_ERR(err) {.tag = CString_Result_Err, .error = (err)}
#define CSTRING_OK_VOID() {.tag = CString_Result_Ok}
#define CSTRING_ERR_VOID(err) {.tag = CString_Result_Err, .error = (err)}

typedef CSTRING_RESULT_VOID(int) CString_AllocResult;
typedef CSTRING_RESULT_VOID(int) CString_ConcatResult;
typedef CSTRING_OPTION(char) CString_CharOption;

CString_AllocResult CString_AllocResult_Ok();
CString_AllocResult CString_AllocResult_Err();

CString_ConcatResult CString_ConcatResult_Ok();
CString_ConcatResult CString_ConcatResult_Err();

CString_CharOption CString_CharOption_None();
CString_CharOption CString_CharOption_Some(char c);

CString *CString_new(const char *str);
void CString_destroy(CString *str);
void CString_print(const CString *str);
size_t CString_len(const CString *str);
CString_Boolean CString_isEmpty(const CString *str);

// string concatenation
CString_ConcatResult
CString_concat_cstr(CString *dest,
                    const char *src); // append stringliteral to end of CString
CString_ConcatResult
CString_concat_char(CString *dest,
                    const char src); // append char to end of CString
CString_ConcatResult CString_concat_CString(
    CString *dest,
    const CString *src); // append another CString to end of current CString

// indexing into string
CString_CharOption CString_charAt(const CString *str, size_t index);

// // comparison
CString_Boolean
CString_equals(const CString *str1,
               const CString *str2); // compares two CStrings to see if
                                     // their content is equal
//
// CString_Boolean
// CString_eq_cstr(const CString *a,
//                 const char *b); // compares the contents of a CString and a
//                                 // regular c string to see if they're equal
//
// // insertion
// void CString_insert_cstr(
//     CString *dest, const char *src,
//     size_t startIndex); // insert a regular c string on the CString
//                         // starting from some index on the CString
// void CString_insert_CString(CString *dest, const CString *src,
//                             size_t startIndex);
//
// CString *CString_slice(
//     const CString *a, size_t startIndex,
//     size_t count); // creates a substring from the CString from the CString
//
// // finding within cstring
// CString_Boolean CString_includes_cstr(const CString *haystack,
//                                       const char *needle);
// CString_Boolean CString_includes_CString(const CString *haystack,
//                                          const CString *needle);
// CString_Boolean CString_startsWith_CString(const CString *haystack,
//                                            const char *needle);
// CString_Boolean CString_startsWith_cstr(const CString *haystack,
//                                         const char *needle);
