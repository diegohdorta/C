/*
 * lwib - Simple Lightweight and Speedy Low Latency iMX Web Server
 * Copyright (c) 2019 Diego Dorta <diego.dorta@nxp.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */
#ifndef _LWIB_H_
#define _LWIB_H_

#define _XOPEN_SOURCE 700

#define BUFSIZE 8096
#define ERROR 42
#define SORRY 43
#define LOG   44

#define INCORRECT_ARGUMENTS -1
#define CORRECT_ARGUMENTS   3
#define SIZE_EXTENSION      10
#define SIZE_FILE_TYPE      1024
#define REQUIRED_ARGUMENTS  3
#define PORT_MINIMUM        1
#define PORT_MAXIMUM        65000
#define BACKLOG             16
#define CHILD               0
#define FILE_TYPES_NAME     "lwib-data/supported-file-types.lwib"
struct dict_extensions {
	char ext[SIZE_EXTENSION];
	char filetype[SIZE_FILE_TYPE];
};
typedef struct dict_extensions dict_ext_t;


#endif /* _LWIB_H_DEFINED_ */
