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

/* This file is  tpipe.c
 *
 * Copies its standard input to both its standard output and
 * as input to another pipe specified as string argument.
 * Both output data streams can be made confluent later.
 */


/* Compile:
 * $ cc -o tpipe tpipe.c
 * or, under GNU :
 * $ gcc -Wall -O6 -ansi -pedantic -o tpipe tpipe.c
 *
 * inside vi:
 * :set makeprg=gcc\ -Wall\ -O6\ -ansi\ -pedantic\ -o\ tpipe\ tpipe.c
 * :make
 */


/* Part 1 : INITIALIZATION */

#include <stdio.h>
#include <string.h>	/* strcmp() */

#ifndef VERSION
#define VERSION "1.6"
#endif

int main (int argc, char ** argv)
{
	unsigned show_version=0, show_help=0;
	int byte;	/* signed char suffices, but getc returns an int */
	FILE *stream;
	extern FILE *popen(); extern int pclose();


/* Part 2 : PARSING INPUTS */

	for (byte = 1; byte < argc; byte++) {
		if ((strcmp (argv[byte], "--usage") == 0) ||
			(strcmp (argv[byte], "--help") == 0) ||
			(strcmp (argv[byte], "-h") == 0))
		{
			show_help = 1;
			argv[byte] = NULL;
		}
		else if (strcmp (argv[byte], "--version") == 0 ||
			strcmp (argv[byte], "-v") == 0)
		{
			show_version = 1;
			argv[byte] = NULL;
		}
	/* Anything else starting with a '-' is an error. */
		else if (argv[byte][0] == '-') show_help = 1;
	}

	if (show_version)
		printf ("%s version %s \n", argv[0], VERSION);

	if (show_help) {
		printf ("\007Usage: %s [option ...] [string]\n", argv[0]);
		printf ("Valid options are:\n");
		printf ("  -v --version           Output version info.\n");
		printf ("  -h --help --usage      Output this help.\n");
	}

	if (show_version || show_help)
		exit (0);


/* Part 3 : VALIDATION */

	if (--byte == 0) {
		fprintf(stderr, "%s: No string argument specified.\n",argv[0]);
		byte=1;
	}

	if (!(stream = popen(argv[byte],"w"))) {
		fprintf(stderr, "%s: Could not open subpipe for writing.\n",argv[0]);
		while ((byte=getchar())!=EOF) putchar(byte); /* so stdout is assured */
		fclose(stdout);
		exit (1);
	}


/* Part 4 : EXECUTION */

	while ((byte=getc(stdin)) != EOF) {
		putc(byte,stdout);	/* to stdout */
		putc(byte,stream);	/* to pipe */
	}


/* Part 5 : FINALIZATION */

	if (fclose(stdout)) { /* Very IMPORTANT to close standard output first.
	Otherwise, when subpipe output is not redirected to a file we end up having
	SIMULTANEOUSLY opened two or even more different stdouts with equal privi-
	leges, breaking op. system assumptions and causing unstable behavior. */
		fprintf(stderr, "%s: Could not close standard output.\n",argv[0]);
	}
	if (pclose(stream))
		fprintf(stderr, "%s: Could not close subpipe.\n",argv[0]);
	return(0);
}

