.. 快速开始
    FileName:   quick-start.rst
    Author:     Fasion Chan
    Created:    2018-03-25 11:13:53
    @contact:   fasionchan@gmail.com
    @version:   $Id$

    Description:

    Changelog:

.. meta::
    :description lang=zh:
        点击VirtualBox下载 ，根据宿主系统选择合适版本下载。
        点击安装包，运行安装引导。
        安装成功后，运行VirtualBox进入以下界面，开始配置一台新的虚拟机。
        安装操作系统，需要系统镜像，比如一块光盘。
    :keywords: virtualbox安装, hostonly, 光盘, 安装操作系统

========
快速开始
========

下载
====

点击 `VirtualBox 下载 <https://www.virtualbox.org/wiki/Downloads>`_ ，根据宿主系统选择合适版本下载。

安装
====

以 `OSX` 为例，点击下载好的文件：

.. figure:: /_images/environment/virtualbox/quick-start/fbb2b37ebce31edcc8d29206a3e17f7b.png
    :width: 336px

点击安装包，运行安装引导：

.. figure:: /_images/environment/virtualbox/quick-start/696d18f5a07c46d818dc8dea658152de.png
    :width: 512px

如果系统弹出安全提示，点击继续忽略之：

.. figure:: /_images/environment/virtualbox/quick-start/af25063cbcb950dceaa3867a4d6d6876.png
    :width: 210px

安装位置默认即可，直接点击安装：

.. figure:: /_images/environment/virtualbox/quick-start/80fa660187465aa9d168437c96608eaf.png
    :width: 512px

安装过程中，可能会因为安全限制而失败：

.. figure:: /_images/environment/virtualbox/quick-start/577489fa6237a80571599d45e5004886.png
    :width: 210px

这时，必须打开 系统偏好设置 >> 安全性与隐私 >> 通用 面板，允许 ``Oracle America, Inc`` ，并重新安装。

创建虚拟机
==========

安装成功后，运行 `VirtualBox` 进入以下界面：

.. figure:: /_images/environment/virtualbox/quick-start/70e24e4299385aaae5ca98b708aab8f7.png
    :width: 349px

点击新建，开始配置一台新的虚拟机：

.. figure:: /_images/environment/virtualbox/quick-start/4f3f98981c628aa5e825ecb37b0869b7.png
    :width: 286px

配置虚拟机 **内存** 大小：

.. figure:: /_images/environment/virtualbox/quick-start/2dcf8d7157efcf58625bd45b99c458d6.png
    :width: 286px

新建 **虚拟硬盘** (用虚拟硬盘文件模拟硬盘存储数据)：

.. figure:: /_images/environment/virtualbox/quick-start/c6581a0f590c432b57763c57bc74930a.png
    :width: 286px

选择 **虚拟硬盘文件类型** ，默认即可：

.. figure:: /_images/environment/virtualbox/quick-start/a339e486c01c95ac0c6ca6577c61b9ab.png
    :width: 327px

**分配方式** 选择动态分配，这样在前期可以节省一些磁盘存储空间：

.. figure:: /_images/environment/virtualbox/quick-start/1da7435a94b47039a24741031a87dd20.png
    :width: 327px

选择虚拟硬盘文件 **存储路径** ，同样默认即可：

.. figure:: /_images/environment/virtualbox/quick-start/72706b943b6a763db3a3b5455631c822.png
    :width: 327px

点击 **创建** ，然后新虚拟机就建好了：

.. figure:: /_images/environment/virtualbox/quick-start/2a2a87ab9ff975fd55ed19f457d3a1ff.png
    :width: 349px

到这你可能忍不住想点启动按钮，开启虚拟机了。
但是，现在的虚拟机硬盘还是空的，需要先安装操作系统才能启动。

挂载光盘
--------

安装操作系统，需要系统镜像，比如一块光盘。

虚拟机可以直接访问宿主的光驱；也可以通过虚拟光驱直接连接到一个 `ISO` 文件，这种方式更加便捷。

点击存储进入虚拟机 **存储介质** 管理：

.. figure:: /_images/environment/virtualbox/quick-start/98f6c9927931e51c9fbb93787b38ed5a.png
    :width: 334px

选中光驱并点击右边光盘标识，在弹出的文件选择框中选定光盘文件( `ISO` 格式)即可：

.. figure:: /_images/environment/virtualbox/quick-start/c38e3fb86cadafe47afd6fd4539cb193.png
    :width: 349px

`Linux` 系统 `ISO` 镜像可以在各发行版官网上下载：

- `获取 Debian <https://www.debian.org/distrib/>`_
- `获取 Ubuntu <https://www.ubuntu.com/download>`_

这时，可以点击启动开启虚拟机了。
虚拟机启动后，将在光盘的引导下开始安装操作系统。

组建网络
--------

虚拟机默认通过一个 `NAT` 网络与宿主相连，这样虚拟机便能上网。

在 `NAT` 模式下，宿主不能通过网络访问虚拟机。
如果想通过 ``ssh`` 登录虚拟机或者想访问虚拟机提供的网络服务，只能再配置一块虚拟网卡。

进入虚拟机 **网络管理** ，看到默认已经接入了一块虚拟网卡，连接方式为 `NAT` ：

.. figure:: /_images/environment/virtualbox/quick-start/0f9043ba3c23ecbdd773eb78b4fa9a0f.png
    :width: 334px

虚拟机最多可以接入 ``4`` 块网卡，可以组建各种网络用于学习实验，而且非常方便！

接着，我们选中第二块网卡，并启用：

.. figure:: /_images/environment/virtualbox/quick-start/8122af198b10b417da3d69dcd318b8f2.png
    :width: 334px

连接方式选择 `Host-Only` 网络，然后选择一个网络(界面)。
如果还没建过 `Host-Only` 网络，需要新建一个。
点击 `VirtualBox` **管理** 菜单，选择 **主机网络管理器** ：

.. figure:: /_images/environment/virtualbox/quick-start/eef03db3e5be2dec106ecf5604bb4414.png
    :width: 512px

如上，网络建好后，宿主机可以看到一块名为 ``vboxnet0`` 的虚拟网卡， `IP` 地址为 ``192.168.56.1`` (可自定义)。
虚拟机网卡连接到这个界面后，简单配置后便可与宿主通讯。

下一步
======

.. include:: /_fragments/next-step-to-wechat-mp.rst

.. include:: /_fragments/wechat-reward.rst

.. comments
    comment something out below
