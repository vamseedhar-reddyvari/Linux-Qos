
tc qdisc replace dev br-lan root handle 1: htb default 3
tc class add dev br-lan parent 1: classid 1:2 htb rate 200kbps ceil 200kbps

#reset
tc qdisc replace dev  wlan0 root pfifo
tc qdisc replace dev  eth0 root pfifo
tc qdisc replace dev  eth1 root pfifo
