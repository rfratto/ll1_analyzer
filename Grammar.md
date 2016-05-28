# Grammar

This document outlines the format of an ll1_analyzer grammar file.
Traditionally, grammar files are packaged with the .y extension. ll1_analyzer
doesn't expect any specific extension to be tied to a file, but an extension
of .lly will be used for syntax highlighting.

## Comments

Comments may be placed in your grammar file using the familiar `//` C-style
comments. `/*` and `*/` may be used for block comments. Note that unlike C,
multi-line comments may be nested in `.lly` files.

## Terminals

Terminals must be declared in the file with on a line prefixed with `%token`.
Any number of terminals can then be declared on that line, delimited by spaces:

```
%token TERMINALA TERMINALB TERMINALC
```

Terminals may be alphanumeric and contain underscores, however the first
character in the terminal must always be an alphabetical letter.

Terminals must be declared at the top of your file before your productions.
Some constants also work as terminals: any numeric value or a string wrapped
in double quotes will be interpreted as a terminal.

## Production Rules

A grammar production can be defined with the following format:

```
non_terminal : /* body */ ;
```

Production rules must end in a semi-colon, although it doesn't have to be on
the same line as the production rule, as whitespace is ignored.

The body of the production may be a string of non-termials and terminals
separated by spaces. Epsilon can be inserted by using `%epsilon`. Empty rules
are not permitted and `%epsilon` must be used to represent the empty string.

Production rules with the same left side can be chained together by using `|`.
A `|` is inserted in place of the semi-colon between two bodies:

```
non_terminal : TERMINALA | TERMINALB | TERMINALC ;
```

## Start Production

The starting non-terminal is simply the first production rule in your grammar.

## Example

Here's an simple example grammar of a calculator:

```
// Math operations
%token PLUS TIMES
%token NUMBER

start: E

E: T + E | T ;
T: F * T | F ;
F: "(" E ")" | NUMBER ;
```

This grammar derives strings like `92 + 1 * 6` and `(3 + 5) * 2`.
