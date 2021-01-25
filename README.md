# Space Invaders

Space Invaders written in C with SDL2 library.

## Installation on linux

```bash
sudo apt install build-essential
```

```bash
sudo apt install libsdl2-dev libsdl2-2.0-0 -y;
```

```bash
sudo apt install libjpeg-dev libwebp-dev libtiff5-dev libsdl2-image-dev libsdl2-image-2.0-0 -y;
```

```bash
sudo apt install libmikmod-dev libfishsound1-dev libsmpeg-dev liboggz2-dev libflac-dev libfluidsynth-dev libsdl2-mixer-dev libsdl2-mixer-2.0-0 -y;
```

```bash
sudo apt install libfreetype6-dev libsdl2-ttf-dev libsdl2-ttf-2.0-0 -y;
```

```bash
sudo apt install make
```


## Usage

Go to the code folder. Open the terminal

```bash 
make
```
```
./space_invaders
```

or

```bash 
bash build.sh
```


## Game controls
### Player
- The player is controlled with the W, S, A, D or arrow keys up, down, right and left
- Shoot the bullet with the SPACE key


The game contains two game modes
- Normal mode 
- Hard mode 

#### Normal mode 
- Player have 3 lives
- Enemy have 2 lives 


#### Hard mode 
- Player have 1 live
- Enemy have 3 lives
