cmd_/home/vamsee/OpenWrt-14-07/build_dir/toolchain-mips_34kc_gcc-4.8-linaro_uClibc-0.9.33.2/linux-dev//include/rdma/.install := /bin/bash scripts/headers_install.sh /home/vamsee/OpenWrt-14-07/build_dir/toolchain-mips_34kc_gcc-4.8-linaro_uClibc-0.9.33.2/linux-dev//include/rdma /home/vamsee/OpenWrt-14-07/build_dir/toolchain-mips_34kc_gcc-4.8-linaro_uClibc-0.9.33.2/linux-3.10.49/include/uapi/rdma ib_user_cm.h ib_user_mad.h ib_user_sa.h ib_user_verbs.h rdma_netlink.h rdma_user_cm.h; /bin/bash scripts/headers_install.sh /home/vamsee/OpenWrt-14-07/build_dir/toolchain-mips_34kc_gcc-4.8-linaro_uClibc-0.9.33.2/linux-dev//include/rdma /home/vamsee/OpenWrt-14-07/build_dir/toolchain-mips_34kc_gcc-4.8-linaro_uClibc-0.9.33.2/linux-3.10.49/include/rdma ; /bin/bash scripts/headers_install.sh /home/vamsee/OpenWrt-14-07/build_dir/toolchain-mips_34kc_gcc-4.8-linaro_uClibc-0.9.33.2/linux-dev//include/rdma /home/vamsee/OpenWrt-14-07/build_dir/toolchain-mips_34kc_gcc-4.8-linaro_uClibc-0.9.33.2/linux-3.10.49/include/generated/uapi/rdma ; for F in ; do echo "\#include <asm-generic/$$F>" > /home/vamsee/OpenWrt-14-07/build_dir/toolchain-mips_34kc_gcc-4.8-linaro_uClibc-0.9.33.2/linux-dev//include/rdma/$$F; done; touch /home/vamsee/OpenWrt-14-07/build_dir/toolchain-mips_34kc_gcc-4.8-linaro_uClibc-0.9.33.2/linux-dev//include/rdma/.install
