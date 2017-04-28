#! /usr/bin/env python
#coding=utf-8

import pty
import os
import select
import time
import struct 
import binascii
def mkpty():
    # 打开伪终端
    master, slave = pty.openpty()
    slaveName = os.ttyname(slave)
    print '\nslave device names: ',slaveName
    return master ,slaveName
def sendfloat(chx,foatdata):
    value=('{',chx,foatdata,1)
    s=struct.Struct('cB<fB')
    sendbuffer=s.pack(*value)
    return sendbuffer
if __name__ == "__main__":
    master,slaveName= mkpty()
    while True:
            data=sendfloat(1,10000.1)
            print slaveName + " ;%d data." % len(data) 
            print 'Format:',binascii.hexlify(data)
            os.write(master, data)
            time.sleep(0.1)


