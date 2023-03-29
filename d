[1mdiff --git a/asembler.c b/asembler.c[m
[1mindex b935189..59eaba2 100644[m
[1m--- a/asembler.c[m
[1m+++ b/asembler.c[m
[36m@@ -72,12 +72,6 @@[m [mint main(int argc, char *argv[])[m
   return 1;[m
 }[m
 /*to do- valgrind*/[m
[31m-/*to do - add more error finding*/[m
 /*to do -decide if extern and entry stay*/[m
 /*to do- make sure they print to file*/[m
[31m-/*go through everything correctly*/[m
[31m-/*to do - what if label in secondpass doesnt exist??*/[m
[31m-/*to do- fix entry and external*/[m
[31m-/*to do- fix comments and such*/[m
[31m-/*to do- make sure that dump symbols to main file dumps only data/string*[m
[31m-/*to do- make sure that we post correct file names*/[m
\ No newline at end of file[m
[32m+[m[32m/*go through everything correctly*/[m
\ No newline at end of file[m
[1mdiff --git a/helpers.c b/helpers.c[m
[1mindex ebd6fe6..b2a5281 100644[m
[1m--- a/helpers.c[m
[1m+++ b/helpers.c[m
[36m@@ -618,7 +618,6 @@[m [mvoid calculateOperatorsBinaryAndPrint(char *oper1, char *oper2, int adTypeOper1,[m
             break;[m
 [m
         case 1: /*label*/[m
[31m-        [m
             if (existInSymbolTable(oper1) != -1 && symbolTypeFromTable(oper1, sym_list) == EXTERN)[m
             {[m
                 /*oper1+E(01)*/[m
