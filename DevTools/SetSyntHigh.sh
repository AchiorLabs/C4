#!/bin/bash

set -e  # Stop on error

echo "Setting up C4 syntax highlighters for your editors..."


# --------------------------------------------
# Detect distro
# --------------------------------------------
if [ -f /etc/os-release ]; then
  . /etc/os-release
  DISTRO=$ID
else
  echo "Cannot detect Linux distribution"
  exit 1
fi

echo "[+] Detected distro: $DISTRO"

# --------------------------------------------
# Install Node.js (v20 LTS)
# --------------------------------------------

install_node_debian() {
  echo "[+] Installing Node.js (Debian/Ubuntu)..."
  sudo apt update -y
  sudo apt install -y curl ca-certificates gnupg

  curl -fsSL https://deb.nodesource.com/setup_20.x | sudo -E bash -
  sudo apt install -y nodejs
}

install_node_arch() {
  echo "[+] Installing Node.js (Arch)..."
  sudo pacman -Sy --noconfirm nodejs npm
}

install_node_fedora() {
  echo "[+] Installing Node.js (Fedora)..."
  sudo dnf install -y nodejs npm
}

install_node_opensuse() {
  echo "[+] Installing Node.js (OpenSUSE)..."
  sudo zypper install -y nodejs npm
}

install_node_alpine() {
  echo "[+] Installing Node.js (Alpine)..."
  sudo apk add --no-cache nodejs npm
}

# --------------------------------------------
# Check Node.js
# --------------------------------------------

if ! command -v node >/dev/null 2>&1; then
  echo "Node.js not found. Installing..."

  case "$DISTRO" in
    ubuntu|debian|linuxmint|pop)
      install_node_debian
      ;;
    arch|manjaro)
      install_node_arch
      ;;
    fedora)
      install_node_fedora
      ;;
    opensuse*|suse)
      install_node_opensuse
      ;;
    alpine)
      install_node_alpine
      ;;
    *)
      echo "Unsupported distro: $DISTRO"
      echo "Please install Node.js manually:"
      echo "https://nodejs.org/"
      exit 1
      ;;
  esac
fi

# --------------------------------------------
# Verify Node version
# --------------------------------------------

NODE_VERSION=$(node -v | sed 's/v//')
MAJOR=$(echo "$NODE_VERSION" | cut -d. -f1)

if [ "$MAJOR" -lt 18 ]; then
  echo "Node version too old ($NODE_VERSION). Upgrading..."

  case "$DISTRO" in
    ubuntu|debian|linuxmint|pop)
      install_node_debian
      ;;
    arch|manjaro)
      sudo pacman -S --noconfirm nodejs npm
      ;;
    fedora)
      sudo dnf upgrade -y nodejs
      ;;
    opensuse*|suse)
      sudo zypper update -y nodejs
      ;;
    alpine)
      sudo apk upgrade nodejs npm
      ;;
    *)
      echo "Cannot auto-upgrade Node on this distro"
      exit 1
      ;;
  esac
fi

echo "Node.js OK ($(node -v))"

# --------------------------------------------
# Check npm
# --------------------------------------------

echo "Checking npm..."

if ! command -v npm >/dev/null 2>&1; then
  echo "npm missing. Attempting to install..."

  case "$DISTRO" in
    arch|manjaro)
      sudo pacman -S --noconfirm npm
      ;;
    *)
      echo "npm should come with Node.js. Reinstalling Node..."
      install_node_debian
      ;;
  esac
fi

echo "npm OK ($(npm -v))"




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
