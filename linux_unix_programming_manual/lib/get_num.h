/*
 * get_num.h
 *
 *  Created on: Jul 25, 2019
 *      Author: JianRong
 *	Linux-UNIX系统编程手册（上、下册）.pdf chapter --- 3.5.2
 */

#ifndef LINUX_UNIX_PROGRAMMING_MANUAL_LIB_GET_NUM_H_
#define LINUX_UNIX_PROGRAMMING_MANUAL_LIB_GET_NUM_H_

#define GN_NONNEG	01		/* Value must be >= 0 */
#define GN_GT_O		02		/* Value must be > 0 */

							/* By default, integers are decimal */
#define GN_ANY_BASE	0100	/* Can use any base - like strtol(3) */
#define GN_BASE_8	0200	/* Value is expressed in octal */
#define GN_BASE_16	0400	/* Value is expressed in hexadecimal */

long getLong(const char *arg, int flags, const char *name);
int getInt(const char *arg, int flags, const char *name);

#endif /* LINUX_UNIX_PROGRAMMING_MANUAL_LIB_GET_NUM_H_ */
