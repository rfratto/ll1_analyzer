# ll1_analyzer

ll1_analyzer is a program that accepts a .y BNF bison-like grammar file and
determines if the grammar is LL(1) or not.

It will detect instances of:
- Left recursion (done)
- FIRST/FIRST conflicts (not done)
- FIRST/FOLLOW conflicts (not done)

## Using

`$ ll1_analyzer [grammar file]`

## Grammar Definition

ll1_analyzer makes some assumptions about the input grammar:

- All nonterminals are all lowercase and start with an alphabetic character,
with all following characters being either alphanumeric, an underscore, or a
single quote ( ' ) to define a prime.
- All terminals are all uppercase and start with an alphabetic character,
with all following character being alphanumeric or an underscore.
- Terminals can also be defined as constant strings (e.g., `"+"`).
- A production rule is defined as follows, with the rules terminated with
a semicolon:
```
	nonterminal: rule_1 | rule_2 | ... | rule_n;
```
- The first production rule defined is always treated as the start nonterminal.
- `$` is used as epsilon.
- Whitespace is ignored.

## License

```
The MIT License (MIT)

Copyright (c) 2015 Robert Fratto

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
```
