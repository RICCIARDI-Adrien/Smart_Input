/** @file Log.h
 * Simple logging system displaying messages to the console.
 * @author Adrien RICCIARDI
 */
#ifndef H_LOG_H
#define H_LOG_H

#include <stdio.h>

//-------------------------------------------------------------------------------------------------
// Constants and macros
//-------------------------------------------------------------------------------------------------
/** @def LOG_ERROR(String_Message, ...)
 * Display an error message with red font.
 * @param String_Message The error message to display.
 */
#ifndef NDEBUG
	#define LOG_ERROR(String_Message, ...) printf("\033[31m[%s:%s():%d ERROR] " String_Message "\033[0m\n", __FILE__, __FUNCTION__, __LINE__, ##__VA_ARGS__)
#else
	#define LOG_ERROR(String_Message, ...) {} // Replace by an empty scope instead of nothing in case the log is the only instruction of an if, which would have an empty body if logs are disabled
#endif

/** @def LOG_DEBUG(String_Message, ...)
 * Display a debug message with green font.
 * @param String_Message The error message to display.
 */
#ifndef NDEBUG
	#define LOG_DEBUG(String_Message, ...) printf("\033[32m[%s:%s():%d DEBUG] " String_Message "\033[0m\n", __FILE__, __FUNCTION__, __LINE__, ##__VA_ARGS__)
#else
	#define LOG_DEBUG(String_Message, ...) {} // Replace by an empty scope instead of nothing in case the log is the only instruction of an if, which would have an empty body if logs are disabled
#endif

#endif
