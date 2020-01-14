/*
 * tlpi_hdr.h
 *  Created on: Jul 25, 2019
 *      Author: JianRong
 *  Linux-UNIX系统编程手册（上、下册）.pdf chapter --- 3.5.2
 */

#ifndef LINUX_UNIX_PROGRAMMING_MANUAL_LIB_TLPI_HDR_H_
#define LINUX_UNIX_PROGRAMMING_MANUAL_LIB_TLPI_HDR_H_

#include <sys/types.h>		/* Type definitions used by many programs */
#include <stdio.h>			/* Standard I/O functions */
#include <stdlib.h>			/* 	Prototypes of commonly used library functions,
 	 	 	 	 	 	 	 	 plus EXIT_SUCCESS and EXIT_FAILURE constants */
#include <unistd.h>			/* Prototypes for many system calls */
#include <errno.h>			/* Declares errno and defines error constants */
#include <string.h>			/* Commonly used string-handling functions */
#include "get_num.h"		/* Declares our functions for handling numeric
 	 	 	 	 	 	 	 	 arguments (getInt(), getLong()) */
#include "error_functions.h"    /* Declares our error-handling functions */

typedef enum { FALSE, TRUE } Boolean;

#define min(m, n) ((m) < (n) ? (m) : (n))
#define max(m, n) ((m) > (n) ? (m) : (n))

#endif /* LINUX_UNIX_PROGRAMMING_MANUAL_LIB_TLPI_HDR_H_ */
