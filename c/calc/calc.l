%{
#include <stdio.h>
#include "y.tab.h"

extern int yylval;

int yywrap(void) {
    return 1;
}
%}

%%

^exit$ exit(0);
"+" return ADD;
"-" return SUB;
"*" return MUL;
"/" return DIV;
"(" return LP;
")" return RP;
[0-9]+ {
    sscanf(yytext, "%d", &yylval);
    return NUMBER;
}
\n|\r|\r\n return LF;
[ \t] ;
. ;

%%
