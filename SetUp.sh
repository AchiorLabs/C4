#!/usr/bin/env bash
set -e

# set up tools and dependencies for some linux distros
#



mkdir -p bin
mkdir -p Objects
mkdir -p Objects/FrontEnd/Lexer
mkdir -p Objects/FrontEnd/AST
mkdir -p Objects/FrontEnd/Parser
mkdir -p Objects/FrontEnd/TreeWalker
mkdir -p Objects/FrontEnd/IdentifierResolution
mkdir -p Objects/FrontEnd/LoopLabelling
mkdir -p Objects/FrontEnd/TypeChecking
mkdir -p Objects/FrontEnd/Driver
mkdir -p Objects/CmdLine
mkdir -p Objects/C4COptions
mkdir -p Objects/Driver
mkdir -p Objects/Support



mkdir -p Objects/MiddleEnd/C
mkdir -p Objects/MiddleEnd/Driver

sudo mkdir -p /usr/include/AchiorLabs/C4
sudo cp Support/Include/Types.h /usr/include/AchiorLabs/C4/Types.h

exit 0

mkdir -p Objects/MiddleEnd/c4il
mkdir -p Objects/MiddleEnd/optimization

mkdir -p Objects/backend/x86_64

if [ -f /etc/os-release ]; then
	. /etc/os-release
	DISTRO=$ID
else
	echo "[-] cannot detect distro information !! please install the reqired packages manually"
	echo "required packages are gcc and nasm and their dependencies"

fi

echo "[+] Detected distro : $DISTRO"
install_debian(){
	sudo apt install -y gcc nasm 
}
install_arch(){
	sudo pacman -Sy --noconfirm
	sudo pacman -S --noconfirm gcc nasm
}
## updating the distro has not been included due to reasons known to arch users and maybe others
install_opensuse(){
	sudo zypper install -y gcc nasm pattern devel_basis
}
install_fedora(){
	sudo dnf install -y gcc nasm @development-tools
}
install_alpine(){
	sudo apk add gcc nasm buid-base
}
case "$DISTRO" in
	ubuntu|debian|linuxmint|pop)
		install_debian
		;;
	arch|manjaro)
		install_arch
		;;
	fedora)
		install_fedora
		;;
	opensuse*|suse)
		install_opensuse
		;;
	alpine)
		install_alpine
		;;
	*)
		echo "[-] distro unsuported please install nasm and gcc manually before proceeding"
		exit 1
		;;
esac
echo "[+] Installlation complete!!"
echo "Have fun using c4 :)"
