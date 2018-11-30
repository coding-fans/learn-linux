.. 文本处理
    FileName:   index.rst
    Author:     Fasion Chan
    Created:    2018-11-29 18:35:11
    @contact:   fasionchan@gmail.com
    @version:   $Id$

    Description:

    Changelog:

.. meta::
    :description lang=zh:
        作为一名Linux研发人员，几乎每天都要面对文本处理场景。
        因此掌握文本处理套路并熟练运用文本处理命令，对于提升工作效率意义重大。
    :keywords: 文本处理, linux, grep, awk, sed, cut, xargs, text processing


========
文本处理
========

作为一名 *Linux* 研发人员，几乎每天都要面对文本处理场景。
因此 **掌握文本处理套路** 并 **熟练运用文本处理命令** ，对于 **提升工作效率** 意义重大。

本文以一个实战例子抛砖引玉，介绍如何运用 `grep` 、 `awk` 、 `sed` 、 `cut` 等命令进行文本处理，
以 **快速** 完成原本很繁琐的操作。

背景
====

笔者开发机上有很多 `Docker`_ 镜像，现在需要删除名为 ``none`` 的那些：

.. code-block:: shell-session

    $ docker images
    REPOSITORY          TAG                 IMAGE ID            CREATED             SIZE
    api-adapter         v1                  e9bc8e28af2a        3 hours ago         7.67MB
    <none>              <none>              f0fa889be9e8        2 days ago          956MB
    <none>              <none>              257954316455        2 days ago          956MB
    <none>              <none>              99739acbfe7a        2 days ago          956MB
    <none>              <none>              52b10754a70c        2 days ago          956MB
    <none>              <none>              86878eefdd39        2 days ago          956MB
    golang              1.10                0a19f4d16598        12 days ago         729MB
    python              3                   1e80caffd59e        12 days ago         923MB

如何操作呢？莫非手工一个个删除么？

.. code-block:: shell-session

    $ docker image rm f0fa889be9e8

试想，如果有上百个这样的镜像待删，要搞到何年何月！但如何改进呢？

文本过滤
========

考虑先把名字为 ``none`` 的镜像从结果中过滤出来， `grep` 命令即可搞定：

.. code-block:: shell-session

    $ docker images | grep none
    <none>              <none>              f0fa889be9e8        2 days ago          956MB
    <none>              <none>              257954316455        2 days ago          956MB
    <none>              <none>              99739acbfe7a        2 days ago          956MB
    <none>              <none>              52b10754a70c        2 days ago          956MB
    <none>              <none>              86878eefdd39        2 days ago          956MB

字段提取
========

接着，将容器 *ID* 一列提取出来，这对 `awk` 来说简直是小儿科：

.. code-block:: shell-session

    $ docker images | grep none | awk '{print $3}'
    f0fa889be9e8
    257954316455
    99739acbfe7a
    52b10754a70c
    86878eefdd39

当然了，通过 `cut` 命令进行 **字段切分** 也可以得到相同的结果。
由于 `cut` 只能按单个字符进行切分，而原文本中的空格为多个，因此需要先进行 **文本替换** 。

文本替换
========

文本替换是 `sed` 命令擅长的事，下面将一个或多个空格替换成一个：

.. code-block:: shell-session

    $ docker images | grep none | sed 's/  */ /g'
    <none> <none> f0fa889be9e8 2 days ago 956MB
    <none> <none> 257954316455 2 days ago 956MB
    <none> <none> 99739acbfe7a 2 days ago 956MB
    <none> <none> 52b10754a70c 2 days ago 956MB
    <none> <none> 86878eefdd39 2 days ago 956MB

.. comments
    **


.. comments
    注意到，正则表达式 ``  *`` 可以匹配一个或多个空格。
    **

文本切分
========

接下来，使用 `cut` 命令对结果进行进一步切分并取出第三个字段：

.. code-block:: shell-session

    $ docker images | grep none | sed 's/  */ /g' | cut -d ' ' -f 3
    f0fa889be9e8
    257954316455
    99739acbfe7a
    52b10754a70c
    86878eefdd39

.. comments
    **

不错，我们得到与运用 `awk` 命令相同的结果。

批量删除
========

接下来，通过 `xargs` 批量删除镜像：

.. code-block:: shell-session

    $ docker images | grep none | awk '{print $3}' | xargs docker image rm
    Deleted: sha256:f0fa889be9e8f8369353a32e8cec17e9333cbeb581de5f78bf6875917d971bc9
    Deleted: sha256:d301d0546b29b7daa55d29f29d9253664870fd83465aefe8b92ff6a7048d5612
    ...

在这个例子中， `xargs` 最终将执行以下命令：

.. code-block:: shell-session

    $ docker image rm f0fa889be9e8 257954316455 99739acbfe7a 52b10754a70c 86878eefdd39

看到没有，所有不想要的镜像都删除干净了，而且只需要进行一次操作：

.. code-block:: shell-session

    $ docker images
    REPOSITORY          TAG                 IMAGE ID            CREATED             SIZE
    api-adapter         v1                  e9bc8e28af2a        3 hours ago         7.67MB
    golang              1.10                0a19f4d16598        12 days ago         729MB
    python              3                   1e80caffd59e        12 days ago         923MB

下面这个操作也是等价的：

.. code-block:: shell-session

    $ docker images | grep none | sed 's/  */ /g' | cut -d ' ' -f 3 | xargs docker image rm

.. comments
    **

下一步
======

.. include:: /_fragments/next-step-to-wechat-mp.rst

参考文献
========

#. `awk(1) - Linux man page <https://linux.die.net/man/1/awk>`_
#. `cut(1) - Linux man page <https://linux.die.net/man/1/cut>`_
#. `grep(1) - Linux man page <https://linux.die.net/man/1/grep>`_
#. `sed(1) - Linux man page <https://linux.die.net/man/1/sed>`_
#. `xargs(1) - Linux man page <https://linux.die.net/man/1/xargs>`_

.. include:: /_fragments/wechat-reward.rst

.. include:: /_fragments/disqus.rst

.. _Docker: https://docker-note.readthedocs.io/zh_CN/latest/

.. comments
    comment something out below

