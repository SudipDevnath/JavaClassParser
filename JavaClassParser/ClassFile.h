#pragma once
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <memory>
#include <unordered_map>
#include <bitset>

#include "JavaCommon.h"
#include "JavaException.h"

namespace Java
{


	class ClassFile
	{

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
				return "{" +std::to_string(name_index) + "}";
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
				return "{"+ std::to_string(class_index) + "." + std::to_string(name_and_type_index) + "}";
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
				return "{" + std::to_string(class_index) + "." + std::to_string(name_and_type_index) + "}";
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
				return "{" + std::to_string(class_index) + "." + std::to_string(name_and_type_index) + "}";
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
				return "{" + std::to_string(string_index) + "}";
			}
		private:
			u2 string_index;
		};

		class CONSTANT_Integer_info :public cp_info {
		public:
			CONSTANT_Integer_info() = delete;

			CONSTANT_Integer_info(std::ifstream& infile)
			{
				u4 bytes;
				ReadBytes(infile, bytes);
				this->value = bytes;
			}
			std::string to_string() override
			{
				return "{" + std::to_string((int)value) + "}";
			}
		private:
			int value = 0;
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
				return "{" + std::to_string(bytes) + "}";
			}
		private:
			u4 bytes;
		};

		class CONSTANT_Long_info :public cp_info {
		public:
			CONSTANT_Long_info() = delete;

			CONSTANT_Long_info(std::ifstream& infile)
			{
				u4 high_bytes;
				u4 low_bytes;
				ReadBytes(infile, high_bytes);
				ReadBytes(infile, low_bytes);

				this->value = (static_cast<long long int>(high_bytes) << 32) | low_bytes;
			}
			std::string to_string() override
			{
				return "{" + std::to_string(value) + "}";
			}
		private:
			long long int value = 0L;
		};

		class CONSTANT_Double_info :public cp_info {
		public:
			CONSTANT_Double_info() = delete;

			CONSTANT_Double_info(std::ifstream& infile)
			{
				u4 high_bytes;
				u4 low_bytes;
				ReadBytes(infile, high_bytes);
				ReadBytes(infile, low_bytes);

				this->value = (double)((static_cast<long long int>(high_bytes) << 32) | low_bytes);
			}
			std::string to_string() override
			{
				return "{" + std::to_string(value) + "}";
			}
		private:
			double value = 0.0;
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
				return "{" + std::to_string(name_index) + "." + std::to_string(descriptor_index) + "}";
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
				std::vector<u1> bytes;
				bytes.reserve(length);

				for (u2 i = 0; i < length; i++)
				{
					u1 temp = {};
					ReadBytes(infile, temp);
					bytes.push_back(temp);
				}

				value = std::string(bytes.begin(), bytes.end());
			}
			std::string to_string() override
			{
				return "{" + value + "}";
			}
			std::string value = {};
		private:
			
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
				return "{" + std::to_string(reference_kind) + "." + std::to_string(reference_index) + "}";
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
				return "{" + std::to_string(descriptor_index) + "}";
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
				return "{" + std::to_string(bootstrap_method_attr_index) + "." + std::to_string(name_and_type_index) + "}";
			}
		private:
			u2 bootstrap_method_attr_index;
			u2 name_and_type_index;
		};
		/*****************************************************************************************************************************************************************************/
	
		class I_attribute_info {

		public:
			virtual std::string to_string() = 0;
		};
		
		class field_info {
		public:
			field_info() = delete;
			field_info(std::ifstream& infile, const std::unordered_map<unsigned int, std::shared_ptr<cp_info>>& constant_pool)
			{
				ReadBytes(infile, this->access_flags	  );
				ReadBytes(infile, this->name_index		  );
				ReadBytes(infile, this->descriptor_index  );
				u2 attributes_count;
				ReadBytes(infile, attributes_count  );

				for (u4 i = 0; i < attributes_count; i++)
				{
					this->attributes.emplace_back(ClassFile::make_Attribute_Instance(infile, constant_pool));
				}
			}

			std::string to_string()
			{
				std::string s =
					" [access_flags] = " + std::to_string(access_flags) +
					" [name_index] = " + std::to_string(name_index) +
					" [descriptor_index] = " + std::to_string(descriptor_index);


				if (attributes.size() != 0)
				{
					s += " [attributes] = ";
					for (auto& a : attributes)
					{
						s += a->to_string();
					}
				}
					
				return "{" + s + "}";
			}

		private:
			u2             access_flags;
			u2             name_index;
			u2             descriptor_index;

			std::vector<std::shared_ptr<I_attribute_info>> attributes;
		};

		/*****************************************************************************************************************************************************************************/

		class method_info
		{
		public:
			method_info() = delete;
			method_info(std::ifstream& infile,const std::unordered_map<unsigned int, std::shared_ptr<cp_info>>& constant_pool)
			{
				ReadBytes(infile, this->access_flags);
				ReadBytes(infile, this->name_index);
				ReadBytes(infile, this->descriptor_index);
				u2 attributes_count;
				ReadBytes(infile, attributes_count);

				attributes.reserve(attributes_count);
				for (u2 i = 0; i < attributes_count; i++)
				{
					attributes.emplace_back(ClassFile::make_Attribute_Instance(infile, constant_pool));
				}
			}

			std::string to_string()
			{
				std::string s =
					" [access_flags] = " + std::to_string(access_flags) +
					" [name_index] = " + std::to_string(name_index) +
					" [descriptor_index] = " + std::to_string(descriptor_index);


				if (attributes.size() != 0)
				{
					s += " [attributes] = ";
					for (auto& a : attributes)
					{
						s += a->to_string();
					}
				}

				return "{" + s + "}";
			}

		private:
			u2             access_flags;
			u2             name_index;
			u2             descriptor_index;

			std::vector<std::shared_ptr<I_attribute_info>> attributes;
		};

		/*****************************************************************************************************************************************************************************/

		class annotation {
			u2 type_index;
			u2 num_element_value_pairs;
			class Element_value_pairs {
				u2            element_name_index;
//				element_value value;
			};
			std::vector<Element_value_pairs> element_value_pairs;
		};

		class ConstantValue_attribute : public I_attribute_info {
			u2 constantvalue_index;
		public:
			ConstantValue_attribute() = delete;
			ConstantValue_attribute(std::ifstream& infile)
			{
				ReadBytes(infile, this->constantvalue_index);
			}
			

			std::string to_string() override
			{
				return std::string("{") + "[ConstantValue_attribute]= constantvalue_index = " + std::to_string((int)constantvalue_index) + "}";
			}
		};

		class Code_attribute : public I_attribute_info {
			u2 max_stack;
			u2 max_locals;

			std::vector<u1> code;//u1 code[code_length];
			
			struct Exception_table {
				Exception_table() = delete;
				Exception_table(std::ifstream& infile)
				{
					ReadBytes(infile, this->start_pc);
					ReadBytes(infile, this->end_pc);
					ReadBytes(infile, this->handler_pc);
					ReadBytes(infile, this->catch_type);
				}
				u2 start_pc;
				u2 end_pc;
				u2 handler_pc;
				u2 catch_type;

				std::string to_string()
				{
					std::string s;
					s = "[start_pc] = " + std::to_string(start_pc) +
						", [end_pc] = " + std::to_string(end_pc) +
						", [handler_pc]" + std::to_string(handler_pc) +
						", [catch_type]" + std::to_string(catch_type);

					return "{" + s + "}";
				}
			};

			std::vector<Exception_table> exception_table;
			std::vector<std::shared_ptr<I_attribute_info>> attributes;

		public:
			Code_attribute() = delete;
			Code_attribute(std::ifstream& infile,const std::unordered_map<unsigned int, std::shared_ptr<cp_info>>& constant_pool)
			{
				ReadBytes(infile, this->max_stack);
				ReadBytes(infile, this->max_locals);
				u4 code_length;
				ReadBytes(infile, code_length);
				this->code.reserve(code_length);
				for (u4 i = 0; i < code_length; i++)
				{
					u1 temp;
					ReadBytes(infile, temp);
					this->code.emplace_back(temp);
				}
				u2 exception_table_length;
				ReadBytes(infile, exception_table_length);
				this->exception_table.reserve(exception_table_length);
				for (u2 i = 0; i < exception_table_length; i++)
				{
					this->exception_table.emplace_back(infile);
				}
				u2 attributes_count;
				ReadBytes(infile, attributes_count);
				for (u2 i = 0; i < attributes_count; i++)
				{
					this->attributes.emplace_back(ClassFile::make_Attribute_Instance(infile, constant_pool));
				}
			}


			std::string to_string() override
			{
				std::string s;
				
				s = "[Code_attribute] = [max_stack] = " + std::to_string((int)this->max_stack) +
					", [max_locals] = " + std::to_string((int)this->max_locals);
					

				if (this->code.size() > 0)
				{
					s += ", [code] = {";

					for (auto& a : this->code)
					{
						s += ("[" + std::to_string((int)a) + "],");
					}

					s += "\b}";
				}


				if (this->exception_table.size() > 0)
				{
					s += ", [exception_table] = {";

					for (auto& a : this->exception_table)
					{
						s += ("[" + a.to_string() + "],");
					}

					s += "\b}";
				}

				if (this->attributes.size() > 0)
				{
					s += ", [attributes] = {";

					for (auto& a : this->attributes)
					{
						s += ("[" + a->to_string() + "],");
					}

					s += "\b}";
				}

				return "{" + s + "}";

			}
		};

		class StackMapTable_attribute : public I_attribute_info {			// UNIMPLEMENTED: DO NOT USE

			class stack_map_frame {
			private:
//				class same_frame {};
//				class same_locals_1_stack_item_frame{};
//				class same_locals_1_stack_item_frame_extended{};
//				class chop_frame{};
//				class same_frame_extended{};
//				class append_frame{};
				class full_frame {

				private:
					class verification_type_info
					{
					public:
						verification_type_info(std::ifstream& infile)
						{
							ReadBytes(infile, this->tag);
							if (this->tag > 8 || this->tag < 0)
							{
								throw JavaException("INCORECT verification_type_info::tag:: " + std::to_string((int)tag), __FILENAME__, __LINE__);
							}

							if (this->tag == 7 || this->tag == 8)
							{
								ReadBytes(infile, this->extraBytes);
								return;
							}

							extraBytes = 0;
						}

						u2 getExtraBytes()
						{
							if (this->tag == 7 || this->tag == 8)
							{
								return this->extraBytes;
							}
							else 
							{
								throw JavaException("verification_type_info::tag:: " + std::to_string((int)tag) + " do not contain extraBytes", __FILENAME__, __LINE__);
							}
						}

						std::string to_string()
						{
							switch (this->tag)
							{
							case 0: {return std::string("{ tag=ITEM_Top }");																	}
							case 1: {return std::string("{ tag=ITEM_Integer }");																}
							case 2: {return std::string("{ tag=ITEM_Float }");																	}
							case 3: {return std::string("{ tag=ITEM_Double }");																	}
							case 4: {return std::string("{ tag=ITEM_Long }");																	}
							case 5: {return std::string("{ tag=ITEM_Null }");																	}
							case 6: {return std::string("{ tag=ITEM_UninitializedThis }");														}
							case 7: {return std::string("{ tag=ITEM_Object, cpool_index= ")		+ std::to_string((int)this->extraBytes) + " }";	}
							case 8: {return std::string("{ tag=ITEM_Uninitialized, offset= ")	+ std::to_string((int)this->extraBytes) + " }";	}
							}
						}
						u1 tag;
					private:
						u2 extraBytes;
					};

				public:
					full_frame(std::ifstream& infile)
					{
						ReadBytes(infile, this->frame_type);
						ReadBytes(infile, this->offset_delta);
						u2 number_of_locals;
						ReadBytes(infile, number_of_locals);
						this->locals.reserve(number_of_locals);

						for (u1 i = 0; i < number_of_locals; i++)
						{
							this->locals.emplace_back(infile);
						}

						u2 number_of_stack_items;
						ReadBytes(infile, number_of_stack_items);
						this->stack.reserve(number_of_stack_items);

						for (u1 i = 0; i < number_of_stack_items; i++)
						{
							this->stack.emplace_back(infile);
						}
					}

					std::string to_string()
					{
						std::string s;
						s = "{ full_frame = {";
						s += (" frame_type = " + std::to_string((int)frame_type));
						s += (", offset_delta = " + std::to_string((int)offset_delta));

						s += ", locals = {";
						for (auto& a : this->locals)
						{
							s += ("{" + a.to_string() + "},");
						}
						s += "\b }";

						s += ", stack = {";
						for (auto& a : this->stack)
						{
							s += ("{" + a.to_string() + "},");
						}
						s += "\b }";

						s += " } }";

						return s;
					}

					u1 frame_type;
					u2 offset_delta;
					std::vector<verification_type_info> locals;
					std::vector<verification_type_info> stack;
				};


			public:
//				same_frame									same_frame;
//				same_locals_1_stack_item_frame				same_locals_1_stack_item_frame;
//				same_locals_1_stack_item_frame_extended		same_locals_1_stack_item_frame_extended;
//				chop_frame									chop_frame;
//				same_frame_extended							same_frame_extended;
//				append_frame								append_frame;
				full_frame									m_full_frame;

				stack_map_frame(std::ifstream& infile)
					:
					m_full_frame(infile)
				{
					
				}
			};

			std::vector<stack_map_frame> entries;

		public:
			StackMapTable_attribute() = delete;
			StackMapTable_attribute(std::ifstream& infile)
			{
				u2 number_of_entries;
				ReadBytes(infile, number_of_entries);
				this->entries.reserve(number_of_entries);

				for (u2 i = 0; i < number_of_entries; i++)
				{
					this->entries.emplace_back(infile);
				}
			}

			std::string to_string() override
			{
				std::string s;
				s = "{ StackMapTable_attribute = {entries = {";

				for (auto& a : this->entries)
				{
					s += ("{" + a.m_full_frame.to_string() + "},");
				}

				s += "\b} } }";
				return s;
			}
		};

		class Exceptions_attribute : public I_attribute_info {
			u2 attribute_name_index;
			u4 attribute_length;
			u2 number_of_exceptions;
			std::vector<u2> exception_index_table;

		public:
			Exceptions_attribute() = delete;
			Exceptions_attribute(std::ifstream& infile)
			{
				throw JavaException("unimplemented", __FILENAME__, __LINE__);
			}
			std::string to_string() override
			{
				throw JavaException("unimplemented", __FILENAME__, __LINE__);
			}
		};

		class InnerClasses_attribute : public I_attribute_info {
			u2 attribute_name_index;
			u4 attribute_length;
			u2 number_of_classes;
			class Classes {
				u2 inner_class_info_index;
				u2 outer_class_info_index;
				u2 inner_name_index;
				u2 inner_class_access_flags;
			};
			std::vector<Classes> classes;

		public:
			InnerClasses_attribute() = delete;
			InnerClasses_attribute(std::ifstream& infile)
			{
				throw JavaException("unimplemented", __FILENAME__, __LINE__);
			}
			std::string to_string() override
			{
				throw JavaException("unimplemented", __FILENAME__, __LINE__);
			}
		};

		class EnclosingMethod_attribute : public I_attribute_info {
			u2 attribute_name_index;
			u4 attribute_length;
			u2 class_index;
			u2 method_index;

		public:
			EnclosingMethod_attribute() = delete;
			EnclosingMethod_attribute(std::ifstream& infile)
			{
				throw JavaException("unimplemented", __FILENAME__, __LINE__);
			}
			std::string to_string() override
			{
				throw JavaException("unimplemented", __FILENAME__, __LINE__);
			}
		};

		class Synthetic_attribute : public I_attribute_info {
			u2 attribute_name_index;
			u4 attribute_length;

		public:
			Synthetic_attribute() = delete;
			Synthetic_attribute(std::ifstream& infile)
			{
				throw JavaException("unimplemented", __FILENAME__, __LINE__);
			}
			std::string to_string() override
			{
				throw JavaException("unimplemented", __FILENAME__, __LINE__);
			}
		};

		class Signature_attribute : public I_attribute_info {
			u2 attribute_name_index;
			u4 attribute_length;
			u2 signature_index;

		public:
			Signature_attribute() = delete;
			Signature_attribute(std::ifstream& infile)
			{
				throw JavaException("unimplemented", __FILENAME__, __LINE__);
			}
			std::string to_string() override
			{
				throw JavaException("unimplemented", __FILENAME__, __LINE__);
			}
		};

		class SourceFile_attribute : public I_attribute_info {
			u2 sourcefile_index;

		public:
			SourceFile_attribute() = delete;
			SourceFile_attribute(std::ifstream& infile)
			{
				ReadBytes(infile, this->sourcefile_index);
			}
			std::string to_string() override
			{
				return std::string("{") + "[sourcefile_index] = "+ std::to_string(this->sourcefile_index) + "}";
			}
		};

		class SourceDebugExtension_attribute : public I_attribute_info {
			u2 attribute_name_index;
			u4 attribute_length;
			std::vector<u1> debug_extension;

		public:
			SourceDebugExtension_attribute() = delete;
			SourceDebugExtension_attribute(std::ifstream& infile)
			{
				throw JavaException("unimplemented", __FILENAME__, __LINE__);
			}
			std::string to_string() override
			{
				throw JavaException("unimplemented", __FILENAME__, __LINE__);
			}
		};

		class LineNumberTable_attribute : public I_attribute_info {

			struct Line_number_table {   
				Line_number_table() = delete;
				Line_number_table(std::ifstream& infile)
				{
					ReadBytes(infile, this->start_pc);
					ReadBytes(infile, this->line_number);
				}
				std::string to_string()
				{
					std::string s;
					s = "[start_pc]" + std::to_string(start_pc) +
						", [line_number]" + std::to_string(line_number);
					return "{" + s + "}";
				}
				u2 start_pc;
				u2 line_number;
			};
			std::vector<Line_number_table> line_number_table;
		public:
			LineNumberTable_attribute() = delete;
			LineNumberTable_attribute(std::ifstream& infile)
			{
				u2 line_number_table_length;
				ReadBytes(infile, line_number_table_length);
				this->line_number_table.reserve(line_number_table_length);
				for (u2 i = 0; i < line_number_table_length; i++)
				{
					this->line_number_table.emplace_back(infile);
				}
			}
			std::string to_string() override
			{
				std::string s;

				if (this->line_number_table.size() > 0)
				{
					s += "[line_number_table] = {";

					for (auto& a : this->line_number_table)
					{
						s += ("[" + a.to_string() + "],");
					}

					s += "\b}";
				}
				else
				{
					s = "[line_number_table] = empty";
				}

				return "{" + s + "}";
			}
		};

		class LocalVariableTable_attribute : public I_attribute_info {

			struct Local_variable_table {
				Local_variable_table() = delete;
				Local_variable_table(std::ifstream& infile)
				{
					ReadBytes(infile, this->start_pc);
					ReadBytes(infile, this->length);
					ReadBytes(infile, this->name_index);
					ReadBytes(infile, this->descriptor_index);
					ReadBytes(infile, this->index);
				}

				u2 start_pc;
				u2 length;
				u2 name_index;
				u2 descriptor_index;
				u2 index;

				std::string to_string()
				{
					std::string s = "[start_pc] = " + std::to_string(start_pc) +
						"[length] = " + std::to_string(length) +
						"[name_index] = " + std::to_string(name_index) +
						"[descriptor_index] = " + std::to_string(descriptor_index) +
						"[index] = " + std::to_string(index);
					return "{" + s + "}";
				}
			};
			std::vector<Local_variable_table> local_variable_table;
		public:
			LocalVariableTable_attribute() = delete;
			LocalVariableTable_attribute(std::ifstream& infile)
			{
				u2 local_variable_table_length;
				ReadBytes(infile, local_variable_table_length);
				this->local_variable_table.reserve(local_variable_table_length);
				for (u2 i = 0; i < local_variable_table_length; i++)
				{
					this->local_variable_table.emplace_back(infile);
				}
			}
			std::string to_string() override
			{
				std::string s;

				if (this->local_variable_table.size() > 0)
				{
					s += "[local_variable_table] = ";

					for (auto& a : this->local_variable_table)
					{
						s += ("[" + a.to_string() + "],");
					}

					s += "\b";
				}
				else
				{
					s = "[local_variable_table] = empty";
				}

				return "{" + s + "}";
			}
		};

		class LocalVariableTypeTable_attribute : public I_attribute_info {
			u2 attribute_name_index;
			u4 attribute_length;
			u2 local_variable_type_table_length;
			class Local_variable_type_table {
				u2 start_pc;
				u2 length;
				u2 name_index;
				u2 signature_index;
				u2 index;
			};
			std::vector<Local_variable_type_table> local_variable_type_table;
		public:
			LocalVariableTypeTable_attribute() = delete;
			LocalVariableTypeTable_attribute(std::ifstream& infile)
			{
				throw JavaException("unimplemented", __FILENAME__, __LINE__);

			}
			std::string to_string() override
			{
				throw JavaException("unimplemented", __FILENAME__, __LINE__);
			}
		};

		class Deprecated_attribute : public I_attribute_info {
			u2 attribute_name_index;
			u4 attribute_length;
		public:
			Deprecated_attribute() = delete;
			Deprecated_attribute(std::ifstream& infile)
			{
				throw JavaException("unimplemented", __FILENAME__, __LINE__);

			}
			std::string to_string() override
			{
				throw JavaException("unimplemented", __FILENAME__, __LINE__);
			}
		};

		class RuntimeVisibleAnnotations_attribute : public I_attribute_info {
			u2         attribute_name_index;
			u4         attribute_length;
			u2         num_annotations;
			std::vector<annotation> annotations;

		public:
			RuntimeVisibleAnnotations_attribute() = delete;
			RuntimeVisibleAnnotations_attribute(std::ifstream& infile)
			{
				throw JavaException("unimplemented", __FILENAME__, __LINE__);

			}
			std::string to_string() override
			{
				throw JavaException("unimplemented", __FILENAME__, __LINE__);
			}
		};

		class RuntimeInvisibleAnnotations_attribute : public I_attribute_info {
			u2         attribute_name_index;
			u4         attribute_length;
			u2         num_annotations;
			std::vector<annotation> annotations;

		public:
			RuntimeInvisibleAnnotations_attribute() = delete;
			RuntimeInvisibleAnnotations_attribute(std::ifstream& infile)
			{
				throw JavaException("unimplemented", __FILENAME__, __LINE__);

			}
			std::string to_string() override
			{
				throw JavaException("unimplemented", __FILENAME__, __LINE__);
			}
		};

		class RuntimeVisibleParameterAnnotations_attribute : public I_attribute_info {
			u2 attribute_name_index;
			u4 attribute_length;
			u1 num_parameters;
			struct Parameter_annotations {
				u2         num_annotations;
				std::vector<annotation> annotations;
			};
			std::vector<Parameter_annotations> parameter_annotations;

		public:
			RuntimeVisibleParameterAnnotations_attribute() = delete;
			RuntimeVisibleParameterAnnotations_attribute(std::ifstream& infile)
			{
				throw JavaException("unimplemented", __FILENAME__, __LINE__);

			}
			std::string to_string() override
			{
				throw JavaException("unimplemented", __FILENAME__, __LINE__);
			}
		};

		class RuntimeInvisibleParameterAnnotations_attribute : public I_attribute_info {
			u2 attribute_name_index;
			u4 attribute_length;
			u1 num_parameters;
			struct Parameter_annotations {
				u2         num_annotations;
				std::vector<annotation> annotations;
			};
			std::vector<Parameter_annotations> parameter_annotations;

		public:
			RuntimeInvisibleParameterAnnotations_attribute() = delete;
			RuntimeInvisibleParameterAnnotations_attribute(std::ifstream& infile)
			{
				throw JavaException("unimplemented", __FILENAME__, __LINE__);

			}
			std::string to_string() override
			{
				throw JavaException("unimplemented", __FILENAME__, __LINE__);
			}
		};

		class AnnotationDefault_attribute : public I_attribute_info {
			u2            attribute_name_index;
			u4            attribute_length;

//			class element_value {
//				u1 tag;
//				union {
//					u2 const_value_index;
//
//					{   u2 type_name_index;
//					u2 const_name_index;
//					} enum_const_value;
//
//					u2 class_info_index;
//
//					annotation annotation_value;
//
//					{   u2            num_values;
//					element_value values[num_values];
//					} array_value;
//				} value;
//			};

//			element_value default_value;

		public:
			AnnotationDefault_attribute() = delete;
			AnnotationDefault_attribute(std::ifstream& infile)
			{
				throw JavaException("unimplemented", __FILENAME__, __LINE__);

			}
			std::string to_string() override
			{
				throw JavaException("unimplemented", __FILENAME__, __LINE__);
			}
		};

		class BootstrapMethods_attribute : public I_attribute_info {
			u2 attribute_name_index;
			u4 attribute_length;
			u2 num_bootstrap_methods;
			class Bootstrap_methods {
				u2 bootstrap_method_ref;
				u2 num_bootstrap_arguments;
				std::vector<u2> bootstrap_arguments;
			};
			std::vector<Bootstrap_methods> bootstrap_methods;
			
		public:
			BootstrapMethods_attribute() = delete;
			BootstrapMethods_attribute(std::ifstream& infile)
			{

				throw JavaException("unimplemented", __FILENAME__, __LINE__);

			}

			std::string to_string() override
			{
				throw JavaException("unimplemented", __FILENAME__, __LINE__);
			}

		};




		/*****************************************************************************************************************************************************************************/

		std::unordered_map<unsigned int,std::shared_ptr<cp_info>> constant_pool;
		std::vector<u2> interfaces;
		std::vector<field_info> fields;
		std::vector<method_info> methods;
		std::vector< std::shared_ptr<I_attribute_info>> attributes;

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

			u2 methods_count;
			ReadBytes(infile, methods_count);
#ifdef _DEBUG
			std::cout << "----------------------------------------------" << std::endl;
			std::cout << "methods_count = " << methods_count << std::endl;
#endif

			ParseMethods(infile, methods_count);

			u2 attributes_count;
			ReadBytes(infile, attributes_count);
#ifdef _DEBUG
			std::cout << "----------------------------------------------" << std::endl;
			std::cout << "attributes_count = " << attributes_count << std::endl;
#endif

			ParseAttributes(infile, attributes_count);

			std::cout << "----------------------------------------------" << std::endl;


			u1 dumy;
			ReadBytes(infile, dumy);
			if (infile.eof())
			{
				std::cout << "[EoF reached]" << std::endl;
			}// check for EOF
			else
			{
				std::cout << "[error reading]" << std::to_string(dumy) << std::endl;
				throw JavaException("Invalid class file (Additional data): " + filepath, __FILENAME__, __LINE__);
			}

			infile.close();
		}

	private:

		void ParseAttributes(std::ifstream& infile, u2 attributes_count)
		{
			this->attributes.reserve(attributes_count);

			for (u2 i = 0; i < attributes_count; i++)
			{
				this->attributes.emplace_back(ClassFile::make_Attribute_Instance(infile, constant_pool));
			}

#ifdef _DEBUG
			for (auto& a : this->attributes)
			{
				std::cout << a->to_string() << std::endl;
			}
#endif
		}

		void ParseMethods(std::ifstream& infile, u2 methods_count)
		{
			this->methods.reserve(methods_count);

			for (u2 i = 0; i < methods_count; i++)
			{
				this->methods.emplace_back(infile, constant_pool);
			}

#ifdef _DEBUG
			for (auto& a : this->methods)
			{
				std::cout << a.to_string() << std::endl;
			}
#endif
		}

		void ParseFields(std::ifstream& infile, u2 fields_count)
		{
			this->fields.reserve(fields_count);

			for (u2 i = 0; i < fields_count; i++)
			{
				this->fields.emplace_back(infile, constant_pool);
			}

#ifdef _DEBUG
			for (auto& a : this->fields)
			{
				std::cout << a.to_string() << std::endl;
			}
#endif

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
				case CONSTANT_Class:				this->constant_pool.emplace(i,std::make_shared<CONSTANT_Class_info>(infile));				break;
				case CONSTANT_Fieldref:				this->constant_pool.emplace(i,std::make_shared<CONSTANT_Fieldref_info>(infile));			break;
				case CONSTANT_Methodref:			this->constant_pool.emplace(i,std::make_shared<CONSTANT_Methodref_info>(infile));			break;
				case CONSTANT_InterfaceMethodref:	this->constant_pool.emplace(i,std::make_shared<CONSTANT_InterfaceMethodref_info>(infile));	break;
				case CONSTANT_String:				this->constant_pool.emplace(i,std::make_shared<CONSTANT_String_info>(infile));				break;
				case CONSTANT_Integer:				this->constant_pool.emplace(i,std::make_shared<CONSTANT_Integer_info>(infile));				break;
				case CONSTANT_Float:				this->constant_pool.emplace(i,std::make_shared<CONSTANT_Float_info>(infile));				break;
				case CONSTANT_Long:			i++;	this->constant_pool.emplace(i,std::make_shared<CONSTANT_Long_info>(infile)); 				break;
				case CONSTANT_Double:		i++;	this->constant_pool.emplace(i,std::make_shared<CONSTANT_Double_info>(infile));				break;
				case CONSTANT_NameAndType:			this->constant_pool.emplace(i,std::make_shared<CONSTANT_NameAndType_info>(infile));			break;
				case CONSTANT_Utf8:					this->constant_pool.emplace(i,std::make_shared<CONSTANT_Utf8_info>(infile));				break;
				case CONSTANT_MethodHandle:			this->constant_pool.emplace(i,std::make_shared<CONSTANT_MethodHandle_info>(infile));		break;
				case CONSTANT_MethodType:			this->constant_pool.emplace(i,std::make_shared<CONSTANT_MethodType_info>(infile));			break;
				case CONSTANT_InvokeDynamic:		this->constant_pool.emplace(i,std::make_shared<CONSTANT_InvokeDynamic_info>(infile));		break;
				default: throw JavaException("Inalid tag : " + std::to_string((int)tag), __FILENAME__, __LINE__);
				}
			}


#ifdef _DEBUG
			for (u2 i = 1; i < constant_pool_count; i++)
			{
				if (this->constant_pool.find(i) != this->constant_pool.end())
				{
					std::cout << "#" << i << " :: " << this->constant_pool.at(i)->to_string() << std::endl;
				}
			}
#endif
		}
	
		static std::shared_ptr<I_attribute_info> make_Attribute_Instance(std::ifstream& infile,const std::unordered_map<unsigned int, std::shared_ptr<cp_info>>& constant_pool)
		{
			u2 attribute_name_index;
			u4 attribute_length;
			ReadBytes(infile, attribute_name_index);
			ReadBytes(infile, attribute_length);

			if (constant_pool.find(attribute_name_index) != constant_pool.end())
			{

				std::shared_ptr<CONSTANT_Utf8_info> s = std::dynamic_pointer_cast<CONSTANT_Utf8_info>(constant_pool.at(attribute_name_index));

				if (s == NULL) {
					throw JavaException("Incorrect constant pool entry: " + std::to_string((int)attribute_name_index), __FILENAME__, __LINE__);
				}

				if (s->value == "ConstantValue") { return std::make_shared<ConstantValue_attribute>(infile);}
				if (s->value == "Code") { return std::make_shared<Code_attribute>(infile, constant_pool);}
				if (s->value == "StackMapTable") { return std::make_shared<StackMapTable_attribute>(infile);}
				if (s->value == "StackMap") { return std::make_shared<StackMapTable_attribute>(infile); }  // only for JAVA ME
				if (s->value == "Exceptions") { return std::make_shared<Exceptions_attribute>(infile);}
				if (s->value == "InnerClasses") { return std::make_shared<InnerClasses_attribute>(infile);}
				if (s->value == "EnclosingMethod") { return std::make_shared<EnclosingMethod_attribute>(infile);}
				if (s->value == "Synthetic") { return std::make_shared<Synthetic_attribute>(infile);}
				if (s->value == "Signature") { return std::make_shared<Signature_attribute>(infile);}
				if (s->value == "SourceFile") { return std::make_shared<SourceFile_attribute>(infile);}
				if (s->value == "SourceDebugExtension") { return std::make_shared<SourceDebugExtension_attribute>(infile);}
				if (s->value == "LineNumberTable") { return std::make_shared<LineNumberTable_attribute>(infile);}
				if (s->value == "LocalVariableTable") { return std::make_shared<LocalVariableTable_attribute>(infile);}
				if (s->value == "LocalVariableTypeTable") { return std::make_shared<LocalVariableTypeTable_attribute>(infile);}
				if (s->value == "Deprecated") { return std::make_shared<Deprecated_attribute>(infile);}
				if (s->value == "RuntimeVisibleAnnotations") { return std::make_shared<RuntimeVisibleAnnotations_attribute>(infile);}
				if (s->value == "RuntimeInvisibleAnnotations") { return std::make_shared<RuntimeInvisibleAnnotations_attribute>(infile);}
				if (s->value == "RuntimeVisibleParameterAnnotations") { return std::make_shared<RuntimeVisibleParameterAnnotations_attribute>(infile);}
				if (s->value == "RuntimeInvisibleParameterAnnotations") { return std::make_shared<RuntimeInvisibleParameterAnnotations_attribute>(infile);}
				if (s->value == "AnnotationDefault") { return std::make_shared<AnnotationDefault_attribute>(infile);}
				if (s->value == "BootstrapMethods") { return std::make_shared<BootstrapMethods_attribute>(infile);}

				throw JavaException("Invalid attribute: " + s->value, __FILENAME__, __LINE__);
			}
			else
			{
				throw JavaException("Incorrect constant pool entry: " + std::to_string((int)attribute_name_index), __FILENAME__, __LINE__);
			}
		}
	};
}