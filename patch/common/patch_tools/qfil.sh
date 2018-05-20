#!/bin/bash


readonly usage="\

Usage: 
	$0 [<targets>]
	$0

Examples:
	$0 -m
	$0 -f
	$0 -a
	$0 -r
"

# 显示帮助
function show_help()
{
	echo -e "$usage"
}


# meta build for qfil
function build_meta()
{
	echo "build meta::++++++++++"
	
	python3 ./qfil_meta.py

	echo "build meta::----------"
}

# flat build for qfil
function build_flat()
{
	echo "build flat::++++++++++"
	
	python3 ./qfil_flat.py

	echo "build flat::----------"
}


# image build for fastboot
function build_adb()
{
	echo "build fastboot image::++++++++++"
	
	mkdir -p ./qfil
	cp -rf ./common/build/ufs/bin/BTFM.bin ./qfil
	cp -rf ./common/build/ufs/bin/asic/NON-HLOS.bin ./qfil
	cp -rf ./common/sectools/resources/build/fileversion2/sec.dat ./qfil	
	cp -rf ./trustzone_images/build/ms/bin/RAGAANAA/tz.mbn ./qfil
	cp -rf ./trustzone_images/build/ms/bin/RAGAANAA/hyp.mbn ./qfil
	cp -rf ./trustzone_images/build/ms/bin/RAGAANAA/keymaster.mbn ./qfil
	cp -rf ./trustzone_images/build/ms/bin/RAGAANAA/cmnlib64.mbn ./qfil
	cp -rf ./trustzone_images/build/ms/bin/RAGAANAA/cmnlib.mbn ./qfil
	cp -rf ./trustzone_images/build/ms/bin/RAGAANAA/devcfg.mbn ./qfil	
	cp -rf ./boot_images/QcomPkg/Msm8998Pkg/Bin/8998/LA/RELEASE/xbl.elf ./qfil
	cp -rf ./boot_images/QcomPkg/Msm8998Pkg/Bin/8998/LA/RELEASE/pmic.elf ./qfil
	cp -rf ./rpm_proc/build/ms/bin/AAAAANAZR/rpm.mbn ./qfil
	cp -rf ./slpi_proc/obj_v1/qdsp6v5_ReleaseG/slpi_v1.mbn ./qfil
	cp -rf ./slpi_proc/obj_v2/qdsp6v5_ReleaseG/slpi_v2.mbn ./qfil

	cp -rf ./LINUX/android/out/target/product/msm8998/abl.elf ./qfil
	cp -rf ./LINUX/android/out/target/product/msm8998/boot.img ./qfil
	cp -rf ./LINUX/android/out/target/product/msm8998/system.img ./qfil
	cp -rf ./LINUX/android/out/target/product/msm8998/userdata.img ./qfil
	cp -rf ./LINUX/android/out/target/product/msm8998/persist.img ./qfil
	cp -rf ./LINUX/android/out/target/product/msm8998/recovery ./qfil
	cp -rf ./LINUX/android/out/target/product/msm8998/cache	./qfil

	echo "build fastboot image::----------"
}

function recovery_meta()
{
	mkdir -p ./qfil

	mkdir -p ./qfil/common/build/ufs/bin
	cp -rf ./BTFM.bin  ./qfil/common/build/ufs/bin/

	mkdir -p ./qfil/common/build/ufs/bin/asic
	cp -rf ./NON-HLOS.bin ./qfil/common/build/ufs/bin/asic/ 

	mkdir -p ./qfil/common/sectools/resources/build/fileversion2
	cp -rf ./sec.dat ./qfil/common/sectools/resources/build/fileversion2/

	mkdir -p ./qfil/trustzone_images/build/ms/bin/RAGAANAA
	cp -rf ./tz.mbn ./qfil/trustzone_images/build/ms/bin/RAGAANAA/

	mkdir -p ./qfil/trustzone_images/build/ms/bin/RAGAANAA
	cp -rf ./hyp.mbn ./qfil/trustzone_images/build/ms/bin/RAGAANAA/

	mkdir -p ./qfil/trustzone_images/build/ms/bin/RAGAANAA
	cp -rf ./keymaster.mbn ./qfil/trustzone_images/build/ms/bin/RAGAANAA/

	mkdir -p ./qfil/trustzone_images/build/ms/bin/RAGAANAA
	cp -rf ./cmnlib64.mbn ./qfil/trustzone_images/build/ms/bin/RAGAANAA/

	mkdir -p ./qfil/trustzone_images/build/ms/bin/RAGAANAA
	cp -rf ./cmnlib.mbn ./qfil/trustzone_images/build/ms/bin/RAGAANAA/

	mkdir -p ./qfil/trustzone_images/build/ms/bin/RAGAANAA
	cp -rf ./devcfg.mbn ./qfil/trustzone_images/build/ms/bin/RAGAANAA/

	mkdir -p ./qfil/boot_images/QcomPkg/Msm8998Pkg/Bin/8998/LA/RELEASE
	cp -rf ./xbl.elf ./qfil/boot_images/QcomPkg/Msm8998Pkg/Bin/8998/LA/RELEASE/

	mkdir -p ./qfil/boot_images/QcomPkg/Msm8998Pkg/Bin/8998/LA/RELEASE
	cp -rf ./pmic.elf ./qfil/boot_images/QcomPkg/Msm8998Pkg/Bin/8998/LA/RELEASE/

	mkdir -p ./qfil/rpm_proc/build/ms/bin/AAAAANAZR
	cp -rf ./rpm.mbn	./qfil/rpm_proc/build/ms/bin/AAAAANAZR/

	mkdir -p ./qfil/slpi_proc/obj_v1/qdsp6v5_ReleaseG
	cp -rf ./slpi_v1.mbn ./qfil/slpi_proc/obj_v1/qdsp6v5_ReleaseG/

	mkdir -p ./qfil/slpi_proc/obj_v2/qdsp6v5_ReleaseG
	cp -rf ./slpi_v2.mbn ./qfil/slpi_proc/obj_v2/qdsp6v5_ReleaseG/
}

# 解析编译命令
function build_parse()
{
	echo "build parse::++++++++++"
	echo "params = $1"

	case $1 in
		-m)
			rm -rf ./qfil
			build_meta
			rm -rf ./qfil/system.img
			rm -rf ./qfil/userdata.img
			;;
		-f)
			rm -rf ./qfil
			build_flat
			rm -rf ./qfil/system.img
			rm -rf ./qfil/userdata.img
			;;

		-a)
			rm -rf ./qfil
			build_adb
			;;

		-r)
			recovery_meta
			;;
 
		*)
			echo "wrong target: $i"
			show_help
			exit 1
			;;
	esac
	
	echo "build parse::----------"
}




set -x

# 获取顶层目录
TOP_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
echo "TOP DIR = $TOP_DIR"

# 获取参数列表
echo "arg num = $#"
echo "args = $@"


if [ $# -eq 1 ]; then
	build_parse $1

	exit 0
fi

show_help
exit 1

:'
for i in $*
do
	case $i in
	modem)
		build_modem
		;;
	boot)
		build_boot
		;;
	rpm)
		build_rpm
		;;
	slpi)
		build_slpi
		;;
	adsp)
		build_adsp
		;;
	tz)
		build_tz
		;;
	android)
		build_android
		;;
	non-hlos)
		build_non-hlos
		;;
	meta)
		build_meta
		;;
	all)
		build_all
		;;
	clear)
		build_clear
		;;
	*)
		echo "wrong target: $i"
		show_help
		exit 1
		;;
	esac
done
'

#show_help
#build_modem
#build_boot
#build_rpm
#build_slpi
#build_android

