# Lab Geek Game Engine (LGGE)
Lab Geek Game Engine is the game engine specifically designed for the ease-of-development for the currently on-development indie game Lab Geek. Developed by [\_\_merahm\_\_ (Mertahmetsen)](https://github.com/Mertahmetsen) and [ra1n (ra1n321)](https://github.com/ra1n321), **LGGE's primary principle is to provide readable code while sacrificing complex features as little as possible.** LGGE is written in pure C and built from reliable and efficient libraries [Raylib](https://github.com/raysan5/raylib) and [RayGUI](https://github.com/raysan5/raygui). LGGE also embraces the core idea behind the Raylib library, to quote directly from the [Raylib GitHub Repository](https://github.com/raysan5/raylib):
>_"...a programming library to enjoy videogames programming; no fancy interface, no visual helpers, no debug button... just coding in the most pure spartan-programmers way."_
## Before you read!
I am not a professional C programmer by any means. There are many unorthodox (and sometimes risky) design choices made in this library. Also, LGGE is not made for general-purpose game development, but is designed specifically for the development of the game "Lab Geek".
## Before you compile!
- You can download the source code and compile it as a static or shared library. You can either pull the repository and use the `Makefile` inside the `dev` folder to automatically compile the library and the entry point file, or compile the engine code manually yourself in your own desired way.
- LGGE is a library developed on Linux. It does not intentionally use any platform-specific APIs. However, cross-platform compilation has still not been tested yet. 
### Dependencies
- Raylib must be installed locally as **shared libraries**. [RayGUI already kind of recommends you to install itself as a **shared library**](https://github.com/raysan5/raygui#building), but you also need to install Raylib as a **shared library** as well. If you install these libraries as static libraries, or if you do not even install them at all, LGGE will most likely either fail to compile, or become unstable. *Check FAQ if you're feeling like it.*
## Standard Code Structure
A standard code written using LGGE consists of two main parts:
1. The Runner file that includes the `main()` function.
2. The Scene file that handles most of the game loop.
### The Runner File
The Runner File acts as a host executable. Its responsibilities include:
- Initializing OS-level runtime state, window contexts, and Raylib defaults.
- Handling global memory before code execution.
- Handles fallback features.
### The Scene file
A Scene file defines scene-specific behaviour without managing the host environment. It does this via the implementation of three main functions:

| Function | Execution Point | Primary Purpose |
| :--- | :--- | :--- |
| `onLoad()` | Runs once before the main game loop | Loads resources, sets up local variables, etc.
| `onUpdate()` | Runs every frame | Rendering, I/O, game state updating.
| `onFinish()` | Runs once after the main game loop | Unloading resources, handling local memory cleanup.
## Basic Code Example
As mentioned earlier in the previous section, the code will consist of two main parts:
1. The "Entry Point/Runner" file that has the **main()** function.
2. The "Scene" file that will mostly handle the game loop.

Let's code a  very simple program written with LGGE that does nothing but clear the background with the color red, and then compile this program using the Makefile LGGE provides. Now, because LGGE is in early stages of development, some of the stuff inside the code might change, but the general structure will most likely stay the same. We will assume that the compiled binary will be in "dev/src", the scene file will be in "../../resources/scenes/" and the headers will be inside "dev/src" as well.
### The Runner File
We will name our file `main.c` for it to be obvious that it holds the `main()` function. After we see the full file, I will explain every line as clear as possible. Here it is:

```c
#define RAYGUI_IMPLEMENTATION
#include "independent/include-all.h"
const Scene* currentScene = &SCENE_MYSCENE;
int main (int argc, char** argv) {
    ChangeDirectory(GetApplicationDirectory());
	initLogHandler(COMPLETE);
    preWinInitGlobals();
    InitWindow(g_windowW, g_windowH, g_windowTitle);
    defaultGlobals();
    currentScene->onLoad();
    while (!WindowShouldClose()) {
	    currentScene->onUpdate();
	}
	currentScene->onFinish();
    CloseWindow();
	return 0;
}
```
**Now, let's check out what the code does line by line:**
```c
#define RAYGUI_IMPLEMENTATION
```
RayGUI is a single-file header-only library. What this means is, both the function definitions AND implementations are inside the same file. We add this line at the start of the file to avoid duplicate errors during compilation.
```c
#include "independent/include-all.h"
```
One of the LGGE's headers is the `include-all` header inside the `independent` folder. This line includes all of the library for us to use, even though our code does not use every feature of LGGE.
```c
const Scene* currentScene = &SCENE_MYSCENE;
```
We pick `SCENE_MYSCENE` as our scene. One scene file can technically have multiple scenes *if you really feel like opening a can of worms*.
```c
int main (int argc, char** argv)
```
We declare our entry point! *(You DO know C, **right?**)*    
```c
ChangeDirectory(GetApplicationDirectory());
```
This one is not mandatory, you can set the working directory wherever you want, but setting it as the output of `GetApplicationDirectory()` is good practice.
```c
initLogHandler(COMPLETE);
```
LGGE uses its own log handling rather than using the `TraceLog()` function Raylib offers. The `COMPLETE` parameter tells the initializer that every single log message will be printed on the console, no matter the "log level".
```c
preWinInitGlobals();
```
As stated in the previous section, one of the runner file's duties is to initialize standard values to global variables. The `preWinInitGlobals()` function handles the extremely basic global variables that need to be initialized before Raylib initializes the game window.
```c
InitWindow(g_windowW, g_windowH, g_windowTitle);
```
This is a function that Raylib provides. It initializes the game window using the standard values for the window width, height, and title.
```c
defaultGlobals();
```
The `defaultGlobals()` function initializes almost all of the global variables.
```c
currentScene->onLoad();
```
This function's implementation is given by the desired scene. The scene provides the runner what to do before the game loop begins.
```c
while (!WindowShouldClose())
``` 
We enter the main game loop.
```c
currentScene->onUpdate();
```
This function's implementation is given by the desired scene. The scene provides the runner what to do during the game loop.
```c
currentScene->onFinish();
```
This provides the runner what to do after the game loop ends.
```c
CloseWindow();
```
We use the Raylib library's `CloseWindow()` function to deinitialize the window.
### The Scene File
Now, we are going to check out the scene file's code:
```c
#ifndef HEADERGUARD
#define HEADERGUARD
#include "../../dev/src/independent/include-all.h"
static void myscene_onLoad (void) {}
static void myscene_onFinish (void) {}
static void myscene_onUpdate (void) {
    BeginDrawing();
    ClearBackground(RED);
    EndDrawing();
}
static const Scene SCENE_MYSCENE = {
    .name = "My scene",
    .onLoad = myscene_onLoad,
    .onFinish = myscene_onFinish,
    .onUpdate = myscene_onUpdate
};
#endif
```
**Let's check what the code does:**
```c
#ifndef  HEADERGUARD
#define  HEADERGUARD
```
We define our include guards so that the scene does not get included more than once. This may not be necessary here, but it is good practice to use include guards.
```c
#include  "../../dev/src/independent/include-all.h"
```
This includes all of the LGGE library.
```c
static void myscene_onUpdate (void) {
    BeginDrawing();
    ClearBackground(RED);
    EndDrawing();
}
```
All we want our scene to do, is to clear the background with the color red. We begin drawing with `BeginDrawing()`, Clear the background red with `ClearBackground(RED)` and end drawing with `EndDrawing()`.
### Compilation
Now is time to compile our code! We will use the `Makefile` that is provided by LGGE:
#### Compile as Shared Library
```bash
foo@bar:~$ make
```
Compiles LGGE as a shared library and compiles the entry point file.
#### Compile as Static Library
```bash
foo@bar:~$ make BUILD_TYPE=static
```
Does the same thing as the other one but it compiles as a static library.
## FAQ
These are the questions that were asked to me by many people, or will most likely be asked by many people.

> Why use C?

Because at the time of starting to write the library, the language I know the best was C. Since I have decided that I will use Raylib at the time, and since Raylib only supports C and C++, the only realistic alternative I had to C was C++. But as any C++ dev will tell you, **C++ is not C with some "extra stuff"**. These languages embrace different design principles. And I not only have very limited knowledge of C++, I also simply do not like C++'s syntax. I feel like it verbosifies stuff more than it should, at least for writing a library that focuses on code readibility. And while C is an old language and is slowly starting to become overshadowed by alternatives like Rust, it is still a semi-popular language with good enough community support.
> Why do I have to have RayGUI installed as a shared library?

I'll be 100% honest here, ***you most likely do not***. It's just that ***I*** have it installed as a shared library on the computer I use to develop LGGE, and I don't want to hit the brick wall of *"but it worked on my PC!"*. If you don't want to install RayGUI as a shared library and use it as a header-only library ~~*(for WHATEVER reason, compiling it takes like 5 minutes at worst case scenario)*~~, just don't. I just can't guarantee that stuff won't break when you do it that way.
> Why write your own game engine while you can use an already existing one?

Writing my own game engine has been a goal that I had for a very long time. Even though I had tried using other engines like Unity, they felt overwhelming to use. Also, I like the part of programming where you sit behind two monitors, one has the code editor while the other one has the terminal open. I like the bare-bones kind of programming.
> Do you use AI in the engine's development?

I would never copy-paste AI code and tell people it's my own. You can be sure that the engine's code is written completely by me. I only use AI to learn more about the capabilities of the C language itself, and in intense debugging sessions that sometimes take hours. Why do I not ask programming forums for help rather than AI? Because *I have a life*, and I can't just wait for a notification on my phone for 3 days just to be hit with "random-nitwit-342" answering my post with *"that is the most DISGUSTING code I have EVER seen! GIVE UP!"*.
## Development History / Former Significant Design Changes
- Before [Pre-Alpha 2 (v0.1.1)](https://github.com/Mertahmetsen/labgeekgameengine/releases/tag/v0.1.1-alpha.2), LGGE used a code structure that heavily relied on "maps", which were code blocks that handled many different features and were recompiled at runtime. However, from [Pre-Alpha 2 (v0.1.1)](https://github.com/Mertahmetsen/labgeekgameengine/releases/tag/v0.1.1-alpha.2) and onwards, this design has been abandoned and replaced with a much better *(and cross-platform)* alternative called "scenes". *(This is because the design of maps relied heavily on some linux backend libraries, and the terminology was also causing issues.)*
- LGGE stopped using platform-specific APIs in [Pre-Alpha 2 (v0.1.1)](https://github.com/Mertahmetsen/labgeekgameengine/releases/tag/v0.1.1-alpha.2).
- LGGE switched away from a header-only library design in [Pre-Alpha 3 (v0.2.0)](https://github.com/Mertahmetsen/labgeekgameengine/releases/tag/v0.2.0-alpha.3).
- LGGE started providing a built-in Makefile in [Pre-Alpha 3 (v0.2.0)](https://github.com/Mertahmetsen/labgeekgameengine/releases/tag/v0.2.0-alpha.3).
## Special Thanks

 - [Special thanks to everyone who contributed to the Raylib project](https://github.com/raysan5/raylib/graphs/contributors).
 - [Special thanks to everyone who contributed to the RayGUI project](https://github.com/raysan5/raygui/graphs/contributors)
 - Special thanks to [ra1n](https://github.com/ra1n321) for providing help with engine design, emotional support, and so much more.
 - Special thanks to my father, mother, and everybody else who keeps supporting me on the development.
 ## Contacts
 ### \_\_merahm\_\_
 - Mail Account: mertahmetsen@gmail.com
 - [GitHub Account](https://github.com/Mertahmetsen)
 - [Reddit Account](https://www.reddit.com/user/WebHaunting5143/)
### ra1n
- [GitHub Account](https://github.com/ra1n321)
### Other
- Lab Geek Project's Official Mail Account: labgeekproject@gmail.com
