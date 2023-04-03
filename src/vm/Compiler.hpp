#ifndef DVM_COMPILER_HPP
#define DVM_COMPILER_HPP

#include <filesystem>
#include <fstream>
#include <cstdint>
#include <type_traits>
#include "OpCodes.hpp"
#include "VirtualMachine.hpp"
#include "../parser/Parser.hpp"

namespace dialang
{
	enum class VarType
	{
		Integer32,
		Boolean,
		String
	};

	struct CompileState
	{
		VarType varDeclarationType;
		int32_t localCount;
		int32_t scopeDepth;
	};

	class Compiler
	{
	private:
		Parser m_parser;
		vm::Chunk m_chunk;
		CompileState m_state;
	public:
		Compiler() = default;
		Compiler(std::string code);

		bool openFile(const std::filesystem::path &path);

		vm::Chunk compile();

		template<typename... Ts>
		void emitBytes(Ts &&...args)
		{
			(m_chunk.write(args), ...);
		}

		void emitConstant(vm::Value value);
		uint8_t emitIdConst(const std::string &id);

		void setState(CompileState state);
		CompileState &getState();
	};
}

#endif // DVM_COMPILER_HPP
