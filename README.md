# tpipe

Duplicate standard input and/or standard output

# Notes

tpipe was written by Juanjo Garcia in 2003. This source is from the last stable release in 2004. The URL listed in [the software directory](https://directory.fsf.org/wiki/Tpipe) 404s; luckily I was able to recover the source from the Funtoo cache. This repo is an unmodified mirror of v1.6.

I discovered tpipe today looking for a tool to solve this exactly problem and simultaneously discovered that the source is difficult to find.
It works unmodified on modern Linux distros.

# Installation

```
gcc -Wall -O6 -ansi -pedantic -o tpipe tpipe.c
cp tpipe /usr/bin/tpipe
cp tpipe.1 /usr/share/man/man1/tpipe.1
```

# Licence

GPLv2

# Original README.txt

/* PRELIMINARY NOTE
Windows users: This software is only for Unix-like systems or,
more specifically, it will only work on operating systems that
have pipes and the popen-pclose function calls.

Look into the accompanying INSTALL file for instructions on
how to install this software.


tpipe --  Command plumbing.

tpipe  -  duplicate standard input and/or standard ouput

tpipe	originally written by David B Rosen <rosen@bucasb.bu.edu>
in 1990 for HP-UX 10.10

Completely rewritten from scratch under the terms of the GNU
General Public License by Juanjo Garcia <juanjo@eurogaran.com>
November 2003

Unlike other implementations, this one adheres strictly to
operative system standards in the sense that there is no more
than one standard output at any given moment.

Error: Reports error in case the subpipe could not be opened.
Beware this is different from unsuccesful execution of the subpipe.


 Use. Examples :

 1- Duplicate standard output by redirecting it to a file through a pipe:
    $ command1 | tpipe "pipeline > file" | command2

    command1 --> tpipe -----------> command2
                  \
                   --> pipeline --> file

 2- Reinject pipe output into standard output by simply NOT redirecting:
    $ pipeline1 | tpipe "pipeline2" | pipeline3

      pipeline1 --------------------> pipeline3
                  \                ^
                   \               |
                    --> pipeline2 -

 Note: UNDETERMINED final result, but it is assumed this is what you want:
Depending on which is executed faster, pipeline3 can collect pipeline2 output
either before or after receiving that of pipeline1.

tpipe does its best to balance both outputs, therefore maximizing
in fact the a-priori chance of receiving them interspersed.

 3- Inject into pipeline data from an independent origin:
    $ cat wordlist1 | tpipe "cat dictionary2" >> passwords

      cat wordlist1 ---------------------------> passwords
                                            /
                        cat dictionary2 ---

Same comments made for the previous example apply here, so you know 
all outputs will in the end be collected, only you don't know beforehand
in which order they will arrive.

Again, it is presumed that you don't care or even that it is precisely
what you want, or you would rather be using more traditional things like:
    $ cat wordlist1 >> passwords;  cat dictionary2 >> passwords

 4- Multiple instances:
    $ cat textfile | tpipe "echo world" | tpipe 'echo hello' | ...

      tpipe '...'--
                   |
                   v
      tpipe '...'--
                   |
                   v
  command1 -------> command2
                   ^
                   |
      tpipe '...'--
                   ^
                   |
      tpipe '...'--

 5- Nesting:
    $ cat textfile | tpipe "echo world | tpipe 'echo hello'" | ...
which is subtly different from the previous example.

 6- No operation:
    $ ... | tpipe '' | ...
which is tantamount to    $ ... | ...

 7- Environment variables as shell macros:
    $ PIPE1='cat > textfile'; PIPE2='sort | uniq'
    $ ... | tpipe $PIPE1 | eval $PIPE2 | ...
would be equivalent to:
    $ ... | tpipe 'cat > textfile' | sort | uniq | ...
which would in turn be equivalent to:
    $ ... | tee textfile | sort | uniq | ...

*/

