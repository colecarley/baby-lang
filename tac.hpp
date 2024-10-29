#pragma once

#include <string>
#include <vector>

enum class TAC_OP
{
    ADD,
    SUB,
    MUL,
    DIV,
    LESS,
    LESS_EQUAL,
    GREATER,
    GREATER_EQUAL,
    EQUAL_EQUAL,
    NOT_EQUAL,
    NONE,
    EQUAL,
    UNARY_MINUS,
    IF,
    GOTO,
    LABEL,
    PARAM,
    CALL,
    RETURN,
    BEGIN_FN,
    END_FN,
    ARG,
};

inline std::string to_string(TAC_OP op)
{
    switch (op)
    {
    case TAC_OP::ADD:
        return "+";
    case TAC_OP::SUB:
        return "-";
    case TAC_OP::MUL:
        return "*";
    case TAC_OP::DIV:
        return "/";
    case TAC_OP::NONE:
        return "";
    case TAC_OP::UNARY_MINUS:
        return "-";
    case TAC_OP::EQUAL:
        return "";
    case TAC_OP::LESS:
        return "<";
    case TAC_OP::LESS_EQUAL:
        return "<=";
    case TAC_OP::GREATER:
        return ">";
    case TAC_OP::GREATER_EQUAL:
        return ">=";
    case TAC_OP::EQUAL_EQUAL:
        return "==";
    case TAC_OP::NOT_EQUAL:
        return "!=";
    case TAC_OP::IF:
        return "if";
    case TAC_OP::GOTO:
        return "goto";
    case TAC_OP::LABEL:
        return "label";
    case TAC_OP::PARAM:
        return "param";
    case TAC_OP::CALL:
        return "call";
    case TAC_OP::RETURN:
        return "return";
    case TAC_OP::BEGIN_FN:
        return "begin_fn";
    case TAC_OP::END_FN:
        return "end_fn";
    case TAC_OP::ARG:
        return "arg";
    }

    return "";
}

struct TAC
{
    TAC_OP op;
    std::string arg1;
    std::string arg2;
    std::string result;

    TAC(TAC_OP op, std::string arg1, std::string arg2, std::string result)
        : op(op), arg1(arg1), arg2(arg2), result(result) {}
};

struct TACCollector
{
    std::vector<TAC> instructions;
    int label_index = 0;

    void add(TAC tac)
    {
        instructions.push_back(tac);
    }

    void add_label(TAC tac)
    {
        tac.result = "L" + std::to_string(++label_index);
        instructions.push_back(tac);
    }
};
