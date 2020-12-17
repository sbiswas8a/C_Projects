# C Projects
Few of the C Projects I worked on for one my classes

## Huffman Compressor
This program uses bitwise manipulation and Huffman encoding techniques for compressing ASCII text files

There are two components to this program, one for deflating (compressing) text files, and one for inflating (decompressing) compressed binary files

**Compile:** Use makefile to compile

**Usage:** Use a code file (one of the given ones or create a new one) for compressing a text file. The same code file must then be used to decompress the compressed binary file

./deflate [code-file] [infile] [outfile]

./inflate [code-file] [infile] [outfile]

***
## Text Match
Given a text file and some parameters, this program prints the lines from the file that matches the selection

**Compile:** Use makefile to compile

**Usage:** ./select -lines [start] [end] +lines [start] [end] -pat [string] +pat [string] -word [string] +word [string] [filename]

All of the parameters except the filename are optional<br>
+lines selects the lines within the given range<br>
-lines deselects the lines within the given range<br>
+pat selects lines that contain the given pattern<br>
-pat deselects lines that contain the given pattern<br>
+word selects lines that contain the given word<br>
-word deselects lines that contain the given word<br>
[filename] is the name of the text file being used

*Word is defined as a string delimited by punctuation or whitespace / Pattern is defined as a simple substring*
*** 
## Connect4
Console version of the Connect Four game

&emsp;**Compile:** Use makefile to compile <br>&emsp;
    **Run:** ./connect4 <br>&emsp;
  **Usage:** [number of rows] [number of columns]<br>&emsp;
         Red has first turn, Yellow goes next<br>&emsp;
         Input the column number to add disc at every turn<br>&emsp;
         The board is printed to standard output when a player wins or there is a draw
