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


		/*****************************************************************************************************************************************************************************/

		class cp_info
		{
		public:
			virtual std::string to_string() = 0;
		private:
		};

		class CONSTANT_Class_info :public cp_info {
		public:
			CONSTANT_Class_info() = delete;
			CONSTANT_Class_info(std::ifstream& infile)
			{
				ReadBytes(infile, name_index);
			}
			std::string to_string() override
			{
				return std::to_string(name_index);
			}
		private:
			u2 name_index;
		};

		class CONSTANT_Fieldref_info :public cp_info {
		public:
			CONSTANT_Fieldref_info() = delete;

			CONSTANT_Fieldref_info(std::ifstream& infile)
			{
				ReadBytes(infile, class_index);
				ReadBytes(infile, name_and_type_index);
			}
			std::string to_string() override
			{
				return std::to_string(class_index)+"."+ std::to_string(name_and_type_index);
			}
		private:
			u2 class_index;
			u2 name_and_type_index;
		};

		class CONSTANT_Methodref_info :public cp_info {
		public:
			CONSTANT_Methodref_info() = delete;

			CONSTANT_Methodref_info(std::ifstream& infile)
			{
				ReadBytes(infile, class_index);
				ReadBytes(infile, name_and_type_index);
			}
			std::string to_string() override
			{
				return std::to_string(class_index) + "." + std::to_string(name_and_type_index);
			}
		private:
			u2 class_index;
			u2 name_and_type_index;
		};

		class CONSTANT_InterfaceMethodref_info :public cp_info {
		public:
			CONSTANT_InterfaceMethodref_info() = delete;

			CONSTANT_InterfaceMethodref_info(std::ifstream& infile)
			{
				ReadBytes(infile, class_index);
				ReadBytes(infile, name_and_type_index);
			}
			std::string to_string() override
			{
				return std::to_string(class_index) + "." + std::to_string(name_and_type_index);
			}
		private:
			u2 class_index;
			u2 name_and_type_index;
		};

		class CONSTANT_String_info :public cp_info {
		public:
			CONSTANT_String_info() = delete;

			CONSTANT_String_info(std::ifstream& infile)
			{
				ReadBytes(infile, string_index);
			}
			std::string to_string() override
			{
				return std::to_string(string_index);
			}
		private:
			u2 string_index;
		};

		class CONSTANT_Integer_info :public cp_info {
		public:
			CONSTANT_Integer_info() = delete;

			CONSTANT_Integer_info(std::ifstream& infile)
			{
				ReadBytes(infile, bytes);
			}
			std::string to_string() override
			{
				return std::to_string(bytes);
			}
		private:
			u4 bytes;
		};

		class CONSTANT_Float_info :public cp_info {
		public:
			CONSTANT_Float_info() = delete;

			CONSTANT_Float_info(std::ifstream& infile)
			{
				ReadBytes(infile, bytes);
			}
			std::string to_string() override
			{
				return std::to_string(bytes);
			}
		private:
			u4 bytes;
		};

		class CONSTANT_Long_info :public cp_info {
		public:
			CONSTANT_Long_info() = delete;

			CONSTANT_Long_info(std::ifstream& infile)
			{
				ReadBytes(infile, high_bytes);
				ReadBytes(infile, low_bytes);
			}
			std::string to_string() override
			{
				long l = (high_bytes << 32) | low_bytes;
				return std::to_string(l);
			}
		private:
			u4 high_bytes;
			u4 low_bytes;
		};

		class CONSTANT_Double_info :public cp_info {
		public:
			CONSTANT_Double_info() = delete;

			CONSTANT_Double_info(std::ifstream& infile)
			{
				ReadBytes(infile, high_bytes);
				ReadBytes(infile, low_bytes);
			}
			std::string to_string() override
			{
				long l = (high_bytes << 32) | low_bytes;
				return std::to_string(l);
			}
		private:
			u4 high_bytes;
			u4 low_bytes;
		};

		class CONSTANT_NameAndType_info :public cp_info {
		public:
			CONSTANT_NameAndType_info() = delete;

			CONSTANT_NameAndType_info(std::ifstream& infile)
			{
				ReadBytes(infile, name_index);
				ReadBytes(infile, descriptor_index);
			}
			std::string to_string() override
			{
				return std::to_string(name_index) + "." + std::to_string(descriptor_index);
			}
		private:
			u2 name_index;
			u2 descriptor_index;
		};

		class CONSTANT_Utf8_info :public cp_info {
		public:
			CONSTANT_Utf8_info() = delete;

			CONSTANT_Utf8_info(std::ifstream& infile)
			{
				u2 length;
				ReadBytes(infile, length);
				this->bytes.reserve(length);

				for (u2 i = 0; i < length; i++)
				{
					u1 temp = {};
					ReadBytes(infile, temp);
					bytes.push_back(temp);
				}
			}
			std::string to_string() override
			{
				return std::string(bytes.begin(), bytes.end());
			}
		private:
			std::vector<u1> bytes;
		};

		class CONSTANT_MethodHandle_info :public cp_info {
		public:
			CONSTANT_MethodHandle_info() = delete;

			CONSTANT_MethodHandle_info(std::ifstream& infile)
			{
				ReadBytes(infile, reference_kind);
				ReadBytes(infile, reference_index);
			}
			std::string to_string() override
			{
				return std::to_string(reference_kind) + "." + std::to_string(reference_index);
			}
		private:
			u1 reference_kind;
			u2 reference_index;
		};

		class CONSTANT_MethodType_info :public cp_info {
		public:
			CONSTANT_MethodType_info() = delete;

			CONSTANT_MethodType_info(std::ifstream& infile)
			{
				ReadBytes(infile, descriptor_index);
			}
			std::string to_string() override
			{
				return std::to_string(descriptor_index);
			}
		private:
			u2 descriptor_index;
		};

		class CONSTANT_InvokeDynamic_info :public cp_info {
		public:
			CONSTANT_InvokeDynamic_info() = delete;

			CONSTANT_InvokeDynamic_info(std::ifstream& infile)
			{
				ReadBytes(infile, bootstrap_method_attr_index);
				ReadBytes(infile, name_and_type_index);
			}
			std::string to_string() override
			{
				return std::to_string(bootstrap_method_attr_index) + "." + std::to_string(name_and_type_index);
			}
		private:
			u2 bootstrap_method_attr_index;
			u2 name_and_type_index;
		};
		/*****************************************************************************************************************************************************************************/

		
		class attribute_info {

		public:
			attribute_info() = delete;
			attribute_info(std::ifstream& infile)
			{
				ReadBytes(infile, this->attribute_name_index);
				ReadBytes(infile, this->attribute_length);
				this->info.reserve(this->attribute_length);

				for (u4 i = 0; i < this->attribute_length; i++)
				{
					u1 temp = {};
					ReadBytes(infile, temp);
					this->info.push_back(temp);
				}
			}

		private:
			u2 attribute_name_index;
			u4 attribute_length;
			std::vector<u1> info;
		};
		
		
		class field_info {
		public:
			field_info() = delete;
			field_info(std::ifstream& infile)
			{
				ReadBytes(infile, this->access_flags	  );
				ReadBytes(infile, this->name_index		  );
				ReadBytes(infile, this->descriptor_index  );
				ReadBytes(infile, this->attributes_count  );

				for (u4 i = 0; i < this->attributes_count; i++)
				{
					this->attributes.emplace_back(infile);
				}
			}

		private:
			u2             access_flags;
			u2             name_index;
			u2             descriptor_index;
			u2             attributes_count;
			std::vector<attribute_info> attributes;
		};




		/*****************************************************************************************************************************************************************************/

		std::vector<std::shared_ptr<cp_info>> constant_pool;
		std::vector<u2> interfaces;
		std::vector<field_info> fields;

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

#ifdef _DEBUG
			std::ostringstream oss;
			oss << std::hex << std::uppercase << magic;
			std::cout << filepath << " @" << oss.str() << "[" << MajorVersion << "." << minor_version << "]" << std::endl;
			std::cout << "----------------------------------------------" << std::endl;
#endif

			ParseConstantPool(infile, constant_pool_count);

			u2 access_flags;
			u2 this_class;
			u2 super_class;
			u2 interfaces_count;
			
			ReadBytes(infile, access_flags);
			ReadBytes(infile, this_class);
			ReadBytes(infile, super_class);
			ReadBytes(infile, interfaces_count);
			


#define ACC_PUBLIC 			0x0001 	//Declared public; may be accessed from outside its package.
#define ACC_FINAL 			0x0010 	//Declared final; no subclasses allowed.
#define ACC_SUPER 			0x0020 	//Treat superclass methods specially when invoked by the invokespecial instruction.
#define ACC_INTERFACE 		0x0200 	//Is an interface, not a class.
#define ACC_ABSTRACT 		0x0400 	//Declared abstract; must not be instantiated.
#define ACC_SYNTHETIC		0x1000 	//Declared synthetic; not present in the source code.
#define ACC_ANNOTATION 		0x2000 	//Declared as an annotation type.
#define ACC_ENUM 			0x4000 	//Declared as an enum type. 

			std::string parsed_access_flags = "";

			u2 temporary_access_flags  = access_flags;

			if ((access_flags & ACC_PUBLIC		) == ACC_PUBLIC		) { parsed_access_flags += "ACC_PUBLIC ";		temporary_access_flags = temporary_access_flags & (~ACC_PUBLIC);}
			if ((access_flags & ACC_FINAL		) == ACC_FINAL		) { parsed_access_flags += "ACC_FINAL ";		temporary_access_flags = temporary_access_flags & (~ACC_FINAL);}
			if ((access_flags & ACC_SUPER		) == ACC_SUPER		) { parsed_access_flags += "ACC_SUPER ";		temporary_access_flags = temporary_access_flags & (~ACC_SUPER);}
			if ((access_flags & ACC_INTERFACE	) == ACC_INTERFACE	) { parsed_access_flags += "ACC_INTERFACE ";	temporary_access_flags = temporary_access_flags & (~ACC_INTERFACE);}
			if ((access_flags & ACC_ABSTRACT	) == ACC_ABSTRACT	) { parsed_access_flags += "ACC_ABSTRACT ";		temporary_access_flags = temporary_access_flags & (~ACC_ABSTRACT);}
			if ((access_flags & ACC_SYNTHETIC	) == ACC_SYNTHETIC	) { parsed_access_flags += "ACC_SYNTHETIC ";	temporary_access_flags = temporary_access_flags & (~ACC_SYNTHETIC);}
			if ((access_flags & ACC_ANNOTATION	) == ACC_ANNOTATION	) { parsed_access_flags += "ACC_ANNOTATION ";	temporary_access_flags = temporary_access_flags & (~ACC_ANNOTATION);}
			if ((access_flags & ACC_ENUM		) == ACC_ENUM		) { parsed_access_flags += "ACC_ENUM ";			temporary_access_flags = temporary_access_flags & (~ACC_ENUM);}

			if(temporary_access_flags != 0x0000){ throw JavaException("Inalid access_flags : " + std::to_string((int)temporary_access_flags) + " in filepath", __FILENAME__, __LINE__); }

#ifdef _DEBUG
			std::cout << "----------------------------------------------" << std::endl;
			std::cout << "access_flags = "		<< parsed_access_flags << std::endl;
			std::cout << "this_class = "		<< this_class << std::endl;
			std::cout << "super_class = "		<< super_class << std::endl;
			std::cout << "interfaces_count = "	<< interfaces_count << std::endl;
#endif

			ParseInterfaces(infile, interfaces_count);

			u2 fields_count;
			ReadBytes(infile, fields_count);

#ifdef _DEBUG
			std::cout << "----------------------------------------------" << std::endl;
			std::cout << "fields_count = " << fields_count << std::endl;
#endif

			ParseFields(infile, fields_count);

			infile.close();
		}

	private:

		void ParseFields(std::ifstream& infile, u2 fields_count)
		{
			this->fields.reserve(fields_count);

			for (u2 i = 0; i < fields_count; i++)
			{
				this->fields.emplace_back(infile);
			}
		}

		void ParseInterfaces(std::ifstream& infile, u2 interfaces_count)
		{
			this->interfaces.reserve(interfaces_count);
			for (u2 i = 0; i < interfaces_count; i++)
			{
				u2 temp = {};
				ReadBytes(infile, temp);
				this->interfaces.push_back(temp);
			}

#ifdef _DEBUG
			std::cout << "----------------------------------------------" << std::endl;
			for (u2 i = 0; i < interfaces_count; i++)
			{
				std::cout << "Interface[" << i << "] = #" << this->interfaces[i] << std::endl;
			}
#endif
		}

		void ParseConstantPool(std::ifstream& infile, u2 constant_pool_count)
		{

#define CONSTANT_Class 					7
#define CONSTANT_Fieldref 				9
#define CONSTANT_Methodref 				10
#define CONSTANT_InterfaceMethodref 	11
#define CONSTANT_String 				8
#define CONSTANT_Integer 				3
#define CONSTANT_Float 					4
#define CONSTANT_Long 					5
#define CONSTANT_Double 				6
#define CONSTANT_NameAndType 			12
#define CONSTANT_Utf8 					1
#define CONSTANT_MethodHandle 			15
#define CONSTANT_MethodType 			16
#define CONSTANT_InvokeDynamic 			18

			this->constant_pool.reserve(constant_pool_count-1);
			for (u2 i =  1; i < constant_pool_count; i++)
			{
				u1 tag;
				ReadBytes(infile, tag);
				switch ((int)tag)
				{
				case CONSTANT_Class:				this->constant_pool.emplace_back(std::make_shared<CONSTANT_Class_info>(infile));				break;
				case CONSTANT_Fieldref:				this->constant_pool.emplace_back(std::make_shared<CONSTANT_Fieldref_info>(infile));				break;
				case CONSTANT_Methodref:			this->constant_pool.emplace_back(std::make_shared<CONSTANT_Methodref_info>(infile));			break;
				case CONSTANT_InterfaceMethodref:	this->constant_pool.emplace_back(std::make_shared<CONSTANT_InterfaceMethodref_info>(infile));	break;
				case CONSTANT_String:				this->constant_pool.emplace_back(std::make_shared<CONSTANT_String_info>(infile));				break;
				case CONSTANT_Integer:				this->constant_pool.emplace_back(std::make_shared<CONSTANT_Integer_info>(infile));				break;
				case CONSTANT_Float:				this->constant_pool.emplace_back(std::make_shared<CONSTANT_Float_info>(infile));				break;
				case CONSTANT_Long:					this->constant_pool.emplace_back(std::make_shared<CONSTANT_Long_info>(infile));					break;
				case CONSTANT_Double:				this->constant_pool.emplace_back(std::make_shared<CONSTANT_Double_info>(infile));				break;
				case CONSTANT_NameAndType:			this->constant_pool.emplace_back(std::make_shared<CONSTANT_NameAndType_info>(infile));			break;
				case CONSTANT_Utf8:					this->constant_pool.emplace_back(std::make_shared<CONSTANT_Utf8_info>(infile));					break;
				case CONSTANT_MethodHandle:			this->constant_pool.emplace_back(std::make_shared<CONSTANT_MethodHandle_info>(infile));			break;
				case CONSTANT_MethodType:			this->constant_pool.emplace_back(std::make_shared<CONSTANT_MethodType_info>(infile));			break;
				case CONSTANT_InvokeDynamic:		this->constant_pool.emplace_back(std::make_shared<CONSTANT_InvokeDynamic_info>(infile));		break;
				default: throw JavaException("Inalid tag : " + (int)tag, __FILENAME__, __LINE__);
				}
			}


#ifdef _DEBUG
			for (auto cp : this->constant_pool)
			{
				std::cout << cp->to_string() << std::endl;
			}
#endif



		}
	};
}