/*****************************************************
 *                                                   *
 * Modified "Zed's Awesome Debug Macros"             *
 * Originally from:                                             *
 *  http://c.learncodethehardway.org/book/ex20.html  *
 *                                                   *
 *****************************************************/

#ifndef __dbg_h__
#define __dbg_h__

#include <stdio.h>
#include <errno.h>
#include <string.h>
#define clean_errno() (errno == 0 ? "None" : strerror(errno))

#ifdef __WIN32
/**
HANDLE DBG_h_console;
CONSOLE_SCREEN_BUFFER_INFO DBG_console_info;
WORD DBG_saved_attributes;

#define DBG_WIN32_INIT()  DBG_h_console = GetStdHandle(STD_OUTPUT_HANDLE);\
                          GetConsoleScreenBufferInfo(DBG_h_console, &DBG_console_info);\
                          DBG_saved_attributes = DBG_console_info.wAttributes


#define DBG_COLOR_DEBUG_WIN32 GetConsoleScreenBufferInfo(DBG_h_console, &DBG_console_info);\
                              DBG_saved_attributes = DBG_console_info.wAttributes;\
                              SetConsoleScreenBufferInfo(DBG_h_console,DBG_saved_attributes);

#define DBG_COLOR_ERR_WIN32 GetConsoleScreenBufferInfo(DBG_h_console, &DBG_console_info);\
                              DBG_saved_attributes = DBG_console_info.wAttributes;\
                              SetConsoleScreenBufferInfo(DBG_h_console,FOREGROUND_RED);

#define DBG_COLOR_WARN_WIN32 GetConsoleScreenBufferInfo(DBG_h_console, &DBG_console_info);\
                              DBG_saved_attributes = DBG_console_info.wAttributes;\
                              SetConsoleScreenBufferInfo(DBG_h_console,FOREGROUND_GREEN);

#define DBG_COLOR_INFO_WIN32 GetConsoleScreenBufferInfo(DBG_h_console, &DBG_console_info);\
                             DBG_saved_attributes = DBG_console_info.wAttributes;\
                             SetConsoleScreenBufferInfo(DBG_h_console,FOREGROUND_BLUE);

#define DBG_COLOR_RESET_WIN32 ;SetConsoleScreenBufferInfo(DBG_h_console, DBG_saved_attributes)
**/
#define DBG_COLOR_DEBUG
#define DBG_COLOR_ERR
#define DBG_COLOR_WARN
#define DBG_COLOR_INFO
#define DBG_COLOR_RESET 

#else

#define DBG_COLOR_DEBUG "\x1B[35m"
#define DBG_COLOR_ERR "\x1B[31m"
#define DBG_COLOR_WARN "\x1B[33m"
#define DBG_COLOR_INFO "\x1B[34m"
#define DBG_COLOR_RESET "\033[0m"

#endif // __WIN32

#define DBG_COLOR_DEBUG_WIN32
#define DBG_COLOR_ERR_WIN32
#define DBG_COLOR_WARN_WIN32
#define DBG_COLOR_INFO_WIN32
#define DBG_COLOR_RESET_WIN32


#ifdef NDEBUG
#define debug(M, ...)
#else
#define debug(M, ...) DBG_COLOR_DEBUG_WIN32; fprintf(stderr, DBG_COLOR_DEBUG "DEBUG %s:%d: " M "\n" DBG_COLOR_RESET, __FILE__, __LINE__, ##__VA_ARGS__); DBG_COLOR_RESET_WIN32
#endif


#define log_err(M, ...) DBG_COLOR_ERR_WIN32; fprintf(stderr, DBG_COLOR_ERR "[ERROR] (%s:%d: errno: %s) " M "\n" DBG_COLOR_RESET, __FILE__, __LINE__, clean_errno(), ##__VA_ARGS__); DBG_COLOR_RESET_WIN32

#define log_warn(M, ...) DBG_COLOR_WARN_WIN32; fprintf(stderr, DBG_COLOR_WARN "[WARN] (%s:%d: errno: %s) " M "\n" DBG_COLOR_RESET, __FILE__, __LINE__, clean_errno(), ##__VA_ARGS__); DBG_COLOR_RESET_WIN32

#define log_info(M, ...) DBG_COLOR_INFO_WIN32; fprintf(stderr, DBG_COLOR_INFO "[INFO] (%s:%d) " M "\n" DBG_COLOR_RESET, __FILE__, __LINE__, ##__VA_ARGS__); DBG_COLOR_RESET_WIN32

#define check(A, M, ...) if(!(A)) { log_err(M, ##__VA_ARGS__); errno=0; goto error; }

#define sentinel(M, ...)  { log_err(M, ##__VA_ARGS__); errno=0; goto error; }

#define check_mem(A) check((A), "Out of memory.")

#define check_debug(A, M, ...) if(!(A)) { debug(M, ##__VA_ARGS__); errno=0; goto error; }

#endif // __dbg_h__
