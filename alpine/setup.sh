#!/bin/sh
# Run as root inside the Alpine VM, from the project folder:  sh alpine/setup.sh
set -e

sed -i 's|^#\(.*/community\)$|\1|' /etc/apk/repositories
apk update
apk add build-base gdb valgrind git

make clean
make
cp dotsandboxes /usr/local/bin/dotsandboxes

# run the game on tty1 instead of the login prompt (respawns after it exits)
sed -i 's|^tty1::respawn:.*|tty1::respawn:/usr/local/bin/dotsandboxes|' /etc/inittab
grep '^tty1' /etc/inittab

# keep kernel messages from printing over the board
echo "kernel.printk = 1 4 1 7" > /etc/sysctl.d/quiet-console.conf

echo "Setup done. Type: reboot"
