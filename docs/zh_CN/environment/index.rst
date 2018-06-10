.. 环境准备
    FileName:   index.rst
    Author:     Fasion Chan
    Created:    2018-03-14 19:31:33
    @contact:   fasionchan@gmail.com
    @version:   $Id$

    Description:

    Changelog:

========
环境准备
========

学习 `Linux` ，首先要有 `Linux` 系统。那么，如何获得 `Linux` 系统呢？

第一个选择是 **虚拟机** ——使用虚拟机软件(如 :doc:`virtualbox/index` )模拟出一台电脑，
在其上安装操作系统进行练习。
点击链接查看如何 :doc:`安装VirtualBox <virtualbox/quick-start>` ，
以及 :doc:`安装Linux <install>` 。

另一个选择是 **物理机** ——直接将 `Linux` 系统安装到你的电脑之上。
这种情况下，一般会采用 **双系统** 模式， `Linux` 系统与原有系统共存，
开机时选择进入其中一个。
初学者可能对磁盘分区以及格式化等操作理解不足，需要 **格外小心** ！

最后一个选择是 **公有云** ——花钱买一个云虚拟机， `SSH` 连上去即可使用。
国内知名的云厂商有：
`阿里云 <https://www.aliyun.com/>`_ 、
`腾讯云 <https://cloud.tencent.com/>`_ ；
国外的有：
`AWS <https://aws.amazon.com/>`_ 、
`Linode <https://www.linode.com/?r=8e45c4effcbbafe17fd593b5064d219bfab37e7d>`_ 。

.. toctree::
    :maxdepth: 2

    VirtualBox <virtualbox/index>
    安装系统 <install>
