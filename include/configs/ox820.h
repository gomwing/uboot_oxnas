#ifndef __CONFIG_H
#define __CONFIG_H

/* High Level Configuration Options */
#define CONFIG_ARM1136
#define CONFIG_OX820

/* make cmd_ide.c quiet when compile */
#define __io

#include <asm/arch/cpu.h>		/* get chip and board defs */

/*#define CONFIG_ARCH_CPU_INIT*/
/*#define CONFIG_DISPLAY_CPUINFO*/
/*#define CONFIG_DISPLAY_BOARDINFO*/
/*#define CONFIG_BOARD_EARLY_INIT_F*/
/*#define CONFIG_SKIP_LOWLEVEL_INIT*/

/* mem */
#define CONFIG_SYS_SDRAM_BASE		0x60000000
#define CONFIG_NR_DRAM_BANKS		1
#define CONFIG_MIN_SDRAM_SIZE		(128 * 1024 * 1024)	/* 128 MB */
#define CONFIG_MAX_SDRAM_SIZE		(512 * 1024 * 1024)	/* 512 MB */
#define CONFIG_SRAM_BASE		0x50000000
#define CONFIG_SRAM_SIZE		(64 * 1024)

/* need do dma so better keep dcache off */
#define CONFIG_SYS_DCACHE_OFF

/* clock */
#define CONFIG_PLLA_FREQ_MHZ		800
#define CONFIG_RPSCLK			6250000
#define CONFIG_SYS_HZ			1000
#define CONFIG_SYS_CLK_FREQ		CONFIG_RPSCLK
#define CONFIG_SYS_TIMERBASE		TIMER1_BASE
#define CONFIG_TIMER_PRESCALE		TIMER_PRESCALE_16

/* serial */
#define CONFIG_SYS_NS16550
#define CONFIG_SYS_NS16550_SERIAL
#define CONFIG_SYS_NS16550_CLK		CONFIG_RPSCLK
#define CONFIG_SYS_NS16550_REG_SIZE	1
#define CONFIG_BAUDRATE			115200
#define CONFIG_SYS_NS16550_COM1		UART_1_BASE
#define CONFIG_CONS_INDEX		1

/* ide */
#define CONFIG_SYS_ATA_BASE_ADDR	0
#define CONFIG_SYS_ATA_DATA_OFFSET	0
#define CONFIG_SYS_ATA_REG_OFFSET	0
#define CONFIG_SYS_ATA_ALT_OFFSET	0
#define CONFIG_IDE_PLX
#define CONFIG_SYS_IDE_MAXDEVICE	1
#define CONFIG_SYS_IDE_MAXBUS		1
#define CONFIG_IDE_PREINIT
#define CONFIG_LBA48

/* nand */
#define CONFIG_NAND
#define CONFIG_SYS_MAX_NAND_DEVICE	1
#define CONFIG_SYS_NAND_BASE		STATIC_CS0_BASE
#define NAND_CLE_ADDR_PIN		19
#define NAND_ALE_ADDR_PIN		18
#define MTDPARTS_DEFAULT		"mtdparts=41000000.nand:" \
						"14m(boot)," \
                                                "-(data)"
#define MTDIDS_DEFAULT			"nand0=41000000.nand"

/* net */
#define CONFIG_DESIGNWARE_ETH
#define CONFIG_DW_ALTDESCRIPTOR
#define CONFIG_DW_AUTONEG
#define CONFIG_DW_SEARCH_PHY
#define CONFIG_MII
#define CONFIG_PHY_GIGE
#define CONFIG_CMD_MII
#define CONFIG_PHYLIB
#define CONFIG_ETHADDR			00:25:31:01:66:5F

/* spl */

#if defined(CONFIG_BOOT_FROM_NAND) || defined(CONFIG_BOOT_FROM_SATA)
#define CONFIG_SPL
#define CONFIG_SPL_FRAMEWORK
#define CONFIG_SPL_LIBCOMMON_SUPPORT
#define CONFIG_SPL_SERIAL_SUPPORT
#define CONFIG_SPL_LIBGENERIC_SUPPORT
#define CONFIG_SPL_TEXT_BASE			0x50000000
#define CONFIG_SPL_STACK			(CONFIG_SRAM_BASE + (48 * 1024))
#define CONFIG_SPL_DISPLAY_PRINT
#define CONFIG_SPL_BSS_DRAM_START			0x65000000
#define CONFIG_SPL_BSS_DRAM_SIZE			0x01000000
#define CONFIG_SPL_MALLOC_START				0x66000000
#endif

#ifdef CONFIG_SPL_BUILD
#define USE_DL_PREFIX	/* rename malloc free etc, so we can override them */
#define DYNAMIC_CRC_TABLE /* save a few bytes */

#if defined(CONFIG_BOOT_FROM_NAND)
#define CONFIG_CMD_NAND
#define CONFIG_SPL_NAND_SUPPORT
#define BOOT_DEVICE_TYPE			"NAND"
#define BOOT_DEVICE_NAND			0xfeedbacc
#define CONFIG_SPL_BOOT_DEVICE			BOOT_DEVICE_NAND
#define CONFIG_SPL_NAND_SIMPLE
#define CONFIG_SPL_NAND_ECC
#define CONFIG_SPL_NAND_SOFTECC
#define CONFIG_SYS_NAND_ECCSIZE			512
#define CONFIG_SYS_NAND_ECCBYTES		6
#define CONFIG_SYS_NAND_ECCPOS			{40, 41, 42, 43, 44, 45, 46, 47, \
						48, 49, 50, 51, 52, 53, 54, 55, \
						56, 57, 58, 59, 60, 61, 62, 63}
#define CONFIG_SYS_NAND_PAGE_SIZE		2048
#define CONFIG_SYS_NAND_OOBSIZE			64
#define CONFIG_SYS_NAND_BLOCK_SIZE		(128 * 1024)
#define CONFIG_SYS_NAND_BAD_BLOCK_POS		0
/* pages per erase block */
#define CONFIG_SYS_NAND_PAGE_COUNT		(CONFIG_SYS_NAND_BLOCK_SIZE / CONFIG_SYS_NAND_PAGE_SIZE)
/* nand spl use 1 erase block, and use bit to byte encode for reliability */
#define CONFIG_SPL_MAX_SIZE			(128 * 1024 / 8)
#define CONFIG_SYS_NAND_U_BOOT_OFFS		0x00040000
/* spl kernel load is not enabled */
#define CONFIG_SYS_NAND_SPL_KERNEL_OFFS		0x00200000
#define CONFIG_CMD_SPL_NAND_OFS			0
#define CONFIG_CMD_SPL_WRITE_SIZE		1024
#define CONFIG_SYS_SPL_ARGS_ADDR		(CONFIG_SYS_SDRAM_BASE + 0x100)
/* CONFIG_BOOT_FROM_NAND end */

#elif defined(CONFIG_BOOT_FROM_SATA)

#define CONFIG_CMD_IDE
#define CONFIG_SPL_BLOCK_SUPPORT
#define BOOT_DEVICE_TYPE				"SATA"
#define BOOT_DEVICE_BLOCK				860202
#define CONFIG_SPL_BOOT_DEVICE				BOOT_DEVICE_BLOCK
#define CONFIG_SPL_MAX_SIZE				(32 * 1024)
#define CONFIG_SPL_LIBDISK_SUPPORT
#define CONFIG_SPL_BLOCKDEV_INTERFACE			"ide"
#define CONFIG_SPL_BLOCKDEV_ID				0

#ifdef CONFIG_BOOT_FROM_FAT /* u-boot in fat partition */

#define CONFIG_FS_FAT
#define CONFIG_SPL_FAT_SUPPORT
#define CONFIG_BLOCKDEV_FAT_BOOT_PARTITION		1 /* first partition */
#define CONFIG_SPL_FAT_LOAD_PAYLOAD_NAME		"u-boot.img" /* u-boot file name */
/* enable U-Boot Falcon Mode */
#define CONFIG_CMD_SPL
#define CONFIG_SPL_OS_BOOT
#define CONFIG_SPL_FAT_LOAD_ARGS_NAME			"bootargs.bin" /* boot parameters */
#define CONFIG_SPL_FAT_LOAD_KERNEL_NAME			"falcon.img" /* kernel */
#define CONFIG_SYS_SPL_ARGS_ADDR			(CONFIG_SYS_SDRAM_BASE + 0x100)

#elif CONFIG_BOOT_FROM_EXT4

#define CONFIG_FS_EXT4
#define CONFIG_SPL_EXT4_SUPPORT
#define CONFIG_BLOCKDEV_EXT4_BOOT_PARTITION		1 /* first partition */
#define CONFIG_SPL_EXT4_LOAD_PAYLOAD_NAME		"/boot/u-boot.img" /* u-boot file name */
/* enable U-Boot Falcon Mode */
#define CONFIG_CMD_SPL
#define CONFIG_SPL_OS_BOOT
#define CONFIG_SPL_EXT4_LOAD_ARGS_NAME			"/boot/bootargs.bin" /* boot parameters */
#define CONFIG_SPL_EXT4_LOAD_KERNEL_NAME		"/boot/falcon.img" /* kernel */
#define CONFIG_SYS_SPL_ARGS_ADDR			(CONFIG_SYS_SDRAM_BASE + 0x100)

#else /* u-boot in raw sectors */

#define CONFIG_SYS_BLOCK_RAW_MODE_U_BOOT_SECTOR		1024
/* spl kernel load is not enabled */
#define CONFIG_SYS_BLOCK_RAW_MODE_KERNEL_SECTOR		4096
#define CONFIG_SYS_BLOCK_RAW_MODE_ARGS_SECTOR		0
#define CONFIG_SYS_BLOCK_RAW_MODE_ARGS_SECTORS		(1024 / 512)
#define CONFIG_SYS_SPL_ARGS_ADDR			(CONFIG_SYS_SDRAM_BASE + 0x100)

#endif /* CONFIG_BOOT_FROM_FAT */
/* CONFIG_BOOT_FROM_SATA end */

#else
/* generic, no spl support */
#endif
#endif /* CONFIG_SPL_BUILD */

/* boot */
#define CONFIG_IDENT_STRING		" for OXNAS"
#define CONFIG_MACH_TYPE		MACH_TYPE_OXNAS
#ifndef CONFIG_SPL_BUILD
/* Enable devicetree support */
#define CONFIG_OF_LIBFDT
#endif
#define CONFIG_SETUP_MEMORY_TAGS
#define CONFIG_CMDLINE_TAG
#define CONFIG_INITRD_TAG
#define CONFIG_BOOTDELAY		3
#define CONFIG_ZERO_BOOTDELAY_CHECK
#define CONFIG_DEFAULT_CONSOLE		"console=ttyS0,115200n8\0"
/* Boot Argument Buffer Size */
#define CONFIG_SYS_BARGSIZE		CONFIG_SYS_CBSIZE
/* memtest works on */
#define CONFIG_SYS_LOAD_ADDR		(CONFIG_SYS_SDRAM_BASE)
#define CONFIG_SYS_AUTOLOAD		"no"

#define CONFIG_BOOTARGS			"console=ttyS0,115200n8 root=/dev/sda2 ubi.mtd=data,512"
#define CONFIG_BOOTCOMMAND		"run ideboot"
#define CONFIG_BOOT_RETRY_TIME		-1
#define CONFIG_RESET_TO_RETRY		60
#define CONFIG_PREBOOT			"run safeboot"

#define CONFIG_NETCONSOLE
#define CONFIG_IPADDR			192.168.0.100

#define CONFIG_EXTRA_ENV_SETTINGS	\
	"console=" CONFIG_DEFAULT_CONSOLE \
	"bootargs=" CONFIG_DEFAULT_CONSOLE \
	"mtdids=" MTDIDS_DEFAULT "\0" \
	"mtdparts=" MTDPARTS_DEFAULT "\0" \
	"safeboot=" \
			"setexpr.b keypressed '*44200005' '&' 1;" \
			"if test $keypressed = 0;" \
				"then run netcon;" \
			"fi" "\0" \
	"serialcon=" \
			"echo switch to serial console;" \
			"setenv stderr serial;" \
			"setenv stdin serial;" \
			"setenv stdout serial;" \
			"echo switch to serial console" "\0" \
	"netcon=" \
			"echo switch to net console;" \
			"setenv stderr nc;" \
			"setenv stdin nc;" \
			"setenv stdout nc;" \
			"echo switch to net console" "\0"

/* env */
#if defined(CONFIG_BOOT_FROM_NAND)
#define CONFIG_ENV_IS_IN_NAND
#define CONFIG_ENV_OFFSET		0x00100000
#define CONFIG_ENV_SIZE			0x00020000
#define CONFIG_ENV_RANGE		(CONFIG_ENV_SIZE * 2)
/* CONFIG_BOOT_FROM_NAND end */

#elif defined(CONFIG_BOOT_FROM_SATA)
#ifdef CONFIG_BOOT_FROM_EXT4
#define CONFIG_ENV_IS_IN_EXT4
#define CONFIG_START_IDE
#define EXT4_ENV_INTERFACE 		"ide"
#define EXT4_ENV_DEVICE			0
#define EXT4_ENV_PART			1
#define EXT4_ENV_FILE			"/boot/u-boot.env"
#define CONFIG_ENV_SIZE			(16 * 1024)
#else
#define CONFIG_ENV_IS_IN_FAT
#define CONFIG_START_IDE
#define FAT_ENV_INTERFACE 		"ide"
#define FAT_ENV_DEVICE			0
#define FAT_ENV_PART			1
#define FAT_ENV_FILE			"u-boot.env"
#define CONFIG_ENV_SIZE			(16 * 1024)
#endif
/* CONFIG_BOOT_FROM_SATA end */

#else
/* generic */
#define CONFIG_ENV_IS_NOWHERE
#define CONFIG_ENV_SIZE			(16 * 1024)

#endif

/* allow to overwrite serial and ethaddr */
#define CONFIG_ENV_OVERWRITE

#define CONFIG_SYS_MONITOR_LEN		(512 * 1024)
#define CONFIG_SYS_TEXT_BASE		0x64000000
#define CONFIG_SYS_INIT_SP_ADDR		0x65000000
/* Size of malloc() pool */
#define CONFIG_SYS_MALLOC_LEN		(1 * 1024 * 1024)

/* Miscellaneous configurable options */
#define CONFIG_SYS_LONGHELP		/* undef to save memory */
#define CONFIG_SYS_HUSH_PARSER		/* use "hush" command parser	*/
#define CONFIG_SYS_PROMPT		"OX820 # "
#define CONFIG_SYS_CBSIZE		1024	/* Console I/O Buffer Size*/
#define CONFIG_SYS_PBSIZE		1024	/* Print Buffer Size */
#define CONFIG_SYS_MAXARGS		32	/* max number of command args */
#define CONFIG_CMDLINE_EDITING
#define CONFIG_AUTO_COMPLETE

/* usb */
#define CONFIG_USB_MAX_CONTROLLER_COUNT	1
#define CONFIG_USB_EHCI
#define CONFIG_EHCI_IS_TDI
/* #define CONFIG_USB_EHCI_TXFIFO_THRESH	0x3F */
#define CONFIG_USB_PLLB_CLK
#define CONFIG_USB_EHCI_OXNAS

/* cmds */
#define CONFIG_SYS_NO_FLASH

#define CONFIG_DOS_PARTITION
#define CONFIG_EFI_PARTITION

#ifndef CONFIG_SPL_BUILD /* !CONFIG_SPL_BUILD */
#include <config_cmd_default.h>

#define CONFIG_CMD_SAVEENV
#define CONFIG_CMD_ASKENV
#define CONFIG_CMD_GREPENV
#define CONFIG_CMD_ENV_FLAGS

#define CONFIG_CMD_NET
#define CONFIG_CMD_DHCP
#define CONFIG_CMD_NFS
#define CONFIG_CMD_PING
#define CONFIG_CMD_PXE

#define CONFIG_CMD_NAND
#define CONFIG_CMD_MTDPARTS
#define CONFIG_CMD_UBI
#define CONFIG_CMD_UBIFS

#define CONFIG_USB_STORAGE
#define CONFIG_CMD_USB

#define CONFIG_CMD_IDE
#define CONFIG_CMD_FAT
#define CONFIG_FAT_WRITE
#define CONFIG_CMD_EXT2
#define CONFIG_CMD_EXT4
#define CONFIG_CMD_EXT4_WRITE

#define CONFIG_CMD_ZIP
#define CONFIG_CMD_UNZIP
#define CONFIG_CMD_TIME
#define CONFIG_CMD_TERMINAL
#define CONFIG_CMD_SETEXPR
#define CONFIG_CMD_MD5SUM
#define CONFIG_CMD_HASH
#define CONFIG_CMD_INI
#define CONFIG_CMD_GETTIME
#define CONFIG_CMD_BOOTMENU
#define CONFIG_CMD_ELF

/* for CONFIG_CMD_MTDPARTS */
#define CONFIG_MTD_DEVICE
/* for CONFIG_CMD_UBI */
#define CONFIG_MTD_PARTITIONS
/* for CONFIG_CMD_UBI */
#define CONFIG_RBTREE

/* optional, for CONFIG_CMD_BOOTM & required by CONFIG_CMD_UBIFS */
#define CONFIG_LZO
#define CONFIG_LZMA
#define CONFIG_BZIP2

/* for CONFIG_CMD_ZIP */
#define CONFIG_GZIP_COMPRESSED
/* for CONFIG_CMD_MD5SUM */
#define CONFIG_MD5
#define CONFIG_MD5SUM_VERIFY
/* enable CONFIG_CMD_HASH's verification feature */
#define CONFIG_HASH_VERIFY
#define CONFIG_REGEX
/* for CONFIG_CMD_BOOTMENU & CONFIG_CMD_PXE */
#define CONFIG_MENU
#endif /* !CONFIG_SPL_BUILD */

#endif	/* __CONFIG_H */
