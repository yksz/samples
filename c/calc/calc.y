%{
#include <stdio.h>
%}
%token LF
%token NUMBER
%token LP RP
%left ADD SUB
%left MUL DIV

%%

input
    : line
    | input line
    ;

line
    : LF
    | expression LF { printf(">> %d\n", $1); }
    | error LF { yyclearin; yyerrok; }
    ;

expression
    : term
    | expression ADD expression { $$ = $1 + $3; }
    | expression SUB expression { $$ = $1 - $3; }
    | expression MUL expression { $$ = $1 * $3; }
    | expression DIV expression { $$ = $1 / $3; }
    ;

term
    : NUMBER
    | LP expression RP { $$ = $2; }
    ;

%%

int yyerror(const char *s) {
    fprintf(stderr, "ERROR: %s\n", s);
    return 0;
}

int main() {
    return yyparse();
}
