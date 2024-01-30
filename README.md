# Moj Broj Clone

Linux cli clone of **Moj Broj** from [Slagalica](https://www.youtube.com/user/SlagalicaRTS/videos)

Demonstration

![Demo](https://media.giphy.com/media/v1.Y2lkPTc5MGI3NjExejJ6Z3N0eWM2b25kYWVuYnVuZW1rczJkNnYycWtwMjJzc3hvd3ZkbyZlcD12MV9pbnRlcm5hbF9naWZfYnlfaWQmY3Q9Zw/2accXUKL5N3TuCO5ZH/giphy.gif)

## Rules of the game
- Press any key 3 times to get the 3 digit number you'll be looking for
<<<<<<< HEAD
- Press any key 4 times to get the available single digit ( != 0) numbers 
=======
- Press any key 4 times to get the 4 available single digit ( != 0 ) numbers 
>>>>>>> c22ec73 (Azuriran readme, dodate build instrukcije)
- Press any key once to get the available number ∈ {10, 15, 20}
- Press any key once to ge the available number ∈ {25, 50, 75, 100}
- After this, **90 seconds** start ticking
- Try to write a mathematical expression using the available numbers 
which equals to the number you're searching for
- Expressions can only contain +, -, *, /, and ()
- In case of division, numbers must be divisible
- Points
    - Correct: **10**
    - +- 5: **5**
    - +- 10: **2**

## Building
Requirements: 
- [CMake](https://cmake.org/download/)

Steps:
1. Clone the repository 
```bash
git clone github.com/MihajloVelickovic/MojBroj.git
cd MojBroj
```
2. Generate buildfiles 
```bash
cmake . -B ./build [-DCMAKE_BUILD_TYPE=Release]
```
3. Build
```bash
cmake --build build
```
4. Run
```bash
cd build
./mojbroj
```