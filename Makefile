
all: baby

baby: lexer.l parser.y main.cpp
	bison -d -o parser.cpp parser.y
	flex -o lexer.cpp lexer.l
	g++ -std=c++11 -o baby main.cpp parser.cpp lexer.cpp

clean:
	rm -f baby

