.. 共享文件夹
    FileName:   shared-folder.rst
    Author:     Fasion Chan
    Created:    2018-03-14 19:35:52
    @contact:   fasionchan@gmail.com
    @version:   $Id$

    Description:

    Changelog:

.. meta::
    :keywords: virtualbox共享文件夹, virtualbox shared folder

==========
共享文件夹
==========

我们经常需要在虚拟机与宿主(即外面的系统)之间传输文件。

系统间传输文件的方法有很多： `scp` 、 `rsync` 、 `ftp服务器` 、 `nfs` (网络文件系统)等等。
这些都是通用的服务，与虚拟化无关。

除此之外，`Virtualbox` 虚拟机软件还提供一种更便捷的文件共享方式—— **共享文件夹** 。

通过共享文件夹，可以将宿主某个目录共享给虚拟机。
虚拟机文件系统可以访问到该宿主目录，并进行读写，就像自己的一样。

宿主设置
========

先关闭需要设置共享文件夹的虚拟机，
点击 **共享文件夹** 进入设置界面：

.. figure:: /_images/environment/virtualbox/shared-folder/2970540906dc95452a9dd42efd20795f.png
    :width: 338px

点击右侧小加号，新增一个共享文件夹：

.. figure:: /_images/environment/virtualbox/shared-folder/a58264ec444d35fbfa26cc2d38e6f1d8.png
    :width: 170px

在弹出的对话框里，选择需要共享的 **文件夹路径** (宿主)以及 **文件夹名称** 。
文件夹名称用于区分为虚拟机添加的多个文件夹，与实际文件夹本身并无关系。

此外，文件夹还有两个选项可供勾选：

- **只读分配** ，选中后虚拟机只能读取而不能写入；
- **自动分配** ，选中后虚拟机启动时自动将自动挂载共享文件夹；

这两个选项均先不勾选。确认无误后，点击确定即可。

.. figure:: /_images/environment/virtualbox/shared-folder/7461889ac38e7a751c5c655d99dd03c6.png
    :width: 338px

虚拟机挂载
==========

在虚拟机中，共享目录以一种特殊文件系统的方式进行挂载。
挂载后，访问共享目录就像访问本地文件系统一样。

跟其他文件系统一样，共享目录需要用 `mount` 命令进行挂载。
挂载前，还需要先安装 `Virtualbox` 扩展包。
现在，扩展包可以通过 `apt` 命令进行安装：

.. code-block:: shell-session

    $ sudo apt install virtualbox-guest-utils

命令执行完毕后，可以通过查看相关内核模块是否正常启用：

.. code-block:: shell-session

    $ $ lsmod | grep vbox
    vboxsf                 45056  1
    vboxvideo              36864  1
    ttm                   106496  1 vboxvideo
    drm_kms_helper        167936  1 vboxvideo
    drm                   401408  4 vboxvideo,ttm,drm_kms_helper
    vboxguest             303104  2 vboxsf

在输出中可以找到名为 ``vboxsf`` 的内核模块，则意味着扩展包安装成功。

手工挂载
--------

接下来便可以用 `mount` 命令挂载共享文件夹了：

.. code-block:: shell-session

    $ sudo mkdir -p /media/home
    $ sudo mount -t vboxsf -o uid=`id -u`,gid=`id -g` HOME /media/home

`mkdir` 命令创建一个目录，用作共享文件夹的挂载点。

`mount` 命令则将指定共享文件夹挂载到指定挂载点。
其中， ``-t`` 指定文件系统类型为 ``vboxsf`` ；
``-o`` 参数指定挂载选项；
``HOME`` 是共享文件夹名称；
``/media/home`` 是挂载点。

注意到，我们在挂载选项中指定了 ``uid`` (用户ID) 以及 ``gid`` (组ID)。

``mount`` 命令默认将 ``uid`` 和 ``gid`` 分别设置为 ``root`` 用户和 ``root`` 组，
这样其他用户需要 ``sudo`` 提升权限才能访问。
将 ``uid`` 、 ``gid`` 设置成当前用户、组，则免去了权限的烦恼。

顺便提下，当前用户 ``uid`` 、 ``gid`` 可以通过以下命令获得：

.. code-block:: shell-session

    $ id -u
    1000
    $ id -g
    1004

fstab
-----

手工挂载还是有些麻烦，特别是每次系统启动都要操作一遍！
可以在 ``/etc/fstab`` 配置文件新增一行配置解决这个问题。
接下来，我们往配置文件追加以下配置行：

.. code-block:: text

    HOME /media/home vboxsf defaults,uid=1000,gid=1004 0 0

``HOME`` 是共享文件夹名称； ``/media/home`` 是挂载点；
``vboxsf`` 是文件系统类型； ``defaults,uid=1000,gid=1004`` 是挂载选项……
看上去与 ``mount`` 命令基本一致，但是已经固化到文件里头了。

后续系统启动时，将根据这个配置信息自动挂载共享文件夹，再无须额外操作了。

需要调整挂载配置时，先用 `umount` 命令卸载，再用 `mount` 命令重新挂载即可生效：

.. code-block:: shell-session

    $ sudo umount /media/home
    $ sudo mount /media/home

注意到，这里 `mount` 命令只需指定挂载点，其他信息系统均可从配置文件中获取。

下一步
======

.. include:: /_fragments/next-step-to-wechat-mp.rst

.. include:: /_fragments/wechat-reward.rst

.. include:: /_fragments/disqus.rst

.. comments
    comment something out below

