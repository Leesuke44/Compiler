%{
#include "y.tab.h"
#include "hdr.h"
#include <math.h>
%}

%%

[ \t]	;		 /* ignore white space */

[Pp][Rr][Oo][Gg][Rr][Aa][Mm]	{ return PROGRAM; }

[Bb][Ee][Gg][Ii][Nn]	{ return START; }

[Ee][Nn][Dd]	{ return END; } 

[Dd][Ee][Cc][Ll][Aa][Rr][Ee] {	return DECLARE; }

[Aa][Ss] { return AS; }

[Ii][Nn][Tt][Ee][Gg][Ee][Rr] {	return INTEGER; }

[Ff][Ll][Oo][Aa][Tt] {	return FLOAT; }

[Ff][Oo][Rr] {return FOR;}

[Ee][Nn][Dd][Ff][Oo][Rr] {return ENDFOR; }

[Tt][Oo] {return TO; }

[Dd][Oo][Ww][Nn][Tt][Oo] {return DOWNTO; }

, { return yytext[0]; }

[A-Za-z][A-Za-z0-9]*	{	/* return symbol pointer */
		struct symtab *sp = symlook(yytext);
		
		yylval.symp = sp;
		return NAME;
	}
[0-9]+		{yylval.ival = atoi(yytext); return INUMBER;}

[0-9]+.[0-9]+	{yylval.fval = atof(yytext); return FNUMBER;}

\n	|
\;	|
\:	|
\=	|
\+	|
\-	|
\*	|
\/	|
\(	|
\)	|
\[	|
\]	return yytext[0];
%%
