
#include <iostream>
#include <fstream>
#include "parser.hpp"
#include "tac.hpp"

int main()
{

	auto code = "a = 1 + 2 * 3 - 4 / 5;"
				"b = 2;"
				"c = a + b;"
				"if a < b { c = 1; } else { c = 2; }"
				"if b > a { c = 3; } else { c = 4; }"
				"fn test(a, b, c) { return a + b + c; } "
				"test(1, a, 3 + b + c);";

	// auto code = "if a < b { c = 1; } else { c = 2; }";

	ASTNode *root = nullptr;
	baby_parse(&root, code);

	if (!root)
	{
		return 1;
	}

	TACCollector collector;
	root->generateFunctionTAC(&collector);

	TAC main_label(TAC_OP::LABEL, "", "", "main");

	collector.add(main_label);
	root->generateTAC(&collector);

	int i = 1;
	for (auto &instruction : collector.instructions)
	{
		if (instruction.op == TAC_OP::NONE)
		{
			std::cout << "SOMETHING WENT WRONG" << std::endl;
			exit(1);
			continue;
		}

		std::cout << i++ << ": ";
		if (instruction.op == TAC_OP::LABEL)
		{
			std::cout << instruction.result << ": " << std::endl;
			continue;
		}

		std::cout << "    ";

		if (instruction.op == TAC_OP::GOTO)
		{
			std::cout << "goto " << instruction.result << std::endl;
			continue;
		}

		if (instruction.op == TAC_OP::IF)
		{
			std::cout << "if " << instruction.arg1 << " goto " << instruction.result << std::endl;
			continue;
		}

		if (instruction.op == TAC_OP::BEGIN_FN)
		{
			std::cout << "begin_fn" << std::endl;
			continue;
		}

		if (instruction.op == TAC_OP::END_FN)
		{
			std::cout << "end_fn" << std::endl;
			continue;
		}

		if (instruction.op == TAC_OP::RETURN)
		{
			std::cout << "return " << instruction.result << std::endl;
			continue;
		}

		if (instruction.op == TAC_OP::PARAM)
		{
			std::cout << instruction.result << " = " << instruction.arg1 << std::endl;
			continue;
		}

		if (instruction.op == TAC_OP::ARG)
		{
			std::cout << "arg " << instruction.arg1 << std::endl;
			continue;
		}

		if (instruction.op == TAC_OP::CALL)
		{
			std::cout << "call " << instruction.arg1 << std::endl;
			continue;
		}

		if (instruction.op == TAC_OP::EQUAL)
		{
			std::cout << instruction.result << " = " << instruction.arg1 << std::endl;
			continue;
		}

		std::cout << instruction.result << " = " << instruction.arg1 << " "
				  << to_string(instruction.op) << " " << instruction.arg2 << std::endl;
	}

	delete root;
	return 0;
}
