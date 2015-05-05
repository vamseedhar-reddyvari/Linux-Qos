CC=gcc
tc-stat-server: tc-stat-server.o
	$(CC) $(LDFLAGS) tc-stat-server.o -o tc-stat-server
tc-stat-server.o: tc-stat-server.c
	$(CC) $(CFLAGS) -c tc-stat-server.c
clean:
	rm *.o tc-stat-server
install:
	cp ./tc-stat-server.c ../../OpenWrt-SDK-ar71xx-generic_gcc-4.8-linaro_uClibc-0.9.33.2.Linux-i686/package/tc-stat-server/src/
	cd ../../OpenWrt-SDK-ar71xx-generic_gcc-4.8-linaro_uClibc-0.9.33.2.Linux-i686/ && make V=99
    scp ../../OpenWrt-SDK-ar71xx-generic_gcc-4.8-linaro_uClibc-0.9.33.2.Linux-i686/bin/ar71xx/packages/base/tc-stat-server_1_ar71xx.ipk root@192.168.1.1:/tmp
    
