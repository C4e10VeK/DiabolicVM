#ifndef DVM_VIRTUALMACHINE_HPP
#define DVM_VIRTUALMACHINE_HPP

#include <iostream>
#include <vector>
#include <unordered_map>
#include "Value.hpp"
#include "Stack.hpp"

namespace dialang::vm
{

	constexpr size_t STACK_MAX = 256;

	class Chunk
	{
	private:
		std::vector<Value> m_constants;
		std::vector<uint8_t> m_code;
	public:
		void write(uint8_t code)
		{
			m_code.emplace_back(code);
		}

		int32_t addConstant(Value value)
		{
			m_constants.emplace_back(value);
			return m_constants.size() - 1;
		}

		uint8_t *getFirstOp()
		{
			return &m_code[0];
		}

		Value getConstant(int32_t index)
		{
			return m_constants[index];
		}
	};

	enum class InterpretResult : uint8_t
	{
		Ok,
		CompileError,
		RuntimeError,
	};

	class VM
	{
	private:
		Chunk *m_chunk;
		uint8_t *m_ip;
		Stack<STACK_MAX> m_stack;
		std::unordered_map<std::string, Value> m_globals;
		std::unordered_map<std::string, Value> m_strings;
	public:

		InterpretResult interpret(Chunk &chunk);	
	};
}

#endif // DVM_VIRTUALMACHINE_HPP
