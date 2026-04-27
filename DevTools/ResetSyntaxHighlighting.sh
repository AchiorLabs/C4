echo "FULL C4 ENV RESET STARTING..."

# ============================
# 1. VS Code extension uninstall
# ============================
echo "Removing VS Code C4 extension..."

# Try known extension IDs (adjust if needed)
code --uninstall-extension local.c4-language 2>/dev/null || true
code --uninstall-extension c4-language 2>/dev/null || true

# Remove any leftover installed extension folders
rm -rf ~/.vscode/extensions/*c4* 2>/dev/null || true

# Remove VS Code workspace settings
rm -rf .vscode 2>/dev/null || true

# ============================
# 2. Remove VSIX packages (your project builds)
# ============================
echo "Removing VSIX build artifacts..."

find . -name "*.vsix" -type f -delete 2>/dev/null || true

# remove extension build dir if exists
rm -rf devtools/c4-vscode-extension 2>/dev/null || true

# ============================
# 3. Uninstall vsce (global npm tool)
# ============================
echo "Uninstalling vsce..."

npm uninstall -g vsce 2>/dev/null || true

# optional cleanup of npm cache (safe)
npm cache clean --force >/dev/null 2>&1 || true

# ============================
# 4. Vim cleanup
# ============================
echo "Cleaning Vim configs..."

rm -f ~/.vim/syntax/c4.vim
rm -f ~/.vim/ftdetect/c4.vim

# ============================
# 5. Optional Neovim cleanup (safe even if unused)
# ============================
rm -rf ~/.config/nvim/after 2>/dev/null || true

# ============================
# Done
# ============================
echo "FULL RESET COMPLETE"
echo "Now restart terminal + VS Code before reinstalling."