# Lab Geek Game Engine (LGGE)
Lab Geek Game Engine is the game engine specifically designed for the ease-of-development for the currently on-development indie game Lab Geek. Developed by [\_\_merahm\_\_ (Mertahmetsen)](https://github.com/Mertahmetsen) and [ra1n (ra1n321)](https://github.com/ra1n321), **LGGE's primary principle is to provide readable code while sacrificing complex features as little as possible.** LGGE is written in pure C and built from reliable and efficient libraries [Raylib](https://github.com/raysan5/raylib) and [RayGUI](https://github.com/raysan5/raygui). LGGE also embraces the core idea behind the Raylib library, to quote directly from the [Raylib GitHub Repository](https://github.com/raysan5/raylib):
>_"...a programming library to enjoy videogames programming; no fancy interface, no visual helpers, no debug button... just coding in the most pure spartan-programmers way."_
## Before you read!
I am not a professional C programmer by any means. There are many unorthodox (and sometimes risky) design choices made in this library. *Hey, at least the code compiles, no?*
## Before you compile!
- LGGE is a header-only library with a primitive design style, meaning you don't need to compile the source code into a separate library in order to work with it. You also *can't* compile the source code into a separate library either without major modifications to the source code *(see: [Dynamic Library Experimental Branch](https://github.com/Mertahmetsen/labgeekgameengine/tree/dynamic-libs-experiment))*.
- LGGE is a library written in and for Linux. It uses many backend features native to Linux. Although some parts of the library can *theoretically* work cross-platform, some of the essential features like map support are dependent on a Linux backend. If you really want to make it work on Windows ~~*(who even uses Windows in the 2026)*~~, you can try using a virtualization layer like [WSL](https://github.com/microsoft/WSL). And if you are using MacOS, well, *god help you*.
- Both Raylib and RayGUI libraries must be installed locally as **shared libraries**. [RayGUI already kind of recommends you to install itself as a **shared library**](https://github.com/raysan5/raygui#building), but you also need to install Raylib as a **shared library** as well. If you install these libraries as static libraries, or if you do not even install them at all, LGGE will most likely either fail to compile, or become unstable.
- Although the library consists of many *seemingly-independent* headers, in reality, some of these headers can be quite dependent on each other.  Some headers like *"fundamental/basic.h"* are vital, while some headers like *"obsolete/render-groups.h"* have became obsolete in the development.
## Standard Code Structure and "Maps"
This will probably be the most difficult part to explain, but I will try my best.
A standard LGGE code heavily depends on **"maps"**, which are code blocks (or headers) that tell the runner file ***(like main.c)*** what to do before, during, and after the game loop **(mostly during the game loop)**. *I might change the name of this feature, as the name can be misleading. The "maps" in the traditional sense are called "worlds" in LGGE.* This might bring up the question *"Isn't that what the runner already should be doing?"*. This is not necessarily true in LGGE. The runner *"prepares"* the environment for the map to be loaded:
- It assigns default values to global variables.
- It initializes fallback actions.
- It prepares the initialization of some core features like the default camera.
- It recompiles maps when requested.
- It initializes the OS environment.
- It handles actions that are independent from the maps. *(e.g: Loading other maps)*

As you can see, the runner's job is to mainly to prepare the very essentials. The rest of the stuff is the duty of the maps. A map code can be written to become almost entirely independent from the runner, and vice versa, **but I do not recommend doing so.** There is no easy way to explain this without the code examples, but most of the time, you want to add the fallback features and the *backend* initializations in the runner, while keeping the *frontend* stuff in the maps.
You can think of the map feature as dividing the entry point file/runner file into *backend* and *frontend* parts. While the *backend* stuff stays at the file itself, the *frontend* gets separated into another "map file". During compilation, the runner includes the map file and both of them get compiled into a single executable. That is also the reason why the runner can just work without the maps, **but again, it's not what i recommend**.
Until now, everything I have said probably sounded like utter gibberish to you. If that is the case, trust me, when you see the code examples, you will get the core design idea.
## Basic Code Example
I believe this is the part that will make everything clear about our design choices. As mentioned earlier in the previous section, the code will consist of two main parts:
1. The "Entry Point/Runner" file that has the **main()** function. We will handle most *"backend"* and *"fallback"* features inside this file.
2. The "Map" file that will mostly handle the game loop.

Let's code a  very simple program written with LGGE that does nothing but clear the background with the color red, and then compile this program using GCC. Now, because LGGE is in early stages of development, some of the stuff inside the code might change, but the general structure will most likely stay the same. We will assume that the compiled binary will be in "./", the map file will be in "resources/maps/" and the headers will be inside "dev/src/".
### The Runner File
We will name our file **main.c** for it to be obvious that it holds the **main()** function. After we see the full file, I will explain every line as clear as possible. Here it is:

    #define RAYGUI_IMPLEMENTATION
    #include "independent/include-all.h"
    
    int main (int argc, char** argv) {
	    ChangeDirectory(GetApplicationDirectory());
	    initLogHandler(COMPLETE);
	    argTools(argc, argv);
	    preWinInitGlobals();
	    InitWindow(g_windowW, g_windowH, g_windowTitle);
	    defaultGlobals();
	    
	    loadMap("resources/maps/debug.lgmap", argc, argv);
	    
	    map_onLoad();
	    while (!WindowShouldClose()) {
		    map_onUpdate();
		}
		map_onFinish();
		
		CloseWindow();
		return 0;
	}
**Now, let's check out what the code does line by line:**

    #define RAYGUI_IMPLEMENTATION
RayGUI is a single-file header-only library. What this means is, both the function definitions AND implementations are inside the same file. We add this line at the start of the file to avoid duplicate errors during compilation.

    #include "independent/include-all.h"
One of the LGGE's headers is the `include-all` header inside the `independent` folder. This line includes all of the library for us to use, even though our code does not use every feature of LGGE.

    int main (int argc, char** argv)
We declare our entry point! *(You DO know C, **right?**)*    

    ChangeDirectory(GetApplicationDirectory());
This one is not mandatory, you can set the working directory wherever you want, but setting it as the output of `GetApplicationDirectory()` is good practice.

    initLogHandler(COMPLETE);
LGGE uses it's own log handling rather than using the `TraceLog()` function Raylib offers. The `COMPLETE` parameter tells the initializer that every single log message will be printed on the console, no matter the "log level".

    argTools(argc, argv);
The `fundamental/devtools.h` header provides many useful (and sometimes even mandatory) tools for us to use. The `argTools()` function handles console arguments, like `--recompile` or `--verbosity`.

    preWinInitGlobals();
As stated in the previous section, one of the runner file's duties is to initialize standard values to global variables. The `preWinInitGlobals()` function handles the extremely basic global variables that need to be initialized before Raylib initializes the game window.

    InitWindow(g_windowW, g_windowH, g_windowTitle);
This is a function that Raylib provides. It initializes the game window using the standard values for the window width, height, and title.

    defaultGlobals();
The `defaultGlobals()` function initializes almost all of the global variables.

    loadMap("resources/maps/debug.lgmap", argc, argv);
This function does **A LOT** of stuff on the backend part, but for simplicity, let's just say that it recompiles the runner file before editing it to include the map file. Before this function is ran, the program uses a default map called "the fallback map" located inside `dev/src/map/fallback.h`.
*Please do not insult me for my design choices. I know this can just be achieved by compiling the map as a library. During development, I hit a bootstrap bug so bad i couldn't fix it for weeks. There were around 3-4 different binaries trying to use each other's code. **I want you to imagine the pain I went through** to decide on something like this. As I said before, I am not a good developer by any means.*

    map_onload();
This function's implementation is given by the map. The map provides the runner what to do before the game loop begins.

    while (!WindowShouldClose())
 We enter the main game loop.

    map_onUpdate();
This function's implementation is given by the map. The map provides the runner what to do during the game loop.

    map_onFinish();
This provides the runner what to do after the game loop ends.

    CloseWindow();
We use the Raylib library's `CloseWindow()` function to deinitialize the window.
### The Map File
Now, we are going to check out the map file's code:

    #ifndef  HEADERGUARD_DEBUG
    #define  HEADERGUARD_DEBUG
    #include  "../../dev/src/fundamental/include-all.h"
    void  map_onLoad (void) {}
    void  map_onUpdate (void) {
	    BeginDrawing();
	    ClearBackground(RED);
	    EndDrawing();
    }
    void  map_onFinish (void) {}
    #endif
**Let's check what the code does:**

    #ifndef  HEADERGUARD_DEBUG
    #define  HEADERGUARD_DEBUG
We define our include guards so that the map does not get included more than once. This may not be necessary here, but it is good practice to use include guards.

    #include  "../../dev/src/fundamental/include-all.h"
This includes all of the LGGE library.

    void  map_onUpdate (void) {
    	    BeginDrawing();
    	    ClearBackground(RED);
    	    EndDrawing();
    }
All we want our map to do, is to clear the background with the color red. We begin drawing with `BeginDrawing()`, Clear the background red with `ClearBackground(RED)` and end drawing with `EndDrawing()`.
### Compilation
Let's compile our code with this simple line:

    gcc main.c -o ./bin -lraylib -lm
This tells the `gcc` compiler *"I want to compile this file `main.c`, I want the compiled output's name to be `bin` and I will use the `raylib` and `math` libraries.*
## FAQ
These are the questions that were asked to me by many people, or will most likely be asked by many people.

> Why use C?

Because at the time of starting to write the library, the language I know the best was C. Since I have decided that I will use Raylib at the time, and since Raylib only supports C and C++, the only realistic alternative I had to C was C++. But as any C++ dev will tell you, **C++ is not C with some "extra stuff"**. These languages embrace different design principles. And I not only have very limited knowledge of C++, I also simply do not like C++'s syntax. I feel like it verbosifies stuff more than it should, at least for writing a library that focuses on code readibility. And while C is an old language and is slowly starting to become overshadowed by alternatives like Rust, it is still a semi-popular language with good enough community support.
> Why write your own game engine while you can use an already existing one?

Writing my own game engine has been a goal that I had for a very long time. Even though I had tried using other engines like Unity, they felt overwhelming to use. Also, I like the part of programming where you sit behind two monitors, one has the code editor while the other one has the terminal open. I like the bare-bones kind of programming.
> Do you use AI in the engine's development?

I would never copy-paste AI code and tell people it's my own. You can be sure that the engine's code is written completely by me. I only use AI to learn more about the capabilities of the C language itself, and in intense debugging sessions that sometimes take hours. Why do I not ask programming forums for help rather than AI? Because *I have a life*, and I can't just wait for a notification on my phone for 3 days just to be hit with "random-nitwit-342" answering my post with *"that is the most DISGUSTING code I have EVER seen! GIVE UP!"*.
> Why did you design the engine code like this? You could have just compiled your engine as a library, and that would make things easier for you.

I ***know***. I simply get PTSD from the various compiler errors and bootleg errors everytime someone utters the word "library".
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
