


CC=gcc
OBJ=Objects
SRC=Src
TARGET=Target

OBJECTS= $(OBJ)/Support/BumpAllocator.o                   \
		 $(OBJ)/Support/String.o                          \
		 $(OBJ)/Support/Log.o                             \
		 $(OBJ)/Support/List.o                            \
		 $(OBJ)/CmdLine/CmdLineArgumentList.o             \
		 $(OBJ)/CmdLine/CmdLine.o                         \
		 $(OBJ)/C4COptions/C4COptions.o                   \
		 $(OBJ)/FrontEnd/Lexer/Token.o                    \
		 $(OBJ)/FrontEnd/Lexer/Lexer.o                    \
		 $(OBJ)/FrontEnd/AST/AST.o                        \
		 $(OBJ)/FrontEnd/AST/ASTPrint.o                   \
		 $(OBJ)/FrontEnd/Parser/Parser.o                  \
		 $(OBJ)/FrontEnd/TreeWalker/TreeWalker.o          \
		 $(OBJ)/FrontEnd/Driver/Driver.o                  \
		 $(OBJ)/MiddleEnd/C/ASTToC.o                      \
		 $(OBJ)/MiddleEnd/Driver/Driver.o                 \
		 $(OBJ)/Driver/Driver.o                           \






Target/Main: $(OBJECTS) $(SRC)/Main.c
	$(CC) $^ -o $@


$(OBJ)/Support/BumpAllocator.o: $(SRC)/Support/BumpAllocator.c
	$(CC) -c $^ -o $@


$(OBJ)/Support/String.o: $(SRC)/Support/String.c
	$(CC) -c $^ -o $@


$(OBJ)/Support/Log.o: $(SRC)/Support/Log.c
	$(CC) -c $^ -o $@


$(OBJ)/Support/List.o: $(SRC)/Support/List.c
	$(CC) -c $^ -o $@




$(OBJ)/CmdLine/CmdLineArgumentList.o:$(SRC)/CmdLine/CmdLineArgumentList.c
	$(CC) -c $^ -o $@

$(OBJ)/CmdLine/CmdLine.o:$(SRC)/CmdLine/CmdLine.c
	$(CC) -c $^ -o $@




$(OBJ)/C4COptions/C4COptions.o:$(SRC)/C4COptions/C4COptions.c
	$(CC) -c $^ -o $@





$(OBJ)/FrontEnd/Lexer/Token.o: $(SRC)/FrontEnd/Lexer/Token.c
	$(CC) -c $^ -o $@


$(OBJ)/FrontEnd/Lexer/Lexer.o: $(SRC)/FrontEnd/Lexer/Lexer.c
	$(CC) -c $^ -o $@




$(OBJ)/FrontEnd/AST/AST.o: $(SRC)/FrontEnd/AST/AST.c
	$(CC) -c $^ -o $@


$(OBJ)/FrontEnd/AST/ASTPrint.o: $(SRC)/FrontEnd/AST/ASTPrint.c
	$(CC) -c $^ -o $@


$(OBJ)/FrontEnd/Parser/Parser.o: $(SRC)/FrontEnd/Parser/Parser.c
	$(CC) -c $^ -o $@




$(OBJ)/FrontEnd/TreeWalker/TreeWalker.o: $(SRC)/FrontEnd/TreeWalker/TreeWalker.c
	$(CC) -c $^ -o $@


$(OBJ)/FrontEnd/Driver/Driver.o: $(SRC)/FrontEnd/Driver/Driver.c
	$(CC) -c $^ -o $@



$(OBJ)/MiddleEnd/C/ASTToC.o: $(SRC)/MiddleEnd/C/ASTToC.c
	$(CC) -c $^ -o $@


$(OBJ)/MiddleEnd/Driver/Driver.o: $(SRC)/MiddleEnd/Driver/Driver.c
	$(CC) -c $^ -o $@


$(OBJ)/Driver/Driver.o: $(SRC)/Driver/Driver.c
	$(CC) -c $^ -o $@



clean:
	rm -rf $(OBJ) $(TARGET)/Main
	bash SetUp.sh
