.. 安装系统
    FileName:   install.rst
    Author:     Fasion Chan
    Created:    2018-06-09 16:23:02
    @contact:   fasionchan@gmail.com
    @version:   $Id$

    Description:

    Changelog:

.. meta::
    :keywords: Linux, 安装Linux系统, install Linux, 安装Ubuntu, install Ubuntu, Virtualbox

========
安装系统
========

.. figure:: /_images/environment/install/660f20a39b4c4efbc91cb647e52eb707.png
    :width: 300px

安装系统前，需要准备一台机器(电脑)。
机器可以是 :ref:`environment/install/pm` ，
也可以是 :ref:`environment/install/vm` 。

`Linux <https://www.kernel.org/>`_ 不同发行版， :ref:`environment/install/procedures` 基本上是大同小异。

本节只以 `Ubuntu <https://www.ubuntu.com/>`_ 为例，
演示如何安装 `Ubuntu 服务器版 <https://www.ubuntu.com/download/server>`_ 。
`Ubuntu <https://www.ubuntu.com/>`_ 当前版本为 ``18.04`` 。
至于其他发行版，读者可以触类旁通。

准备机器
========

.. _environment/install/pm:

物理机
------

在物理机上安装系统， :ref:`environment/install/procedures` 大致相同，应该没有障碍。

在这特别提醒一下，对磁盘进行分区调整、格式化等操作会清空数据。
因此， **在物理机上安装系统有一定的危险性，请务必小心操作！**

.. _environment/install/vm:

虚拟机
------

使用 :doc:`virtualbox/index` 软件
:ref:`environment/virtualbox/quick-start/create-vm` ，
并 :ref:`environment/virtualbox/quick-start/insert-iso` 。

点击启动按钮，开启虚拟机，虚拟机默认从光盘引导。

启动顺序
++++++++

如需调整启动顺序，可以在点击启动按钮后，按下 ``F12`` 唤出启动盘选择界面：

.. figure:: /_images/environment/install/5d0e2edfc62d542134e088ca65cbe7e5.png
    :width: 380px

系统列举所有可用的启动设备，如上图所示。
按下设备前的字符，系统即从该设备启动：

- 按下 ``1`` 从硬盘启动；
- 按下 ``f`` 从软盘启动；
- 按下 ``c`` 从光盘启动；
- 等等

还有一种方式是，打开 **系统** -> **主板** 进行设置：

.. figure:: /_images/environment/install/c1d85ba41b7ada11a8ad6ee6240ff33a.png
    :width: 338px

.. _environment/install/procedures:

安装步骤
========

从光盘启动后，安装程序将引导用户进行简单设置，并将系统安装到硬盘。
主要步骤如下：

语言
----

第一步是选择语言：

.. figure:: /_images/environment/install/a96324b9fc769ff7d1ff783e076de27f.png
    :width: 400px

第一个选项是英语，按键可以将光标下移至其他选项。
选好语言后，按下回车即可进入下一设置环节。

推荐读者 **不妨选英语** 好了，理由有二：

#. 计算机发源于英语国家，英语能力是必须的；
#. 一些术语可能翻译得不是很准确，影响理解；

再说了，读了这么些年书，谁还不会个英语？

键盘
----

第二步进行键盘设置：

.. figure:: /_images/environment/install/b1ceb7b132d6a4c997f08c19fe061314.png
    :width: 400px

对于普通电脑，按照默认选美式英语即可。

安装类型
--------

第三步选择安装类型：

.. figure:: /_images/environment/install/c12dc19ce22c841dadc808e9a61438b4.png
    :width: 400px

我们选择第一个，即安装 `Ubuntu` 服务器版。

网络
----

第四步进行网络设置：

.. figure:: /_images/environment/install/6a4c86ff8a9e511c2425ee6d34c7cdae.png
    :width: 400px

这个界面显示电脑当前可用的 `网卡 <https://linux-network-programming.readthedocs.io/zh_CN/latest/protocols/ethernet.html#nic>`_ 以及配置状态。
设置因网络环境而异：

#. 如果网络支持 `DHCP` ，系统将自动获取 `IP` 地址(如上图)；
#. 如果网络使用静态 `IP` ，则需要填写 `IP` 地址、网关地址以及 `DNS` 服务器地址等；

接下来设置网络代理：

.. figure:: /_images/environment/install/752d0c535f371f8aa59d131f6af8d6ed.png
    :width: 400px

如果不使用网络代理，留空即可。在这，我们直接点击回车进入下一环节。

.. _install/disk-setting:

磁盘分区
--------

第六步是进行磁盘设置，这是 **非常关键** 也是 **比较危险** 的一步。

.. figure:: /_images/environment/install/f59adafc836a31d926dbdbbce781ba78.png
    :width: 400px

这里有两种不同的选项：

#. 使用整块磁盘(系统将自动在磁盘上分区)；
#. 手动设置；

使用整块磁盘
++++++++++++

在这个模式下，安装程序将按照默认分区策略定磁盘进行分区。
选择安装磁盘，这是一块 :doc:`virtualbox/index` 虚拟磁盘：

.. figure:: /_images/environment/install/d757e37523da07f9daf76bd092974c1e.png
    :width: 400px

安装程序自动设置两个分区：

.. figure:: /_images/environment/install/72eadd06cbaaf03d08dbf475b1f59f80.png
    :width: 400px

分区一用于存放 `grub` 引导程序；分区二用于安装系统，挂载到根目录( ``/`` )。

确认无误后，点击回车，进入二次确认界面：

.. figure:: /_images/environment/install/ca5006055ca56e0ca79cb679c6d12252.png
    :width: 400px

选择继续( ``continue`` )并点击回车进入下一环节。

.. warning::

    将系统安装在物理磁盘上时要格外谨慎！

    分区调整、格式化、安装系统时均可能清理数据。
    因此做这类危险操作前，一定要先备份数据，以免造成不必要损失！

用户设置
--------

在这个环节，配置一个用于登录系统的用户：

.. figure:: /_images/environment/install/1987c090487bdf01d7457f07d0ca1515.png
    :width: 400px

需要填写的信息包括：

- 真实姓名
- 服务器名
- 用户名(用于登录，可以与真实姓名不同，简单好记即可)
- 密码
- 公钥(可选)

.. warning::

    用户名以及密码需要牢牢记住！

开始安装
--------

.. figure:: /_images/environment/install/cf5353113f75fa61f25c15234cabfc47.png
    :width: 400px

在这个环节，无须额外操作，耐心等待即可。

注意到，在 :ref:`install/disk-setting` 环节设置完毕后，后台即开始进行安装了。
这是一个不错的改进，帮你节省一些时间。

重启
----

第九步进行重启。
走到这一步，也就意味着系统已经安装成功！

.. figure:: /_images/environment/install/5cdbaaa47017ce1150b7bd14d19ee832.png
    :width: 400px

重启前，系统将自动弹出光盘：

.. figure:: /_images/environment/install/58a2525eb7ec4634b5dd8e79800c46d2.png
    :width: 400px

点击回车确认后即可重启。
电脑重新启动后，即进入新装系统！

登录
----

系统启动完毕后，进入登录界面。
用户需要输入 **用户名** 以及 **密码** ，认证通过后方可进行操作：

.. figure:: /_images/environment/install/34f14f83a3eb65dfcc2440de267bd6df.png
    :width: 400px

.. note::

    注意到，密码输入时屏幕没有任何显示！
    这是 Unix 的风格， **默念密码准确输入** 并按回车即可。

Shell
-----

成功登录系统后，进入 `Shell` 环境：

.. figure:: /_images/environment/install/d15fd6f9af44dbe725f78d352843e637.png
    :width: 400px

在 `Shell` 中，用户可以输入一些命令，由系统执行并返回结果：

.. figure:: /_images/environment/install/e755e3795b5f9082b3a7a883ad2a05ea.png
    :width: 400px

我们输入 `ls` 命令用于列举当前目录(家目录)下的所有文件及目录。
因为系统是新装的，我们没有看到任何文件存在。

我们通过 `echo` 将一句话( ``Hello, welcome to Linux!`` )写入一个文件，名为 ``first_file.txt`` 。
接着，我们用 ``ls`` 确认，当前目录下确实存在 ``first_file.txt`` 文件。

最后，我们用 ``cat`` 命令将文件输出文件内容，确实是之前写进入的内容。
**欢迎来到 Linux 世界！**

下一步
======

.. include:: /_fragments/next-step-to-wechat-mp.rst

.. include:: /_fragments/wechat-reward.rst

.. include:: /_fragments/disqus.rst

.. comments
    comment something out below

