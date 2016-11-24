#include "transpositioncipher.h"
#include <exception>
#include <iostream>

int main(int argc, char *argv[])
{
    AbstractCipher* chiper = new TranspositionCipher();

    try
    {
        chiper->encrypt("asd", "in.txt", "out.txt");
        chiper->decrypt("asd", "out.txt", "dec.txt");
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }

    delete chiper;
    return 0;
}
