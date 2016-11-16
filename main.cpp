#include <cstdio>
#include "cryptkey.h"



int main(int argc, char *argv[])
{

    CryptKey key(25, "asdasdasdfafasdasdffas");

    for(int i = 0; i < key.getKeyLength(); ++i)
    {
        printf("%d ", key.getRowKey()[i]);
    }

    printf("\n");

    for(int i = 0; i < key.getKeyLength(); ++i)
    {
        printf("%d ", key.getColKey()[i]);
    }

    printf("\n");

    return 0;
}
