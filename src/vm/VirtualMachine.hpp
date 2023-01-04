#ifndef DVM_VIRTUALMACHINE_HPP
#define DVM_VIRTUALMACHINE_HPP

#include <iostream>
#include <vector>
#include <string>
#include <functional>
#include "../Instruction.hpp"

namespace dialang::vm
{
	struct BaseObject
	{
		DiaBcTypes type_;
		bool isSigned_ = false;

		virtual ~BaseObject() = default;

		virtual std::string toString() = 0;
	};

	namespace priv
	{
		template<typename T>
		inline std::string toString(T value)
		{
			return "";
		}
	
		template<>
		inline std::string toString<std::string>(std::string value)
		{
			return value;
		}
	
		template<>
		inline std::string toString<int32_t>(int32_t value)
		{
			return std::to_string(value);
		}
	
		template<>
		inline std::string toString<int64_t>(int64_t value)
		{
			return std::to_string(value);
		}
	}

	template<typename T, DiaBcTypes>
	struct BaseObjectGen : public BaseObject
	{
		T value_;

		std::string toString() override
		{
			return priv::toString(value_);
		}
	};

	using StringObject = BaseObjectGen<std::string, TYPE_STRING>;
	using I32Object = BaseObjectGen<int32_t, TYPE_DWORD>;
	using I64Object = BaseObjectGen<int64_t, TYPE_QWORD>;

	class VmState;

	using FnNativeType = std::function<bool(VmState &, const std::vector<BaseObject *> &args)>;
	class NativeFunction
	{
	private:
		FnNativeType m_function;
	public:
		NativeFunction() = default;
		NativeFunction(FnNativeType fn) : m_function(fn) { }

		bool call(VmState &state, const std::vector<BaseObject *> &args)
		{
			return m_function(state, args);
		}
	};

	struct VmState
	{
		uint64_t regs[REGISTERS_COUNT] = {0};
		std::vector<BaseObject *> stack;

		std::unordered_map<std::string, NativeFunction> natives;

		~VmState()
		{
			for (const auto &val : stack)
			{
				delete val;
			}
		}

		void addNativeFn(const std::string &fnName, FnNativeType fn)
		{
			natives[fnName] = NativeFunction(fn);
		}
	};

	// TODO: rework executer virtual machine
	inline bool exec(const std::vector<uint8_t> &bc)
	{
		VmState state;	
		state.addNativeFn("println", [](VmState &state, const std::vector<BaseObject *> &args)
		{
			for (const auto &obj : args)
			{
				std::cout << obj->toString();
			}

			std::cout << std::endl;

			return true;
		});

		while (state.regs[R_IP] != bc.size())
		{
			uint8_t op = bc[state.regs[R_IP]++];

			switch (op)
			{
			case OP_NOP:
				++state.regs[R_IP];
				break;
			case OP_LOAD:
			{
				StringObject obj;
				obj.type_ = (DiaBcTypes)bc[state.regs[R_IP]++];
				obj.isSigned_ = true;
				while (bc[state.regs[R_IP]] != '\0')
				{
					obj.value_.push_back(bc[state.regs[R_IP]++]);
				}
				++state.regs[R_IP];
				state.stack.emplace_back(new StringObject(obj));
				break;
			}
			case OP_CALL:
			{
				std::string fnName;
				while(bc[state.regs[R_IP]] != '\0')
				{
					fnName.push_back(bc[state.regs[R_IP]++]);
				}
				++state.regs[R_IP];

				state.natives[fnName].call(state, state.stack);

				break;
			}
			case OP_RET:
				return true;
			default:
				return false;
			}
		}

		return false;
	}
}

#endif // DVM_VIRTUALMACHINE_HPP
