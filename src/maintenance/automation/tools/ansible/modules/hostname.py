#!/usr/bin/python
# -*- encoding=utf8 -*-

'''
FileName:   hostname.py
Author:     Fasion Chan
@contact:   fasionchan@gmail.com
@version:   $Id$

Description:

Changelog:

'''

import platform

from ansible.module_utils.basic import (
    AnsibleModule,
)

MODULE_ARGS = {}


def run_module():
    module = AnsibleModule(
        argument_spec=MODULE_ARGS,
    )

    result = {
        'changed': False,
        'original_message': '',
        'message': '',
        'hostname': platform.node(),
    }

    module.exit_json(**result)

def main():
    run_module()

if __name__ == '__main__':
    main()
