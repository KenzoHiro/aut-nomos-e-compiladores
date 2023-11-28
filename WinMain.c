#include <stdio.h>
#include "parser.h"

int main() {
	int x,y;
    const char* input = "program Test; begin var x, y: integer;  x := 5; y := x + 10; end.";
    
    initParser(input);
    parseProgram();
    

    return 0;
}
