# xuxiake


How to debu



`gdb-multiarch xuxiake.elf`

If "auto loading" warning is encountered, add `.gdbinit` to `~/.gdbinit`, e.g. `add-auto-load-safe-path /home/bamvor/works/source/xuxiake/.gdbinit`
```
bamvor@VM-24-2-ubuntu:~/works/source/xuxiake$ gdb-multiarch xuxiake.elf
GNU gdb (Ubuntu 9.2-0ubuntu1~20.04.1) 9.2
Copyright (C) 2020 Free Software Foundation, Inc.
License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.
Type "show copying" and "show warranty" for details.
This GDB was configured as "x86_64-linux-gnu".
Type "show configuration" for configuration details.
For bug reporting instructions, please see:
<http://www.gnu.org/software/gdb/bugs/>.
Find the GDB manual and other documentation resources online at:
    <http://www.gnu.org/software/gdb/documentation/>.

For help, type "help".
Type "apropos word" to search for commands related to "word"...
Reading symbols from xuxiake.elf...
warning: File "/home/bamvor/works/source/xuxiake/.gdbinit" auto-loading has been declined by your `auto-load safe-path' set to "$debugdir:$datadir/auto-load:/home/bamvor/works/source/buildroot/output/build/linux-5.15.18/scripts/gdb/vmlinux-gdb.py:/home/bamvor/works/source/linux/scripts/gdb/vmlinux-gdb.py".
To enable execution of this file add
        add-auto-load-safe-path /home/bamvor/works/source/xuxiake/.gdbinit
line to your configuration file "/home/bamvor/.gdbinit".
To completely disable this security protection add
        set auto-load safe-path /
line to your configuration file "/home/bamvor/.gdbinit".
For more information about this security protection see the
"Auto-loading safe path" section in the GDB manual.  E.g., run from the shell:
        info "(gdb)Auto-loading safe path"
(gdb) q
```
