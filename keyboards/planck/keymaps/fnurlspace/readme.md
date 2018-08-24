# fnurlspace layout for The Planck and other 40% ortholinear keyboards

Partially updated for fnurlspace v1.2, 2018-08-23

The fnurlspace layout was designed with the following goals:

- remove the need for a number row (i.e. only require fingers to move one
  row up or down from the home row)
- reduce the need to use keys that require streching the pinky-fingers
- facilitate both writing code as well as writing natural language

To accomplish these goals, the fnurlspace layout uses the following:

- Dual role split space bar for ergonomic access to two additional
  layers (`PLEFT` and `PRIGHT`)
- Logical and symmetric placement of parenthesis characters on the home row
- Common symbols (`!@#^+*$=&%`) on the home row (with a slight reordering
  to make the layout more usage oriented, with a small bias to towards vim
  usage)
- One handed arrow cluster
- Numbers and F-keys on top row (QWERTY-row)
- Left-Right layer accessed by pressing and holding the left then the right
  space key.
- Right-Left layer accessed by pressing and holding the right then the left
  space key.


## Base layer

![The fnurlspace layout, ANSI SE and ANSI US variations](./fnurlspace-ansi_se-us.png)

The base layer features a dual role `ESC/CTRL` key which works like the
`Escape` key when tapped, but like the `Ctrl` key when held. I actually use
my ring finger to press it rather then using my pinkey.

In the lower left and right corners are two `HYPER` keys, i.e.
`Cmd-Ctrl-Opt-Shift` and I use it to trigger my [Keyboard
Maestro](https://www.keyboardmaestro.com/main/) macros which are mostly for
when I am not working in the terminal. The placement however usually
requires me to lift my hand.

If you are wondering where the `Enter` and `Backspace` keys are, they are
actually on the split space bar. Holding the `Left Space` activates the
`PLEFT` layer which has the `Enter` key on the `Right Space` key. This
means that to press enter, I press and hold `Left Space`, then tap `Right
Space`. The `Backspace` key is found by doing the opposite; press and hold
`Right Space`, then tap `Left Space`. I have found this quite intuitive, as
the `Enter` key sequence is a forward moving left to right movement whereas
the `Backspace` key sequence is a backward moving right to left movement.

A standard US version can be toggled from the `NAV` layer.


## PLEFT and PRIGHT layers

![PLEFT and PRIGHT layers](./fnurlspace-leftright.png)

The `PLEFT` and `PRIGHT` layers contain parenthesis, symbols and numbers.
The parenthesis are symmetrically laid out on the home row and the logic
is that you use your left thumb with your left-hand fingers on the home row
to get the various left-parenthesis and the right thumb together with your
right-hand fingers on the home row to get the various right-parenthesis.

Using the left thumb with the right-hand fingers produces the symbols
usually accessed by using `Shift` and the number row keys. Here however,
the `^` character has been placed under the left index finger as it moves
the cursor to the beginning (i.e. moves the cursor to the left) of the
current line from `NORMAL` mode in Vim. For the same reason, the `$`
character has been moved under the right index finger as it moves the
cursor to the end of the line (i.e. moves the cursor to the right) from
`NORMAL` mode in Vim.

Numbers, dashes, punctuation and vertical lines are placed on the bottom
row and have the same position for both the `PLEFT` and `PRIGHT` layers.
Numbers are placed on the top row, and unfortunately, `0` is not placed on
the `O` key, but rather on the `P` key. However, `3` is placed on the `E`
key which is nice.

The topleft side is used for `Backquote` and `Tilde` which also have the
same position for both `PLEFT` and `PRIGHT` layers. Finally, the top right
keys are used for zooming in and out as they produce `Cmd-=` and `Cmd--`.


## NAV and CNAV layers

![NAV layer](./fnurlspace-nav-cnav.png)

The `NAV` layer simply provides an arrow cluster, media keys, modifier+arrow
keys + `PgUp` and `PgDn` and the idea is that you just have to move your thumb
to the right one step and use the already positioned fingers to use the arrow
cluster. This layer also contains the `Game Mode` and `ANSI-US` toggle keys.

The `Previous Tab` and `Next Tab` keys are actually `CMD+OPT+Left Arrow` and
`CMD+OPT+Right Arrow` which I have bound to previous/next tab using the general
system preferences in macOS.

`Zoom in` and `Zoom out` are the standard bindings to `CMD+=` and `CMD+-`.


The *CNAV layer* contains modifier + arrow key bindings using `CTRL` instead of
`CMD`.

## FN layer

![FN layer](./fnurlspace-fn.png)

The `FN` layer contains F-keys `F1` through `F12` placed on the same keys
as the numbers `1`-`0` followed by `F12` just below `F11`. 


## Game Mode and NUM layers

![GAME and NUM layers](./fnurlspace-gamenum.png)

The `Game Mode` layer is toggled on from the `FN` layer and the Planck
makes a sound when it toggles on, and another when it toggles off (the
Plover sounds).

The `Game Mode` layer has a `Space` key in the lower left corner since I am
left handed. With my left hand on the mouse, I use my right hand for `WASD`
and need the space key there to be able to press it with my right
thumb.

The `NUM` layer simply contains the number keys for easy access with my
right hand.

I also removed the dual role `CTRL`/`ESC` becase the `CTRL` key sometimes
needs to be tapped in games. The `ESC` key is accessed on the same key but
with the `NUM` layer activated.


## Hardware specific layers

![Planck and general hardware layer](./fnurlspace-planck-adjust.png)

Triggered by pressing NAV

# Some background

I have been working and using this layout on various keyboards since around 2016
and it has proven to be great, at least for me. Initially the reason for
creating it was to add Swedish characters (`åäö`) to the default US ANSI layout.

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


