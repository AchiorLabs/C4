#!/bin/bash

set -e  # Stop on error

echo "Setting up C4 syntax highlighters for your editors..."



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
