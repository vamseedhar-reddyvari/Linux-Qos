import matplotlib.pyplot as plt




def count_pkts(file_name):
    opened_file = open(file_name,encoding='utf-8')

    IP_Tables_Line = False
    tc_sent = []
    ip_mark = []
    for line in opened_file:
        if(IP_Tables_Line):
            line = line.strip(' ')
            mark_base = (int(line.split(' ')[1] ))
            IP_Tables_Line = False
            break
        else:
            tc_base = int(line.split(' ')[2])
            IP_Tables_Line = True


    for line in opened_file:
        if(IP_Tables_Line):
            line = line.strip(' ')
            ip_mark.append(int(line.split(' ')[1] ) - mark_base)
            IP_Tables_Line = False
        else:
            tc_sent.append(int(line.split(' ')[2]) - tc_base)
            IP_Tables_Line = True

    return (ip_mark,tc_sent)

file_name = "./queue-udp-under-utilised.txt"
ip_mark,tc_sent = count_pkts(file_name)
fig,ax = plt.subplots(1,1,figsize=(12,8))
ax.plot(ip_mark,tc_sent,'*r-',label='UDP under utilised')
ax.grid(True)
file_name = "./queue-udp-over-utilised.txt"
ip_mark,tc_sent = count_pkts(file_name)
ax.plot(ip_mark,tc_sent,'*b-',label='UDP over utilised')
ax.set_xlabel('No of Bytes Marked')
ax.set_ylabel('No of Bytes tc Transmitted')
ax.hold(True)
ax.legend(loc="upper left")
plt.savefig('pkts-plot.pdf',dpi='300')

plt.show()
