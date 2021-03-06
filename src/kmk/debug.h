/* Debugging macros and interface.
Copyright (C) 1999, 2000, 2001, 2002, 2003, 2004, 2005, 2006, 2007 Free
Software Foundation, Inc.
This file is part of GNU Make.

GNU Make is free software; you can redistribute it and/or modify it under the
terms of the GNU General Public License as published by the Free Software
Foundation; either version 3 of the License, or (at your option) any later
version.

GNU Make is distributed in the hope that it will be useful, but WITHOUT ANY
WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
A PARTICULAR PURPOSE.  See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with
this program.  If not, see <http://www.gnu.org/licenses/>.  */

#define DB_NONE         (0x000)
#define DB_BASIC        (0x001)
#define DB_VERBOSE      (0x002)
#define DB_JOBS         (0x004)
#define DB_IMPLICIT     (0x008)
#define DB_MAKEFILES    (0x100)
#ifdef KMK
# define DB_KMK         (0x800)
#endif 

#define DB_ALL          (0xfff)

extern int db_level;

#ifdef KMK

/* Some extended info for -j and .NOTPARALLEL tracking. */
extern unsigned int makelevel;
extern unsigned int job_slots;
extern unsigned int job_slots_used;

#define DB_HDR()    do { printf ("[%u:%u/%u]", makelevel, job_slots_used, job_slots); } while (0)

#define ISDB(_l)    ((_l)&db_level)

#define DBS(_l,_x)  do{ if(ISDB(_l)) {DB_HDR(); \
                                      print_spaces (depth); \
                                      printf _x; fflush (stdout);} }while(0)

#define DBF(_l,_x)  do{ if(ISDB(_l)) {DB_HDR(); \
                                      print_spaces (depth); \
                                      printf (_x, file->name); \
                                      fflush (stdout);} }while(0)

#define DB(_l,_x)   do{ if(ISDB(_l)) {DB_HDR(); printf _x; fflush (stdout);} }while(0)

#else  /* !KMK */

#define ISDB(_l)    ((_l)&db_level)

#define DBS(_l,_x)  do{ if(ISDB(_l)) {print_spaces (depth); \
                                      printf _x; fflush (stdout);} }while(0)

#define DBF(_l,_x)  do{ if(ISDB(_l)) {print_spaces (depth); \
                                      printf (_x, file->name); \
                                      fflush (stdout);} }while(0)

#define DB(_l,_x)   do{ if(ISDB(_l)) {printf _x; fflush (stdout);} }while(0)

#endif /* !KMK */
