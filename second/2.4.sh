#!bin/bash
ping -c 1 www.baidu.com > /dev/null
if ping -c 1 www.baidu.com &> /dev/null
then
	echo "Internet is up"
else
	echo "Internet is down"
fi
