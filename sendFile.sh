#!/bin/bash
cat "$1" | ./a.out e testpass | nc -v -w 2 hostname.example.com 6666

