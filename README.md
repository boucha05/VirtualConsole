# VirtualConsole

An experiment in virtual console design.

## Disclaimer

This project is still in early development. This is a pet project I am working on it in my free time while I am also working on other projects.

I don't consider this project is close to completion or ready to be used. You migth be interested in following it or just take a look at it later.

## Introduction

Inspiration for this project started after discovering PICO-8, a project that describes itself as a *fantasy console*. PICO-8 is basically a fake console for non existing hardware. It has very nice features like it's image based cartridge, it's free to play web server and it's very simple API. By design, it also comes with its own limitations that are intended to be fun to work with as describes on the PICO-8 website. I highly recommend that you take a look at this cool console on: http://www.lexaloffle.com/pico-8.php.

I wanted to start from the simplicity of PICO-8 because I really like it but at the same time, I didn't want to constrain game development to the limitations of PICO-8, no matter how cool they look. If you want to design a game with a bigger memory budget, a different screen resolution, more colors, bigger sprites, you should be able to do so. On the other side, if you want to come up with your own limitations to reproduce the look and feel of a specific system, this projects will allow you to do so in an easy way. It will even make it easy to share and reuse constraints for other similar projects.

## Features

As I am still very early in the development of this project, the list of features is currently very limited but here is what can be done so far:

* Games are written using Lua.
* Configurable screen resolution and window size.
* Very basic primitive rendering (sprites, rectangles, clipping rectangles, color tables).

Here is what I plan to add soon:

* Basic inputs support.
* More rendering primitives (tile maps, lines, palettes).
* Tools for importing and exporting ROM data.
* Examples of constrained environments.
* Transform the application in a specialized Lua interpreter that allow any Lua game script to be passed as a command line argument.

In the long term, I would also like to add the following:

* Savegame support.
* Sound support.
* Multiplayer support.
* Means of sharing and distributing games.

## Contribution

For now, this project is really a way for me to experiment with console development. I want to get my own hands dirty and come up with a nice feature set.

I am currently not looking for contribution but I am open to feedback. Later, when this project is a little more mature, I will probably make it open to contributions from other developers.

## Credits

* If it was not for PICO-8. This project would not exists. Great thanks to Joseph White for the inspiration. Try PICO-8, it's really cool: http://www.lexaloffle.com/pico-8.php
* All these videogame companies who made games look so cool in the '80s and the '90s.
