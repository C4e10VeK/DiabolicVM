#ifndef DVM_PARSER_HPP
#define DVM_PARSER_HPP

#include "Lexer.hpp"

namespace dialang
{
    class Parser
    {
    private:
        Lexer m_lexer;
        Token m_current;
        Token m_prev;
    public:

        Parser() = default;
        Parser(std::string code);

        void setSourceCode(const std::string &code);
    };
}

#endif // DVM_PARSER_HPP