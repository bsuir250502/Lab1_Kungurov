#include "dates.h"

time_t parse_date(const char *input_buffer, const char *format,
                  error_tm * err)
{
    struct tm tm;
    time_t res;
    char *strptime_result;
    memset(&tm, 0, sizeof(struct tm));
    strptime_result = strptime(input_buffer, format, &tm);
    if (strptime_result && *strptime_result == '\0') {
        res = mktime(&tm);
        if (res != -1) {
            *err = NO_ERROR;
        } else {
            *err = INVALID_INPUT;
        }
    } else {
        *err = INVALID_INPUT;
    }
    return res;
}

time_t try_get_date(char *terminate_string, const char *format)
{
    error_tm err;
    time_t res;
    int first = 1;
    const int input_buffer_length = 31;
    char input_buffer[input_buffer_length];
    do {
        if (!first) {
            puts("Invalid date, please try again");
        } else {
            first = 0;
        }
        my_gets(input_buffer, input_buffer_length);
        if (terminate_string && !strcmp(input_buffer, terminate_string)) {
            return 0;
        }
        res = parse_date(input_buffer, format, &err);
    } while (err);
    return res;
}

time_t get_date(const char *format)
{
    return try_get_date(NULL, format);
}
