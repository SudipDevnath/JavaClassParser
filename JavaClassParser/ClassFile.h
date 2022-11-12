#pragma once
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <memory>

#include "JavaCommon.h"
#include "JavaException.h"

namespace Java
{


	class ClassFile
	{
        /*
		ClassFile {
		u4             magic;
		u2             minor_version;
		u2             major_version;
		u2             constant_pool_count;
		cp_info        constant_pool[constant_pool_count-1];
		u2             access_flags;
		u2             this_class;
		u2             super_class;
		u2             interfaces_count;
		u2             interfaces[interfaces_count];
		u2             fields_count;
		field_info     fields[fields_count];
		u2             methods_count;
		method_info    methods[methods_count];
		u2             attributes_count;
		attribute_info attributes[attributes_count];
		}
		*/

	private:
		class cp_info
		{
		public:
			virtual std::string print() = 0;
		private:
		};

		class CONSTANT_Class_info : cp_info {
		public:
			CONSTANT_Class_info(std::ifstream& infile)
			{
				ReadBytes(infile, name_index);
			}
			std::string print()
			{
				return std::to_string(name_index);
			}
		private:
			u2 name_index;
		};

		class CONSTANT_Fieldref_info : cp_info {
		public:
			CONSTANT_Fieldref_info(std::ifstream& infile)
			{
				ReadBytes(infile, class_index);
				ReadBytes(infile, name_and_type_index);
			}
			std::string print()
			{
				return std::to_string(class_index)+"."+ std::to_string(name_and_type_index);
			}
		private:
			u2 class_index;
			u2 name_and_type_index;
		};

		class CONSTANT_Methodref_info : cp_info {
		public:
			CONSTANT_Methodref_info(std::ifstream& infile)
			{
				ReadBytes(infile, class_index);
				ReadBytes(infile, name_and_type_index);
			}
			std::string print()
			{
				return std::to_string(class_index) + "." + std::to_string(name_and_type_index);
			}
		private:
			u2 class_index;
			u2 name_and_type_index;
		};

		class CONSTANT_InterfaceMethodref_info : cp_info {
		public:
			CONSTANT_InterfaceMethodref_info(std::ifstream& infile)
			{
				ReadBytes(infile, class_index);
				ReadBytes(infile, name_and_type_index);
			}
			std::string print()
			{
				return std::to_string(class_index) + "." + std::to_string(name_and_type_index);
			}
		private:
			u2 class_index;
			u2 name_and_type_index;
		};

		class CONSTANT_String_info : cp_info {
		public:
			CONSTANT_String_info(std::ifstream& infile)
			{
				ReadBytes(infile, string_index);
			}
			std::string print()
			{
				return std::to_string(string_index);
			}
		private:
			u2 string_index;
		};

		class CONSTANT_Integer_info : cp_info {
		public:
			CONSTANT_Integer_info(std::ifstream& infile)
			{
				ReadBytes(infile, bytes);
			}
			std::string print()
			{
				return std::to_string(bytes);
			}
		private:
			u4 bytes;
		};

		class CONSTANT_Float_info : cp_info {
		public:
			CONSTANT_Float_info(std::ifstream& infile)
			{
				ReadBytes(infile, bytes);
			}
			std::string print()
			{
				return std::to_string(bytes);
			}
		private:
			u4 bytes;
		};

		class CONSTANT_Long_info : cp_info {
		public:
			CONSTANT_Long_info(std::ifstream& infile)
			{
				ReadBytes(infile, high_bytes);
				ReadBytes(infile, low_bytes);
			}
			std::string print()
			{
				long l = (high_bytes << 32) | low_bytes;
				return std::to_string(l);
			}
		private:
			u4 high_bytes;
			u4 low_bytes;
		};

		class CONSTANT_Double_info : cp_info {
		public:
			CONSTANT_Double_info(std::ifstream& infile)
			{
				ReadBytes(infile, high_bytes);
				ReadBytes(infile, low_bytes);
			}
			std::string print()
			{
				long l = (high_bytes << 32) | low_bytes;
				return std::to_string(l);
			}
		private:
			u4 high_bytes;
			u4 low_bytes;
		};

		class CONSTANT_NameAndType_info : cp_info {
		public:
			CONSTANT_NameAndType_info(std::ifstream& infile)
			{
				ReadBytes(infile, name_index);
				ReadBytes(infile, descriptor_index);
			}
			std::string print()
			{
				return std::to_string(name_index) + "." + std::to_string(descriptor_index);
			}
		private:
			u2 name_index;
			u2 descriptor_index;
		};

		class CONSTANT_Utf8_info : cp_info {
		public:
			CONSTANT_Utf8_info(std::ifstream& infile)
			{
				u2 length;
				ReadBytes(infile, length);
				this->bytes.reserve(length);

				for (u2 i = 0; i < length; i++)
				{
					ReadBytes(infile, this->bytes[i]);	
				}
			}
			std::string print()
			{
				return std::string(bytes.begin(), bytes.end());
			}
		private:
			std::vector<u1> bytes;
		};

		class CONSTANT_MethodHandle_info : cp_info {
		public:
			CONSTANT_MethodHandle_info(std::ifstream& infile)
			{
				ReadBytes(infile, reference_kind);
				ReadBytes(infile, reference_index);
			}
			std::string print()
			{
				return std::to_string(reference_kind) + "." + std::to_string(reference_index);
			}
		private:
			u1 reference_kind;
			u2 reference_index;
		};

		class CONSTANT_MethodType_info : cp_info {
		public:
			CONSTANT_MethodType_info(std::ifstream& infile)
			{
				ReadBytes(infile, descriptor_index);
			}
			std::string print()
			{
				return std::to_string(descriptor_index);
			}
		private:
			u2 descriptor_index;
		};

		class CONSTANT_InvokeDynamic_info : cp_info {
		public:
			CONSTANT_InvokeDynamic_info(std::ifstream& infile)
			{
				ReadBytes(infile, bootstrap_method_attr_index);
				ReadBytes(infile, name_and_type_index);
			}
			std::string print()
			{
				return std::to_string(bootstrap_method_attr_index) + "." + std::to_string(name_and_type_index);
			}
		private:
			u2 bootstrap_method_attr_index;
			u2 name_and_type_index;
		};




		std::vector<std::shared_ptr<cp_info>> constant_pool;

	public:

		ClassFile(std::string filepath)
		{
			std::ifstream infile;
			infile.open(filepath, std::ios::binary);
			if (!infile.is_open()) { throw JavaException("Unable to Read File : " + filepath, __FILENAME__, __LINE__); }

			u4 magic;
			u2 minor_version;
			u2 major_version;
			u2 constant_pool_count;

			ReadBytes(infile, magic);
			ReadBytes(infile, minor_version);
			ReadBytes(infile, major_version);
			ReadBytes(infile, constant_pool_count);

			if (magic != 3405691582) { throw JavaException("Invalid class file : " + filepath, __FILENAME__, __LINE__); }
			
			std::string MajorVersion = "";
			switch (major_version)
			{
			case 0x3E: MajorVersion = "Java SE 18"; break;
			case 0x3D: MajorVersion = "Java SE 17"; break;
			case 0x3C: MajorVersion = "Java SE 16"; break;
			case 0x3B: MajorVersion = "Java SE 15"; break;
			case 0x3A: MajorVersion = "Java SE 14"; break;
			case 0x39: MajorVersion = "Java SE 13"; break;
			case 0x38: MajorVersion = "Java SE 12"; break;
			case 0x37: MajorVersion = "Java SE 11"; break;
			case 0x36: MajorVersion = "Java SE 10"; break;
			case 0x35: MajorVersion = "Java SE 9"; break;
			case 0x34: MajorVersion = "Java SE 8"; break;
			case 0x33: MajorVersion = "Java SE 7"; break;
			case 0x32: MajorVersion = "Java SE 6.0"; break;
			case 0x31: MajorVersion = "Java SE 5.0"; break;
			case 0x30: MajorVersion = "JDK 1.4"; break;
			case 0x2F: MajorVersion = "JDK 1.3"; break;
			case 0x2E: MajorVersion = "JDK 1.2"; break;
			case 0x2D: MajorVersion = "JDK 1.1"; break;
			default: throw JavaException("Unimplemented class version : "+ std::to_string(major_version)+"@" + filepath, __FILENAME__, __LINE__);
			}

			ParseConstantPool(infile, constant_pool_count);



			// u2 access_flags;
			// u2 this_class;
			// u2 super_class;
			// u2 interfaces_count;
			// 
			// ReadBytes(infile, access_flags);
			// ReadBytes(infile, this_class);
			// ReadBytes(infile, super_class);
			// ReadBytes(infile, interfaces_count);
			// 
			// std::cout << "access_flags"		<< access_flags << std::endl;
			// std::cout << "this_class"		<< this_class << std::endl;
			// std::cout << "super_class"		<< super_class << std::endl;
			// std::cout << "interfaces_count"	<< interfaces_count << std::endl;




#ifdef _DEBUG
			std::ostringstream oss;
			oss << std::hex << std::uppercase << magic;
			std::cout << filepath << " @" << oss.str() << "[" << MajorVersion << "." << minor_version << "]" << std::endl;
#endif

			infile.close();
		}

	private:

		void ParseConstantPool(const std::ifstream& infile, u2 constant_pool_count)
		{
			/*
			CONSTANT_Class 	7
			CONSTANT_Fieldref 	9
			CONSTANT_Methodref 	10
			CONSTANT_InterfaceMethodref 	11
			CONSTANT_String 	8
			CONSTANT_Integer 	3
			CONSTANT_Float 	4
			CONSTANT_Long 	5
			CONSTANT_Double 	6
			CONSTANT_NameAndType 	12
			CONSTANT_Utf8 	1
			CONSTANT_MethodHandle 	15
			CONSTANT_MethodType 	16
			CONSTANT_InvokeDynamic 	18
			*/

			this->constant_pool.reserve(constant_pool_count-1);
			for (u2 i =  1; i < constant_pool_count; i++)
			{
				
			}

		}
	};
}