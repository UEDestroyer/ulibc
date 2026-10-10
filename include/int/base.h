#include "types/base.h"
#include "low-access-UEDestroyer/defines/x86_64/linux.h"
#include "low-access-UEDestroyer/funcs/linux.h"
#include <limits.h>
#include "base/errno.h"
#include "str/base.h"
#include "str/convert.h"

intmax_t imaxabs(intmax_t j);
struct imaxdiv_t imaxdiv(intmax_t a, intmax_t b);
intmax_t strtoimax(const char* s, char** end, int base);
uintmax_t strtoumax(const char* s, char** end, int base);
intmax_t wcstoimax(const wchar_t* s, wchar_t** end, int base);
uintmax_t wcstoumax(const wchar_t* s, wchar_t** end, int base);