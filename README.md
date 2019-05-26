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

## ATS2 version (prototype)
Once we've done with compiling C version, object files generated (unless you run `make clean` to remove all object files) can be used for compiling the version written in ATS2. Right now it's just calling the main routine under ATS2's `main0` function. You can run this command to generate a file named `play_ats.exe`, which is essentially the same as `./play.exe` generated from make utility:

```shell
patscc -cleanaft ./ats2_draft/main.dats ./bin/*.o ./bin/resource/*.o      \
  `pkg-config --cflags --libs                                             \
    allegro-5 allegro_main-5 allegro_image-5 allegro_font-5 allegro_ttf-5 \
    allegro_audio-5 allegro_acodec-5` -o play_ats.exe
```

