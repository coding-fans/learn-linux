.. 二进制管理
    FileName:   index.rst
    Author:     Fasion Chan
    Created:    2019-01-09 19:20:42
    @contact:   fasionchan@gmail.com
    @version:   $Id$

    Description:

    Changelog:

.. meta::
    :description lang=zh:
        通过LD_LIBRARY_PATH环境变量指定动态库搜索路径。
        该方法同样适用于glibc，只需将其放置于LD_LIBRARY_PATH指定的目录下。
    :keywords: 动态库, 静态库, 管理, LD_LIBRARY_PATH, glibc, ld.so, 链接器

==========
二进制管理
==========

通过 `LD_LIBRARY_PATH` 环境变量指定 **动态库** 搜索路径：

.. code-block:: shell-session

    $ LD_LIBRARY_PATH=/some/lib/path /some/program

该方法同样适用于 `glibc`_ ，只需将其放置于 `LD_LIBRARY_PATH` 指定的目录下。
但由于动态链接器( `ld.so`_ )是系统默认的，可能与 `glibc`_ 不兼容而产生 **段错误** 。

这种情况下，需要同时指定与 `glibc`_ 相兼容的 `ld.so`_ ，方法如下：

.. code-block:: shell-session

    $ LD_LIBRARY_PATH=/some/lib/path /some/ld.so /some/program

这行命令的意思是，以 `/some/ld.so` 为动态链接器启动程序 `/some/program` ，
优先在 `/some/lib/path` 目录搜索动态库。

这种方式虽然可以顺利启动 `/some/program` 程序，但是程序路径却是 `/some/ld.so` 。
换句话讲，程序的入口变了。
那么，有办法更优雅地指定 `ld.so`_ 么？

其实， `ld.so`_ 路径作为段信息写在二进制程序中，因此修改该信息即可：

.. code-block:: shell-session

    $ patchelf --set-interpreter /some/ld.so /some/program

这个命令通过 `patchelf`_ 工具将 `/some/program` 的动态链接器改为 `/some/ld.so` 。
之后直接运行程序即可启动：

.. code-block:: shell-session

    $ LD_LIBRARY_PATH=/some/lib/path /some/program

这种方式很完美，程序入口不会莫名其妙地变成 `ld.so` 。
美中还有不足， `ld.so`_ 不能在运行时指定，不太灵活。

参考文献
========

#. `Can I modify the dynamic linker and use without recompiling the glibc? - Stack Overflow <https://stackoverflow.com/questions/19828204/can-i-modify-the-dynamic-linker-and-use-without-recompiling-the-glibc>`_

.. _glibc: https://www.gnu.org/software/libc/
.. _ld.so: http://man7.org/linux/man-pages/man8/ld.so.8.html
.. _patchelf: https://nixos.org/patchelf.html

.. comments
    comment something out below

