#include <cstdio>
#include <cstdlib>
#include <cstring>
extern "C"
{
#include "sql.tab.h"
#include "sql-parser.h"
    extern int yydebug;
    extern int yylex_init_extra (void* user_defined,yyscan_t* scanner);
    extern void yyset_in  (FILE * in_str ,yyscan_t yyscanner );
}
int yydebug;
int main(int ac,char** av)
{
FILE *in_f;
  struct psql_state pstate;

  if(ac > 1 && !strcmp(av[1], "-d")) {
    yydebug = 1; ac--; av++;
  }

  memset(&pstate, 0, sizeof(pstate));
  if (yylex_init_extra(&pstate, &pstate.scanner))
  	return 1;

  if(ac > 1) {
    if((in_f = fopen(av[1], "r")) == NULL) {
      perror(av[1]);
      exit(1);
    }
    filename = av[1];
  } else {
    filename = "(stdin)";
    in_f = stdin;
  }

  yyset_in(in_f, pstate.scanner);

  if(!yyparse(pstate.scanner, &pstate)) {
    printf("SQL parse worked\n");
    return 0;
  } else {
    printf("SQL parse failed\n");
    return 1;
  }
}
