.. Linux二进制程序移植
    FileName:   portable-linux-binaries.rst
    Author:     Fasion Chan
    Created:    2019-01-07 19:10:43
    @contact:   fasionchan@gmail.com
    @version:   $Id$

    Description:

    Changelog:

.. meta::
    :description lang=zh:
		在一个系统上构建二进制程序，并在其他系统上运行。
		最保险的做法是在老系统编译代码，存在一些潜在的问题需要避开。
		新系统编译的二进制程序在老系统上执行可能因 浮点异常 ( SIGFPE )而崩溃。
    :keywords: 二进制, 移植, 向下兼容, 静态链接, 可移植性, libstdc++, glibc, 浮点异常, SIGFPE

===================
Linux二进制程序移植
===================

`Linux` 在二进制程序移植方面表现并不是很出色。
不同 `Linux` 系统，二进制库千差万别；而且内核接口也多有变动。
尽管如此，构建一个可运行于多种系统环境的二进制程序还是可以做到的。
注意到， `Adobe` 为 `Linux` 系统构建的二进制 `Flash` 播放器似乎可以在各种系统上运行。
最近我需要 **在一个系统上构建二进制程序，并在其他系统上运行** 。
由于我只使用 `C` 库函数，因此预计难度不大。
然而并不是如此。
由于 `Linux` 二进制是向下兼容的，因此 **最保险的做法是在老系统编译代码**
( `chroot` 到一个老版本的 `Linux` 环境亦可)。
当然了，还是存在一些潜在的问题需要避开。

浮点异常
========

新系统编译的二进制程序在老系统上执行可能因 **浮点异常** ( `SIGFPE` )而崩溃。
根源在于：新版链接器生成新的 `.gnu.hash` 节，而不是原来的 `.hash` 节。
老 `Linux` 系统不知道如何链接二进制程序，导致了这个异常。
为 `GCC` 指定参数 `-Wl,--hash-style=both` 便可解决这个问题。

静态链接C++标准库
=================

如果用到 `C++` 标准库，程序可能依赖一个目标系统上没有的 `libstdc++`_ 版本。
虽然比较繁琐，但还是可以通过
`静态链接libstdc++ <http://codearcana.com/posts/2015/12/09/statically-linking-libstdc.html>`_
来避免。

glibc不兼容
===========

`Linux` 采用 **符号版本** ( `symbol versioning`_ )来保护 `C` 库向下兼容性。
如果在新系统构建二进制程序，程序可能会依赖新版的 `glibc`_ 。
为了确认二进制程序依赖的版本，可以运行 `readelf`_ 命令：

.. code-block:: shell-session

    $ readelf -V [binary]

命令输出信息大致如下：

.. code-block:: text

	Version needs section '.gnu.version_r' contains 5 entries:
 	 Addr: 0x000000000804901c  Offset: 0x00101c  Link to section: 7 (.dynstr)
	  000000: Version: 1  File: libpthread.so.0  Cnt: 1
	  0x0010:   Name: GLIBC_2.0  Flags: none  Version: 11
	  0x0020: Version: 1  File: librt.so.1  Cnt: 1
	  0x0030:   Name: GLIBC_2.2  Flags: none  Version: 8
	  0x0040: Version: 1  File: ld-linux.so.2  Cnt: 1
	  0x0050:   Name: GLIBC_2.3  Flags: none  Version: 6
	  0x0060: Version: 1  File: libgcc_s.so.1  Cnt: 3
	  0x0070:   Name: GCC_4.2.0  Flags: none  Version: 9
	  0x0080:   Name: GCC_3.3  Flags: none  Version: 5
	  0x0090:   Name: GCC_3.0  Flags: none  Version: 3
	  0x00a0: Version: 1  File: libc.so.6  Cnt: 4
	  0x00b0:   Name: GLIBC_2.4  Flags: none  Version: 10
	  0x00c0:   Name: GLIBC_2.2  Flags: none  Version: 7
	  0x00d0:   Name: GLIBC_2.3.2  Flags: none  Version: 4
	  0x00e0:   Name: GLIBC_2.0  Flags: none  Version: 2

如果发现有不对的版本，可以通过 `nm` 命令查出依赖它的符号：

.. code-block:: shell-session

    $ nm [binary] | grep [name]

输出大致如下：

.. code-block:: text

    U __stack_chk_fail@@GLIBC_2.4


`GCC` **栈保护** ( `stack protector`_ )功能需要用到这个函数，而老版本的 `glibc`_ 并不提供！
该功能在 `Fedora` 和 `Ubuntu` 下默认是开启的，
因此为了避免 **未知符号** ( `missing symbol` )错误，
需要通过编译参数 `-fnostack-protector` 显式关闭。

.. note::

    **栈保护** 功能用于应对 **栈攻击** ：
    一旦检测到便强行退出程序并输出错误信息。

下一步
======

.. include:: /_fragments/next-step-to-wechat-mp.rst

参考文献
========

#. `Portable Linux Binaries <http://www.evanjones.ca/portable-linux-binaries.html>`_

.. include:: /_fragments/wechat-reward.rst

.. include:: /_fragments/disqus.rst

.. _glibc: https://www.gnu.org/s/libc/
.. _libstdc++: http://gcc.gnu.org/onlinedocs/libstdc++/
.. _readelf: https://linux.die.net/man/1/readelf
.. _stack protector: http://gcc.gnu.org/onlinedocs/gcc-4.2.3/gcc/Optimize-Options.html#index-fstack_002dprotector-611
.. _symbol versioning: http://people.redhat.com/drepper/symbol-versioning

.. comments
    comment something out below

