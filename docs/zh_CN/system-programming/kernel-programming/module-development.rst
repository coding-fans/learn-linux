.. 内核模块开发
    FileName:   module-development.rst
    Author:     Fasion Chan
    Created:    2018-10-29 21:28:23
    @contact:   fasionchan@gmail.com
    @version:   $Id$

    Description:

    Changelog:

.. meta::
	:keywords: Linux内核模块, linux kernel module, kernel module

============
内核模块开发
============

`Linux` 内核管理着计算机的所有资源，为上层应用程序提供统一的编程接口( :doc:`../syscall/index` )，屏蔽底层设备的差异。
由于不同用户物理设备以及对内核功能需求的差异性，需要一种类似插件的运行机制——编写插件实现所需功能，然后嵌入到内核中，与内核形成一个整体。

**Linux内核模块** 便是这样的插件。
作为 `Linux` 内核的扩展手段，可以在运行时动态加载和卸载。
那么，一个内核模块是怎么编写的呢？与普通程序编写有什么区别呢？

程序开发经常以 ``hello world`` 程序入门，因为这是最简单的。
本文也通过一个最简单的内核模块，演示如何一步步编写一个内核模块。

结构
====

内核模块与普通程序不同，没有执行流。
可以这样理解，内核模块实现一些函数，作为回调函数注册到内核中。
在内核加载/卸载时，或者其他应用程序调用系统调用时，注册的回调函数才得到调用。

有两个最基本的回调函数 `init` 和 `exit` ，分别由 `module_init` 和 `module_exit` 登记，分别在模块加载和卸载的时候执行。
下面实现的 ``hello world`` 内核模块，将只实现这两个最基本的函数。

内核模块支持 **参数** ，用户借此控制内核模块的行为。
参数有默认值，可以在加载时指定，也可以在通过 `proc` 伪文件系统等手段动态修改。

此外，内核模块还需要带一些描述信息，包括 **许可证** 、 **作者** 、 **描述** 以及 **版本** 等等。
描述信息由 ``MODULE_`` 系列宏指定， `modinfo` 等命令可以展示这些信息。

编码
====

开干了！新建一个文件， `hello.c` 用于实现一个玩具型内核模块—— `hello` 模块。

`hello` 模块只实现 `init` 和 `exit` 函数，分别在加载和卸载时往内核日志输出一条记录。
同时，也演示了参数的使用方式——通过参数控制日志输出内容。

.. code-block:: c

	/**
	 * FileName:   hello.c
	 * Author:     Chen Yanfei
	 * @contact:   fasionchan@gmail.com
	 * @version:   $Id$
	 *
	 * Description:
	 *
	 * Changelog:
	 *
	 **/

	// 引入相关内核头文件
	#include <linux/module.h>

	// 内核模块信息，包括许可证、作者、描述和版本等
	MODULE_LICENSE("GPL");
	MODULE_AUTHOR("Fasion Chan");
	MODULE_DESCRIPTION("An hello worlk module for demonstration");
	MODULE_VERSION("1.0");

	// 内核模块参数，加载时指定或者动态指定，以此控制模块行为
	static char *name = "world";
	module_param(name, charp, S_IRUGO);
	MODULE_PARM_DESC(name, "Whom this module say hello to");


	// 初始化函数，在加载时调用，分配资源准备执行环境
	// 这里只是往内核日志输出一行记录
	static int __init hello_init(void)
	{
		printk(KERN_INFO "HELLO: Hello %s, this is hello module speaking\n", name);
		return 0;
	}


	// 清理函数，在卸载时调用，回收资源销毁执行环境
	static void __exit hello_exit(void)
	{
		printk(KERN_INFO "HELLO: Goodbye %s", name);
	}

	// 登记初始化函数及清理函数
	module_init(hello_init);
	module_exit(hello_exit);

编译
====

内核模块代码已经写好了，怎样知道写得对不对呢？
编译运行一下不就知道了？可问题是如何编译呢？
跟普通程序一样吗？用 `gcc` 来编译？

没错，内核模块用 `gcc` 来编译，但不会直接运行 `gcc` 。
我们需要先准备一个 `Makefile` ，内容如下：

.. code-block:: makefile

	obj-m+=hello.o

	all:
		make -C /lib/modules/$(shell uname -r)/build/ M=$(PWD) modules

	clean:
		make -C /lib/modules/$(shell uname -r)/build/ M=$(PWD) modules

好了之后，我们再命令行下运行 `make` 即可：

.. code-block:: shell-session

	$ ls
	hello.c  Makefile
	$ make
	make -C /lib/modules/3.16.0-4-amd64/build/ M=/home/fasion/hello modules
	make[1]: Entering directory '/usr/src/linux-headers-3.16.0-4-amd64'
	make[1]: Entering directory `/usr/src/linux-headers-3.16.0-4-amd64'
	  CC [M]  /home/fasion/hello/hello.o
	  Building modules, stage 2.
	  MODPOST 1 modules
	  CC      /home/fasion/hello/hello.mod.o
	  LD [M]  /home/fasion/hello/hello.ko
	make[1]: Leaving directory '/usr/src/linux-headers-3.16.0-4-amd64'
	$ ls
	hello.c  hello.ko  hello.mod.c  hello.mod.o  hello.o  Makefile  modules.order  Module.symvers

看到 `hello.ko` 文件生成，意味着编译大功告成了！
该文件就是二进制内核模块目标文件，其他文件的作用不再深入讨论。

顺便提一句， `Makefile` 中分成 `all` 和 `clean` 两节。
其中 `all` 用来编译， `clean` 用来清理编译环境：

.. code-block:: shell-session

	$ make clean
	make -C /lib/modules/3.16.0-4-amd64/build/ M=/home/fasion/hello clean
	make[1]: Entering directory '/usr/src/linux-headers-3.16.0-4-amd64'
	make[1]: Entering directory `/usr/src/linux-headers-3.16.0-4-amd64'
	  CLEAN   /home/fasion/hello/.tmp_versions
	  CLEAN   /home/fasion/hello/Module.symvers
	make[1]: Leaving directory '/usr/src/linux-headers-3.16.0-4-amd64'
	$ ls
	hello.c  Makefile

可以看到，运行了 `make clean` 后，所有编译生成的文件都清理掉了，只剩源码文件和 `Makefile` 。

运行
====

内核模块编译完成后，要怎么使用呢？跟普通程序直接运行不同，内核模块需要加载到内核里面发挥作用。
使用 `insmod`_ 命令加载内核模块：

.. code-block:: shell-session

	$ ls
	hello.c  hello.ko  hello.mod.c  hello.mod.o  hello.o  Makefile  modules.order  Module.symvers
	$ sudo insmod hello.ko
	$ dmesg
	[   14.226777] 00:00:00.000718 main     OS Product: Linux
	[   14.226814] 00:00:00.000779 main     OS Release: 3.16.0-4-amd64
	[   14.226845] 00:00:00.000814 main     OS Version: #1 SMP Debian 3.16.7-ckt20-1+deb8u4 (2016-02-29)
	[   14.226873] 00:00:00.000844 main     OS Service Pack: #1 SMP Debian 3.16.7-ckt20-1+deb8u4 (2016-02-29)
	[   14.226912] 00:00:00.000872 main     Executable: /opt/VBoxGuestAdditions-5.0.8/sbin/VBoxService
	00:00:00.000873 main     Process ID: 716
	00:00:00.000874 main     Package type: LINUX_64BITS_GENERIC
	[   14.232015] 00:00:00.005962 main     5.0.8 r103449 started. Verbose level = 0
	[ 4368.359895] HELLO: Hello world, this is hello module speaking

内核模块加载后，用 `dmesg`_ 命令看到，内核模块初始化时输出的一条内核日志。

加载内核模块时怎么指定参数的值呢？
下面演示移除内核模块，并以 `fasion` 为 `name` 参数值重新挂载：

.. code-block:: shell-session

	$ sudo rmmod hello
	$ sudo insmod hello.ko name=fasion

操作完成后，用 `dmesg`_ 可以看到以下内核日志：

.. code-block:: text

	[ 4368.359895] HELLO: Hello world, this is hello module speaking
	[ 4812.067761] HELLO: Goodbye world
	[ 4841.011892] HELLO: Hello fasion, this is hello module speaking

第二次挂载时， `name` 参数的值不是默认值 ``world`` ，而是 ``fasion`` 了。

跟内核模块相关还有 `insmod`_ 、 `rmmod`_ 、 `lsmod`_ 、 `modinfo`_ 、 `modprobe`_ 等命令，用法请参考`man`文档。

下一步
======

.. include:: /_fragments/next-step-to-wechat-mp.rst

参考文献
========

#. `dmesg(1) - Linux manual page <http://man7.org/linux/man-pages/man1/dmesg.1.html>`_
#. `insmod(8) - Linux manual page <http://man7.org/linux/man-pages/man8/insmod.8.html>`_
#. `rmmod(8) - Linux manual page <http://man7.org/linux/man-pages/man8/rmmod.8.html>`_

.. include:: /_fragments/wechat-reward.rst

.. include:: /_fragments/disqus.rst

.. _dmesg: http://man7.org/linux/man-pages/man1/dmesg.1.html
.. _insmod: http://man7.org/linux/man-pages/man8/insmod.8.html
.. _lsmod: http://man7.org/linux/man-pages/man8/lsmod.8.html
.. _modinfo: http://man7.org/linux/man-pages/man8/modinfo.8.html
.. _modprobe: http://man7.org/linux/man-pages/man8/modprobe.8.html
.. _rmmod: http://man7.org/linux/man-pages/man8/rmmod.8.html

.. comments
    comment something out below

