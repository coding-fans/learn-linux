.. C/C++ 开发环境(终端)
    FileName:   c-cpp.rst
    Author:     Fasion Chan
    Created:    2018-06-29 17:01:46
    @contact:   fasionchan@gmail.com
    @version:   $Id$

    Description:

    Changelog:

.. meta::
    :keywords: linux, c, c++, gcc, g++, 安装

====================
C/C++ 开发环境(终端)
====================

`Linux` 终端系统，例如 `Ubuntu 服务器版 <https://www.ubuntu.com/download/server>`_ ，是不带图形桌面的。
因此，在终端系统上做开发，只能依赖一些命令行工具，与 `IDE` 环境颇有不同。

C 语言
======

在 `Linux` 下，一般使用 `gcc` 编译 `C` 语言代码。
`gcc` 可以通过包管理工具进行安装，以 `Ubuntu` 为例：

.. code-block:: shell-session

    $ sudo apt-get install gcc

接下来，我们编译一个非常简单的 `C` 语言程序 `hello_world.c <http://github.com/fasionchan/learn-linux/tree/master/src/development-environment/c/hello_world.c>`_ 。
代码如下：

.. literalinclude:: /_src/development-environment/c/hello_world.c
    :caption: hello_world.c
    :name: development-environment/c/hello_world.c
    :language: c
    :lines: 13-
    :linenos:

你可以使用任何编辑工具来编写代码，`nano` 、 `vi` 甚至于记事本均可。

代码编辑完毕后，运行 `gcc` 命令进行编译：

.. code-block:: shell-session

    $ ls
    hello_world.c
    $ gcc -o hello_world hello_world.c

其中， `-o` 选项指定可执行程序名， `hello_world.c` 是源码文件。
不出意外，当前目录下将出现一个可执行文件：

.. code-block:: shell-session

    $ ls
    hello_world  hello_world.c

最后，还是在命令行下，将程序运行起来。
看，程序输出预期内容：

.. code-block:: shell-session

    $ ./hello_world
    Hello, world!

C++ 语言
========

`C++` 语言编译与 `C` 语言类似，只不过编译工具不再是 `gcc` ，而是 `g++` 。
同样地， `g++` 也可以通过包管理工具来安装：

.. code-block:: shell-session

    $ sudo apt install g++

还是编译一个简单的程序 `hello_world.cpp <http://github.com/fasionchan/learn-linux/tree/master/src/development-environment/cpp/hello_world.cpp>`_ ，代码如下：

.. literalinclude:: /_src/development-environment/cpp/hello_world.cpp
    :caption: hello_world.cpp
    :name: development-environment/cpp/hello_world.cpp
    :language: c
    :lines: 13-
    :linenos:

运行 `g++` 命令进行编译，用法与 `gcc` 一样：

.. code-block:: shell-session

    $ ls
    hello_world.c
    $ g++ -o hello_world hello_world.cpp

编译完毕后，执行程序：

.. code-block:: shell-session

    $ ./hello_world
    Hello, world!

下一步
======

.. include:: /_fragments/next-step-to-wechat-mp.rst

.. include:: /_fragments/wechat-reward.rst

.. include:: /_fragments/disqus.rst

.. comments
    comment something out below

    .. meta::
        :description lang=zh:
        :keywords:

