#include "Parser.hpp"
#include "../utils.hpp"

namespace dialang
{
    Parser::Parser(std::string code) : m_lexer(std::move(code)) { }

    void Parser::setSourceCode(const std::string &code)
    {
        m_lexer.setCode(code);
    }

}