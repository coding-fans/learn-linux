.. CPU使用率
    FileName:   cpu.rst
    Author:     Fasion Chan
    Created:    2018-10-18 21:42:17
    @contact:   fasionchan@gmail.com
    @version:   $Id$

    Description:

    Changelog:

.. meta::
    :keywords: CPU使用率, CPU usage, Linux

=========
CPU使用率
=========

`CPU` 使用率是最常见的监控指标之一，用于衡量 `CPU` 的 **繁忙程度** 。

一方面，如果某个系统 `CPU` 使用率越高，意味着应用进程得不到调度的概率越大，应用响应速度将受负面影响；
另一方面，某个应用 `CPU` 使用率过高，意味着其消耗太多 `CPU` 资源，很可能存在优化的空间。

指标
====

大多数系统管理员或开发人员对 `CPU` 使用率或多或少有所了解，但未必准确。

那么，操作系统如何衡量 `CPU` 的繁忙程度呢？

最简单的方式是，统计 `CPU` 在执行任务的时间以及空闲的时间，并计算这两部分时间的占比。
如果执行任务时间占比很高，则说明 `CPU` 非常繁忙；反之亦然。
因此， `CPU` 使用率是一个 **百分比** 也就非常好理解了。

通常，操作系统对 `CPU` 时间的统计更为细化。
以 `Linux` 为例，内核进一步将执行时间和空闲时间进行分类，形成更为细致指标：

.. csv-table:: CPU使用率指标(%)
    :header: "指标名", "含义"

    "user", "用户态"
    "nice", "低优先级用户态"
    "system", "内核态"
    "idle", "空闲"
    "iowait", "IO等待"
    "irq", "中断处理"
    "softirq", "软中断处理"
    "steal", "被其他虚拟化系统占用"
    "guest", "运行客户机系统"
    "guest_nice", "运行低优先级客户机系统"

user
----

`user` 表示 `CPU` 运行在 **用户态** 的时间占比。

应用进程执行分为 **用户态** 以及 **内核态** ：
`CPU` 在用户态执行应用进程自身的代码逻辑，通常是一些 **逻辑** 或 **数值计算** ；
`CPU` 在内核态执行进程发起的 :doc:`../../../system-programming/syscall/index` ，通常是响应进程对资源的请求。

如果应用为 **计算密集型** (包含大量计算很少系统调用)，则 `CPU` `user` 状态使用率很高。

nice
----

`nice` 表示 `CPU` 运行在 **低优先级用户态** 的时间占比，低优先级意味着进程 `nice` 值小于 `0` 。

system
------

`user` 表示 `CPU` 运行在 **内核态** 的时间占比。

一般而言， **内核态** `CPU` 使用率不应过高，除非应用进程发起大量系统调用。
如果该值较高，需要着手分析原因，重新审视程序设计是否存在缺陷。

idle
----

`idle` 表示 `CPU` 在空闲状态的时间占比，该状态下 `CPU` 没有任何任务可执行。

iowait
------

`iowait` 表示“等待I/O”的时间。
大部分人对此有误解，认为 `CPU` 此时不能工作。

这是不正确的， `CPU` 在等待 `I/O` 时，可以切换到其他就绪任务执行，只是当时刚好没有就绪任务可以运行。
准确讲， `iowait` 是 `CPU` 空闲并且系统有 `I/O` 请求未完成的时间。

另一个误解是： `iowait` 升高时便认为系统存在 `I/O` 瓶颈。
同种 `I/O` 条件下，如果系统还有其他计算密集型任务， `iowait` 将明显降低。

因此， `iowait` 是一个非常模糊的指标，并不足以说明问题。
大部分情况下，还需要检查 `I/O` 量，等待队列等更加明确的指标。
如果只是 `iowait` 升高，其他指标没有明显变化，便无需担心。

.. note::

    `idle` 和 `iowait` 都说明 `CPU` 很空闲， `iowait` 还说明系统有未完成的 `I/O` 请求。

irq
---

`irq` 表示 `CPU` 处理 **硬件中断** 的时间占比。

**网卡中断** 是一个典型的例子：网卡接到数据包后，通过硬件中断通知 `CPU` 进行处理。
如果系统网络流量非常大，则可观察到 `irq` 使用率明显升高。

通常，网卡中断只由一个 `CPU` 来响应。
如果网络处理上不去并观察到单个 `CPU` `irq` 指标较高，则可以考虑通过 `irqbalance`_ 将中断处理平衡到更多 `CPU` 上。

softirq
-------

对应地， `softirq` 表示 `CPU` 处理 **软件中断** 的时间占比。

steal
-----

`steal` 是指在虚拟化环境中，被其他系统占用的时间。
这体现为物理 `CPU` 没有办法为当前系统服务，通常正在为另一个系统服务。
在虚拟机超卖比较严重的场景，这个数值非常明显。
这部分时间显然不是当前系统所用，而是被其他系统占用了。

total
-----

总 `CPU` 时间片数是各种状态时间的和，计算公式如下：

.. math::

    total = user + nice + system + idle + iowait + irq + softirq + steal

注意到， `guest` 以及 `guest_nice` 不参与求和计算，因为这两种时间分别作为 `user` 以及 `nice` 的一部分统计在其中了。

utilized
--------

`CPU` 用于执行任务的时间将是 `6` 种执行状态时间的总和：

.. math::

    utilized = user + nice + system + irq + softirq + steal

除此之外，还有另外一种计算方法，只包含 `5` 种执行状态：

.. math::

    utilized = user + nice + system + irq + softirq

两种计算方式区别只在于： `steal` 状态占用的时间是否参与计算。
前者反应了系统的 **实际负载** ， `steal` 虽不是本系统占用，但也制约了系统对 `CPU` 资源的进一步使用；
后者则反映了系统的 **真实负载** ，也就是系统的实际开销。

算法
====

`Linux` 内核为 `CPU` 各个核心维护了 **自系统启动** 以来各种状态的时间，并暴露在在 `proc`_ 伪文件系统中，路径为 `/proc/stat` 。
通过以下命令可以窥探一二：

.. code-block:: shell-session

    $ cat /proc/stat

.. note::

    `/proc/stat` 中， `CPU` 时间单位为 `jiffy` ，即 ``USER_HZ`` 分之一秒。
    其中， ``USER_HZ`` 是内核计时时钟的频率，表示时钟每秒产生多少次中断。
    时钟每中断一次，内核 `jiffies` 自增 `1` 。

很显然， `CPU` 使用率可以由内核提供的计数器( `counters` )计算而来。

首先，在 `t1` 时间点采集一次 `/proc/stat` 数据并计算总 `CPU` 时间：

.. math::

    total_{t1} = user_{t1} + nice_{t1} + system_{t1} + idle_{t1} + iowait_{t1} + irq_{t1} + softirq_{t1} + steal_{t1}

在 `t2` 时间点再采集一次，同样计算总 `CPU` 时间：

.. math::

    total_{t2} = user_{t2} + nice_{t2} + system_{t2} + idle_{t2} + iowait_{t2} + irq_{t2} + softirq_{t2} + steal_{t2}

那么，从 `t1` 到 `t2` 的 `CPU` 时间为：

.. math::

    delta_{t1,t2} = total_{t2} - total_{t1}

其中，用户态时间占比为：

.. math::

    user\_percent = {\frac{user_{t2} - user_{t1}}{total_{t2} - total_{t1}}} \times 100\%

这便是用户态 `CPU` 使用率，其他状态使用率计算方式以此类推。

很显然，所有状态 `CPU` 使用率加起来刚好就是 `100%` (同样不包括 `guest` 系列)：

.. math::

    user\_percent + nice\_percent + \cdots + steal\_percent = 100\%

采集
====

接下，看看如何读取 `/proc/stat` 文件并计算 `CPU` 使用率。直接上代码：

.. literalinclude:: /_src/maintenance/monitor/os/cpu_usage/cpu_usage.py
    :caption: cpu_usage.py
    :name: maintenance/monitor/os/cpu_usage/cpu_usage.py
    :language: py
    :lines: 16-
    :linenos:

`cpu_counters` 函数负责读取 `/proc/stat` 文件并解析所有 `CPU` 时间计数器：

#. 第 `31` 行，打开 `/proc/stat` 文件；
#. 第 `33` 行，读取所有文本行；
#. 第 `34-35` 行，跳过所有非 `cpu` 开头的行；
#. 第 `38` 行，切分字段；
#. 第 `41` 行，取出 `CPU` 名字段；
#. 第 `43` 行，将所有 `CPU` 时间计数器转换成整数类型；
#. 第 `45` 行，累加总 `CPU` 时间；
#. 第 `47` 行，记录解析结果；

`sample_forever` 函数不断采集并计算 `CPU` 使用率，计算部分逻辑如下：

#. 第 `62-63` 行，遍历每个 `CPU` 设备，分别取出 `CPU` 名、计数器以及总 `CPU` 时间；
#. 第 `66` 行，计算两次采集间的总 `CPU` 时间；
#. 第 `67-70` 行，计算两次采集间 `CPU` 每种状态执行时间的占比(百分比)；
#. 第 `71` 行，计算 `CPU` 繁忙时间占比，包括 `steal` 部分；

注意到，例子程序使用 `tabulate`_ 模块格式化表格，不再赘述。

下一步
======

.. include:: /_fragments/next-step-to-wechat-mp.rst

参考文献
========

#. `proc(5) - Linux manual page <http://man7.org/linux/man-pages/man5/proc.5.html>`_

.. include:: /_fragments/wechat-reward.rst

.. include:: /_fragments/disqus.rst

.. _irqbalance: https://linux.die.net/man/1/irqbalance
.. _proc: http://man7.org/linux/man-pages/man5/proc.5.html
.. _tabulate: https://python-book.readthedocs.io/zh_CN/latest/libs/tabulate.html

.. comments
    comment something out below

