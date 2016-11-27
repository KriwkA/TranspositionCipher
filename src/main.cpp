#include "transpositioncipher.h"
#include <exception>
#include <iostream>

#include "file.h"

#include <Windows.h>

int main(int argc, char *argv[])
{
    AbstractCipher* chiper = new TranspositionCipher();

    try
    {
        uint64_t start = GetTickCount();
        chiper->encrypt("asd", "in.bmp", "out.bmp");
        uint64_t end = GetTickCount();

        std::cout << "encrypt time: " << end - start << std::endl;
        start = end;

        chiper->decrypt("asd", "out.bmp", "dec.bmp");
        end = GetTickCount64();

        std::cout << "decrypt time: " << end - start << std::endl;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }

    delete chiper;
    return 0;
}
