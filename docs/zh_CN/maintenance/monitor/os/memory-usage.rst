.. 内存使用量
    FileName:   memory-usage.rst
    Author:     Fasion Chan
    Created:    2018-10-22 21:42:18
    @contact:   fasionchan@gmail.com
    @version:   $Id$

    Description:

    Changelog:

.. meta::
    :keywords: 内存使用量, 内存监控, memory usage, memory monitor, linux

==========
内存使用量
==========

**内存** ( `memory` )是操作系统管理的一项重要资源，对 **内存使用量** 进行监控，
有助于提前发现内存问题，避免因内存耗尽而造成的故障。
此外，精准的 **监控数据** 也可用于应用程序 **性能分析** 以及更进一步的 **性能优化** 。

执行 `free`_ 命令便可查看 **内存使用量** ：

.. code-block:: shell-session

    $ free
                  total        used        free      shared  buff/cache   available
    Mem:        8174924      806748     5777464       85768     1590712     6952528
    Swap:       7999484           0     7999484

`free`_ 命令展示了 **物理内存** 以及交换内存使用量，指标说明见下节。

指标
====

`Linux` 内核负责统计内存使用量并暴露在 `proc`_ 伪文件系统中，路径是 `/proc/meminfo` 。
一般而言，需要重点关注的指标如下：

.. csv-table:: 内存使用量指标(字节)
    :header: "指标名", "含义"

    "total", "物理内存总量"
    "free", "空闲内存(未使用)"
    "buffers", "内核缓冲区"
    "cached", "文件缓冲页"
    "slab", "内核 `slab` 数据结构"
    "cache", "`cached` 以及 `slab` 之和"
    "g_free", "广义空闲内存"
    "used", "已使用内存"
    "active", "活跃内存"
    "inactive", "非活跃内存"
    "available", "可用内存"

total
-----

`total` 表示 **物理内存总量** ，单位为 **字节** ，对应 `/proc/meminfo` 的 `MemTotal` 字段。

free
----

`free` 表示 **空闲内存量** ，单位为 **字节** ， 对应 `/proc/meminfo` 的 `MemFree` 字段。

buffers
-------

`buffers` 表示 **内核缓冲区** ，单位为 **字节** ，对应 `/proc/meminfo` 的 `Buffers` 字段。

cached
------

`cached` 表示 **文件缓冲页** ，单位为 **字节** ，对应 `/proc/meminfo` 的 `Cached` 字段。

slab
----

`slab` 表示 **内核slab数据结构** ，单位为 **字节** ，对应 `/proc/meminfo` 的 `Slab` 字段。

cache
-----

`cache` 与 `free` 命令中的 `cache` 相同，即 `cached` 以及 `slab` 之和：

.. math::

    cache = cached + slab

g_free
------

`g_free` 表示 **广义空闲内存** ( `generalized free` )，单位为 **字节** ，计算方式如下：

.. math::

    g\_free = free + buffers + cache

`buffers` 和 `cache` 是系统为了提升性能而使用的缓存，内存紧张时可随时回收另做它用。
因此，这部分内存在某种意义上可以认为是空闲的，这就是 **广义空闲内存** 的由来。
在某些场景， `g_free` 比 `free` 更有参考价值。

used
----

`used` 表示 **已用内存** ，单位为 **字节** ，计算方式如下：

.. math::

    used = total - g\_free = total - free - buffers - cache

active
------

`active` 表示 **活跃内存** ，单位为 **字节** ，对应 `/proc/meminfo` 的 `Active` 字段。

**活跃内存** 是指最近经常访问的内存，通常不会被重新分配，除非非常必要。

inactive
--------


`inactive` 表示 **非活跃内存** ，单位为 **字节** ，对应 `/proc/meminfo` 的 `Inactive` 字段。

**非活跃内存** 是指最近较少访问的内存，需要新分配内存时，这部分优先选择。

available
---------

`available` 表示 **可用内存** ，单位为 **字节** ，对应 `/proc/meminfo` 的 `MemAvailable` 字段。

**可用内存** 指的是可用于启动一个新应用进程的内存，该指标是内核提供的一个估计值。
它同样结合 `free` 以及 `cache` 两部分内存，但是考虑到 `cache` 因使用而不能释放的情况。
因此，可以认为：

.. math::

    free \le available \le g\_free

采集
====

数据采集非常简单，读取 `/proc/meminfo` 文件相关字段即可：

.. literalinclude:: /_src/maintenance/monitor/os/memory_usage/memory_usage.py
    :caption: memory_usage.py
    :name: maintenance/monitor/os/memory_usage/memory_usage.py
    :language: py
    :lines: 16-
    :linenos:

下一步
======

.. include:: /_fragments/next-step-to-wechat-mp.rst

参考文献
========

#. `proc(5) - Linux manual page <http://man7.org/linux/man-pages/man5/proc.5.html>`_

.. include:: /_fragments/wechat-reward.rst

.. include:: /_fragments/disqus.rst

.. _proc: http://man7.org/linux/man-pages/man5/proc.5.html
.. _free: http://man7.org/linux/man-pages/man1/free.1.html

.. comments
    comment something out below

