#include <stddef.h>

typedef struct CString CString;

typedef enum Boolean { False = 0, True = 1 } Boolean;

CString *CString_new(const char *str);
void CString_destroy(CString *str);
void CString_print(CString *str);
size_t CString_len(CString *str);
Boolean CString_isEmpty(CString *str);

// clear string
void CString_clear(CString *str);
void CString_pushCStr(
    CString *dest, const char *src); // append stringliteral to end of CString
void CString_pushChar(const CString *dest,
                      const char src); // append char to end of CString
void CString_pushCString(
    const CString *dest,
    const CString *src); // append another CString to end of current CString
CString *CString_concat(const CString *a,
                        const CString *b); // concatenate two CStrings and
                                           // create a new one from that

// comparison
Boolean CString_eq(
    const CString *a,
    const CString *b); // compares two CStrings to see if their content is equal
Boolean
CString_eqCStr(const CString *a,
               const char *b); // compares the contents of a CString and a
                               // regular c string to see if they're equal

void CString_insertCStr(
    const CString *dest, const char *src,
    size_t startIndex); // insert a regular c string on the CString
                        // starting from some index on the CString
void CString_insertCString(const CString *dest, const CString *src,
                           size_t startIndex);

//
CString *CString_slice(
    const CString *a, size_t startIndex,
    size_t count); // creates a substring from the CString from the CString

// finding within cstring
Boolean CString_includesCStr(const CString *haystack, const char *needle);
Boolean CString_includes(const CString *haystack, const CString *needle);
Boolean CString_startsWith(const CString *haystack, const char *needle);
Boolean CString_startsWithCStr(const CString *haystack, const char *needle);
