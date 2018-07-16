.. 系统调用原理
    FileName:   principle.rst
    Author:     Fasion Chan
    Created:    2018-07-10 09:57:09
    @contact:   fasionchan@gmail.com
    @version:   $Id$

    Description:

    Changelog:

.. meta::
    :keywords: Linux系统调用原理, 系统调用处理函数, 系统调用服务例程, Linux, syscall, int 0x80, ret, system call, system call handler, system call service routine

============
系统调用原理
============

操作系统通过系统调用为运行于其上的进程提供服务。

当用户态进程发起一个系统调用， `CPU` 将切换到 **内核态** 并开始执行一个 **内核函数** 。
内核函数负责响应应用程序的要求，例如操作文件、进行网络通讯或者申请内存资源等。

举一个最简单的例子，应用进程需要输出一行文字，需要调用 `write` 这个系统调用：

.. literalinclude:: /_src/system-programming/syscall/principle/hello_world.c
    :caption: hello_world.c
    :name: system-programming/syscall/principle/hello_world.c
    :language: c
    :lines: 13-
    :linenos:

.. note::

    读者可能会有些疑问——输出文本不是用 `printf` 等函数吗？

    确实是。 `printf` 是更高层次的库函数，建立在系统调用之上，实现数据格式化等功能。
    因此，本质上还是系统调用起决定性作用。

调用流程
========

那么，在应用程序内，调用一个系统调用的流程是怎样的呢？

我们以一个假设的系统调用 `xyz` 为例，介绍一次系统调用的所有环节。

.. figure:: /_images/system-programming/syscall/principle/92b3f2ae7105aa2017ac7f475892aca9.jpg

如上图，系统调用执行的流程如下：

#. **应用程序** 代码调用系统调用( `xyz` )，该函数是一个包装系统调用的 **库函数** ；
#. **库函数** ( `xyz` )负责准备向内核传递的参数，并触发 **软中断** 以切换到内核；
#. `CPU` 被 **软中断** 打断后，执行 **中断处理函数** ，即 **系统调用处理函数** ( `system_call` )；
#. **系统调用处理函数** 调用 **系统调用服务例程** ( `sys_xyz` )，真正开始处理该系统调用；

执行态切换
==========

**应用程序** ( `application program` )与 **库函数** ( `libc` )之间，
**系统调用处理函数** ( `system call handler` )与 **系统调用服务例程** ( `system call service routine` )之间，
均是普通函数调用，应该不难理解。
而 **库函数** 与 **系统调用处理函数** 之间，由于涉及用户态与内核态的切换，要复杂一些。

`Linux` 通过 **软中断** 实现从 **用户态** 到 **内核态** 的切换。
**用户态** 与 **内核态** 是独立的执行流，因此在切换时，需要准备 **执行栈** 并保存 **寄存器** 。

内核实现了很多不同的系统调用(提供不同功能)，而 **系统调用处理函数** 只有一个。
因此，用户进程必须传递一个参数用于区分，这便是 **系统调用号** ( `system call number` )。
在 `Linux` 中， **系统调用号** 一般通过 `eax` **寄存器** 来传递。

总结起来， **执行态切换** 过程如下：

#. **应用程序** 在 **用户态** 准备好调用参数，执行 `int` 指令触发 **软中断** ，中断号为 `0x80` ；
#. `CPU` 被软中断打断后，执行对应的 **中断处理函数** ，这时便已进入 **内核态** ；
#. **系统调用处理函数** 准备 **内核执行栈** ，并保存所有 **寄存器** (一般用汇编语言实现)；
#. **系统调用处理函数** 根据 **系统调用号** 调用对应的 `C` 函数—— **系统调用服务例程** ；
#. **系统调用处理函数** 准备 **返回值** 并从 **内核栈** 中恢复 **寄存器** ；
#. **系统调用处理函数** 执行 `ret` 指令切换回 **用户态** ；

编程实践
========

下面，通过一个简单的程序，看看应用程序如何在 **用户态** 准备参数并通过 `int` 指令触发 **软中断** 以陷入 **内核态** 执行 **系统调用** ：

.. literalinclude:: /_src/system-programming/syscall/principle/hello_world-int.S
    :caption: hello_world-int.S
    :name: system-programming/syscall/principle/hello_world-int.S
    :language: gas
    :linenos:

这是一个汇编语言程序，程序入口在 `_start` 标签之后。

第 `12` 行，准备 **系统调用号** ：将常数 `4` 放进 **寄存器** `eax` 。
**系统调用号** `4` 代表 **系统调用** `SYS_write` ，
我们将通过该系统调用向标准输出写入一个字符串。

第 `14-16` 行， 准备系统调用参数：第一个参数放进 **寄存器**  `ebx` ，第二个参数放进 `ecx` ， 以此类推。

`write`_ 系统调用需要 `3` 个参数：

- :doc:`/system-programming/file-io/file-descriptor` ，标准输出文件描述符为 `1` ；
- 写入内容(缓冲区)地址；
- 写入内容长度(字节数)；

第 `17` 行，执行 `int` 指令触发软中断 `0x80` ，程序将陷入内核态并由内核执行系统调用。
系统调用执行完毕后，内核将负责切换回用户态，应用程序继续执行之后的指令( 从 `20` 行开始 )。

第 `20-24` 行，调用 `exit`_ 系统调用，以便退出程序。

.. note::

    注意到，这里必须显式调用 `exit`_ 系统调用退出程序。
    否则，程序将继续往下执行，最终遇到段错误( `segmentation fault` )！

    读者可能很好奇——我在写 `C` 语言或者其他程序时，这个调用并不是必须的！

    这是因为 `C` 库( `libc` )已经帮你把脏活累活都干了。

接下来，我们编译并执行这个汇编语言程序：

.. code-block:: shell-session

    $ ls
    hello_world-int.S
    $ as -o hello_world-int.o hello_world-int.S
    $ ls
    hello_world-int.o  hello_world-int.S
    $ ld -o hello_world-int hello_world-int.o
    $ ls
    hello_world-int  hello_world-int.o  hello_world-int.S
    $ ./hello_world-int
    Hello, world!

其实，将 **系统调用号** 和 **调用参数** 放进正确的 **寄存器** 并触发正确的 **软中断** 是个重复的麻烦事。
`C` 库已经把这脏累活给干了——试试 `syscall`_ 函数吧！

.. literalinclude:: /_src/system-programming/syscall/principle/hello_world-syscall.c
    :caption: hello_world-syscall.c
    :name: system-programming/syscall/principle/hello_world-syscall.c
    :language: c
    :lines: 13-
    :linenos:

下一步
======

.. include:: /_fragments/next-step-to-wechat-mp.rst

参考文献
========

#. `Serg Iakovlev <http://iakovlev.org/index.html?p=1035>`_
#. `write(2) - Linux manual page <http://man7.org/linux/man-pages/man2/write.2.html>`_
#. `syscall(2) - Linux manual page <http://man7.org/linux/man-pages/man2/syscall.2.html>`_
#. `_exit(2) - Linux manual page <http://man7.org/linux/man-pages/man2/exit.2.html>`_

.. include:: /_fragments/wechat-reward.rst

.. include:: /_fragments/disqus.rst

.. _write: http://man7.org/linux/man-pages/man2/write.2.html
.. _syscall: http://man7.org/linux/man-pages/man2/syscall.2.html
.. _exit: http://man7.org/linux/man-pages/man2/exit.2.html

.. comments
    comment something out below

    .. meta::
        :description lang=zh:
        :keywords:

