/*	$NetBSD: mail.c,v 1.16 2003/08/07 09:05:33 agc Exp $	*/

/*-
 * Copyright (c) 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
 *
 * This code is derived from software contributed to Berkeley by
 * Kenneth Almquist.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#if 0
#ifndef lint
static char sccsid[] = "@(#)mail.c	8.2 (Berkeley) 5/4/95";
#else
__RCSID("$NetBSD: mail.c,v 1.16 2003/08/07 09:05:33 agc Exp $");
#endif /* not lint */
#endif

/*
 * Routines to check for mail.  (Perhaps make part of main.c?)
 */
#include <sys/types.h>
#include <stdlib.h>

#include "shell.h"
#include "exec.h"	/* defines padvance() */
#include "var.h"
#include "output.h"
#include "memalloc.h"
#include "error.h"
#include "mail.h"
#include "shinstance.h"


/*#define MAXMBOXES 10*/


/*STATIC int nmboxes;			/* number of mailboxes */
/*STATIC time_t mailtime[MAXMBOXES];*/	/* times of mailboxes */



/*
 * Print appropriate message(s) if mail has arrived.  If the argument is
 * nozero, then the value of MAIL has changed, so we just update the
 * values.
 */

void
chkmail(shinstance *psh, int silent)
{
	int i;
	const char *mpath;
	char *p;
	char *q;
	struct stackmark smark;
	struct stat statb;

	if (silent)
		psh->nmboxes = 10;
	if (psh->nmboxes == 0)
		return;
	setstackmark(psh, &smark);
	mpath = mpathset(psh) ? mpathval(psh) : mailval(psh);
	for (i = 0 ; i < psh->nmboxes ; i++) {
		p = padvance(psh, &mpath, nullstr);
		if (p == NULL)
			break;
		if (*p == '\0')
			continue;
		for (q = p ; *q ; q++);
		if (q[-1] != '/')
			sh_abort(psh);
		q[-1] = '\0';			/* delete trailing '/' */
#ifdef notdef /* this is what the System V shell claims to do (it lies) */
		if (shfile_stat(&psh->fdtab, p, &statb) < 0)
			statb.st_mtime = 0;
		if (statb.st_mtime > psh->mailtime[i] && ! silent) {
			out2str(psh, psh->pathopt ? psh->pathopt : "you have mail");
			out2c(psh, '\n');
		}
		psh->mailtime[i] = statb.st_mtime;
#else /* this is what it should do */
		if (shfile_stat(&psh->fdtab, p, &statb) < 0)
			statb.st_size = 0;
		if (statb.st_size > psh->mailtime[i] && ! silent) {
			out2str(psh, psh->pathopt ? psh->pathopt : "you have mail");
			out2c(psh, '\n');
		}
		psh->mailtime[i] = statb.st_size;
#endif
	}
	psh->nmboxes = i;
	popstackmark(psh, &smark);
}
