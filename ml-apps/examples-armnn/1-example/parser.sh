#!/bin/sh
# Vanessa Maegima <vanessa.maegima@nxp.com>

LOG=/home/root/ArmnnTests/log.txt

ID=$(cat $LOG | grep "prediction" | sed 's/[)(]//g')
ID=$(echo $ID | awk '{print $4}')
[ -z $ID ] && echo error || echo $ID
