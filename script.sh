sudo ifconfig wlp1s0 down
sudo iwconfig wlp1s0 mode ad-hoc
sudo iwconfig wlp1s0 channel 1 essid ABCD mode ad-hoc
sudo ifconfig wlp1s0 up
sudo ifconfig wlp1s0 192.168.0.4 netmask 255.255.255.0
