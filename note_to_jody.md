# HEJ

- 2020-09-16: Lagt till fnurlspace_swedish som är fnurlspace som kan
  användas med en vanlig svensk tangentbordslayout i operativsystemet (fast
  bara om operativsystemet är macOS eftersom specialtecken ligger
  annorlunda jmf med PC, t.ex. \ och <>)


## Senaste kompilerings- och flashinstruktionerna

Bygg med

```
$ make planck/rev4:fnurlspace_swedish
```

Flasha med appen `QMK Toolbox` (som du installerat i /Applications):

1. Välj tangentbord, välj firmware (lät MCU vara kvar på default;
   `atmeta32u4`)
2. Håll ner `Nav` + `Fn` för att aktivera `Planck`-lagret och tryck sedan
   på `q` för att sätta tangentbordet i DFU-läge.
3. Klicka på "Flash". Klart!

