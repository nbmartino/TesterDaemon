#!/bin/ksh


#kill process if running

#get PID

PID="$(cat /var/run/testerd.pid)"

kill -9 $PID

rm /var/run/testerd.pid

exec ./testerd

nc -c localhost 30153

