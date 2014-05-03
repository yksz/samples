%{
#include <stdio.h>
#include <ctype.h>

int yylex();
int yyerror(const char* s);
%}
%token '\n'
%token NUMBER
%token '(' ')'
%left '+' '-'
%left '*' '/'

%%

input
    : line
    | input line
    ;

line
    : '\n'
    | expression '\n' { printf(">> %d\n", $1); }
    | error '\n' { yyclearin; yyerrok; }
    ;

expression
    : term
    | expression '+' expression { $$ = $1 + $3; }
    | expression '-' expression { $$ = $1 - $3; }
    | expression '*' expression { $$ = $1 * $3; }
    | expression '/' expression { $$ = $1 / $3; }
    ;

term
    : NUMBER
    | '(' expression ')' { $$ = $2; }
    ;

%%

int yylex(void)
{
    int c;
    do {
        c = fgetc(stdin);
    } while (c == ' ' || c == '\t');
    if (c == EOF) {
        return 0;
    }
    if (isdigit(c)) {
        ungetc(c, stdin);
        fscanf(stdin, "%d", &yylval);
        return NUMBER;
    }
    return c;
}

int yyerror(const char* s)
{
    fprintf(stderr, "ERROR: %s\n", s);
    return 0;
}

int main()
{
    return yyparse();
}
