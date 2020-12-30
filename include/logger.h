#ifndef __LOGGER_H__
#define __LOGGER_H__

#include <stdio.h>
#include <string.h>

enum
{
    FAIL,
    SUCCESS,
};

enum
{
    RED,
    GRN,
    BLU,
    YEL,
    DFT
};

char *messages[] = {"fail", "success"};
char *colors[] = {"\x1B[31m", "\x1B[32m", "\x1B[34m", "\x1B[33m", "\x1B[0m"};

#define LOG(fname, status) printf("%s[%s]%s => %s%s%s", colors[status], messages[status], colors[DFT], colors[YEL], fname, colors[DFT])

#endif