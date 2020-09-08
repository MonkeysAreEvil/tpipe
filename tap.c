
/* Part 0 : COMMENTS */

/* Programmed in C by Juanjo Garcia <juanjo@eurogaran.com>
This file Copyright: (C)2004 Juanjo Garcia <juanjo@eurogaran.com>

   This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Library General Public License for more details.

  You should have received a copy of the GNU Library General Public License
  along with this program; if not, write to the Free Software
  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */

/* This file is  tap.c
 * EXPERIMENTAL EXPERIMENTAL EXPERIMENTAL EXPERIMENTAL EXPERIMENTAL !!!
 */


/* Compile:
 $ cc -o tap tap.c
 *
 * or, under GNU :
 $ gcc -Wall -O6 -ansi -pedantic -o tap tap.c
 *
 * inside vi:
 :set makeprg=gcc\ -Wall\ -O6\ -ansi\ -pedantic\ -o\ tap\ tap.c
 :make
 */


/* Part 1 : INITIALIZATION */

#include <stdio.h>
#include <string.h>	/* strcmp() */
#include <stdlib.h>	/* strtol()	*/

#ifndef VERSION
#define VERSION "0.8"
#endif

int main (int argc, char ** argv)
{
	unsigned show_version=0, show_help=0;
	unsigned long int i, n;	/* signed char suffices, but getc returns an int */


/* Part 2 : PARSING INPUTS */

	for (n = 1; n < argc; n++) {
		if ((strcmp (argv[n], "--usage") == 0) ||
			(strcmp (argv[n], "--help") == 0) ||
			(strcmp (argv[n], "-h") == 0))
		{
			show_help = 1;
			argv[n] = NULL;
		}
		else if (strcmp (argv[n], "--version") == 0 ||
			strcmp (argv[n], "-v") == 0)
		{
			show_version = 1;
			argv[n] = NULL;
		}
		/* Anything else starting with a '-' is an error
		 * (Numeric argument must be positive). */
		else if (argv[n][0] == '-') show_help = 1;
	}

	if (show_version)
		printf ("%s version %s \n", argv[0], VERSION);

	if (show_help) {
		printf ("\007Usage: %s [option ...] [positive integer]\n", argv[0]);
		printf ("Valid options are:\n");
		printf ("  -v --version           Output version info.\n");
		printf ("  -h --help --usage      Output this help.\n");
	}

	if (show_version || show_help)
		exit (0);


/* Part 3 : VALIDATION */

	if (n == 1)
		fprintf (stderr, "%s: Absent integer argument. Assuming 1.\n",argv[0]);
	else
		n = strtoul(argv[1],NULL,0);

	if (!(n)&&(argv[1] != '\0')) {
		fprintf (stderr, "%s: Unreadable integer arg.; Assuming 1.\n",argv[0]);
		n = 1;
	}


/* Part 4 : EXECUTION */

/*
	for (i=0;i<n;i++)
		putchar(EOF);
	while ((n=getc(stdin)) != EOF)
		putchar(n);
*/
	if (!(freopen (NULL,"r+",stdout))) /* Does work, but nothing is received. */
		fprintf (stderr, "%s: Could not reopen stdout for reading.\n",argv[0]);

	for (i=0;i<n;i++) while (((fgetc(stdout)) != EOF)&&((fgetc(stdout)) != '\f'));
	while ((n=fgetc(stdin)) != EOF) putchar(n);


/* Part 5 : FINALIZATION */

	if (fclose(stdout))
		fprintf (stderr, "%s: Could not close standard output.\n",argv[0]);
	return(0);
}

