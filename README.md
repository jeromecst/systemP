# systemP

systemP is the second project of the first year of computer science in Université Paris Sud, 2018-2019. ([info12](https://www.lri.fr/~hivert/COURS/Info121/projet-lapins.pdf))

---
### overview

#### code
* **documented** functions
* **real-time** curved lines
* all **const** can be easily changed
* **mutliple files** for differents versions, functions, consts...
* use of multiple **struc, enum**

#### graphical version
* using **SFML**
* **Multi-thread** to dislpay the curved lines and the grid at the same time
* **random** colors and rotations withing a range for the fox and rabbit each lap 
* multiple windows

#### terimal version :
* the size of the grid is **adaptive** to the size of the terminal
* use of ```"\033[A"```
* **real-time** display of fps, terminal and grid size
* **interactive** display of title, lines and data 

---
### requirements

* SFML and install it in the `home` directory

---
### compilation

* `make t` to compile the **terminal version**, then `./t` to execute
* `make g` to compile the **graphical version**, then `./g` to execute
