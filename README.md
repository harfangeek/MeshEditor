# MeshEditor
A simple mesh editor. Import an .obj model and edit it or create one from scratch.

## Libraries:
- Freeglut 2.8.1 : http://freeglut.sourceforge.net/
- Glew 1.13.0 : http://glew.sourceforge.net/
- Glm : http://glm.g-truc.net/0.9.7/index.html

## ToDoList
- Mesh loading
  - [x] Implement Mesh data model (half-edge structure)
  - [x] Load Obj file

- Visualization
  - [x] Display the mesh 
  - [x] Draw wireframe
  - [x] Draw vertices
  - [x] Draw normals (faces and vertices)
  - [x] Draw silouhette
  - [ ] Lights
  - [ ] Skybox
  - [ ] Reflection

- Manipulation
  - [x] Rotate the model with the mouse
  - [x] Translate the model
  - [x] Zoom

- Mesh edition
  - [ ] Selection of a vertex/edge/face
  - [ ] Translation/rotation of the selected vertex/edge/face
  - [ ] Add edge (cut a face into two faces)
  - [ ] Remove edge
  - [ ] Extrusion of a face

- Mesh creation
  - [ ] Create 3D primitives (cube, pyramid, ...)

- Implement some mesh algorithms
  - [x] Mesh triangulation
  - [x] Inflate mesh
  - [ ] Smoothen mesh
  - [ ] Mesh improvement (Catmull Clarck)
  - [ ] Mesh simplification

- GUI : To be defined
  - Event architecture:
    - [x] Base architecture (dispatcher/listener interfaces)
    - [ ] IWindowManager interface + freeglut implementation
    - [ ] IMouseManager interface + freeglut implementation
    - [ ] IKeyboardManager interface + freeglut implementation
  - Multi window support:
    - [ ] Open same mesh in multiple window
    - [ ] Lock/Unlock synchronized manipulation
