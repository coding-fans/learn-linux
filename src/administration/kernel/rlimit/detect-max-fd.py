#!/usr/bin/env python
# -*- encoding=utf8 -*-

'''
FileName:   detect-max-fd.py
Author:     Fasion Chan
@contact:   fasionchan@gmail.com
@version:   $Id$

Description:

Changelog:

'''

from socket import (
    socket,
    AF_INET,
    SOCK_STREAM,
)

def main():
    sockets = []

    while True:
        try:
            s = socket(AF_INET, SOCK_STREAM)
            sockets.append(s)
        except OSError as exc:
            print('error no: %s' % (exc.errno,))
            print('error string: %s' % (exc.strerror,))

            print('fd range: [%d, %d]' % (
                sockets[0].fileno(),
                sockets[-1].fileno(),
            ))

            break

if __name__ == '__main__':
    main()
