To do or think:
* Ambigous redirect or not --------------------------
  - export a="Space between args"

Case 1 :
  - echo something > $a
/* In comands this will be
  ! cmd name >
  input -> [0] Space between args NO_QUOTED
*/
bash -> Ambiguos Redirect

Case 2:
  - echo something > "$a"
/* In comands this will be
  ! cmd name >
  input -> [0] Space between args IN_DOUBLE_Q
*/
bash -> Creates a file `Space between args` and put in `something`
_____________________________________________-

* The rest cases is working, if a speciall case is found, coment in this file
