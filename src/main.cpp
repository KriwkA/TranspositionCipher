#include "transpositioncipher.h"
#include <exception>
#include <iostream>

#include "file.h"

int main(int argc, char *argv[])
{
    AbstractCipher* chiper = new TranspositionCipher();

    try
    {
        chiper->encrypt("asd", "in.jpg", "out.jpg");
        chiper->decrypt("asd", "out.jpg", "dec.jpg");
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }

    delete chiper;
    return 0;
}
