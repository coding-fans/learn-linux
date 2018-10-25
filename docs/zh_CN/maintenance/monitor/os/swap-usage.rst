.. 交换空间使用量
    FileName:   swap-usage.rst
    Author:     Fasion Chan
    Created:    2018-10-25 18:11:09
    @contact:   fasionchan@gmail.com
    @version:   $Id$

    Description:

    Changelog:

.. meta::
    :keywords: 交换空间使用量, swap usage, linux, swap, used swap, memory

==============
交换空间使用量
==============

通过 `Swap` 技术， `Linux` 内核可以将较少被访问的 **内存页** 交换到设定好的 **磁盘空间** 。
释放出来的内存页可另做他用，以缓解系统的内存压力。

交换空间通常是一个 **磁盘分区** ，但是也可以是一个 **文件** 。
**物理内存** 和 **交换空间** 的总大小是理论上可以使用的内存总量——也称作 **虚拟内存** 总量。

.. math::

    virtual = physical + swap

.. warning::

    虽然 **交换分区** 理论上可以增加系统可用的内存总量，但不能滥用。
    由于 **磁盘** 的访问速度远比 **内存** 慢， **频繁的交换操作将拖垮系统** 。
    因此，对 **交换空间** 使用情况进行监控很有必要。

指标
====

.. csv-table:: 交换空间使用量指标(字节)
    :header: "指标名", "含义"

    "total", "交换空间总量"
    "free", "空闲交换空间(未使用)"
    "used", "已用交换空间"

total
-----

`total` 表示 **交换空间总量** ，单位为 **字节** ，对应 `/proc/meminfo` 的 `SwapTotal` 字段。

free
----

`free` 表示 **空闲交换空间** ，单位为 **字节** ，对应 `/proc/meminfo` 的 `SwapFree` 字段。

used
----

`used` 表示 **已用交换空间** ，单位为 **字节** ，可由前两个字段计算而来：

.. math::

    used = total - free

采集
====

同样，一个简单的 `Python` 程序读取 `/proc/meminfo` 文件即可采集数据：

.. literalinclude:: /_src/maintenance/monitor/os/swap_usage/swap_usage.py
    :caption: swap_usage.py
    :name: maintenance/monitor/os/swap_usage/swap_usage.py
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

