/* -*- coding: utf-8-dos -*- */
#include "mystdlib.h"
char *my_gets(char *buf, size_t buf_size)
{
    fgets(buf, buf_size, stdin);
    buf[strlen(buf) - 1] = '\0';
    return buf;
}
