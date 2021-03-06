/* $Id: shthread.c 2243 2009-01-10 02:24:02Z bird $ */
/** @file
 *
 * Shell Thread Management.
 *
 * Copyright (c) 2007-2009  knut st. osmundsen <bird-kBuild-spamix@anduin.net>
 *
 *
 * This file is part of kBuild.
 *
 * kBuild is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * kBuild is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with kBuild; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 */

#include "shthread.h"
#include "shinstance.h"

#if defined(_MSC_VER) || defined(__EMX__)
# include <process.h>
#else
# include <pthread.h>
#endif


void shthread_set_shell(struct shinstance *psh)
{

}

struct shinstance *shthread_get_shell(void)
{
    shinstance *psh = NULL;
    return psh;
}


