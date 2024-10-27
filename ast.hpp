#pragma once

#include "parser.hpp"
#include <string>
#include <iostream>
#include <vector>

class ASTNode
{
public:
    virtual ~ASTNode() {}
    virtual void print() = 0;
};

class ASTNodeAdd : public ASTNode
{
protected:
    ASTNode *left;
    ASTNode *right;

public:
    ASTNodeAdd() = default;
    ASTNodeAdd(ASTNode *left, ASTNode *right) : left(left), right(right) {}
    virtual ~ASTNodeAdd()
    {
        delete left;
        delete right;
    }
    virtual void print()
    {
        left->print();
        right->print();
    }
};

class ASTNodeSub : public ASTNode
{
protected:
    ASTNode *left;
    ASTNode *right;

public:
    ASTNodeSub() = default;
    ASTNodeSub(ASTNode *left, ASTNode *right) : left(left), right(right) {}
    virtual ~ASTNodeSub()
    {
        delete left;
        delete right;
    }
    virtual void print()
    {
        left->print();
        right->print();
    }
};

class ASTNodeUnaryMinus : public ASTNode
{
protected:
    ASTNode *child;

public:
    ASTNodeUnaryMinus(ASTNode *child) : child(child) {}
    virtual ~ASTNodeUnaryMinus()
    {
        delete child;
    }
    virtual void print()
    {
        child->print();
    }
};

class ASTNodeIdentifier : public ASTNode
{
protected:
    std::string name;

public:
    ASTNodeIdentifier(std::string name) : name(name) {}
    virtual ~ASTNodeIdentifier()
    {
    }
    virtual void print()
    {
        std::cout << name << std::endl;
    }
};

class ASTNodeNumber : public ASTNode
{
protected:
    int value;

public:
    virtual ~ASTNodeNumber()
    {
    }
    ASTNodeNumber(int value) : value(value) {}
    virtual void print()
    {
        std::cout << value << std::endl;
    }
};

class ASTNodeFunctionDeclaration : public ASTNode
{
protected:
    ASTNodeIdentifier *name;
    ASTNode *body;

public:
    ASTNodeFunctionDeclaration(ASTNodeIdentifier *name, ASTNode *body) : name(name), body(body) {}
    virtual ~ASTNodeFunctionDeclaration()
    {
        delete name;
        delete body;
    }
    virtual void print()
    {
        name->print();
        body->print();
    }
};

class ASTNodeFunctionCall : public ASTNode
{
protected:
    ASTNodeIdentifier *name;
    ASTNode *args;

public:
    ASTNodeFunctionCall(ASTNodeIdentifier *name, ASTNode *args) : name(name), args(args) {}
    virtual ~ASTNodeFunctionCall()
    {
        delete name;
        delete args;
    }
    virtual void print()
    {
        name->print();
        args->print();
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
};

class ASTNodeBlock : public ASTNode
{

public:
    std::vector<ASTNode *> statements;

    ASTNodeBlock(std::vector<ASTNode *> statements) : statements(statements) {}
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
};

class ASTNodeVariableDeclaration : public ASTNode
{
protected:
    ASTNodeIdentifier *name;
    ASTNode *value;

public:
    ASTNodeVariableDeclaration(ASTNodeIdentifier *name, ASTNode *value) : name(name), value(value) {}
    virtual ~ASTNodeVariableDeclaration()
    {
        delete name;
        delete value;
    }
    virtual void print()
    {
        name->print();
        value->print();
    }
};