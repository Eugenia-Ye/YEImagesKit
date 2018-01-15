/**
 * In order to provide fast and flexible logging, GAMMA uses Cocoa Lumberjack and drop NSLog.
 * 
 * The GitHub project page has a wealth of documentation if you have any questions.
 * https://github.com/robbiehanson/CocoaLumberjack
 * 
 * Here's what you need to know concerning how logging is setup for GAMMA:
 * 
 * There are 4 log levels:
 * - Error
 * - Warning
 * - Info
 * - Verbose
 * 
 * In addition to this, there is a Trace flag that can be enabled.
 * When tracing is enabled, it spits out the methods that are being called.
 * 
 * Please note that tracing is separate from the log levels.
 * For example, one could set the log level to warning, and enable tracing.
 * 
 * All logging is asynchronous, except errors.
 * To use logging within your own custom files, follow the steps below.
 * 
 * Step 1:
 * Import this header in the implementation file:
 * 
 * #import "GAMMALogging.h"
 * 
 * Step 2:
 * Define logging level in the implementation file:
 * 
 * // Log levels: off, error, warn, info, verbose
 * static const int logLevel = GAMMA_LOG_LEVEL_VERBOSE;
 * 
 * If you wish to enable tracing, you could do something like this:
 * 
 * // Log levels: off, error, warn, info, verbose
 * static const int logLevel = GAMMA_LOG_LEVEL_INFO | GAMMA_LOG_FLAG_TRACE;
 * 
 * Step 3:
 * Replace NSLog statements with GAMMALog statements according to the severity of the message.
 * 
 * NSLog(@"Fatal error, no dohickey found!"); -> GAMMALogError(@"Fatal error, no dohickey found!");
 * 
 * GAMMALog has the same syntax as NSLog.
 * This means you can pass it multiple variables just like NSLog.
 * 
 * You may optionally choose to define different log levels for debug and release builds.
 * You can do so like this:
 * 
 * // Log levels: off, error, warn, info, verbose
 * #if DEBUG
 *   static const int logLevel = GAMMA_LOG_LEVEL_VERBOSE;
 * #else
 *   static const int logLevel = GAMMA_LOG_LEVEL_WARN;
 * #endif
 * 
 * Xcode projects created with Xcode 4 automatically define DEBUG via the project's preprocessor macros.
 * If you created your project with a previous version of Xcode, you may need to add the DEBUG macro manually.
**/

#import "DDLog.h"

// Global flag to enable/disable logging throughout the entire project.

#ifndef GAMMA_LOGGING_ENABLED
#define GAMMA_LOGGING_ENABLED 1
#endif

// Define logging context for every log message coming from the GAMMA framework.
// The logging context can be extracted from the DDLogMessage from within the logging framework.
// This gives loggers, formatters, and filters the ability to optionally process them differently.

#define GAMMA_LOG_CONTEXT 5678

// Configure log levels.

#define GAMMA_LOG_FLAG_ERROR   (1 << 0) // 0...00001
#define GAMMA_LOG_FLAG_WARN    (1 << 1) // 0...00010
#define GAMMA_LOG_FLAG_INFO    (1 << 2) // 0...00100
#define GAMMA_LOG_FLAG_VERBOSE (1 << 3) // 0...01000

#define GAMMA_LOG_LEVEL_OFF     0                                              // 0...00000
#define GAMMA_LOG_LEVEL_ERROR   (GAMMA_LOG_LEVEL_OFF   | GAMMA_LOG_FLAG_ERROR)   // 0...00001
#define GAMMA_LOG_LEVEL_WARN    (GAMMA_LOG_LEVEL_ERROR | GAMMA_LOG_FLAG_WARN)    // 0...00011
#define GAMMA_LOG_LEVEL_INFO    (GAMMA_LOG_LEVEL_WARN  | GAMMA_LOG_FLAG_INFO)    // 0...00111
#define GAMMA_LOG_LEVEL_VERBOSE (GAMMA_LOG_LEVEL_INFO  | GAMMA_LOG_FLAG_VERBOSE) // 0...01111

// Setup fine grained logging.
// The first 4 bits are being used by the standard log levels (0 - 3)
// 
// We're going to add tracing, but NOT as a log level.
// Tracing can be turned on and off independently of log level.

#define GAMMA_LOG_FLAG_TRACE     (1 << 4) // 0...10000

// Setup the usual boolean macros.

#define GAMMA_LOG_ERROR   (logLevel & GAMMA_LOG_FLAG_ERROR)
#define GAMMA_LOG_WARN    (logLevel & GAMMA_LOG_FLAG_WARN)
#define GAMMA_LOG_INFO    (logLevel & GAMMA_LOG_FLAG_INFO)
#define GAMMA_LOG_VERBOSE (logLevel & GAMMA_LOG_FLAG_VERBOSE)
#define GAMMA_LOG_TRACE   (logLevel & GAMMA_LOG_FLAG_TRACE)


// Configure asynchronous logging.
// We follow the default configuration,
// but we reserve a special macro to easily disable asynchronous logging for debugging purposes.

#if DEBUG
#define GAMMA_LOG_ASYNC_ENABLED  NO
#else
#define GAMMA_LOG_ASYNC_ENABLED  YES
#endif

#define GAMMA_LOG_ASYNC_ERROR     ( NO && GAMMA_LOG_ASYNC_ENABLED)
#define GAMMA_LOG_ASYNC_WARN      (YES && GAMMA_LOG_ASYNC_ENABLED)
#define GAMMA_LOG_ASYNC_INFO      (YES && GAMMA_LOG_ASYNC_ENABLED)
#define GAMMA_LOG_ASYNC_VERBOSE   (YES && GAMMA_LOG_ASYNC_ENABLED)
#define GAMMA_LOG_ASYNC_TRACE     (YES && GAMMA_LOG_ASYNC_ENABLED)


// Define logging primitives.
// These are primarily wrappers around the macros defined in Lumberjack's DDLog.h header file.

#define GAMMA_LOG_OBJC_MAYBE(async, lvl, flg, ctx, frmt, ...) \
    do{ if(GAMMA_LOGGING_ENABLED) LOG_MAYBE(async, lvl, flg, ctx, sel_getName(_cmd), frmt, ##__VA_ARGS__); } while(0)

#define GAMMA_LOG_C_MAYBE(async, lvl, flg, ctx, frmt, ...) \
    do{ if(GAMMA_LOGGING_ENABLED) LOG_MAYBE(async, lvl, flg, ctx, __FUNCTION__, frmt, ##__VA_ARGS__); } while(0)


#define GAMMALogError(frmt, ...)    GAMMA_LOG_OBJC_MAYBE(GAMMA_LOG_ASYNC_ERROR,   logLevel, GAMMA_LOG_FLAG_ERROR,  \
                                                  GAMMA_LOG_CONTEXT, frmt, ##__VA_ARGS__)

#define GAMMALogWarn(frmt, ...)     GAMMA_LOG_OBJC_MAYBE(GAMMA_LOG_ASYNC_WARN,    logLevel, GAMMA_LOG_FLAG_WARN,   \
                                                  GAMMA_LOG_CONTEXT, frmt, ##__VA_ARGS__)

#define GAMMALogInfo(frmt, ...)     GAMMA_LOG_OBJC_MAYBE(GAMMA_LOG_ASYNC_INFO,    logLevel, GAMMA_LOG_FLAG_INFO,    \
                                                  GAMMA_LOG_CONTEXT, frmt, ##__VA_ARGS__)

#define GAMMALogVerbose(frmt, ...)  GAMMA_LOG_OBJC_MAYBE(GAMMA_LOG_ASYNC_VERBOSE, logLevel, GAMMA_LOG_FLAG_VERBOSE, \
                                                  GAMMA_LOG_CONTEXT, frmt, ##__VA_ARGS__)

#define GAMMALogTrace()             GAMMA_LOG_OBJC_MAYBE(GAMMA_LOG_ASYNC_TRACE,   logLevel, GAMMA_LOG_FLAG_TRACE, \
                                                  GAMMA_LOG_CONTEXT, @"%@: %@", THIS_FILE, THIS_METHOD)

#define GAMMALogTrace2(frmt, ...)   GAMMA_LOG_OBJC_MAYBE(GAMMA_LOG_ASYNC_TRACE,   logLevel, GAMMA_LOG_FLAG_TRACE, \
                                                  GAMMA_LOG_CONTEXT, frmt, ##__VA_ARGS__)


#define GAMMALogCError(frmt, ...)      GAMMA_LOG_C_MAYBE(GAMMA_LOG_ASYNC_ERROR,   logLevel, GAMMA_LOG_FLAG_ERROR,   \
                                                  GAMMA_LOG_CONTEXT, frmt, ##__VA_ARGS__)

#define GAMMALogCWarn(frmt, ...)       GAMMA_LOG_C_MAYBE(GAMMA_LOG_ASYNC_WARN,    logLevel, GAMMA_LOG_FLAG_WARN,    \
                                                  GAMMA_LOG_CONTEXT, frmt, ##__VA_ARGS__)

#define GAMMALogCInfo(frmt, ...)       GAMMA_LOG_C_MAYBE(GAMMA_LOG_ASYNC_INFO,    logLevel, GAMMA_LOG_FLAG_INFO,    \
                                                  GAMMA_LOG_CONTEXT, frmt, ##__VA_ARGS__)

#define GAMMALogCVerbose(frmt, ...)    GAMMA_LOG_C_MAYBE(GAMMA_LOG_ASYNC_VERBOSE, logLevel, GAMMA_LOG_FLAG_VERBOSE, \
                                                  GAMMA_LOG_CONTEXT, frmt, ##__VA_ARGS__)

#define GAMMALogCTrace()               GAMMA_LOG_C_MAYBE(GAMMA_LOG_ASYNC_TRACE,   logLevel, GAMMA_LOG_FLAG_TRACE, \
                                                  GAMMA_LOG_CONTEXT, @"%@: %s", THIS_FILE, __FUNCTION__)

#define GAMMALogCTrace2(frmt, ...)     GAMMA_LOG_C_MAYBE(GAMMA_LOG_ASYNC_TRACE,   logLevel, GAMMA_LOG_FLAG_TRACE, \
                                                  GAMMA_LOG_CONTEXT, frmt, ##__VA_ARGS__)

/*
// Setup logging for GAMMAStream (and subclasses such as GAMMAStreamFacebook)

#define GAMMA_LOG_FLAG_SEND      (1 << 5)
#define GAMMA_LOG_FLAG_RECV_PRE  (1 << 6) // Prints data before it goes to the parser
#define GAMMA_LOG_FLAG_RECV_POST (1 << 7) // Prints data as it comes out of the parser

#define GAMMA_LOG_FLAG_SEND_RECV (GAMMA_LOG_FLAG_SEND | GAMMA_LOG_FLAG_RECV_POST)

#define GAMMA_LOG_SEND      (logLevel & GAMMA_LOG_FLAG_SEND)
#define GAMMA_LOG_RECV_PRE  (logLevel & GAMMA_LOG_FLAG_RECV_PRE)
#define GAMMA_LOG_RECV_POST (logLevel & GAMMA_LOG_FLAG_RECV_POST)

#define GAMMA_LOG_ASYNC_SEND      (YES && GAMMA_LOG_ASYNC_ENABLED)
#define GAMMA_LOG_ASYNC_RECV_PRE  (YES && GAMMA_LOG_ASYNC_ENABLED)
#define GAMMA_LOG_ASYNC_RECV_POST (YES && GAMMA_LOG_ASYNC_ENABLED)

#define GAMMALogSend(format, ...)     GAMMA_LOG_OBJC_MAYBE(GAMMA_LOG_ASYNC_SEND, logLevel, \
                                                GAMMA_LOG_FLAG_SEND, GAMMA_LOG_CONTEXT, format, ##__VA_ARGS__)

#define GAMMALogRecvPre(format, ...)  GAMMA_LOG_OBJC_MAYBE(GAMMA_LOG_ASYNC_RECV_PRE, logLevel, \
                                                GAMMA_LOG_FLAG_RECV_PRE, GAMMA_LOG_CONTEXT, format, ##__VA_ARGS__)

#define GAMMALogRecvPost(format, ...) GAMMA_LOG_OBJC_MAYBE(GAMMA_LOG_ASYNC_RECV_POST, logLevel, \
                                                GAMMA_LOG_FLAG_RECV_POST, GAMMA_LOG_CONTEXT, format, ##__VA_ARGS__)
 
 */
