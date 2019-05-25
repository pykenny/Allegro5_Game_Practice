# Allegro5_Game_Practice
Practice C and how to write a simple game in C + Allegro5.

## Ideas
This project is still under early development, so please refer to this [HackMD note](https://hackmd.io/nwfPX-jZT5O-KJozp2durQ) for current thoughts and ideas. Once the draft is complete enough, I'll migrate it to this repo.

## How to run?
Check [*Allegro5*'s wiki](https://github.com/liballeg/allegro_wiki/wiki/Quickstart) for how to install *Allegro5* library on your system.

Running `make` (you'll need `MinGW` on Windows system) under repo's root directory should compile it and generate a file named `play.exe`. Then run this command to start the program:

```shell
./play.exe
```

## Control
Right now we have a space-evader-like game that allows you to move you ship and fire enemies moving on the screen. However for now there's no scoring system, you're invincible (while the enemies aren't. Although they respawn again when there's no any their "friendly force" on screen). Moreover, the game never end unless you shut off the screen.

  - Left/Right arrow key: Move the ship to left/right.
  - Space: Fire.
  - Click the exit button on screen to quit the game.

