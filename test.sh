./echoserver 192.168.99.99 9999 &
sleep 2 
./client 192.168.99.99 9999 &
sleep 5
killall echoserver