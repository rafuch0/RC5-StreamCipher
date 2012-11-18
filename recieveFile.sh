#!/bin/bash
nc -v -p 6666 -l | ./a.out d testpass > $1
md5sum "$1"
