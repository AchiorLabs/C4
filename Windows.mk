CC=cl
SRC=Src
OBJ=Objects
TARGET=Target

CFLAGS=/nologo /c
OUTOBJ=/Fo:
OUTEXE=/Fe:


OBJECTS= \
$(OBJ)/Support/BumpAllocator.obj \
$(OBJ)/Support/String.obj \
$(OBJ)/Support/Log.obj \
$(OBJ)/Support/List.obj \
$(OBJ)/CmdLine/CmdLineArgumentList.obj \
$(OBJ)/CmdLine/CmdLine.obj \
$(OBJ)/C4COptions/C4COptions.obj \
$(OBJ)/FrontEnd/Lexer/Token.obj \
$(OBJ)/FrontEnd/Lexer/Lexer.obj \
$(OBJ)/FrontEnd/AST/AST.obj \
$(OBJ)/FrontEnd/AST/ASTPrint.obj \
$(OBJ)/FrontEnd/Parser/Parser.obj \
$(OBJ)/FrontEnd/TreeWalker/TreeWalker.obj \
$(OBJ)/FrontEnd/Driver/Driver.obj \
$(OBJ)/MiddleEnd/C/ASTToC.obj \
$(OBJ)/MiddleEnd/Driver/Driver.obj \
$(OBJ)/Driver/Driver.obj


$(TARGET)/Main.exe: $(OBJECTS)
	$(CC) $^ /Fe:$(TARGET)/Main.exe


$(OBJ)/Support/BumpAllocator.obj: $(SRC)/Support/BumpAllocator.c
	$(CC) $(CFLAGS) $< $(OUTOBJ)$@

$(OBJ)/Support/String.obj: $(SRC)/Support/String.c
	$(CC) $(CFLAGS) $< $(OUTOBJ)$@

$(OBJ)/Support/Log.obj: $(SRC)/Support/Log.c
	$(CC) $(CFLAGS) $< $(OUTOBJ)$@

$(OBJ)/Support/List.obj: $(SRC)/Support/List.c
	$(CC) $(CFLAGS) $< $(OUTOBJ)$@


$(OBJ)/CmdLine/CmdLineArgumentList.obj: $(SRC)/CmdLine/CmdLineArgumentList.c
	$(CC) $(CFLAGS) $< $(OUTOBJ)$@

$(OBJ)/CmdLine/CmdLine.obj: $(SRC)/CmdLine/CmdLine.c
	$(CC) $(CFLAGS) $< $(OUTOBJ)$@

$(OBJ)/C4COptions/C4COptions.obj: $(SRC)/C4COptions/C4COptions.c
	$(CC) $(CFLAGS) $< $(OUTOBJ)$@

$(OBJ)/FrontEnd/Lexer/Token.obj: $(SRC)/FrontEnd/Lexer/Token.c
	$(CC) $(CFLAGS) $< $(OUTOBJ)$@

$(OBJ)/FrontEnd/Lexer/Lexer.obj: $(SRC)/FrontEnd/Lexer/Lexer.c
	$(CC) $(CFLAGS) $< $(OUTOBJ)$@

$(OBJ)/FrontEnd/AST/AST.obj: $(SRC)/FrontEnd/AST/AST.c
	$(CC) $(CFLAGS) $< $(OUTOBJ)$@

$(OBJ)/FrontEnd/AST/ASTPrint.obj: $(SRC)/FrontEnd/AST/ASTPrint.c
	$(CC) $(CFLAGS) $< $(OUTOBJ)$@

$(OBJ)/FrontEnd/Parser/Parser.obj: $(SRC)/FrontEnd/Parser/Parser.c
	$(CC) $(CFLAGS) $< $(OUTOBJ)$@

$(OBJ)/FrontEnd/TreeWalker/TreeWalker.obj: $(SRC)/FrontEnd/TreeWalker/TreeWalker.c
	$(CC) $(CFLAGS) $< $(OUTOBJ)$@

$(OBJ)/FrontEnd/Driver/Driver.obj: $(SRC)/FrontEnd/Driver/Driver.c
	$(CC) $(CFLAGS) $< $(OUTOBJ)$@


$(OBJ)/MiddleEnd/C/ASTToC.obj: $(SRC)/MiddleEnd/C/ASTToC.c
	$(CC) $(CFLAGS) $< $(OUTOBJ)$@

$(OBJ)/MiddleEnd/Driver/Driver.obj: $(SRC)/MiddleEnd/Driver/Driver.c
	$(CC) $(CFLAGS) $< $(OUTOBJ)$@


$(OBJ)/Driver/Driver.obj: $(SRC)/Driver/Driver.c
	$(CC) $(CFLAGS) $< $(OUTOBJ)$@


