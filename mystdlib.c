/* -*- coding: utf-8-dos -*- */
#include "mystdlib.h"
char *my_gets(char *buf, size_t buf_size)
{
    fgets(buf, buf_size, stdin);
    buf[strlen(buf) - 1] = '\0';
    return buf;
}

int read_number()
{
    error_tm err;
    long int result;
    const int input_buffer_length = 31;
    char input_buffer[input_buffer_length];
    int first = 1;
    do {
        if (!first) {
            puts("Invalid number, please try again");
        } else {
            first = 0;
        }
        my_gets(input_buffer, input_buffer_length);
        result = parse_number(input_buffer, &err);
    } while (err);
    return result;
}

int parse_number(const char *str, error_tm * err)
{
    long int result;
    errno = 0;
    if ((sscanf(str, "%ld", &result) == 1) && !errno) {
        *err = NO_ERROR;
    } else {
        *err = INVALID_INPUT;
    }
    return result;
}
