CC=cl
SRC=Src
OBJ=Objects
TARGET=Target

CFLAGS=/nologo /c
OUTOBJ=/Fo:
OUTEXE=/Fe:


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

# Linking the final executable (Main.exe)

$(TARGET)/Main.exe: \
$(OBJ)/FrontEnd/Lexer/Lexer.obj \
$(OBJ)/FrontEnd/AST/AST.obj \
$(OBJ)/FrontEnd/AST/ASTPrint.obj \
$(OBJ)/FrontEnd/Parser/Parser.obj \
$(OBJ)/FrontEnd/TreeWalker/TreeWalker.obj \
$(OBJ)/FrontEnd/Driver/Driver.obj \
$(OBJ)/MiddleEnd/C/ASTToC.obj \
$(OBJ)/MiddleEnd/Driver/Driver.obj \
$(OBJ)/Driver/Driver.obj
	$(CC) $^ /Fe:$(TARGET)/Main.exe

# Ensure Target directory exists
$(TARGET):
	if not exist $(TARGET) mkdir $(TARGET)

# Default build target
all: $(TARGET) $(TARGET)/Main.exe

# --- Clean ---

clean:
	if exist $(OBJ) rmdir /s /q $(OBJ)
	if exist $(TARGET)\Main.exe del /f /q $(TARGET)\Main.exe
