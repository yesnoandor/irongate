#!/bin/bash

set +x

adb reboot-bootloader

sleep 2

./fastboot flash bluetooth ./qfil/BTFM.bin
./fastboot flash devcfg ./qfil/devcfg.mbn
./fastboot flash dsp ./qfil/adspso.bin
./fastboot flash modem ./qfil/NON-HLOS.bin
./fastboot flash xbl ./qfil/xbl.elf
./fastboot flash pmic ./qfil/pmic.elf
./fastboot flash rpm ./qfil/rpm.mbn
./fastboot flash tz ./qfil/tz.mbn
./fastboot flash hyp ./qfil/hyp.mbn
./fastboot flash sec ./qfil/sec.dat
./fastboot flash keymaster ./qfil/keymaster.mbn
./fastboot flash cmnlib64 ./qfil/cmnlib64.mbn
./fastboot flash cmnlib ./qfil/cmnlib.mbn
./fastboot flash abl ./qfil/abl.elf
./fastboot flash boot ./qfil/boot.img
./fastboot flash system ./qfil/system.img
./fastboot flash userdata userdata.img
./fastboot flash persist ./qfil/persist.img
./fastboot flash recovery ./qfil/recovery.img
./fastboot flash cache ./qfil/cache.img

sleep 2

fastboot reboot
