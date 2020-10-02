# Pixelengine
 
 A simple game engine to create AI simulations


SFML info:
Get the SFML-Source code from: https://www.sfml-dev.org/download/sfml/2.5.1/
You have to install the MinGW 7.3.0 64bit compiler and CMake.

Copy the downloaded SFML-folder to this Repo.
Open QT and build SFML using:
File->open file or project, navigate to: Pixelengine/extern/SFML-2.5.1/CMakeLists.txt
Select your compiler and change the Build output path to: 
... Pixelengine/extern/SFML-2.5.1/bin/Release
... Pixelengine/extern/SFML-2.5.1/bin/Debug

Build the debug and release Version.

You have to copy the dll's from  
Pixelengine/extern/SFML-2.5.1/bin/(Release or Debug)/lib/\*.dll 
into your binary folder where the PixelEngine.exe file is generated.
