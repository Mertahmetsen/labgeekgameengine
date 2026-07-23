# Lab Geek Game Engine
The GitHub repository of the indie narrative job simulator and puzzle game Lab Geek Game Engine (LGGE), developed by \_\_merahm\_\_ and ra1n. Written entirely on C11 using [Raylib](https://github.com/raysan5/raylib) and [RayGUI](https://github.com/raysan5/raygui) libraries.
## How to Compile using LGGE
LGGE is a header-only library, which means you don't have to do any compilation to get it to work properly. All you have to do is include the desired headers in your source code (you can use the include-all.h header inside the "independent" folder to include every header in the library.).

Though, unfortunately, LGGE headers are not completely independent from each other. What this means is: Your desired headers may (and most likely will) require other headers inside the library in order to work properly. For example: As of the time this README file is being written, the "dialoguebox.h" header inside the "ui" folder requires the "time.h" and "globals.h" headers inside the "fundamentals" folder and the "window-pos.h" header inside the "ui" folder.

LGGE uses [Raylib](https://github.com/raysan5/raylib) and [RayGUI](https://github.com/raysan5/raygui) libraries. In order for LGGE to work properly, **both of these libraries must be installed on your local computer as _shared libraries_**. If you install these libraries as static libraries rather than shared libraries, _LGGE will not work properly_.

LGGE is developed on a linux computer. Since both Raylib and RayGUI are cross-platform libraries, on theory, LGGE can work on every platform Raylib and RayGUI supports. However, by the time this file is being written, **this hasn't been tested yet**.
## Contacts
- [Lab Geek Game Engine's official mail account](labgeekproject@gmail.com)
- [\_\_merahm\_\_'s mail account](mertahmetsen@gmail.com)
- [\_\_merahm\_\_'s github page](https://github.com/Mertahmetsen)
- [ra1n's github page](https://github.com/ra1n321)