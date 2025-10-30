# PA2 Demo

This demo implements the example of expanding the non-terminal `<AddExpr>`. This code will not work on any test case, but can still be compiled.

Reminders:
`g++ lex.cpp parser.cpp prog2.cpp -o prog2`

```
<AddExpr> ::= <MultExpr> { ( + | - | . ) <MultExpr> }
```