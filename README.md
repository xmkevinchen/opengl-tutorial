# OpenGL Tutorial

This is a VS Code workspace on macOS for [YouTube OpenGL Tutorial](https://www.youtube.com/playlist?list=PLlrATfBNZ98foTJPJ_Ev03o2oq3-GGOS2).

## Build glew macOS universal library

```
git clone https://github.com/nigels-com/glew.git
cd glew
cd auto
make
cd ../
make SYSTEM=darwin-universal
```

After building the libraries
- Copy the header files from `include` folder
- Copy the library files from `lib` folder (Here, I use the static library)

```
file lib/libGLEW.a
lib/libGLEW.a: Mach-O universal binary with 2 architectures: [x86_64:current ar archive random librarycurrent ar archive random library] [arm64:current ar archive random librarycurrent ar archive random library]
lib/libGLEW.a (for architecture x86_64):	current ar archive random library
lib/libGLEW.a (for architecture arm64):	current ar archive random library
```

## glfw universal library

- Download macOS pre-compiled binaries from [GLFW website](https://github.com/glfw/glfw/releases/download/3.3.8/glfw-3.3.8.bin.MACOS.zip)
- Copy the library from the unzip file
