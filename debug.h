#ifndef __DEBUG_H__
#define __DEBUG_H__

#include <stdio.h>

#define DEBUG

#ifdef DEBUG
#define LOG(x, ...) printf(x, ##__VA_ARGS__)
#else
#define LOG(x, ...)
#endif

#endif