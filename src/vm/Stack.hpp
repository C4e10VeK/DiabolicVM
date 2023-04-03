#ifndef DVM_STACK_HPP
#define DVM_STACK_HPP

#include <assert.h>
#include "Value.hpp"

namespace dialang::vm
{
    template<size_t N>
    class Stack
    {
    private:
        Value m_data[N];
        Value *m_top;
        size_t m_currentSize = 0;
    public:
        explicit Stack() : m_top(m_data) { }

        Value &getTop() const noexcept
        {
            return *m_top;
        }

        constexpr size_t getSize() const noexcept
        {
            return N;
        }

        void push(const Value &value)
        {
            assert(m_currentSize < N);

            *m_top = value;
            ++m_top;
            ++m_currentSize;
        }

        void push(Value &&value)
        {
            assert(m_currentSize < N);
            *m_top = value;
            ++m_top;
            ++m_currentSize;
        }

        Value pop()
        {
            Value res = *(m_top - 1);
            --m_top;
            --m_currentSize;
            return res;
        }

        Value &peek(size_t n) const noexcept
        {
            assert(n < m_currentSize);
            return m_data[n];
        }
    };
}

#endif // DVM_STACK_HPP