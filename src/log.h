/*
The MIT License (MIT)

Copyright (c) 2014 Stuart Wallace <stuart@wapbot.co.uk>

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#ifndef __TINY_LOG_H__
#define __TINY_LOG_H__

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stdlib.h>

#define puts_nonl(S) fputs(S, stdout)

// Define logging levels.
#define TINY_LOG_INFO    0x01
#define TINY_LOG_ERROR   0x02
#define TINY_LOG_WARNING 0x04
#define TINY_LOG_TRACE   0x08
#define TINY_LOG_DEBUG   0x10

#ifndef NDEBUG
    #define TINY_LOG_DEFAULT (TINY_LOG_INFO | TINY_LOG_ERROR | TINY_LOG_WARNING | TINY_LOG_DEBUG)
#else
    #define TINY_LOG_DEFAULT (TINY_LOG_INFO | TINY_LOG_ERROR | TINY_LOG_WARNING)
#endif

// Short logging macros
#define tiny_info(M, ...)\
    tiny_log(TINY_LOG_INFO, M, __FILE__, __LINE__, __func__, ##__VA_ARGS__)

#define tiny_error(M, ...)\
    tiny_log(TINY_LOG_ERROR, M, __FILE__, __LINE__, __func__, ##__VA_ARGS__)

#define tiny_warn(M, ...)\
    tiny_log(TINY_LOG_WARNING, M, __FILE__, __LINE__, __func__, ##__VA_ARGS__)

#define tiny_trace(M, ...)\
    tiny_log(TINY_LOG_TRACE, M, __FILE__, __LINE__,  __func__, ##__VA_ARGS__)

#define tiny_debug(M, ...)\
    tiny_log(TINY_LOG_DEBUG, M, __FILE__, __LINE__, __func__, ##__VA_ARGS__)

#define tiny_do_log(L, M, ...)\
    tiny_log(L, M, __FILE__, __LINE__, __func__, ##__VA_ARGS__)

void tiny_set_log_level(unsigned char level);
void tiny_unset_log_level(unsigned char level);

bool tiny_is_log_level(unsigned char level);

void tiny_log(unsigned char level,
               const char* message,
               const char* file,
               int line,
               const char* function, ...);

void tiny_log_pretty_print(unsigned char level, char* buf, size_t size);

#ifdef __cplusplus
}
#endif

#endif //__TINY_LOG_H__
