/*
 * The u2up-log Logging support module
 *
 * This file is part of the "u2up-log" software project.
 *
 *  Copyright 2019 Samo Pogacnik <samo_pogacnik@t-2.net>
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
*/

/*
 * This "u2up-log" module provides various output definitions in a single header file.
 */

#ifndef U2UP_LOG_FILE_u2up_log_h
#define U2UP_LOG_FILE_u2up_log_h

/*
 * Here starts the PUBLIC stuff.
 */

#include <errno.h>
#include <stdio.h>
#include <syslog.h>
#include <unistd.h>
#include <time.h>
#include <sys/syscall.h>
#include <sys/types.h>

typedef struct u2up_log {
	unsigned char quiet;
	unsigned char normal;
	unsigned char verbose;
	unsigned char trace;
	unsigned char debug;
	unsigned char header;
	unsigned char syslog;
} u2up_log_struct;

#define _MKU2UPSTR(name) #name
#define MKU2UPSTR(name) _MKU2UPSTR(name)

#define _MKU2UPLOG(name) u2upLog_##name
#define MKU2UPLOG(name) _MKU2UPLOG(name)

#define _MKU2UPLOG_SETQUIET(name) u2upLogSetQuiet_##name
#define MKU2UPLOG_SETQUIET(name) _MKU2UPLOG_SETQUIET(name)
#define _MKU2UPLOG_SETNORMAL(name) u2upLogSetNormal_##name
#define MKU2UPLOG_SETNORMAL(name) _MKU2UPLOG_SETNORMAL(name)
#define _MKU2UPLOG_SETVERBOSE(name) u2upLogSetVerbose_##name
#define MKU2UPLOG_SETVERBOSE(name) _MKU2UPLOG_SETVERBOSE(name)
#define _MKU2UPLOG_SETTRACE(name) u2upLogSetTrace_##name
#define MKU2UPLOG_SETTRACE(name) _MKU2UPLOG_SETTRACE(name)
#define _MKU2UPLOG_SETDEBUG(name) u2upLogSetDebug_##name
#define MKU2UPLOG_SETDEBUG(name) _MKU2UPLOG_SETDEBUG(name)
#define _MKU2UPLOG_SETHEADER(name) u2upLogSetHeader_##name
#define MKU2UPLOG_SETHEADER(name) _MKU2UPLOG_SETHEADER(name)
#define _MKU2UPLOG_SETSYSLOG(name) u2upLogSetSyslog_##name
#define MKU2UPLOG_SETSYSLOG(name) _MKU2UPLOG_SETSYSLOG(name)

static u2up_log_struct MKU2UPLOG(U2UP_LOG_NAME) = {
	.quiet = 0,
	.normal = 1,
	.verbose = 0,
	.trace = 0,
	.debug = 0,
	.header = 1,
	.syslog = 0
};

void MKU2UPLOG_SETQUIET(U2UP_LOG_NAME)(unsigned char val) {
	MKU2UPLOG(U2UP_LOG_NAME).quiet = val;
}
void MKU2UPLOG_SETNORMAL(U2UP_LOG_NAME)(unsigned char val) {
	MKU2UPLOG(U2UP_LOG_NAME).normal = val;
}
void MKU2UPLOG_SETVERBOSE(U2UP_LOG_NAME)(unsigned char val) {
	MKU2UPLOG(U2UP_LOG_NAME).verbose = val;
}
void MKU2UPLOG_SETTRACE(U2UP_LOG_NAME)(unsigned char val) {
	MKU2UPLOG(U2UP_LOG_NAME).trace = val;
}
void MKU2UPLOG_SETDEBUG(U2UP_LOG_NAME)(unsigned char val) {
	MKU2UPLOG(U2UP_LOG_NAME).debug = val;
}
void MKU2UPLOG_SETHEADER(U2UP_LOG_NAME)(unsigned char val) {
	MKU2UPLOG(U2UP_LOG_NAME).header = val;
}
void MKU2UPLOG_SETSYSLOG(U2UP_LOG_NAME)(unsigned char val) {
	MKU2UPLOG(U2UP_LOG_NAME).syslog = val;
}

#define U2UP_LOG_DECLARE(modName) \
extern void MKU2UPLOG_SETQUIET(modName)(unsigned char val); \
extern void MKU2UPLOG_SETNORMAL(modName)(unsigned char val); \
extern void MKU2UPLOG_SETVERBOSE(modName)(unsigned char val); \
extern void MKU2UPLOG_SETTRACE(modName)(unsigned char val); \
extern void MKU2UPLOG_SETDEBUG(modName)(unsigned char val); \
extern void MKU2UPLOG_SETHEADER(modName)(unsigned char val); \
extern void MKU2UPLOG_SETSYSLOG(modName)(unsigned char val)

#define U2UP_LOG_SET_QUIET(val) MKU2UPLOG_SETQUIET(U2UP_LOG_NAME)(val)
#define U2UP_LOG_SET_NORMAL(val) MKU2UPLOG_SETNORMAL(U2UP_LOG_NAME)(val)
#define U2UP_LOG_SET_VERBOSE(val) MKU2UPLOG_SETVERBOSE(U2UP_LOG_NAME)(val)
#define U2UP_LOG_SET_TRACE(val) MKU2UPLOG_SETTRACE(U2UP_LOG_NAME)(val)
#define U2UP_LOG_SET_DEBUG(val) MKU2UPLOG_SETDEBUG(U2UP_LOG_NAME)(val)
#define U2UP_LOG_SET_HEADER(val) MKU2UPLOG_SETHEADER(U2UP_LOG_NAME)(val)
#define U2UP_LOG_SET_SYSLOG(val) MKU2UPLOG_SETSYSLOG(U2UP_LOG_NAME)(val)

#define U2UP_LOG_SET_QUIET2(name, val) MKU2UPLOG_SETQUIET(name)(val)
#define U2UP_LOG_SET_NORMAL2(name, val) MKU2UPLOG_SETNORMAL(name)(val)
#define U2UP_LOG_SET_VERBOSE2(name, val) MKU2UPLOG_SETVERBOSE(name)(val)
#define U2UP_LOG_SET_TRACE2(name, val) MKU2UPLOG_SETTRACE(name)(val)
#define U2UP_LOG_SET_DEBUG2(name, val) MKU2UPLOG_SETDEBUG(name)(val)
#define U2UP_LOG_SET_HEADER2(name, val) MKU2UPLOG_SETHEADER(name)(val)
#define U2UP_LOG_SET_SYSLOG2(name, val) MKU2UPLOG_SETSYSLOG(name)(val)

#define U2UP_LOG_5DIGIT_SECS(timespec_x) (timespec_x.tv_sec % 100000)
#define U2UP_LOG_6DIGIT_USECS(timespec_x) (timespec_x.tv_nsec / 1000)

#define U2UP_LOG_WITH_HEADER_DEBUG_FORMAT "[%05ld.%06ld|%d|%s] %s:%d %s(): "
#define U2UP_LOG_WITH_HEADER_DEBUG_ARGS U2UP_LOG_5DIGIT_SECS(ts), U2UP_LOG_6DIGIT_USECS(ts), (int)syscall(SYS_gettid), MKU2UPSTR(U2UP_LOG_NAME), __FILE__, __LINE__, __FUNCTION__
#define U2UP_LOG_WITH_HEADER_TRACE_FORMAT "[%05ld.%06ld|%d|%s] %s(): "
#define U2UP_LOG_WITH_HEADER_TRACE_ARGS U2UP_LOG_5DIGIT_SECS(ts), U2UP_LOG_6DIGIT_USECS(ts), (int)syscall(SYS_gettid), MKU2UPSTR(U2UP_LOG_NAME), __FUNCTION__
#define U2UP_LOG_WITH_HEADER_NORMAL_FORMAT "[%05ld.%06ld|%d|%s] "
#define U2UP_LOG_WITH_HEADER_NORMAL_ARGS U2UP_LOG_5DIGIT_SECS(ts), U2UP_LOG_6DIGIT_USECS(ts), (int)syscall(SYS_gettid), MKU2UPSTR(U2UP_LOG_NAME)

#define U2UP_LOG_NO_HEADER_DEBUG_FORMAT "%s:%d %s(): "
#define U2UP_LOG_NO_HEADER_DEBUG_ARGS __FILE__, __LINE__, __FUNCTION__
#define U2UP_LOG_NO_HEADER_TRACE_FORMAT "%s(): "
#define U2UP_LOG_NO_HEADER_TRACE_ARGS __FUNCTION__
#define U2UP_LOG_NO_HEADER_NORMAL_FORMAT "%s"
#define U2UP_LOG_NO_HEADER_NORMAL_ARGS ""

#define u2up_log_system_error(format, args...) {\
	char buf[1024];\
	strerror_r(errno, buf, 1024);\
	if (MKU2UPLOG(U2UP_LOG_NAME).header) {\
		struct timespec ts;\
		clock_gettime(CLOCK_MONOTONIC, &ts);\
		if (MKU2UPLOG(U2UP_LOG_NAME).syslog) {\
			if (U2UP_LOG_MODULE_DEBUG && MKU2UPLOG(U2UP_LOG_NAME).debug) {\
				syslog(LOG_ERR, U2UP_LOG_WITH_HEADER_DEBUG_FORMAT "%s >> " format, U2UP_LOG_WITH_HEADER_DEBUG_ARGS, buf, ##args);\
			} else if (U2UP_LOG_MODULE_TRACE && MKU2UPLOG(U2UP_LOG_NAME).trace) {\
				syslog(LOG_ERR, U2UP_LOG_WITH_HEADER_TRACE_FORMAT "%s >> " format, U2UP_LOG_WITH_HEADER_TRACE_ARGS, buf, ##args);\
			} else {\
				syslog(LOG_ERR, U2UP_LOG_WITH_HEADER_NORMAL_FORMAT "%s >> " format, U2UP_LOG_WITH_HEADER_NORMAL_ARGS, buf, ##args);\
			}\
		} else {\
			if (U2UP_LOG_MODULE_DEBUG && MKU2UPLOG(U2UP_LOG_NAME).debug) {\
				fprintf(stderr, U2UP_LOG_WITH_HEADER_DEBUG_FORMAT "%s >> " format, U2UP_LOG_WITH_HEADER_DEBUG_ARGS, buf, ##args);\
				fflush(stderr);\
			} else if (U2UP_LOG_MODULE_TRACE && MKU2UPLOG(U2UP_LOG_NAME).trace) {\
				fprintf(stderr, U2UP_LOG_WITH_HEADER_TRACE_FORMAT "%s >> " format, U2UP_LOG_WITH_HEADER_TRACE_ARGS, buf, ##args);\
				fflush(stderr);\
			} else {\
				fprintf(stderr, U2UP_LOG_WITH_HEADER_NORMAL_FORMAT "%s >> " format, U2UP_LOG_WITH_HEADER_NORMAL_ARGS, buf, ##args);\
				fflush(stderr);\
			}\
		}\
	} else {\
		if (MKU2UPLOG(U2UP_LOG_NAME).syslog) {\
			if (U2UP_LOG_MODULE_DEBUG && MKU2UPLOG(U2UP_LOG_NAME).debug) {\
				syslog(LOG_ERR, U2UP_LOG_NO_HEADER_DEBUG_FORMAT "%s >> " format, U2UP_LOG_NO_HEADER_DEBUG_ARGS, buf, ##args);\
			} else if (U2UP_LOG_MODULE_TRACE && MKU2UPLOG(U2UP_LOG_NAME).trace) {\
				syslog(LOG_ERR, U2UP_LOG_NO_HEADER_TRACE_FORMAT "%s >> " format, U2UP_LOG_NO_HEADER_TRACE_ARGS, buf, ##args);\
			} else {\
				syslog(LOG_ERR, U2UP_LOG_NO_HEADER_NORMAL_FORMAT "%s >> " format, U2UP_LOG_NO_HEADER_NORMAL_ARGS, buf, ##args);\
			}\
		} else {\
			if (U2UP_LOG_MODULE_DEBUG && MKU2UPLOG(U2UP_LOG_NAME).debug) {\
				fprintf(stderr, U2UP_LOG_NO_HEADER_DEBUG_FORMAT "%s >> " format, U2UP_LOG_NO_HEADER_DEBUG_ARGS, buf, ##args);\
				fflush(stderr);\
			} else if (U2UP_LOG_MODULE_TRACE && MKU2UPLOG(U2UP_LOG_NAME).trace) {\
				fprintf(stderr, U2UP_LOG_NO_HEADER_TRACE_FORMAT "%s >> " format, U2UP_LOG_NO_HEADER_TRACE_ARGS, buf, ##args);\
				fflush(stderr);\
			} else {\
				fprintf(stderr, U2UP_LOG_NO_HEADER_NORMAL_FORMAT "%s >> " format, U2UP_LOG_NO_HEADER_NORMAL_ARGS, buf, ##args);\
				fflush(stderr);\
			}\
		}\
	}\
}

#define u2up_log_error(format, args...) {\
	if (MKU2UPLOG(U2UP_LOG_NAME).header) {\
		struct timespec ts;\
		clock_gettime(CLOCK_MONOTONIC, &ts);\
		if (MKU2UPLOG(U2UP_LOG_NAME).syslog) {\
			if (U2UP_LOG_MODULE_DEBUG && MKU2UPLOG(U2UP_LOG_NAME).debug) {\
				syslog(LOG_ERR, U2UP_LOG_WITH_HEADER_DEBUG_FORMAT format, U2UP_LOG_WITH_HEADER_DEBUG_ARGS, ##args);\
			} else if (U2UP_LOG_MODULE_TRACE && MKU2UPLOG(U2UP_LOG_NAME).trace) {\
				syslog(LOG_ERR, U2UP_LOG_WITH_HEADER_TRACE_FORMAT format, U2UP_LOG_WITH_HEADER_TRACE_ARGS, ##args);\
			} else {\
				syslog(LOG_ERR, U2UP_LOG_WITH_HEADER_NORMAL_FORMAT format, U2UP_LOG_WITH_HEADER_NORMAL_ARGS, ##args);\
			}\
		} else {\
			if (U2UP_LOG_MODULE_DEBUG && MKU2UPLOG(U2UP_LOG_NAME).debug) {\
				fprintf(stderr, U2UP_LOG_WITH_HEADER_DEBUG_FORMAT format, U2UP_LOG_WITH_HEADER_DEBUG_ARGS, ##args);\
				fflush(stderr);\
			} else if (U2UP_LOG_MODULE_TRACE && MKU2UPLOG(U2UP_LOG_NAME).trace) {\
				fprintf(stderr, U2UP_LOG_WITH_HEADER_TRACE_FORMAT format, U2UP_LOG_WITH_HEADER_TRACE_ARGS, ##args);\
				fflush(stderr);\
			} else {\
				fprintf(stderr, U2UP_LOG_WITH_HEADER_NORMAL_FORMAT format, U2UP_LOG_WITH_HEADER_NORMAL_ARGS, ##args);\
				fflush(stderr);\
			}\
		}\
	} else {\
		if (MKU2UPLOG(U2UP_LOG_NAME).syslog) {\
			if (U2UP_LOG_MODULE_DEBUG && MKU2UPLOG(U2UP_LOG_NAME).debug) {\
				syslog(LOG_ERR, U2UP_LOG_NO_HEADER_DEBUG_FORMAT format, U2UP_LOG_NO_HEADER_DEBUG_ARGS, ##args);\
			} else if (U2UP_LOG_MODULE_TRACE && MKU2UPLOG(U2UP_LOG_NAME).trace) {\
				syslog(LOG_ERR, U2UP_LOG_NO_HEADER_TRACE_FORMAT format, U2UP_LOG_NO_HEADER_TRACE_ARGS, ##args);\
			} else {\
				syslog(LOG_ERR, U2UP_LOG_NO_HEADER_NORMAL_FORMAT format, U2UP_LOG_NO_HEADER_NORMAL_ARGS, ##args);\
			}\
		} else {\
			if (U2UP_LOG_MODULE_DEBUG && MKU2UPLOG(U2UP_LOG_NAME).debug) {\
				fprintf(stderr, U2UP_LOG_NO_HEADER_DEBUG_FORMAT format, U2UP_LOG_NO_HEADER_DEBUG_ARGS, ##args);\
				fflush(stderr);\
			} else if (U2UP_LOG_MODULE_TRACE && MKU2UPLOG(U2UP_LOG_NAME).trace) {\
				fprintf(stderr, U2UP_LOG_NO_HEADER_TRACE_FORMAT format, U2UP_LOG_NO_HEADER_TRACE_ARGS, ##args);\
				fflush(stderr);\
			} else {\
				fprintf(stderr, U2UP_LOG_NO_HEADER_NORMAL_FORMAT format, U2UP_LOG_NO_HEADER_NORMAL_ARGS, ##args);\
				fflush(stderr);\
			}\
		}\
	}\
}

#define u2up_log_warning(format, args...) {\
	if (MKU2UPLOG(U2UP_LOG_NAME).header) {\
		struct timespec ts;\
		clock_gettime(CLOCK_MONOTONIC, &ts);\
		if (MKU2UPLOG(U2UP_LOG_NAME).syslog) {\
			if (U2UP_LOG_MODULE_DEBUG && MKU2UPLOG(U2UP_LOG_NAME).debug) {\
				syslog(LOG_WARNING, U2UP_LOG_WITH_HEADER_DEBUG_FORMAT format, U2UP_LOG_WITH_HEADER_DEBUG_ARGS, ##args);\
			} else if (U2UP_LOG_MODULE_TRACE && MKU2UPLOG(U2UP_LOG_NAME).trace) {\
				syslog(LOG_WARNING, U2UP_LOG_WITH_HEADER_TRACE_FORMAT format, U2UP_LOG_WITH_HEADER_TRACE_ARGS, ##args);\
			} else if (MKU2UPLOG(U2UP_LOG_NAME).normal || MKU2UPLOG(U2UP_LOG_NAME).verbose) {\
				syslog(LOG_WARNING, U2UP_LOG_WITH_HEADER_NORMAL_FORMAT format, U2UP_LOG_WITH_HEADER_NORMAL_ARGS, ##args);\
			}\
		} else {\
			if (U2UP_LOG_MODULE_DEBUG && MKU2UPLOG(U2UP_LOG_NAME).debug) {\
				fprintf(stdout, U2UP_LOG_WITH_HEADER_DEBUG_FORMAT format, U2UP_LOG_WITH_HEADER_DEBUG_ARGS, ##args);\
				fflush(stdout);\
			} else if (U2UP_LOG_MODULE_TRACE && MKU2UPLOG(U2UP_LOG_NAME).trace) {\
				fprintf(stdout, U2UP_LOG_WITH_HEADER_TRACE_FORMAT format, U2UP_LOG_WITH_HEADER_TRACE_ARGS, ##args);\
				fflush(stdout);\
			} else if (MKU2UPLOG(U2UP_LOG_NAME).normal || MKU2UPLOG(U2UP_LOG_NAME).verbose) {\
				fprintf(stdout, U2UP_LOG_WITH_HEADER_NORMAL_FORMAT format, U2UP_LOG_WITH_HEADER_NORMAL_ARGS, ##args);\
				fflush(stdout);\
			}\
		}\
	} else {\
		if (MKU2UPLOG(U2UP_LOG_NAME).syslog) {\
			if (U2UP_LOG_MODULE_DEBUG && MKU2UPLOG(U2UP_LOG_NAME).debug) {\
				syslog(LOG_WARNING, U2UP_LOG_NO_HEADER_DEBUG_FORMAT format, U2UP_LOG_NO_HEADER_DEBUG_ARGS, ##args);\
			} else if (U2UP_LOG_MODULE_TRACE && MKU2UPLOG(U2UP_LOG_NAME).trace) {\
				syslog(LOG_WARNING, U2UP_LOG_NO_HEADER_TRACE_FORMAT format, U2UP_LOG_NO_HEADER_TRACE_ARGS, ##args);\
			} else if (MKU2UPLOG(U2UP_LOG_NAME).normal || MKU2UPLOG(U2UP_LOG_NAME).verbose) {\
				syslog(LOG_WARNING, U2UP_LOG_NO_HEADER_NORMAL_FORMAT format, U2UP_LOG_NO_HEADER_NORMAL_ARGS, ##args);\
			}\
		} else {\
			if (U2UP_LOG_MODULE_DEBUG && MKU2UPLOG(U2UP_LOG_NAME).debug) {\
				fprintf(stdout, U2UP_LOG_NO_HEADER_DEBUG_FORMAT format, U2UP_LOG_NO_HEADER_DEBUG_ARGS, ##args);\
				fflush(stdout);\
			} else if (U2UP_LOG_MODULE_TRACE && MKU2UPLOG(U2UP_LOG_NAME).trace) {\
				fprintf(stdout, U2UP_LOG_NO_HEADER_TRACE_FORMAT format, U2UP_LOG_NO_HEADER_TRACE_ARGS, ##args);\
				fflush(stdout);\
			} else if (MKU2UPLOG(U2UP_LOG_NAME).normal || MKU2UPLOG(U2UP_LOG_NAME).verbose) {\
				fprintf(stdout, U2UP_LOG_NO_HEADER_NORMAL_FORMAT format, U2UP_LOG_NO_HEADER_NORMAL_ARGS, ##args);\
				fflush(stdout);\
			}\
		}\
	}\
}

#define u2up_log_notice(format, args...) {\
	if (MKU2UPLOG(U2UP_LOG_NAME).header) {\
		struct timespec ts;\
		clock_gettime(CLOCK_MONOTONIC, &ts);\
		if (MKU2UPLOG(U2UP_LOG_NAME).syslog) {\
			if (U2UP_LOG_MODULE_DEBUG && MKU2UPLOG(U2UP_LOG_NAME).debug) {\
				syslog(LOG_NOTICE, U2UP_LOG_WITH_HEADER_DEBUG_FORMAT format, U2UP_LOG_WITH_HEADER_DEBUG_ARGS, ##args);\
			} else if (U2UP_LOG_MODULE_TRACE && MKU2UPLOG(U2UP_LOG_NAME).trace) {\
				syslog(LOG_NOTICE, U2UP_LOG_WITH_HEADER_TRACE_FORMAT format, U2UP_LOG_WITH_HEADER_TRACE_ARGS, ##args);\
			} else if (MKU2UPLOG(U2UP_LOG_NAME).normal || MKU2UPLOG(U2UP_LOG_NAME).verbose) {\
				syslog(LOG_NOTICE, U2UP_LOG_WITH_HEADER_NORMAL_FORMAT format, U2UP_LOG_WITH_HEADER_NORMAL_ARGS, ##args);\
			}\
		} else {\
			if (U2UP_LOG_MODULE_DEBUG && MKU2UPLOG(U2UP_LOG_NAME).debug) {\
				fprintf(stdout, U2UP_LOG_WITH_HEADER_DEBUG_FORMAT format, U2UP_LOG_WITH_HEADER_DEBUG_ARGS, ##args);\
				fflush(stdout);\
			} else if (U2UP_LOG_MODULE_TRACE && MKU2UPLOG(U2UP_LOG_NAME).trace) {\
				fprintf(stdout, U2UP_LOG_WITH_HEADER_TRACE_FORMAT format, U2UP_LOG_WITH_HEADER_TRACE_ARGS, ##args);\
				fflush(stdout);\
			} else if (MKU2UPLOG(U2UP_LOG_NAME).normal || MKU2UPLOG(U2UP_LOG_NAME).verbose) {\
				fprintf(stdout, U2UP_LOG_WITH_HEADER_NORMAL_FORMAT format, U2UP_LOG_WITH_HEADER_NORMAL_ARGS, ##args);\
				fflush(stdout);\
			}\
		}\
	} else {\
		if (MKU2UPLOG(U2UP_LOG_NAME).syslog) {\
			if (U2UP_LOG_MODULE_DEBUG && MKU2UPLOG(U2UP_LOG_NAME).debug) {\
				syslog(LOG_NOTICE, U2UP_LOG_NO_HEADER_DEBUG_FORMAT format, U2UP_LOG_NO_HEADER_DEBUG_ARGS, ##args);\
			} else if (U2UP_LOG_MODULE_TRACE && MKU2UPLOG(U2UP_LOG_NAME).trace) {\
				syslog(LOG_NOTICE, U2UP_LOG_NO_HEADER_TRACE_FORMAT format, U2UP_LOG_NO_HEADER_TRACE_ARGS, ##args);\
			} else if (MKU2UPLOG(U2UP_LOG_NAME).normal || MKU2UPLOG(U2UP_LOG_NAME).verbose) {\
				syslog(LOG_NOTICE, U2UP_LOG_NO_HEADER_NORMAL_FORMAT format, U2UP_LOG_NO_HEADER_NORMAL_ARGS, ##args);\
			}\
		} else {\
			if (U2UP_LOG_MODULE_DEBUG && MKU2UPLOG(U2UP_LOG_NAME).debug) {\
				fprintf(stdout, U2UP_LOG_NO_HEADER_DEBUG_FORMAT format, U2UP_LOG_NO_HEADER_DEBUG_ARGS, ##args);\
				fflush(stdout);\
			} else if (U2UP_LOG_MODULE_TRACE && MKU2UPLOG(U2UP_LOG_NAME).trace) {\
				fprintf(stdout, U2UP_LOG_NO_HEADER_TRACE_FORMAT format, U2UP_LOG_NO_HEADER_TRACE_ARGS, ##args);\
				fflush(stdout);\
			} else if (MKU2UPLOG(U2UP_LOG_NAME).normal || MKU2UPLOG(U2UP_LOG_NAME).verbose) {\
				fprintf(stdout, U2UP_LOG_NO_HEADER_NORMAL_FORMAT format, U2UP_LOG_NO_HEADER_NORMAL_ARGS, ##args);\
				fflush(stdout);\
			}\
		}\
	}\
}

#define u2up_log_info(format, args...) {\
	if (MKU2UPLOG(U2UP_LOG_NAME).header) {\
		struct timespec ts;\
		clock_gettime(CLOCK_MONOTONIC, &ts);\
		if (MKU2UPLOG(U2UP_LOG_NAME).syslog) {\
			if (U2UP_LOG_MODULE_DEBUG && MKU2UPLOG(U2UP_LOG_NAME).debug) {\
				syslog(LOG_INFO, U2UP_LOG_WITH_HEADER_DEBUG_FORMAT format, U2UP_LOG_WITH_HEADER_DEBUG_ARGS, ##args);\
			} else if (U2UP_LOG_MODULE_TRACE && MKU2UPLOG(U2UP_LOG_NAME).trace) {\
				syslog(LOG_INFO, U2UP_LOG_WITH_HEADER_TRACE_FORMAT format, U2UP_LOG_WITH_HEADER_TRACE_ARGS, ##args);\
			} else if (MKU2UPLOG(U2UP_LOG_NAME).verbose) {\
				syslog(LOG_INFO, U2UP_LOG_WITH_HEADER_NORMAL_FORMAT format, U2UP_LOG_WITH_HEADER_NORMAL_ARGS, ##args);\
			}\
		} else {\
			if (U2UP_LOG_MODULE_DEBUG && MKU2UPLOG(U2UP_LOG_NAME).debug) {\
				fprintf(stdout, U2UP_LOG_WITH_HEADER_DEBUG_FORMAT format, U2UP_LOG_WITH_HEADER_DEBUG_ARGS, ##args);\
				fflush(stdout);\
			} else if (U2UP_LOG_MODULE_TRACE && MKU2UPLOG(U2UP_LOG_NAME).trace) {\
				fprintf(stdout, U2UP_LOG_WITH_HEADER_TRACE_FORMAT format, U2UP_LOG_WITH_HEADER_TRACE_ARGS, ##args);\
				fflush(stdout);\
			} else if (MKU2UPLOG(U2UP_LOG_NAME).verbose) {\
				fprintf(stdout, U2UP_LOG_WITH_HEADER_NORMAL_FORMAT format, U2UP_LOG_WITH_HEADER_NORMAL_ARGS, ##args);\
				fflush(stdout);\
			}\
		}\
	} else {\
		if (MKU2UPLOG(U2UP_LOG_NAME).syslog) {\
			if (U2UP_LOG_MODULE_DEBUG && MKU2UPLOG(U2UP_LOG_NAME).debug) {\
				syslog(LOG_INFO, U2UP_LOG_NO_HEADER_DEBUG_FORMAT format, U2UP_LOG_NO_HEADER_DEBUG_ARGS, ##args);\
			} else if (U2UP_LOG_MODULE_TRACE && MKU2UPLOG(U2UP_LOG_NAME).trace) {\
				syslog(LOG_INFO, U2UP_LOG_NO_HEADER_TRACE_FORMAT format, U2UP_LOG_NO_HEADER_TRACE_ARGS, ##args);\
			} else if (MKU2UPLOG(U2UP_LOG_NAME).verbose) {\
				syslog(LOG_INFO, U2UP_LOG_NO_HEADER_NORMAL_FORMAT format, U2UP_LOG_NO_HEADER_NORMAL_ARGS, ##args);\
			}\
		} else {\
			if (U2UP_LOG_MODULE_DEBUG && MKU2UPLOG(U2UP_LOG_NAME).debug) {\
				fprintf(stdout, U2UP_LOG_NO_HEADER_DEBUG_FORMAT format, U2UP_LOG_NO_HEADER_DEBUG_ARGS, ##args);\
				fflush(stdout);\
			} else if (U2UP_LOG_MODULE_TRACE && MKU2UPLOG(U2UP_LOG_NAME).trace) {\
				fprintf(stdout, U2UP_LOG_NO_HEADER_TRACE_FORMAT format, U2UP_LOG_NO_HEADER_TRACE_ARGS, ##args);\
				fflush(stdout);\
			} else if (MKU2UPLOG(U2UP_LOG_NAME).verbose) {\
				fprintf(stdout, U2UP_LOG_NO_HEADER_NORMAL_FORMAT format, U2UP_LOG_NO_HEADER_NORMAL_ARGS, ##args);\
				fflush(stdout);\
			}\
		}\
	}\
}

#define u2up_log_debug(format, args...) {\
	if (MKU2UPLOG(U2UP_LOG_NAME).header) {\
		struct timespec ts;\
		clock_gettime(CLOCK_MONOTONIC, &ts);\
		if (MKU2UPLOG(U2UP_LOG_NAME).syslog) {\
			if (U2UP_LOG_MODULE_DEBUG && MKU2UPLOG(U2UP_LOG_NAME).debug) {\
				syslog(LOG_DEBUG, U2UP_LOG_WITH_HEADER_DEBUG_FORMAT format, U2UP_LOG_WITH_HEADER_DEBUG_ARGS, ##args);\
			}\
		} else {\
			if (U2UP_LOG_MODULE_DEBUG && MKU2UPLOG(U2UP_LOG_NAME).debug) {\
				fprintf(stdout, U2UP_LOG_WITH_HEADER_DEBUG_FORMAT format, U2UP_LOG_WITH_HEADER_DEBUG_ARGS, ##args);\
				fflush(stdout);\
			}\
		}\
	} else {\
		if (MKU2UPLOG(U2UP_LOG_NAME).syslog) {\
			if (U2UP_LOG_MODULE_DEBUG && MKU2UPLOG(U2UP_LOG_NAME).debug) {\
				syslog(LOG_DEBUG, U2UP_LOG_NO_HEADER_DEBUG_FORMAT format, U2UP_LOG_NO_HEADER_DEBUG_ARGS, ##args);\
			}\
		} else {\
			if (U2UP_LOG_MODULE_DEBUG && MKU2UPLOG(U2UP_LOG_NAME).debug) {\
				fprintf(stdout, U2UP_LOG_NO_HEADER_DEBUG_FORMAT format, U2UP_LOG_NO_HEADER_DEBUG_ARGS, ##args);\
				fflush(stdout);\
			}\
		}\
	}\
}

#define u2up_log_return_system_err(msg, args...) {\
	int errsv = errno;\
	u2up_log_system_error(msg, ##args);\
	return -errsv;\
}

#define u2up_log_return_err(msg, args...) {\
	int errsv = errno;\
	u2up_log_error(msg, ##args);\
	return -errsv;\
}

#endif /*U2UP_LOG_FILE_u2up_log_h*/

