#!/bin/sh

userresources=$HOME/.Xresources
usermodmap=$HOME/.Xmodmap
sysresources=/etc/X11/xinit/.Xresources
sysmodmap=/etc/X11/xinit/.Xmodmap

# merge in defaults and keymaps

if [ -f $sysresources ]; then







    xrdb -merge $sysresources

fi

if [ -f $sysmodmap ]; then
    xmodmap $sysmodmap
fi

if [ -f "$userresources" ]; then







    xrdb -merge "$userresources"

fi

if [ -f "$usermodmap" ]; then
    xmodmap "$usermodmap"
fi

# start some nice programs

if [ -d /etc/X11/xinit/xinitrc.d ] ; then
 for f in /etc/X11/xinit/xinitrc.d/?*.sh ; do
  [ -x "$f" ] && . "$f"
 done
 unset f
fi

# Wall
feh --bg-scale ~/Pictures/walls/sunsetbeach.jpg &

# Autostart apps
chromium &
mpd &
stalonetray &
volumeicon &
batterymon &

# Start notification server
dunst &

# Cursor
xsetroot -cursor_name left_ptr &

# Candy
compton --config $HOME/.compton.conf --sw-opti &

$HOME/.scripts/clock &
exec cwm
