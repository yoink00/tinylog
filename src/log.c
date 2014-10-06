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

#include <stdio.h>
#include <stdarg.h>
#include <stdbool.h>
#include <sys/time.h>
#include <time.h>
#include <string.h>

#include "log.h"

// Define static logging strings.
static const char* TINY_LOG_INFO_STR    = "INF";
static const char* TINY_LOG_ERROR_STR   = "ERR";
static const char* TINY_LOG_WARNING_STR = "WAR";
static const char* TINY_LOG_TRACE_STR   = "TRC";
static const char* TINY_LOG_DEBUG_STR   = "DBG";

static unsigned char g_tiny_log_level = TINY_LOG_DEFAULT;

/*__attribute__((constructor)) void tiny_log_init()
{
    tiny_info("Loaded libtinylog.so");
}

void tiny_set_log_level_msg(const char* args[])
{
    tiny_info("Received a 'set_log_level_msg'");
}*/

void tiny_set_log_level(unsigned char level)
{
    g_tiny_log_level |= level;
}

bool tiny_is_log_level(unsigned char level)
{
    return ((g_tiny_log_level & level) == level);
}


void tiny_log(unsigned char level,
               const char* message,
               const char* file,
               int line,
               const char* function,
               ...)
{
    if(tiny_is_log_level(level))
    {
        va_list arg_list;
        va_start(arg_list, function);

        const char* levelStr = NULL;
        if(level == TINY_LOG_INFO)
        {
            levelStr = TINY_LOG_INFO_STR;
        }
        else if(level == TINY_LOG_ERROR)
        {
            levelStr = TINY_LOG_ERROR_STR;
        }
        else if(level == TINY_LOG_WARNING)
        {
            levelStr = TINY_LOG_WARNING_STR;
        }
        else if(level == TINY_LOG_TRACE)
        {
            levelStr = TINY_LOG_TRACE_STR;
        }
        else if(level == TINY_LOG_DEBUG)
        {
            levelStr = TINY_LOG_DEBUG_STR;
        }
        else 
        {
            tiny_error("Unknown log level used.");
            levelStr = TINY_LOG_ERROR_STR;
        }

        char timeFmt[64];
        char timeBuf[64];
        struct timeval tv;
        gettimeofday(&tv, NULL);

        struct tm* tm;
        if((tm = localtime(&tv.tv_sec)) != NULL)
        {
            strftime(timeFmt, sizeof(timeFmt), "%Y%m%d %H:%M:%S.%%06u %z", tm);
            snprintf(timeBuf, sizeof(timeBuf), timeFmt, tv.tv_usec);
        }
        else
        {
            strncpy(timeBuf, "NO_TIME", sizeof(timeBuf));
        }

        char tmpMsg[1024];
        snprintf(tmpMsg,
                 1024,
                 "[%s] %s - %s:%s(%d)\n%s\n\n",
                 levelStr,
                 timeBuf,
                 file,
                 function,
                 line,
                 message);
        vprintf(tmpMsg, arg_list);

        va_end(arg_list);
    }
}

void tiny_log_pretty_print(unsigned char level, char* buf, size_t size)
{
    if(tiny_is_log_level(level))
    {
        char text[17];
        tiny_do_log(level, "Pretty print buffer data");
        int i;
        for(i = 0; i < size; ++i)
        {
            if(buf[i] < ' ' || buf[i] > '~')
            {
                text[i % 16] = '.';
            }
            else
            {
                text[i % 16] = buf[i];
            }

            if(i != 0 && i % 16 == 0)
            {
                text[16] = '\0';
                puts_nonl("   ");
                puts(text);
            }

            printf("%02x ", buf[i]);
        }
        text[(i % 16)] = '\0';
        for(int j = 0; j < (51 - ((i % 16) * 3)); ++j)
        {
            putchar(' ');
        }
        puts(text);
        puts("");
    }
}
