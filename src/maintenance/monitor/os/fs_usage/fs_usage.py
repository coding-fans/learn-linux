#!/usr/bin/env python
# -*- encoding=utf8 -*-

'''
FileName:   fs_usage.py
Author:     Fasion Chan
@contact:   fasionchan@gmail.com
@version:   $Id$

Description:

Changelog:

'''

import os

from tabulate import (
    tabulate,
)

TABLE_HEADER = (
    'mount_point',

    'total_bytes',
    'used_bytes',
    'used_bytes_percent',

    'total_files',
    'used_files',
    'used_files_percent',
)

def get_mount_points():
    with open('/proc/mounts') as f:
        return [
            line.strip().split()
            for line in f
        ]


def get_fs_usage():
    devices = set()
    table_data = []
    for device, mount_point, _, _, _, _ in get_mount_points():
        # skip non-device
        if not device.startswith('/dev'):
            continue

        if device in devices:
            continue

        devices.add(device)

        # call statvfs to fetch file system statistics
        statvfs = os.statvfs(mount_point)

        f_frsize = statvfs.f_frsize

        # calculate space
        total_bytes = statvfs.f_blocks * f_frsize
        free_bytes = statvfs.f_bfree * f_frsize
        available_bytes = statvfs.f_bavail * f_frsize

        used_bytes = total_bytes - free_bytes
        used_bytes_percent = 100. * used_bytes / (used_bytes + available_bytes)

        # calculate files
        total_files = statvfs.f_files
        free_files = statvfs.f_ffree
        available_files = statvfs.f_favail

        used_files = total_files - free_files
        used_files_percent = 100. * used_files / (used_files + available_files)

        table_data.append((
            mount_point,
            total_bytes,
            used_bytes,
            used_bytes_percent,
            total_files,
            used_files,
            used_files_percent,
        ))

    print(tabulate(table_data, TABLE_HEADER, floatfmt='6.2f'))
    print()

if __name__ == '__main__':
    get_fs_usage()
