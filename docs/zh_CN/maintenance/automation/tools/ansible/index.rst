.. Ansible
    FileName:   index.rst
    Author:     Fasion Chan
    Created:    2018-09-17 20:41:04
    @contact:   fasionchan@gmail.com
    @version:   $Id$

    Description:

    Changelog:

.. meta::
    :description lang=zh:
        Ansible是一个非常简单轻量级的IT自动化引擎，可应用与很多IT领域：云基础设施；配置管理；应用部署；服务编排。
        Ansible通过描述系统间关系来为IT基础设施建模，从设计之初便瞄准多层部署场景， 因此不局限于单个系统这种简单场景。
    :keywords: ansible, ansible module, ansible playbook, ansible inventory

=======
Ansible
=======

.. figure:: /_images/maintenance/automation/tools/ansible/index/68c978c6cb0189b17af2a436be100d25.png
    :width: 312px

.. toctree::
    :titlesonly:

    模块 <module>

在 `IT` 领域，你可能经常一遍遍重复着同样的操作任务。
如果可以通过自动化一次性解决问题，你的双手将得到解放。
这便是 `Ansible <https://www.ansible.com/>`_ 设计的初衷。

`Ansible <https://www.ansible.com/>`_ 是一个非常简单轻量级的 `IT` 自动化引擎，可应用与很多 `IT` 领域：

- 云设施管控；
- 配置管理；
- 应用部署；
- 服务编排；
- `etc`

`Ansible` 通过描述 **系统间关系** 来为 `IT` 基础设施建模，从设计之初便瞄准多层部署场景，
因此不局限于单个系统这种简单场景。

`Ansible` 非常容易部署，不需要客户端软件，也不需要额外的安全基础设施。
更重要的是， `Ansible` 使用 `YAML` 这样简单的语言来描述自动化任务，非常接近英语大白话。

架构
====

.. figure:: /_images/maintenance/automation/tools/ansible/index/462873202d20007030f00f5a07c85155.png
    :width: 600px

`Ansible` 先连上目标节点，并推送一些称为 `Ansible` 模块( `Ansible modules` )的小程序。
这些程序被设计成描述 **系统目标状态** 的资源模型，可以多次执行( **幂等性** )。
此后， `Ansible` 执行这些模块(默认通过 `SSH` )，并在执行完毕后删除。

你的模块库可以部署在任意机器上，而且不需要任何服务、守护进程或者数据库来支撑。
通常，你只需使用自己喜欢的 **终端程序** 、 **文本编辑器** 以及一个可选的 **版本控制工具** (用于管理内容变更)，便可管理一切。

SSH密钥
=======

`Ansible` 通过 `SSH` 管理目标节点，因此必须通过 `SSH` 认证。
虽然密码认证也是支持的，但是 `Ansible` 更推荐使用 `SSH` 密钥。
尽管如此，如果你想使用 `Kerberos` ，也是可以的。
`root` 用户登录也不是必要的，你可以用任何用户登录，
并通过 `su` 或者 `sudo` 命令切换到任何其他用户。

`Ansible` 提供内置模块 `authorized_key` ，可以用于控制哪些机器可以访问哪些机器。
其他选项，例如 `Kerberos` 、 **身份管理系统** ( `identity management systems` )也可以使用。

.. code-block:: shell-session

    $ ssh-agent bash
    $ ssh-add ~/.ssh/id_rsa

设备清单
========

`Ansible` 默认通过一个非常简单的 `INI` 配置文件维护其管理的机器—— **清单** ( `inventory` )。
通过该配置文件，你可以根据需要为机器进行分组。

添加机器无需额外的 `SSL` 签名，
因此不会因 `NTP` 或者 `DNS` 问题导致机器不能导入。
要知道，排查这些问题还是相当繁琐的。

可以看到，设备清单配置文件是非常直白的文本：

.. code-block:: ini

    [web]
    web01.example.com
    web02.example.com

    [db]
    db01.example.com
    db02.example.com

清单还支持为主机或者集群定义 **变量** ，以此实现差异化操作。
变量可以直接在清单配置文件中定义，也可以由额外的文本文件来定义(放置于 ``group_vars/`` 或者 ``host_vars/`` 子目录)。

如果你的基础设施体系由其他系统提供可靠的数据源， `Ansible` 也可以与其对接。
例如，开发 **动态清单** ( `dynamic inventory` )，
从类型 `EC2` 、 `Rackspace` 、 `Openstack` 等数据源中，
获取 **机器列表** 、 **群组** 以及 **变量** 等信息。

快速执行
========

只要有一个目标节点就绪，即可通过命令行执行任务，无需任何额外配置：

.. code-block:: shell-session

    $ ansible 10.0.1.1 -m yum -a 'name=httpd state=installed'
    $ ansible foo.example.com -a '/usr/sbin/reboot'

注意到，你可以执行确保系统最终状态的模块，或者直接执行原生命令行。
这些模块写起来非常简便，而且 `Ansible` 已经有大量的积累，大部分问题解决方案唾手可得。

定义好设备清单之后，你可以非常方便地进行批量执行。例如，对 ``web`` 集群批量执行：

.. code-block:: shell-session

    $ ansible web -m ping

`Ansible` 包含一个由 `内置模块 <http://docs.ansible.com/modules_by_category.html>`_ 组成的巨大工具箱，数量超过 `750` 个。

执行簿
======

执行簿( `playbooks` )可以非常优雅地编排你的基础设施拓扑，
可以通过非常详细的配置控制每次处理的机器数。
执行簿让 `Ansible` 开始变得非常有趣了。

`Ansible` 有意将编排设计得尽量简单，因为自动化代码需要多年维护，语法特性必须简洁好记。

下面是一个执行簿样例。

.. code-block:: yaml

    ---
    - hosts: web
      serial: 5
      roles:
        - common
        - webapp

本文只是介绍性概述，对此不再继续展开。
完整文档可以跳转到 `docs.ansible.com <http://docs.ansible.com/>`_ 查看，那里可以看到执行簿各种可能的用法。

扩展
====

`Ansible` 是一个非常灵活的引擎，你可以通过 **模块** 、 **插件** ，
以及 **API** 等方式为其提供 **功能扩展** ，或者 **对接外部系统** 。

`Ansible` 模块可以使用任何可以返回 `JSON` 格式结果的语言开发，包括： `Ruby` 、 `Python` 、 `Shell` 等等。
设备清单可以对接任何数据源，只需要写一个程序从中捞数据并以约定的 `JSON` 格式返回即可。
`Ansible` 还提供了大量的 `Python API` 用于扩展 **连接类型** ( `SSH` 不是唯一的 )，
**回调函数** ( `callbacks` ，例如控制日志输出格式)，甚至添加新的服务端行为。

下一步
======

.. include:: /_fragments/next-step-to-wechat-mp.rst

.. include:: /_fragments/wechat-reward.rst

.. include:: /_fragments/disqus.rst

.. comments
    comment something out below

