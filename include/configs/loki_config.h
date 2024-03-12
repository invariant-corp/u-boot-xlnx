
#ifndef INC_LOKI_CONFIG_H
#define INC_LOKI_CONFIG_H


/* Override default preboot settings */
#undef CONFIG_PREBOOT
#define CONFIG_PREBOOT	"echo; echo U-Boot for K26 ZynqMP; echo"

/* MAC address in EEPROM */
// #define CONFIG_SYS_I2C_EEPROM_ADDR_LEN  1
// #define CONFIG_CMD_EEPROM
// #define CONFIG_ZYNQ_EEPROM_BUS          0
// #define CONFIG_ZYNQ_GEM_EEPROM_ADDR     0x52
// #define CONFIG_ZYNQ_GEM_I2C_MAC_OFFSET  0xFA


#define CONFIG_EXTRA_ENV_SETTINGS

#include "xilinx_zynqmp.h"

/* Extra U-Boot Env settings */
#undef CONFIG_EXTRA_ENV_SETTINGS
#define CONFIG_EXTRA_ENV_SETTINGS \
	"root_dev=0\0" \
	"boot_part=1\0" \
   "root_part=2\0" \
	"fpga_dev=0\0" \
	"boot_env=uEnv.txt\0" \
	"fpga_addr=0x15800000\0" \
	"boot_env_addr=0x13800000\0" \
	"dtb_addr=0x11800000\0" \
	"kernel_addr=0x10000000\0" \
	"loadbootenv=fatload mmc $root_dev:$boot_part ${boot_env_addr} ${boot_env}\0" \
	"importbootenv=env import -t ${boot_env_addr} $filesize\0" \
	"fpga_img=loki.bit\0" \
	"dtb_img=loki.dtb\0" \
	"kernel_img=Image\0" \
	"ipaddr=192.168.1.20\0" \
	"gatewayip=192.168.1.1\0" \
	"netmask=255.255.255.0\0" \
	"setup_mmc=mmc dev $root_dev:$boot_part\0" \
	"cp_fpga2ram=fatload mmc $root_dev:$boot_part ${fpga_addr} ${fpga_img}\0" \
	"load_fpga=fpga loadb ${fpga_dev} ${fpga_addr} $filesize\0" \
	"cp_dtb2ram=fatload mmc $root_dev:$boot_part ${dtb_addr} ${dtb_img}\0" \
	"cp_kernel2ram=fatload mmc $root_dev:$boot_part ${kernel_addr} ${kernel_img}\0" \
	"set_bootargs=env set bootargs earlycon console=ttyPS1,115200 clk_ignore_unused root=${rootfs} rootfstype=ext4 rw rootwait cma=100M\0" \
   "set_rootfs=env set rootfs /dev/mmcblk${root_dev}p${root_part}\0" \
	"loadcc=load mmc ${root_dev} ${loadaddr} cc.scr; source ${loadaddr}\0" \
	"bootcmd=run setup_mmc; run loadcc; run set_rootfs; run set_bootargs; run cp_dtb2ram; run cp_kernel2ram; booti ${kernel_addr} - ${dtb_addr}\0" \
""

#endif
