#!/bin/bash
IMG="../2017-02-16-raspbian-jessie-lite.img"
MOUNTPT="/tmp/rpi-mnt"

if [[ $EUID -ne 0  ]]; then
    >&2 echo Script requires root permissions.
    exit -1
fi

if [ "$1" == "mount" ]; then
    mkdir $MOUNTPT || exit -2
    mount $IMG -o loop,offset=$((137216*512)),rw $MOUNTPT
    mount $IMG -o loop,offset=$((8192*512)),rw $MOUNTPT/boot/
    mount --bind /dev $MOUNTPT/dev
    mount --bind /sys $MOUNTPT/sys
    mount --bind /proc $MOUNTPT/proc
    mount --bind /dev/pts $MOUNTPT/dev/pts
    sed -i 's/^\([^#]\)/#\1/g' $MOUNTPT/etc/ld.so.preload
    cp /usr/bin/qemu-arm-static $MOUNTPT/usr/bin/
elif [ "$1" == "enter" ]; then
    if [ ! -d $MOUNTPT ]; then
        $0 mount || exit -2
    fi
    cd $MOUNTPT/ || exit -2
    chroot . bin/bash
elif [ "$1" == "unmount" ]; then
    if [ -d $MOUNTPT ]; then
        sed -i 's/^#//g' $MOUNTPT/etc/ld.so.preload
        rm $MOUNTPT/usr/bin/qemu-arm-static
        umount $MOUNTPT/{dev/pts,proc,sys,dev}
        umount $MOUNTPT/boot
        umount $MOUNTPT
        rmdir $MOUNTPT
    else
        >&2 echo Not mounted.
        exit -2
    fi
elif [ "$1" == "qemu-prep" ]; then
    mkdir $MOUNTPT || exit -2
    mount $IMG -o loop,offset=$((137216*512)),rw $MOUNTPT
    sed -i 's/^\([^#]\)/#\1/g' $MOUNTPT/etc/ld.so.preload
    sed -i 's/mmcblk0p/sda/g' $MOUNTPT/etc/fstab
    umount $MOUNTPT
    rmdir $MOUNTPT
elif [ "$1" == "qemu-clean" ]; then
    mkdir $MOUNTPT || exit -2
    mount $IMG -o loop,offset=$((137216*512)),rw $MOUNTPT
    sed -i 's/^#//g' $MOUNTPT/etc/ld.so.preload
    sed -i 's/sda/mmcblk0p/g' $MOUNTPT/etc/fstab
    umount $MOUNTPT
    rmdir $MOUNTPT
else
    >&2 echo "Usage: $0 [mount|enter|unmount|qemu-prep|qemu-clean]"
    exit -3
fi
