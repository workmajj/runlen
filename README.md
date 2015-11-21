runlen
======

Quick practice writing a run-length encoder/decoder in C

Contact
-------

John J. Workman ([@workmajj](https://twitter.com/workmajj))

I worked on this software during my time as a [Recurse Center](https://www.recurse.com/) facilitator. If you'd like to join a warm community of programmers dedicated to self-improvement, you should consider applying. :-)

Description
-----------

This pair of programs generates files with runs of capital letters (`rungen`), then encodes/decodes them (`runlen`) using a simple [run-length encoding](https://en.wikipedia.org/wiki/Run-length_encoding) scheme. The code is robust in some ways (e.g., will skip newlines and other irrelevant chars) but mostly meant as a quick C exercise.

The RLE scheme used places multiplier numbers before their associated letters, and copies single letters verbatim (since, for example, `1X1Y1Z` takes more room than just `XYZ`).

Install & Usage
---------------

1. In the project directory, build the two programs from source:

        $ make

2. Next, use `rungen` to create a file of random capital letter runs:

        $ ./rungen txt/original.txt

3. Now use `runlen encode` to run-length encode that original file:

        $ ./runlen encode txt/original.txt txt/encoded.txt

4. And `runlen decode` to decode that compressed version:

        $ ./runlen encode txt/encoded.txt txt/decoded.txt

5. Finally, use `diff` to confirm that the original and decoded files match:

        $ diff txt/original.txt txt/decoded.txt

License
-------

This code is in the public domain.
