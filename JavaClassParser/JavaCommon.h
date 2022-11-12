#pragma once
#ifdef _DEBUG


#define DEBUG_PRINT_ENABLED
#define __FILENAME__ (strrchr(__FILE__, '\\') ? strrchr(__FILE__, '\\') + 1 : __FILE__)


#if defined DEBUG_PRINT_ENABLED
#define DEBUG_PRINT(x) std::cout << "[ " << __FILENAME__ << " ] [ " << __LINE__ << " ] {{ "<< x << " }} "<< std::endl;
#else
#define DEBUG_PRINT(x)
#endif


#endif 

#include <iostream>
#include <fstream>
#include <string>

namespace Java
{
#define u1	std::uint8_t
#define u2	std::uint16_t
#define u4	std::uint32_t


    inline void ReadBytes(std::ifstream& file, u1& var)
    {
        u1 temp = {};
        file.read((char*)&(temp), sizeof(temp));
        var = temp;
    }

    inline void ReadBytes(std::ifstream& file, u2& var)
    {
        u2 temp = {};
        file.read((char*)&(temp), sizeof(temp));
        var = _byteswap_ushort(temp);
    }

    inline void ReadBytes(std::ifstream& file, u4& var)
    {
        u4 temp = {};
        file.read((char*)&(temp), sizeof(temp));
        var = _byteswap_ulong(temp);
    }
}