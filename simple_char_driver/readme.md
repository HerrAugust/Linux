# Simple Char Driver

## What is it?
A simple char driver that, taken a string from the user, send it to the driver, which in turn sends it back to the user.
The user can input the string in main.c.

## Install<br/>
Kernel:<br/>
Compile your kernel

Driver:<br/>
cd LinuxDrivers/simple_char_driver<br/>
make<br/>
sudo insmod simple_char_driver.ko<br/>
cat /var/log/kernel.log <---- here you can read YOUR_MAJOR at the bottom!<br/>
sudo mknod /dev/SimpleCharDriver c YOUR_MAJOR 0<br/>

User program:<br/>
gcc main.c<br/>
sudo ./a.out<br/>
