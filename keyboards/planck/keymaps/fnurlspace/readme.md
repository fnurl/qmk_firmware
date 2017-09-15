# fnurlspace layout for The Planck 

The fnurlspace layout was designed with the following goals:

- remove the need for a number row (i.e. only require fingers to move one
  row up or down from the home row)
- reduce the need to use keys that require streching the pinky-fingers
- facilitate both writing code as well as writing natural language

To accomplish these goals, the fnurlspace layout uses the following:

- dual role split space bar(s) for ergonomic access to two additional
  layers
- logical and symmetric placement of parenthesis characters on the home row
- common symbols (`!@#^+*$=&%`) on the home row (with a slight reordering
  to make the layout more useage oriented, with a small bias to towards vim
  usage)
- one handed ergonomic arrow cluster
- numbers and F-keys on top row (QWERTY-row)


## The layout

![The fnurlspace layout](fnurlspace-layout.png)


## Background

I have been working and using this layout on various keyboards for more
than a year now and it has proven to be great, at least for me. Initially
the reason for creating it was to add Swedish characters (`åäö`) to the
default US ANSI layout.

Using a standard Swedish layout (the same problem exists with other layouts
as well) comes with the problem that the keycodes for certain characters
used for keyboard shortcuts use modifiers which make them impossible to
enter. For example, the keyboard shortcut `Cmd+]` requires the user to
press `Cmd` and `]` simultaneously. However, to get the `]` character, the
Swedish layout requires its user to press `Opt-9` which makes `Cmd-9` in
practice the same combination as `Cmd-Opt-9`.

My solution was to add the characters `åäö` to the standard US-ANSI layout
without removing the keys they would normally replace (i.e. `[';`). I did
this by creating a modified US-ANSI character layout where the characters
`åäö` were placed on the top row of the numeric keypad (which I didn't use
anyway since I exclusively use Tenkey-less keyboards). I then had the
keyboard output the keycodes for number pad 9, 8 and 7 when pressing the
keys `[`, `'` and `;`.

The next problem was to find a way to output the keycodes for `[';`.

To be continued...


