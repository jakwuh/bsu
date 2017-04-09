@echo on

:: 1
hostname

:: 2
ipconfig /all

:: 3
nslookup vk.com
ping -i 20 87.240.165.82
ping -l 512 -n 10 -i 255 vk.com

ping ::1
ping 127.0.0.1

ping ya.ru
ping yandex.ru
nslookup ya.ru
nslookup yandex.ru

:: 4
tracert -d -h 10 vk.com

:: 5
arp -a

:: 6
netstat -a -p TCP
netstat -a -n -p TCP
netstat -a -s -r

:: 7
net view
net view \\IE11WIN7

:: 8
route PRINT
