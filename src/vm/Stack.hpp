#ifndef DVM_STACK_HPP
#define DVM_STACK_HPP

#include "Value.hpp"

namespace dialang::vm
{
    template<size_t N>
    class Stack
    {
    private:
        Value m_data[N];
        Value *m_top;
    public:
        explicit Stack() : m_top(m_data) { }

        Value &getTop() const
        {
            return *m_top;
        }

        constexpr size_t getSize() const noexcept
        {
            return N;
        }

        void push(const Value &value)
        {
            *m_top = value;
            ++m_top;
        }

        void push(Value &&value)
        {
            *m_top = value;
            ++m_top;
        }

        Value pop()
        {
            Value res = *(m_top - 1);
            --m_top;
            return res;
        }

        Value &peek(size_t n) const noexcept
        {
            return m_data[n];
        }
    };
}

#endif // DVM_STACK_HPP