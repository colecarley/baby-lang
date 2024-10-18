
#include <iostream>
#include <fstream>

int yyparse();


int main() {
	std::cout << "hello there" << std::endl;

	if (yyparse() == 0)
	{
		std::cout << "parsing completed successfully!" << std::endl;
	}
	else 
	{
		std::cout << "parsing failed" << std::endl;
	}


	return 0;
}

