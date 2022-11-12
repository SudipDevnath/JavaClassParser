#pragma once
#include<exception>
#include<string>
#include<iostream>
#include<stdlib.h>

namespace Java
{
	class JavaException : public std::exception
	{
	public:

		JavaException(std::string msg, std::string file, int line)
		{
			std::cout << "JavaException @["+msg+"] @" << file << " @" << line << std::endl;
			std::exit(-1);
		}

		JavaException() = delete;
	private:

	};
}