#ifndef _DATES_H_
#define _DATES_H_

#define _XOPEN_SOURSE 500
#include <time.h>
#include "mystdlib.h"

time_t parse_date(const char *input_buffer, const char *format,
                  error_tm * err);
time_t try_get_date(char *terminate_string, const char *format);
time_t get_date(const char *format);

#endif                          /* _DATES_H_ */
