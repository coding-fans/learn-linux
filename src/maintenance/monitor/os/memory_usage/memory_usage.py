#!/usr/bin/env python
# -*- encoding=utf8 -*-

'''
FileName:   memory_usage.py
Author:     Fasion Chan
@contact:   fasionchan@gmail.com
@version:   $Id$

Description:

Changelog:

'''

import json

UNIT_MAPPING = {
    'kB': 1024,
    'KB': 1024,
}


def parse_value(value):
    # default, no unit
    unit = ''

    # split value string
    parts = value.strip().split()
    if len(parts) == 2:
        number, unit = parts
    else:
        number, = parts

    return int(number.strip()) * UNIT_MAPPING.get(unit.strip(), -1)


def sample_memory_usage():
    # open data file
    with open('/proc/meminfo') as f:
        # open all lines
        lines = f.readlines()

        # split every line to a pair by :
        pairs = [
            line.strip().split(':', 1)
            for line in lines
        ]

        # data dict
        datas = {
            name.strip(): parse_value(value)
            for name, value in pairs
        }

        # calculate
        total = datas['MemTotal']
        free = datas['MemFree']
        buffers = datas['Buffers']
        cached = datas['Cached']
        slab = datas['Slab']
        cache = cached + slab
        g_free = free + buffers + cache
        used = total - g_free
        active = datas['Active']
        inactive = datas['Inactive']
        available = datas['MemAvailable']

        return {
            'total': total,
            'free': free,
            'buffers': buffers,
            'cached': cached,
            'slab': slab,
            'cache': cache,
            'g_free': g_free,
            'used': used,
            'active': active,
            'inactive': inactive,
            'available': available,
        }

if __name__ == '__main__':
    usage = sample_memory_usage()
    print(json.dumps(usage, indent=4))
