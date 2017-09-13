#! /bin/sh

TEAM_NUM=( "$@" )
i=0

./viewer &

while [ "$i" -lt "${#TEAM_NUM[@]}" ]
do
    ./lemipc -n ${TEAM_NUM[$i]} -i ./lib_chef_player.so -t 100000 &
    ./lemipc -n ${TEAM_NUM[$i]} -i ./lib_soldier_player.so -t 100000 &
    ./lemipc -n ${TEAM_NUM[$i]} -i ./lib_soldier_player.so -t 100000 &
    ./lemipc -n ${TEAM_NUM[$i]} -i ./lib_soldier_player.so -t 100000 &
    ./lemipc -n ${TEAM_NUM[$i]} -i ./lib_scout_player.so -t 100000 &
    ./lemipc -n ${TEAM_NUM[$i]} -i ./lib_jammer_player.so -t 100000 &
    i=$((i+1))
done