#pragma once
#include <cstdint>
#include <vector>
#include <stack>
#include <memory>


namespace Runtime {
	using Slot = uint16_t;

	union LocalVariable {
		bool boolean_value;
		int8_t byte_value;
		uint16_t char_value;
		int16_t short_value;
		int32_t int_value;
		float float_value;	
	};
	
	class LocalVariableTable {
		std::size_t capacity;
		std::unique_ptr<Slot[]> local_variable_table;

	public:
		explicit LocalVariableTable(size_t capacity)
		: capacity(capacity), local_variable_table(std::make_unique<Slot[]>(capacity)){}

		template<typename T>
		void put(const size_t index, const T& value) {
			if (sizeof(T) <= sizeof(Slot)) {
				*(reinterpret_cast<T*>(&(local_variable_table[index]))) = value;
			} else {
				*(reinterpret_cast<T*>(&(local_variable_table[index]))) = value;
			}
		}
		
		template<typename T>
		void get(const size_t index, T& value) {
			if (sizeof(T) <= sizeof(Slot)) {
				value = *(reinterpret_cast<T*>(&(local_variable_table[index])));
			} else {
				value = *(reinterpret_cast<T*>(&(local_variable_table[index])));
			}
		}
	};

	using Operand = uint8_t;
	class OperandStack {
	private:
		std::size_t capacity;
		std::size_t size = 0;
		std::unique_ptr<Slot[]> operand_stack;
	public:
		explicit OperandStack(size_t capacity)
		: capacity(capacity), operand_stack(std::make_unique<Slot[]>(capacity)) {}

		template<typename T, size_t = sizeof(T)> 
		void push(const T& value) {
			if (sizeof(T) <= sizeof(Slot)) {
				*(reinterpret_cast<T*>(&(operand_stack[size]))) = value;
				++size;
			} else {
				*(reinterpret_cast<T*>(&(operand_stack[size]))) = value;
				size += 2;
			}
		}

		template<typename T>
		void pop(T& value) {
			if (sizeof(T) <= sizeof(Slot)) {
				--size;
				value = *(reinterpret_cast<T*>(&(operand_stack[size])));
			} else {
				size -= 2;
				value = *(reinterpret_cast<T*>(&(operand_stack[size])));
			}
		}
	};

	class Frame {
	public:
	    LocalVariableTable local_variable_table;
		OperandStack operand_stack;

	public:
		Frame(size_t local_variable_table_capacity, size_t operand_stack_capacity)
		: local_variable_table(local_variable_table_capacity), operand_stack(operand_stack_capacity)
		{}
	};

	class Stack {
	private:
		const size_t frame_count = 1024;
		std::stack<Frame> stack;
	public:
		
	};
	
	class Thread {
	public:
		uint16_t pc;
		Stack stack;
	};

}

