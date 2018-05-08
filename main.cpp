#include"beforegame.h"
#include <stdlib.h>
#include <string.h>

int main(int argc, const char *argv[])
{
    char *chess = (char *)malloc(sizeof(char) * 256 );

    printUI(chess);

	return 0;
}
