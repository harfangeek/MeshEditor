[![Build Status](https://travis-ci.org/harfangeek/MeshEditor.svg?branch=feature%2Ftravis)](https://travis-ci.org/harfangeek/MeshEditor)

# MeshEditor

- [Presentation](#presentation)
- [Features](#features)
- [Project Dependencies](#project-dependencies)
- [System Dependencies](#system-dependencies)
- [Building](#building)
- [References](#references)
- [ToDo List](#todo-list)
- [Ideas to experiment](#ideas-to-experiment)

## Presentation
A simple mesh editor in C++. Import an .obj model and edit it or create one from scratch.

This project is mostly educational. Even if I try to develop it as seriously as possible, it will not fill any user need.  

This project is for me a laboratory to experiment following topics:
- Modern OpenGL (>= 3.3)
- 3D computation and related algorithms and data structures
- Software architecture
- Modern C++ features
- Makefiles
- Git branching models

If you are interested in any of these topics you may find something interesting in this project. All critics and suggestions are of course welcome.

The goal of this project is to implement myself things I am interested in, in order to understand beneath concepts. I implemented myself all 3D data structures and algorithms. I am only relying on OpenGL for rendering and GLM for basic maths objects (vectors and matrices).

The project has been built and tested on Windows 7 64bits (both 32 and 64bits build with MSVC++ and Mingw-w64) and on Debian 9 64bits (both 32 and 64 bits build with gcc/g++ and clang/clang++)

## Project Dependencies

- **Gl3w**, an OpenGL loader : https://github.com/skaslev/gl3w
- **Glfw** 3.2.1, a windowing library : https://www.glfw.org/
- **Dear Imgui** 1.68, an immediate mode GUI library : https://github.com/ocornut/imgui/releases/tag/v1.67
- **Glm** 0.9.9.3, a math library for 3D computation : https://glm.g-truc.net/0.9.9/index.html

For convenience, all dependencies are shipped with the project. They also are automatically built before building the project so you should not worry about them.

## System Dependencies 

### Windows

The OpenGL library should be provided by your system or your graphic card driver.

### Linux

Some packages need to be installed, instructions for Debian 9 64 bits:

Minimum install: `apt install libx11-dev libxcursor-dev libxrandr-dev libxinerama-dev` 

You can instead install full X.org meta package: `apt install xorg-dev`

The OpenGL library should be provided by your graphic card driver.

## Building

The project can be built using the provided Visual Studio project on Windows, or using the provided Makefile on both Linux and Windows (see below). The executable is generated in the project root folder. Shaders files needed by the executable at runtime are automatically copied in the project root folder from the sources folder. This project needs a compiler supporting C++17 features.

### Visual Studio (Windows)

Open the project, chose your configuration (debug/release, x86/x64), build the solution. Project dependencies are configured to be automatically built before building the program.
The project has been created with Visual Studio Community 2017.

### Makefile (Linux and Windows)

Go to the project root and execute `make`. The Makefile has been tested on:
- Windows 7 64bits using Mingw-w64. The Makefile can be executed from a standard Windows CMD and from Git Bash.
- Debian 9 64bits using gcc/g++ and clang/clang++

Some options are tweakable. Two examples:
- 32 bits binary with debug info with clang/clang++: `make CC=clang CXX=clang++ MODE=debug ARCH=x86`
- 64 bits binary with optimization with gcc/g++: `make CC=gcc CXX=g++ MODE=release ARCH=x64`

The second one is the default when simply invoking `make`

The project Makefile automatically list all .cpp files so it is not needed to edit it when adding new files.

## References

This project being mostly educational, here are some references for the different topics I'm experimenting in this project.

### Architecture
  - Great introduction to software GUI architecture: https://martinfowler.com/eaaDev/uiArchs.html
  - Introduction to MVC, MVP, PM and MVVM:
    - https://www.codeproject.com/Articles/42830/%2FArticles%2F42830%2FModel-View-Controller-Model-View-Presenter-and-Mod
	- https://stackoverflow.com/a/5124291/3650653
  - Presentation Model: https://martinfowler.com/eaaDev/PresentationModel.html
  - MVVM, a specialization of the Presentation Model: https://msdn.microsoft.com/en-us/magazine/dd419663.aspx

### Modern C++
  - C++11 : 15 useful new features: https://cppdepend.com/blog/?p=319
  - C++14 : Main new features: https://isocpp.org/wiki/faq/cpp14-language
  - C++17 : 7 useful new features: https://www.codingame.com/playgrounds/2205/7-features-of-c17-that-will-simplify-your-code/introduction
  - Full documentation of C++11/14/17: https://github.com/AnthonyCalandra/modern-cpp-features
  - Introduction to Smart Pointers: https://www.internalpointers.com/post/beginner-s-look-smart-pointers-modern-c
  - Core Guidelines for Smart Pointers: http://www.modernescpp.com/index.php/c-core-guidelines-rules-to-smart-pointers
  - Full C++ Core Guidelines: http://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines
  - C++17 filesystem library : https://carlosvin.github.io/posts/recursive-directory-iterator/

### OpenGL
  - Learn modern OpenGL: 
    - EN: https://learnopengl.com/
    - FR: https://opengl.developpez.com/tutoriels/apprendre-opengl/
	- FR/EN: http://www.opengl-tutorial.org/
  - Maths for 3D rendering
    - Matrices, basic maths and specificities for 3D rendering, well illustrated: http://www.opengl-tutorial.org/beginners-tutorials/tutorial-3-matrices/
	- Rotations, quaternions: http://www.opengl-tutorial.org/intermediate-tutorials/tutorial-17-quaternions/
  - Great quick introduction to VBO, Shaders and to drawing multiple objects using VAO : https://cognitivewaves.wordpress.com/opengl-vbo-shader-vao/
 
### Algorithm
  - Half-Edge Data Structure (a.k.a. Doubly connected edge list):
    - Wikipedia: https://en.wikipedia.org/wiki/Doubly_connected_edge_list
	- OpenMesh, a library for mesh manipulation using the Half-Edge Data Structure: http://www.openmesh.org/Documentation/OpenMesh-Doc-Latest/a03930.html
  - Mouse picking with ray casting: http://antongerdelan.net/opengl/raycasting.html

### Makefile
  - Introduction to Makefile:
    - EN: https://www.gnu.org/software/make/manual/html_node/index.html
    - FR: https://gl.developpez.com/tutoriel/outil/makefile/
  - Automatically generate headers dependencies (rebuild .cpp when an included .h is modified): https://bruno.defraine.net/techtips/makefile-auto-dependencies-with-gcc/
  - Advance auto dependency generation: http://make.mad-scientist.net/papers/advanced-auto-dependency-generation/
  - Dynamic rule generation using eval:
    -  https://www.gnu.org/software/make/manual/html_node/Eval-Function.html
    -  http://make.mad-scientist.net/the-eval-function/

### Git Flow
  - A successful Git branching model: https://nvie.com/posts/a-successful-git-branching-model/
  - Using git-flow to automate your git branching workflow: https://jeffkreeftmeijer.com/git-flow/
  - Feature branches and pull requests: https://github.com/AgileVentures/shf-project/wiki/Developing-a-Feature-(or-bug,-chore)
  - Resolving pull request merge conflicts: https://github.com/AgileVentures/shf-project/wiki/Resolving-Pull-Request-merge-conflicts

## ToDo List

- GUI
  - Viewer options panel (Render mode, show normals, perspective mode, ...)
  - Object properties panel (translation, rotation)
  - Load/Save panel
  - Selection panel
  - 3D Manipulator

- Rendering
  - Better usage of VAOs
  - Multiple objects rendering
  - Lights
 
- Algorithm
  - Selection
    - Selection of a face
    - Selection of an edge
    - Selection of an object
  - Mesh geometry
    - Split face (cut a face into two faces)
    - Poke face (create new faces from one face by adding a vertex at the center)
    - Remove edge (merge two faces)
    - Extrusion of a face
  - Mesh transformation
    - Smoothen mesh
    - Mesh improvement (Catmull Clarck algorithm)
    - Mesh simplification
  - Mesh creation
    - Create a cube, sphere, pyramid, ...

## Ideas to experiment
- Implement some iterators for the Mesh data model
- Geometry Shader
- Compute Shader
- Some multithreading
- Draw a Skybox
- Draw a grid
- Textures/materials
- Objects reflection
- Multiple windows (multiple views, synchronized views, ...)
- Optimize the mouse selection (using Bounding Volume Hierarchies)
- Mesh reconstruction (construct a mesh from its vertices only, used in 3D scanner)
- Undo/redo for some features
- Mesh physics (Mass-Spring System)

