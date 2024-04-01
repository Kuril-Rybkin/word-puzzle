# word-puzzle
## Task specification

The task is to develop a program that solves a puzzle similar to the wordsearch puzzle.

We assume a square field of characters. The field is entered row-by-row, our program reads it from the standard input. The task is to find the longest repeating word (words) in the field. A word may start at an arbitrary position in the field, moreover, the word may be read in any of the 8 directions (left-to-right, right-to-left, top-bottom, bottom-up, and all four diagonal directions). A word is considered repeating if there exist at least two different ways to read the word. In particular:

- there is only one way to read words of length 1 character. Thus, a word of length 1 character is repeated only if the character appears at least twice in the input field
- longer words are repeated if there are two (or more) different places where the word appears, or the word can be read from the same position in different directions
- if a word is a palindrome of length 2 (or more) characters, the word is inherently repeated

The output of the program is a list of words that can be found at least twice in the field, moreover, are the longest such words. The output lists each such word just once (no duplicates in the output list). The order of words in the output list is not specified, your program may choose any arbitrary order.

The program must validate input data. If the input is invalid, the program must detect it, it shall output an error message, and terminate. If displayed, the error message must be sent to the standard output (do not send it to the error output) and the error message must be terminated by a newline (\n). The following is considered invalid:

the input field is not a square,
the input is empty (0 by 0).

## Complexity

In order to pass the necessary speed tests, this program has a complexity of O(n^3 log n)

## Sample program output

```
Puzzle:
Hi, o
Bye  
HeLlo
+-*/>
Help!

Longest repeating words:
, o
H+H
HBH
e-e
o ,
o o
```
