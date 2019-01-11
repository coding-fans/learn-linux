.. tar
    FileName:   tar.rst
    Author:     Fasion Chan
    Created:    2018-11-29 17:44:03
    @contact:   fasionchan@gmail.com
    @version:   $Id$

    Description:

    Changelog:

.. meta::
    :description lang=zh:
    :keywords: tar

===
tar
===

典型场景
========

打包
----

`-c` 参数表示打包， `-f` 参数指定文件包输出路径， `src` 为待打包文件或目录：

.. code-block:: shell-session

    $ tar -cf dst.tar src

压缩
----

添加 `-z` 参数，在打包的同时对输出文件包进行压缩：

.. code-block:: shell-session

    $ tar -czf dst.tar.gz src

以下参数与 `-z` 等价：

.. code-block:: shell-session

    $ tar --gzip -cf dst.tar.gz src

解除软链
--------

`tar` 命令默认打包软链，也可以将软链替换为其指向的目标文件，添加 `-h` 参数：

.. code-block:: shell-session

    $ tar -chf xxxx.tar xxxx

或者 `--dereference` 参数：

.. code-block:: shell-session

    $ tar --dereference -cf xxxx.tar xxxx

参考文献
========

#. `tar(1) - Linux manual page <http://man7.org/linux/man-pages/man1/tar.1.html>`_

.. _tar: http://man7.org/linux/man-pages/man1/tar.1.html

.. comments
    comment something out below
