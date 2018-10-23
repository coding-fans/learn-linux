#!/usr/bin/env python
# -*- encoding=utf8 -*-

'''
FileName:   cpu_usage.py
Author:     Fasion Chan
@contact:   fasionchan@gmail.com
@version:   $Id$

Description:

Changelog:

'''

import time

from tabulate import (
    tabulate,
)

# sample interval
INTERVAL = 1

# table header
TABLE_HEADER = (
    'device',
    'used',
    'user',
    'nice',
    'system',
    'idle',
    'iowait',
    'irq',
    'softirq',
    'steal',
    'guest',
    'guset_nice',
)


def cpu_counters():
    records = []

    # open /proc/stat to read
    with open('/proc/stat') as f:
        # iterate all lines
        for line in f.readlines():
            if not line.startswith('cpu'):
                continue

            # split to fields
            fields = line.strip().split()

            # cpu name
            name = fields[0]
            # convert all counters to int
            counters = tuple(map(int, fields[1:]))
            # calculate total cpu time
            total = sum(counters[:8])

            records.append((name, counters, total))

    return records


def sample_forever():
    last_records = None

    while True:
        # sample cpu counters
        records = cpu_counters()

        if last_records:
            table_data = []
            # iterate counters for every cpu core
            for (device, last_counters, last_total), (_, counters, total) in \
                    zip(last_records, records):

                # calculate cpu usage
                delta = total - last_total
                percents = list(map(
                    lambda pair: 100. * (pair[0]-pair[1]) / delta,
                    zip(counters, last_counters),
                ))
                used_percent = sum(percents[:3] + percents[5:8])

                table_data.append([device, used_percent] + percents)

            # make table
            table_data = tabulate(
                table_data,
                TABLE_HEADER,
                tablefmt='simple',
                floatfmt='6.2f',
            )

            # print table
            print(table_data)
            print()

        last_records = records

        time.sleep(INTERVAL)


def main():
    try:
        sample_forever()
    except KeyboardInterrupt:
        pass

if __name__ == '__main__':
    main()
