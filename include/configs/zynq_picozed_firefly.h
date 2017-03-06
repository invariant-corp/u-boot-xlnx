

#ifndef __CONFIG_ZYNQ_PICOZED_FIREFLY_H
#define __CONFIG_ZYNQ_PICOZED_FIREFLY_H


#define CONFIG_ZYNQ_SDHCI0
#define CONFIG_ZYNQ_QSPI
#define CONFIG_ZYNQ_I2C0
#define CONFIG_ZYNQ_EEPROM
#define CONFIG_ENV_OFFSET 0x00D00000
#define CONFIG_SPI_FLASH
#define CONFIG_SPI_FLASH_BAR
#define CONFIG_NETCONSOLE
#define CONFIG_PREBOOT

#include <configs/zynq_picozed.h>

#define CONFIG_CMD_UNZIP 1

/* Default environment */
#undef CONFIG_EXTRA_ENV_SETTINGS
#define CONFIG_EXTRA_ENV_SETTINGS   \
   "stdout=serial\0" \
   "stdin=serial\0" \
   "stderr=serial\0" \
   "ethaddr=00:0a:35:00:01:22\0" \
   "ipaddr=192.168.1.200\0" \
   "netmask=255.255.255.0\0" \
   "gatewayip=192.168.1.1\0" \
   "ntpserverip=127.0.0.1\0" \
   "netconsole=false\0" \
   "kernel_image=uImage\0" \
   "kernel_load_address=0x3000000\0" \
   "ramdisk_image=uramdisk.image.gz\0" \
   "ramdisk_load_address=0x4000000\0"  \
   "devicetree_image=devicetree.dtb\0" \
   "devicetree_load_address=0x2A00000\0"  \
   "bitstream_image=system.bit.bin\0"  \
   "boot_image=BOOT.bin\0" \
   "loadbit_addr=0x100000\0"  \
   "loadbootenv_addr=0x2000000\0" \
   "kernel_size=0x500000\0"   \
   "devicetree_size=0x20000\0"   \
   "ramdisk_size=0x5E0000\0"  \
   "boot_size=0xF00000\0"  \
   "fdt_high=0x20000000\0" \
   "initrd_high=0x20000000\0" \
   "mmcroot=PARTUUID=741b37f3-02\0" \
   "mmcroot_fstype=ext4\0" \
   "sdroot=/dev/mmcblk0p2\0" \
   "sdroot_fstype=ext4\0" \
   "bootargs=console=ttyPS0,115200 earlyprintk\0" \
   "qspibootargs=setenv bootargs fsck.repair=yes console=ttyPS0,115200 earlyprintk rootfstype=${mmcroot_fstype} root=${mmcroot} ro rootwait\0" \
   "sdbootargs=setenv bootargs console=ttyPS0,115200 earlyprintk rootfstype=${sdroot_fstype} root=${sdroot} rw rootwait\0" \
   "bootenv=uEnv.txt\0" \
   "loadbootenv=load mmc 0 ${loadbootenv_addr} ${bootenv}\0" \
   "importbootenv=echo Importing environment from SD ...; " \
      "env import -t ${loadbootenv_addr} $filesize\0" \
   "sd_uEnvtxt_existence_test=test -e mmc 0 /uEnv.txt\0" \
   "start_netconsole=setenv bootdelay 5; setenv stdin nc; setenv stdout nc; setenv stderr nc; version\0" \
   "preboot=if test $netconsole = true; " \
         "then env run start_netconsole; " \
      "fi; \0" \
   "mmc_loadbit=echo Loading bitstream from SD/MMC/eMMC to RAM.. && " \
      "mmcinfo && " \
      "load mmc 0 ${loadbit_addr} ${bitstream_image} && " \
      "fpga load 0 ${loadbit_addr} ${filesize}\0" \
   "norboot=echo Copying Linux from NOR flash to RAM... && " \
      "cp.b 0xE2100000 ${kernel_load_address} ${kernel_size} && " \
      "cp.b 0xE2600000 ${devicetree_load_address} ${devicetree_size} && " \
      "echo Copying ramdisk... && " \
      "cp.b 0xE2620000 ${ramdisk_load_address} ${ramdisk_size} && " \
      "bootm ${kernel_load_address} ${ramdisk_load_address} ${devicetree_load_address}\0" \
   "qspiboot_stage2=echo QSPI boot... && " \
      "run qspibootargs && " \
      "mmc dev 1 && " \
      "fatload mmc 1 ${kernel_load_address} ${kernel_image} && " \
      "fatload mmc 1 ${devicetree_load_address} ${devicetree_image} && " \
      "bootm ${kernel_load_address} - ${devicetree_load_address}\0" \
   "qspiboot=" \
      "if test -n $software_update; then " \
         "env delete software_update; " \
         "saveenv; " \
         "echo Performing software update...; " \
      "else run qspiboot_stage2; " \
      "fi\0" \
   "uenvboot=" \
      "if run loadbootenv; then " \
         "echo Loaded environment from ${bootenv}; " \
         "run importbootenv; " \
      "fi; " \
      "if test -n $uenvcmd; then " \
         "echo Running uenvcmd ...; " \
         "run uenvcmd; " \
      "fi\0" \
   "sdboot=echo SD boot... && " \
         "run sdbootargs && " \
         "load mmc 0 ${kernel_load_address} ${kernel_image} && " \
         "load mmc 0 ${devicetree_load_address} ${devicetree_image} && " \
         "bootm ${kernel_load_address} - ${devicetree_load_address}\0" \
   "usbboot=if usb start; then " \
         "run uenvboot; " \
         "echo Copying Linux from USB to RAM... && " \
         "load usb 0 ${kernel_load_address} ${kernel_image} && " \
         "load usb 0 ${devicetree_load_address} ${devicetree_image} && " \
         "load usb 0 ${ramdisk_load_address} ${ramdisk_image} && " \
         "bootm ${kernel_load_address} ${ramdisk_load_address} ${devicetree_load_address}; " \
      "fi\0" \
   "nandboot=echo Copying Linux from NAND flash to RAM... && " \
      "nand read ${kernel_load_address} 0x100000 ${kernel_size} && " \
      "nand read ${devicetree_load_address} 0x600000 ${devicetree_size} && " \
      "echo Copying ramdisk... && " \
      "nand read ${ramdisk_load_address} 0x620000 ${ramdisk_size} && " \
      "bootm ${kernel_load_address} ${ramdisk_load_address} ${devicetree_load_address}\0" \
   "jtagboot=echo TFTPing Linux to RAM... && " \
      "tftpboot ${kernel_load_address} ${kernel_image} && " \
      "tftpboot ${devicetree_load_address} ${devicetree_image} && " \
      "tftpboot ${ramdisk_load_address} ${ramdisk_image} && " \
      "bootm ${kernel_load_address} ${ramdisk_load_address} ${devicetree_load_address}\0" \
   "rsa_norboot=echo Copying Image from NOR flash to RAM... && " \
      "cp.b 0xE2100000 0x100000 ${boot_size} && " \
      "zynqrsa 0x100000 && " \
      "bootm ${kernel_load_address} ${ramdisk_load_address} ${devicetree_load_address}\0" \
   "rsa_nandboot=echo Copying Image from NAND flash to RAM... && " \
      "nand read 0x100000 0x0 ${boot_size} && " \
      "zynqrsa 0x100000 && " \
      "bootm ${kernel_load_address} ${ramdisk_load_address} ${devicetree_load_address}\0" \
   "rsa_qspiboot=echo Copying Image from QSPI flash to RAM... && " \
      "sf probe 0 0 0 && " \
      "sf read 0x100000 0x0 ${boot_size} && " \
      "zynqrsa 0x100000 && " \
      "bootm ${kernel_load_address} ${ramdisk_load_address} ${devicetree_load_address}\0" \
   "rsa_sdboot=echo Copying Image from SD to RAM... && " \
      "load mmc 0 0x100000 ${boot_image} && " \
      "zynqrsa 0x100000 && " \
      "bootm ${kernel_load_address} ${ramdisk_load_address} ${devicetree_load_address}\0" \
   "rsa_jtagboot=echo TFTPing Image to RAM... && " \
      "tftpboot 0x100000 ${boot_image} && " \
      "zynqrsa 0x100000 && " \
      "bootm ${kernel_load_address} ${ramdisk_load_address} ${devicetree_load_address}\0" \
      DFU_ALT_INFO

#endif /* __CONFIG_ZYNQ_PICOZED_FIREFLY_H */
