#!/bin/bash

set -e  # Stop on error

echo "Setting up C4 syntax highlighters for your editors..."

# Get the absolute path to devtools folder
DEVTOOLS_DIR=$(realpath "$(dirname "$0")")

cd "$DEVTOOLS_DIR"


# ============================================
# VS Code Setup 
# ============================================
if command -v code &> /dev/null; then
    echo ""
    echo "Setting up VS Code extension for C4..."

    PROJECT_ROOT=$(realpath "$DEVTOOLS_DIR/..")
    EXT_DIR="$DEVTOOLS_DIR/C4VscodeExtension"

    mkdir -p "$EXT_DIR"

    echo "Creating extension structure..."

    # ----------------------------------------
    # package.json
    # ----------------------------------------
    cat > "$EXT_DIR/package.json" << 'EOF'
{
  "name": "c4-language",
  "displayName": "C4 Language",
  "description": "Syntax highlighting for C4 language",
  "version": "0.0.1",
  "publisher": "local",
  "engines": {
    "vscode": "^1.80.0"
  },
  "categories": ["Programming Languages"],
  "contributes": {
    "languages": [
      {
        "id": "c4",
        "aliases": ["C4", "c4"],
        "extensions": [".c4"]
      }
    ],
    "grammars": [
      {
        "language": "c4",
        "scopeName": "source.c4",
        "path": "./c4.tmLanguage.json"
      }
    ]
  }
}
EOF

    # ----------------------------------------
    # Copy TextMate grammar
    # ----------------------------------------
    cp "$DEVTOOLS_DIR/C4TextMate/c4.tmLanguage.json" "$EXT_DIR/c4.tmLanguage.json"

    cd "$EXT_DIR"

    # ----------------------------------------
    # Ensure Node + npm exist
    # ----------------------------------------
    if ! command -v npm &> /dev/null; then
        echo "npm is required but not installed."
        echo "Install Node.js first."
        exit 1
    fi

    # ----------------------------------------
    # Install vsce if missing
    # ----------------------------------------
    if ! command -v vsce &> /dev/null; then
        echo "Installing vsce (VS Code Extension CLI)..."
        npm install -g vsce
    else
        echo "vsce already installed"
    fi

    # ----------------------------------------
    # Package extension
    # ----------------------------------------
    echo "Packaging extension..."
    vsce package

    VSIX_FILE=$(ls *.vsix | head -n 1)

    if [ -z "$VSIX_FILE" ]; then
        echo "Failed to create VSIX package"
        exit 1
    fi

    # ----------------------------------------
    # Install extension
    # ----------------------------------------
    echo "Installing extension into VS Code..."
    code --install-extension "$VSIX_FILE" --force

    # ----------------------------------------
    # Workspace settings (file association)
    # ----------------------------------------
    mkdir -p "$PROJECT_ROOT/.vscode"

    cat > "$PROJECT_ROOT/.vscode/settings.json" << EOF
{
  "files.associations": {
    "*.c4": "c4"
  }
}
EOF

    echo "VS Code configured successfully!"
    echo ""
    echo "IMPORTANT:"
    echo "   1. Restart VS Code OR run:"
    echo "      Ctrl + Shift + P → Reload Window"
    echo ""
    echo "   2. Open a .c4 file"
    echo "   3. Ensure language mode shows: C4"

    cd "$DEVTOOLS_DIR"
else
    echo ""
    echo "VS Code not found, skipping..."
fi


# ============================================
# Vim Setup
# ============================================
if command -v vim &> /dev/null; then
    echo ""
    echo "Configuring Vim..."

    mkdir -p ~/.vim/syntax
    mkdir -p ~/.vim/ftdetect

    # Filetype detection
    cat > ~/.vim/ftdetect/c4.vim << EOF
augroup filetypedetect
  autocmd!
  autocmd BufRead,BufNewFile *.c4 setfiletype c4
augroup END
EOF

    # Syntax file
    cat > ~/.vim/syntax/c4.vim << 'EOF'
" C4 Syntax Highlighting

if exists("b:current_syntax")
  finish
endif

" Keywords
syntax keyword c4Keyword fn struct return if elif else while loop break continue foreign pub static naked as

" Types
syntax keyword c4Type bool char void i8 i16 i32 i64 u8 u16 u32 u64 f32 f64 str

" Booleans
syntax keyword c4Boolean true false

" Numbers
syntax match c4Number /\v<(\d+|0x[0-9a-fA-F]+|0b[01]+|0o[0-7]+|\d+\.\d+)>/

" Strings
syntax region c4String start=/"/ skip=/\\"/ end=/"/
syntax region c4Char start=/'/ skip=/\\'/ end=/'/

" Comments
syntax match c4Comment "//.*$"
syntax region c4Comment start=/\/\*/ end=/\*\//

" Operators (IMPORTANT FIX)
syntax match c4Operator /[+\-*/%=!<>|&^~]\+/

" Highlight links
highlight link c4Keyword Keyword
highlight link c4Type Type
highlight link c4Boolean Boolean
highlight link c4Number Number
highlight link c4String String
highlight link c4Char Character
highlight link c4Comment Comment
highlight link c4Operator Operator

let b:current_syntax = "c4"
EOF

    echo "Vim syntax highlighting installed"
    echo "  Restart Vim and open a .c4 file"
else
    echo ""
    echo "  Vim not found, skipping..."
fi



# ============================================
# Summary and instructions
# ============================================

echo ""
echo " Your editors are now configured to highlight c4 files"
echo ""


echo ""
echo "========================================================================"
echo " QUICK VERIFICATION:"
echo "========================================================================"
echo ""
echo "To test if highlighting is working "
echo ""
echo "  1. Create a test.c4 file:"
echo "     fn main() :"
echo "       // This is a comment"
echo "       let x = 42"
echo "       return x"
echo "     :"
echo ""
echo "  2. Open it in your editor - comments, keywords, numbers should be colored"
