
#include <iostream>
#include <fstream>
#include "parser.hpp"

int main()
{
	ASTNode *root = nullptr;
	baby_parse(&root);

	if (!root)
	{
		return 1;
	}

	root->print();

	delete root;
	return 0;
}
