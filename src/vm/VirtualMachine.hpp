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
			auto finded = std::find_if(m_constants.begin(), m_constants.end(), [=](const Value &_value){
				return value.value_ == _value.value_;
			});

			if (finded != m_constants.end())
			{
				return std::distance(m_constants.begin(), finded);
			}

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
	public:

		InterpretResult interpret(Chunk &chunk);

		inline void printGlobals()
		{
			std::cout << "global vars: " << std::endl;
			for (const auto &g : m_globals)
			{
				std::cout << g.first << ": ";

				if (g.second.is<int32_t>())
					std::cout << g.second.as<int32_t>();
				if (g.second.is<std::string>())
					std::cout << g.second.as<std::string>();
				
				std::cout << std::endl;
			}
		}
	};
}

#endif // DVM_VIRTUALMACHINE_HPP
