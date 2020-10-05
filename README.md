# Pixelengine
 
 A simple game engine to create AI simulations

SFML info
--------------
This Engine uses [SFML 2.5.1](https://github.com/SFML/SFML)<br>
You have to install the MinGW 7.3.0 64bit compiler and CMake.<br>
<br>
The SFML repository is automatically downloaded when the repository is cloned. <br>
The SFML repo can be found under: PixelEngine/extern/SFML and must be built first.<br>
Build the debug and release Version.<br>
Make sure the SFML build directory looks like this:<br>
DEBUG: **extern/SFML/bin/Debug/lib**<br>
RELEASE: **extern/SFML/bin/Release/lib**<br>
<br>

If you're using QT, you don't have to copy the SFML-dll's from the SFML bin path.<br>
Otherweise, you find them under:<br>
DEBUG: **extern/SFML/bin/Debug/lib/xy.dll**<br>
RELEASE: **extern/SFML/bin/Release/lib/xy.dll**<br>
