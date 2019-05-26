#!/usr/bin/bash

xrdb ~/.Xresources

# Start notification server
dunst &
nm-applet &
volumeicon &
stalonetray &
pulseaudio --start

# Wall
#feh --bg-scale /home/puffy/Pictures/walls/ECLJake.jpg &

compton -b &
$HOME/.scripts/clock &
batti &
xsetroot -solid gray40
#xclock -geometry -0+0 -d -strftime '%H:%M %b %d %Y' -update 1 &
exec ck-launch-session dbus-launch cwm
