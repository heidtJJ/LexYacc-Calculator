%{
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "tree.h"
#include "y.tab.h"

extern int yylex();
extern int yyerror(char*);
%}

%union {
    /* Attribute channel (with scanner) */
    int ival;   /* attribute for NUM */

    /* semantic attributes */
    tree_t* tval; /* attribute for syntax trees */
}

%token <ival> NUM

%left '+'
%left '-'
%left '*'
%left '/'

%type <tval> expr

%%

start: expr '\n'    
    { 
        tree_print($1);
        fprintf(stderr, "\n\nValue = %d\n", tree_eval($1)); 
        exit(0);// Safely exit
    }
    ;

expr: expr '+' expr { $$ = mktree('+', $1, $3); }
    | expr '-' expr { $$ = mktree('-', $1, $3); }
    | expr '*' expr { $$ = mktree('*', $1, $3); }
    | expr '/' expr { $$ = mktree('/', $1, $3); }
    | '(' expr ')'  { $$ = $2; }
    | NUM           { $$ = mktree(NUM, NULL, NULL); $$->attribute = $1; }
    ;

%%

int main(){
    yyparse();
}
