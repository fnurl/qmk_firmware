#!/usr/bin/env zsh
# Script for compiling and flashing firmware (wrapper around make script)
# created since I never remeber the syntax for the make call
#
# author: @fnurl
# created: 2017-09-22
# updates: 2018-04-01

scriptname="$(basename $0)"   # for help messages
num_req_args=3                # number of required positional args

display_usage() {
    echo "Usage: $scriptname [-a|-c] <keyboard> <subproject> <keymap>"
    echo ""
    echo "Positional args:"
    echo "  <keyboard>    keyboard type e.g. planck, lets_split"
    echo "  <subproject>  revision or submodel e.g. ez, infinity, rev1, rev4"
    echo "  <keymap>      keymap name layout to use e.g. fnurlspace"
    echo ""
    echo "Options:"
    echo "  -a            use to flash with avrdude (default is dfu)"
	  echo "  -c            clean build files"
    echo ""
    echo "Examples:"
    echo "  $scriptname planck rev4 fnurlspace"
    echo "  $scriptname -a lets_split rev2 fnurlspace"
}

# Read options using bash buitin getopts)
# http://tuxtweaks.com/2014/05/bash-getopts/
#
# If an option should be followed by an argument, it should be followed by
# a ":". Notice there is no ":" after "h". The leading ":" suppresses error
# messages from getopts. This is required to get my unrecognized option code to
# work.

option=":dfu"  # default options (none)
while getopts :ac arg; do
  case $arg in
    a) # use avrdude 
      option=":avrdude"
      ;;
    c) # clean
      option=":clean"
      ;;
    \?) # show usage
      show_usage
      exit 1
      ;;
  esac
done

# https://unix.stackexchange.com/a/214151/6492
# OPTIND is getopts control variable for keeping track of the current option
# index.
#
# shift n removes n strings from the positional parameters list. Thus shift
# $((OPTIND-1)) removes all the options that have been parsed by getopts from
# the parameters list, and so after that point, $1 will refer to the first
# non-option argument passed to the script.
#
# shift $((OPTIND-1)) can be unsafe. To prevent unwanted word-splitting etc, all
# parameter expansions should be double-quoted, i.e. "$((OPTIND-1))"
shift "$((OPTIND-1))"

# Option parsing done, parse positional args.
# $1 is now the first positional arg
if [[ "$#" -ne $num_req_args ]];then
  echo "ERROR: keyboard, subproject (revision) and layout args needed."
  display_usage
  exit 1
fi

keyboard=$1
subproject=$2
keymap=$3
firmware="${keyboard}_${subproject}_${keymap}.hex"

echo "NOTE TO SELF: To reset keyboard/put in DFU mode, press the q key from the hardware layer."
echo "using fnurlspace layout, the hardware layer is activated by pressing FN and NAV at the same time."
echo ""
echo "Option: ${option}..."
# 2018-02-20, now we can just use
#   make lets_split/rev2:fnurlspace:avrdude
# for automatic flashing of pro micros
make "${keyboard}/${subproject}:${keymap}:${option}" || exit $?

# old version
#echo "Press ENTER to proceed to flash $keyboard keyboard with firmware file '$firmware'"
#read a_line
#
#echo "sudo permission needed to flash keyboard.."
#sudo echo "Ready! Reset the keyboard now. You have 6 seconds until flash."
#for i in $(seq 6 0); do
#  echo -n "${i}... "
#  sleep 1
#done
#echo "GO!"
#sudo dfu-programmer atmega32u4 erase --force || exit $?
#sudo dfu-programmer atmega32u4 flash $firmware || exit $?
#sudo dfu-programmer atmega32u4 start || exit $?
