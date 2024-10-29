#pragma once

#include "parser.hpp"
#include "tac.hpp"
#include <string>
#include <iostream>
#include <vector>

class ASTNode
{
public:
    virtual ~ASTNode() {}
    virtual void print() = 0;
    virtual TAC generateTAC(TACCollector *collector) = 0;
    virtual void generateFunctionTAC(TACCollector *collector) {}
};

class ASTNodeBinary : public ASTNode
{
protected:
    ASTNode *left;
    ASTNode *right;
    std::string op;

public:
    ASTNodeBinary() = default;
    ASTNodeBinary(ASTNode *left, std::string op, ASTNode *right) : left(left), op(op), right(right) {}
    virtual ~ASTNodeBinary()
    {
        delete left;
        delete right;
    }

    virtual void print()
    {
        left->print();
        right->print();
    }

    virtual TAC generateTAC(TACCollector *collector)
    {
        if (op == "+")
        {
            TAC tac(TAC_OP::ADD, left->generateTAC(collector).result, right->generateTAC(collector).result, "t" + std::to_string(collector->instructions.size()));
            collector->add(tac);
            return tac;
        }
        else if (op == "-")
        {
            TAC tac(TAC_OP::SUB, left->generateTAC(collector).result, right->generateTAC(collector).result, "t" + std::to_string(collector->instructions.size()));
            collector->add(tac);
            return tac;
        }
        else if (op == "*")
        {
            TAC tac(TAC_OP::MUL, left->generateTAC(collector).result, right->generateTAC(collector).result, "t" + std::to_string(collector->instructions.size()));
            collector->add(tac);
            return tac;
        }
        else if (op == "/")
        {
            TAC tac(TAC_OP::DIV, left->generateTAC(collector).result, right->generateTAC(collector).result, "t" + std::to_string(collector->instructions.size()));
            collector->add(tac);
            return tac;
        }
        else if (op == ">")
        {
            TAC tac(TAC_OP::GREATER, left->generateTAC(collector).result, right->generateTAC(collector).result, "t" + std::to_string(collector->instructions.size()));
            collector->add(tac);
            return tac;
        }
        else if (op == ">=")
        {
            TAC tac(TAC_OP::GREATER_EQUAL, left->generateTAC(collector).result, right->generateTAC(collector).result, "t" + std::to_string(collector->instructions.size()));
            collector->add(tac);
            return tac;
        }
        else if (op == "<")
        {
            TAC tac(TAC_OP::LESS, left->generateTAC(collector).result, right->generateTAC(collector).result, "t" + std::to_string(collector->instructions.size()));
            collector->add(tac);
            return tac;
        }
        else if (op == "<")
        {
            TAC tac(TAC_OP::LESS_EQUAL, left->generateTAC(collector).result, right->generateTAC(collector).result, "t" + std::to_string(collector->instructions.size()));
            collector->add(tac);
            return tac;
        }
        else if (op == "==")
        {
            TAC tac(TAC_OP::EQUAL_EQUAL, left->generateTAC(collector).result, right->generateTAC(collector).result, "t" + std::to_string(collector->instructions.size()));
            collector->add(tac);
            return tac;
        }
        else if (op == "!=")
        {
            TAC tac(TAC_OP::NOT_EQUAL, left->generateTAC(collector).result, right->generateTAC(collector).result, "t" + std::to_string(collector->instructions.size()));
            collector->add(tac);
            return tac;
        }
        else
        {
            std::cerr << "Unknown operator: " << op << std::endl;
            exit(1);
        }
    }
};

class ASTNodeUnary : public ASTNode
{
protected:
    ASTNode *child;
    std::string op;

public:
    ASTNodeUnary(std::string op, ASTNode *child) : child(child), op(op) {}
    virtual ~ASTNodeUnary()
    {
        delete child;
    }

    virtual void print()
    {
        child->print();
    }

    virtual TAC generateTAC(TACCollector *collector)
    {
        if (op == "-")
        {
            TAC tac(TAC_OP::UNARY_MINUS, child->generateTAC(collector).result, "", "t" + std::to_string(collector->instructions.size()));
            collector->add(tac);
            return tac;
        }
        else
        {
            std::cerr << "Unknown operator: " << op << std::endl;
            exit(1);
        }
    }
};

class ASTNodeNumber : public ASTNode
{
public:
    int value;

    ASTNodeNumber(int value) : value(value) {}
    virtual ~ASTNodeNumber()
    {
    }

    virtual void print()
    {
        std::cout << value << std::endl;
    }

    virtual TAC generateTAC(TACCollector *collector)
    {

        return TAC(TAC_OP::NONE, "", "", std::to_string(value));
    }
};

class ASTNodeVariableDeclaration : public ASTNode
{
protected:
    std::string name;
    ASTNode *value;

public:
    ASTNodeVariableDeclaration(std::string name, ASTNode *value) : name(name), value(value) {}
    virtual ~ASTNodeVariableDeclaration()
    {
        delete value;
    }

    virtual void print()
    {
        std::cout << name << std::endl;
        value->print();
    }

    virtual TAC generateTAC(TACCollector *collector)
    {
        TAC tac(TAC_OP::EQUAL, value->generateTAC(collector).result, "", name);
        collector->add(tac);
        return tac;
    }
};

class ASTNodeIdentifier : public ASTNode
{
protected:
    std::string name;

public:
    ASTNodeIdentifier(std::string name) : name(name) {}
    virtual ~ASTNodeIdentifier() {}

    virtual void print()
    {
        std::cout << name << std::endl;
    }

    virtual TAC generateTAC(TACCollector *collector)
    {
        return TAC(TAC_OP::NONE, "", "", name);
    }
};

class ASTNodeBlock : public ASTNode
{
public:
    std::vector<ASTNode *> statements;

    ASTNodeBlock(std::vector<ASTNode *> statements) : statements(statements) {}

    ASTNodeBlock() = default;
    virtual ~ASTNodeBlock()
    {
        for (auto &statement : statements)
        {
            delete statement;
        }
    }

    virtual void print()
    {
        for (auto &statement : statements)
        {
            statement->print();
        }
    }

    virtual TAC generateTAC(TACCollector *collector)
    {
        for (auto &statement : statements)
        {
            statement->generateTAC(collector);
        }

        return TAC(TAC_OP::NONE, "", "", "");
    }

    virtual void generateFunctionTAC(TACCollector *collector)
    {
        for (auto &statement : statements)
        {
            statement->generateFunctionTAC(collector);
        }
    }
};

class ASTNodeIf : public ASTNode
{
protected:
    ASTNode *condition;
    ASTNode *thenBlock;
    ASTNode *elseBlock;

public:
    ASTNodeIf(ASTNode *condition, ASTNode *thenBlock, ASTNode *elseBlock)
        : condition(condition), thenBlock(thenBlock), elseBlock(elseBlock) {}

    virtual ~ASTNodeIf()
    {
        delete condition;
        delete thenBlock;
        delete elseBlock;
    }

    virtual void print()
    {
        std::cout << "if" << std::endl;
        condition->print();
        thenBlock->print();
        elseBlock->print();
    }

    virtual TAC generateTAC(TACCollector *collector)
    {
        TAC if_tac(TAC_OP::IF, condition->generateTAC(collector).result, "", "");
        int if_index = collector->instructions.size();

        TAC false_goto(TAC_OP::GOTO, "", "", "");

        collector->add(if_tac);

        int false_goto_index = collector->instructions.size();

        collector->add(false_goto);

        TAC true_label(TAC_OP::LABEL, "", "", "");
        collector->add_label(true_label);

        thenBlock->generateTAC(collector);

        TAC then_goto_tac(TAC_OP::GOTO, "", "", "");
        int then_goto_index = collector->instructions.size();

        collector->add(then_goto_tac);

        collector->instructions[if_index].result = std::to_string(collector->label_index);

        TAC false_label(TAC_OP::LABEL, "", "", "");
        collector->add_label(false_label);

        elseBlock->generateTAC(collector);

        collector->instructions[false_goto_index].result = std::to_string(collector->label_index);

        TAC end_label(TAC_OP::LABEL, "", "", "");

        collector->add_label(end_label);

        collector->instructions[then_goto_index].result = std::to_string(collector->label_index);

        return TAC(TAC_OP::NONE, "", "", "");
    }
};

class ASTNodeParameters : public ASTNode
{
public:
    std::vector<std::string> params;

    ASTNodeParameters(std::vector<std::string> params) : params(params) {}
    virtual ~ASTNodeParameters() {}

    virtual void print()
    {
        for (auto &param : params)
        {
            std::cout << param << std::endl;
        }
    }

    virtual TAC generateTAC(TACCollector *collector)
    {
        return TAC(TAC_OP::NONE, "", "", "");
    }

    virtual void generateFunctionTAC(TACCollector *collector)
    {
        for (int i = 0; i < params.size(); i++)
        {
            TAC tac(TAC_OP::PARAM, "ARG " + std::to_string(i), "", params[i]);
            collector->add(tac);
        }
    }
};

class ASTNodeFunctionDeclaration : public ASTNode
{
protected:
    std::string name;
    ASTNodeBlock *block;
    ASTNodeParameters *params;

public:
    ASTNodeFunctionDeclaration(std::string name, ASTNodeParameters *params, ASTNodeBlock *block)
        : name(name), block(block), params(params) {}

    virtual ~ASTNodeFunctionDeclaration()
    {
        delete block;
        delete params;
    }

    virtual void print()
    {
        std::cout << name << std::endl;
        block->print();
    }

    virtual TAC generateTAC(TACCollector *collector)
    {
        return TAC(TAC_OP::NONE, "", "", "");
    }

    virtual void generateFunctionTAC(TACCollector *collector)
    {
        TAC label(TAC_OP::LABEL, "", "", name);
        collector->add(label);

        TAC begin_fn(TAC_OP::BEGIN_FN, "", "", "");

        collector->add(begin_fn);

        params->generateTAC(collector);

        block->generateFunctionTAC(collector);

        TAC end_fn(TAC_OP::END_FN, "", "", "");

        collector->add(end_fn);
    }
};

class ASTNodeReturn : public ASTNode
{
protected:
    ASTNode *value;

public:
    ASTNodeReturn(ASTNode *value) : value(value) {}
    virtual ~ASTNodeReturn()
    {
        delete value;
    }

    virtual void print()
    {
        value->print();
    }

    virtual TAC generateTAC(TACCollector *collector)
    {
        return TAC(TAC_OP::NONE, "", "", "");
    }

    virtual void generateFunctionTAC(TACCollector *collector)
    {
        TAC tac(TAC_OP::RETURN, value->generateTAC(collector).result, "", "");
        collector->add(tac);
    }
};

class ASTNodeArguments : public ASTNode
{
public:
    std::vector<ASTNode *> arguments;

    ASTNodeArguments(std::vector<ASTNode *> arguments) : arguments(arguments) {}

    virtual ~ASTNodeArguments()
    {
        for (auto &argument : arguments)
        {
            delete argument;
        }
    }

    virtual void print()
    {
        for (auto &argument : arguments)
        {
            argument->print();
        }
    }

    virtual TAC generateTAC(TACCollector *collector)
    {
        for (auto &argument : arguments)
        {
            TAC tac(TAC_OP::ARG, argument->generateTAC(collector).result, "", "");
            collector->add(tac);
        }

        return TAC(TAC_OP::NONE, "", "", "");
    }
};

class ASTNodeFunctionCall : public ASTNode
{
protected:
    std::string name;
    ASTNodeArguments *arguments;

public:
    ASTNodeFunctionCall(std::string name, ASTNodeArguments *arguments)
        : name(name), arguments(arguments) {}

    virtual ~ASTNodeFunctionCall()
    {
        delete arguments;
    }

    virtual void print()
    {
        std::cout << name << std::endl;
        arguments->print();
    }

    virtual TAC generateTAC(TACCollector *collector)
    {
        arguments->generateTAC(collector);

        TAC tac(TAC_OP::CALL, name, "", "");

        collector->add(tac);
        return TAC(TAC_OP::NONE, "", "", "");
    }
};
