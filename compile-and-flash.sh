#!/usr/bin/env zsh

# author: @fnurl, 2017-09-22


display_usage() {
    scriptname="$(basename $0)"
    echo "Usage: $scriptname <keyboard> <subproject> <keymap>"
    echo "<keyboard>      keyboard type e.g. planck, letssplit"
    echo "<subproject>    revision or submodel e.g. ez, infinity, rev1, rev4"
    echo "<keymap>        keymap name layout to use"
    echo ""
    echo "Example: $scriptname planck rev4 fnurlspace"
}

# number of args required
num_req_args=3

# run with single argument (help or reset)
if [[ "$#" -ne $num_req_args ]]; then
    display_usage
    exit 0
fi

keyboard=$1
subproject=$2
keymap=$3
firmware="${keyboard}_${subproject}_${keymap}.hex"

echo "Cleaning..."
make SILENT=true "${keyboard}-${subproject}-${keymap}-clean" || exit $?

echo "Compiling..."
make SILENT=true "${keyboard}-${subproject}-${keymap}-all" || exit $?

echo "Press ENTER to proceed to flash $keyboard keyboard with firmware file '$firmware'"
read a_line

echo "sudo permission needed to flash keyboard.."
sudo echo "Ready! Reset the keyboard now. You have 6 seconds until flash."
#echo -n "10... ";sleep 1
#echo -n "9... ";sleep 1
#echo -n "8... ";sleep 1
#echo -n "7... ";sleep 1
echo -n "6... ";sleep 1
echo -n "5... ";sleep 1
echo -n "4... ";sleep 1
echo -n "3... ";sleep 1
echo -n "2... ";sleep 1
echo -n "1... ";sleep 1
echo -n "0... ";sleep 1
echo "GO!"

sudo dfu-programmer atmega32u4 erase --force || exit $?
sudo dfu-programmer atmega32u4 flash $firmware || exit $?
sudo dfu-programmer atmega32u4 start || exit $?

