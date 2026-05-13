make -f Linux.mk clean
make -f Linux.mk

sudo cp Target/Main /usr/bin/C4C
sudo cp c4pm.sh /usr/bin/c4pm
sudo chmod 777 /usr/bin/c4pm
