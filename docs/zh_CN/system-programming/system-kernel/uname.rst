.. 获取系统内核信息
    FileName:   uname.rst
    Author:     Fasion Chan
    Created:    2018-10-18 21:11:52
    @contact:   fasionchan@gmail.com
    @version:   $Id$

    Description:

    Changelog:

.. meta::
    :description lang=zh:
    :keywords:

================
获取系统内核信息
================

通过 `uname` ，可以获取当前操作系统相关信息：

.. code-block:: shell-session

    $ uname -a
    Linux ant.x.fasionchan.com 4.4.0-87-generic #110-Ubuntu SMP Tue Jul 18 12:55:35 UTC 2017 x86_64 x86_64 x86_64 GNU/Linux

命令展示的信息包括：

- 操作系统名
- 机器名
- 操作系统发布号
- 操作系统版本
- 处理器体系结构
- etc

命令通过同名系统调用获得信息， `uname`_ 系统调用非常简单，一个例子足以说明用法：

.. literalinclude:: /_src/system-programming/system-kernel/uname/uname.c
    :caption: uname.c
    :name: system-programming/system-kernel/uname/uname.c
    :language: c
    :lines: 13-
    :linenos:

第 `9` 行，调用 `uname` 需要传入一个 `utsname` 类型结构体，内核为其填写相关字段。
结构体定义如下：

.. code-block:: c

    struct utsname {
        char sysname[];    /* Operating system name (e.g., "Linux") */
        char nodename[];   /* Name within "some implementation-defined
                              network" */
        char release[];    /* Operating system release (e.g., "2.6.28") */
        char version[];    /* Operating system version */
        char machine[];    /* Hardware identifier */
    #ifdef _GNU_SOURCE
        char domainname[]; /* NIS or YP domain name */
    #endif
    };

结构体字段都是字符串类型，解释如下：

- `sysname` ，操作系统名(内核类型)
- `nodename` ，节点名(即机器名)
- `release` ，操作系统发布号(内核版本号)
- `version` ，操作系统版本(发行版信息)
- `machine` ，机型(处理器体系结构)

下一步
======

.. include:: /_fragments/next-step-to-wechat-mp.rst

参考文献
========

#. `uname(1) - Linux man page <https://linux.die.net/man/1/uname>`_
#. `uname(2) - Linux man page <https://linux.die.net/man/2/uname>`_

.. include:: /_fragments/wechat-reward.rst

.. include:: /_fragments/disqus.rst

.. _uname: https://linux.die.net/man/2/uname

.. comments
    comment something out below

