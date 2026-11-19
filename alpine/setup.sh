#!/bin/sh
# Run as root inside the Alpine VM, from the project folder:  sh alpine/setup.sh
# If the VM screen is a serial console, pass its name:  sh alpine/setup.sh ttyAMA0
set -e
TTY=${1:-tty1}

sed -i 's|^#\(.*/community\)$|\1|' /etc/apk/repositories
apk update
apk add build-base gdb valgrind git

make clean
make
cp dotsandboxes /usr/local/bin/dotsandboxes

# run the game on $TTY instead of the login prompt (respawns after it exits)
sed -i "/^#*$TTY::/d" /etc/inittab
echo "$TTY::respawn:/usr/local/bin/dotsandboxes" >> /etc/inittab
grep "^$TTY" /etc/inittab

# keep kernel messages from printing over the board
echo "kernel.printk = 1 4 1 7" > /etc/sysctl.d/quiet-console.conf

echo "Setup done. Type: reboot"
