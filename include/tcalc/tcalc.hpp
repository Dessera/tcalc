#pragma once

// variable : IDENTIFIER

// call : IDENTIFIER LPAREN (expr (COMMA expr)*)? RPAREN

// factor : PLUS factor |
//         MINUS factor |
//         call |
//         LPAREN expr RPAREN |
//         NUMBER |
//         variable

// term : factor ((MUL | DIV) factor)

// expr : term ((PLUS | MINUS) term)