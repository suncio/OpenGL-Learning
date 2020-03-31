## OpenGL Project Settings



- **Dependencies**

  OpenGL->GLEW->GLFW

  - GLFW: *GLFW will allow us to create a window, and receive mouse and keyboard input in a cross-platform way. OpenGL does not handle window creation or input, so we have to use these library for handling window, keyboard, mouse, joysticks, input and other purpose.*

    GLEW: *The OpenGL Extension Wrangler (GLEW) is used to access the modern OpenGL API functions(version 3.2 up to latest version). GLEW will handle the run time loading of the OpenGL API.*

    OpenGL: *You still need to link OpenGL lib*

  - GLEW must be `#include` before GLFW

  - `glewInit()` must be called after we have a OpenGL context, in this code namely `glfwMakContextCurrent(window)`



- **Static Link and Macro**

  Since the following code in <GL/glew.h> and we are using static linking, we need to `#define GLEW_STATIC` whether in project setting or in source file:

```c++
#ifdef GLEW_STATIC
#  define GLEWAPI extern
#else
#  ifdef GLEW_BUILD
#    define GLEWAPI extern __declspec(dllexport)
#  else
#    define GLEWAPI extern __declspec(dllimport)
#  endif
#endif
```



- **Reference**

  https://www.gamedev.net/forums/topic/670250-glfw-or-glew-which-opengl-library-should-i-use/ 

  https://www.glfw.org/documentation.html 

  

  

  