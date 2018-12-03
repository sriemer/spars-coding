# openSUSE Leap 15 Upgrade Fix

## Problem Description

If you want to upgrade from Leap 42.3 to Leap 15 with encrypted partitions,
then you run into the following bug:<br/>
https://bugzilla.suse.com/show_bug.cgi?id=1094963

It throws an exception right when selecting the distro to be upgraded:
```
Details: Storage::Exception
Caller:/mounts/mp_0001/usr/share/YaST2/lib/y2storage/storage_class_wrapper.rb:260: in `find_by_any_name`
```

## Building the Fix

Only updated YaST2 and `libstorage-ng` files fix this. So I have prepared a
**Driver Update Disk (DUD)** `y2lp15.dud` here with files which were latest on
**2018-11-29**.

**File source**: http://download.opensuse.org/update/leap/15.0/oss/x86_64/

**File list:**
```
libstorage-ng1-3.3.315-lp150.2.9.1.x86_64.rpm
libstorage-ng-python3-3.3.315-lp150.2.9.1.x86_64.rpm
libstorage-ng-ruby-3.3.315-lp150.2.9.1.x86_64.rpm
libstorage-ng-utils-3.3.315-lp150.2.9.1.x86_64.rpm
yast2-4.0.87-lp150.2.9.1.x86_64.rpm
yast2-bootloader-4.0.39-lp150.2.8.1.x86_64.rpm
yast2-core-4.0.4-lp150.2.6.1.x86_64.rpm
yast2-storage-ng-4.0.214-lp150.2.15.1.x86_64.rpm
yast2-update-4.0.18-lp150.2.6.1.x86_64.rpm
```

Command used to build the DUD:
```
mkdud --create y2lp15.dud --dist leap15.0 --name "Upgrade fix boo#1094963" for-lp15-dud/*
```

Command to show its contents:
```
mkdud --show y2lp15.dud
```

## Applying the DUD via Network

Select the upgrade and use the following upgrade boot options:
```
dud=ftp://your_ftpserver/y2lp15.dud insecure=1
```

Applying DUDs via network (http/ftp) is preferred. I use a Raspberry Pi 2 on my
desk as my DUD FTP server. DUDs for openSUSE are never signed (no
`y2lp15.dud.asc`). So the option `insecure=1` is required here to avoid a
warning.<br/>
If you want to know what the installation initrd `linuxrc` is doing and if it
applies the DUD properly, then press <kbd>Esc</kbd> when the green bar is
visible at the bottom pretending that some progress is going on. You can also
add the `startshell=1` boot option to get more control.

I have **tested** this method. Using this DUD fixes this bug for me.

## Applying the DUD from USB

Besides network install, it is also possible to extract DUDs to the root of a
filesystem which supports symlinks like e.g. `ext3`. DUDs are `cpio.gz`
archives. Let us assume I have a USB stick with only one ext3 partition
mounted to `/mnt`.

Then I use the following commands as root:
```
cp y2lp15.dud /mnt; cd /mnt
zcat y2lp15.dud | cpio -idmv
cd ~; umount /mnt
```

A directory `linux` should appear. `linuxrc` is looking for that directory on
all partitions and picks up the DUD automatically this way. The option `dud=1`
can make this more visible. But it is rather meant for the case of only one
DVD drive providing both, the regular media and the DUD.

**Tested** in affected QEMU/KVM VM with emulated SATA disk + LUKS. Works.

## Building a new Installation ISO with DUD

With the tool `mksusecd` it is possible to build a new ISO based on the regular
installation ISO which applies the DUD fully automatically. Using the new ISO
is pretty idiot-proof.

Example build command:
```
sudo mksusecd --create openSUSE-Leap-15.0-DVD-x86_64-boo1094963.iso \
--initrd y2lp15.dud -- ./openSUSE-Leap-15.0-DVD-x86_64.iso
```

**Tested** in affected QEMU/KVM VM with emulated SATA disk + LUKS. Works.

## Getting mkdud and mksusecd

**mkdud**: https://github.com/openSUSE/mkdud<br/>
**mksusecd**: https://github.com/openSUSE/mksusecd

Just clone those repositories and use `sudo make install` to install the tools.
For `mksusecd` install the packages `squashfs` and `createrepo` as well.
