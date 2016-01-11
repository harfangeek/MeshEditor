# MeshEditor
A simple mesh editor. Import an .obj model or create one from scratch.

Step 1 :
  - Implement Mesh data model (half-edge structure)
  - Load Obj file
  - Display the model
  - Manipulation (rotate around)

Step 2 :
  - Selection of a vertex/edge/face
  - Translation/rotation of the selected vertex/edge/face
  - Add edge (cut a face into two faces)
  - Remove edge
  - Extrusion of a face

Step 3 :
  - Implement some mesh algorithms:
    . Smooth mesh
    . Mesh improvement : Catmull clarck
    . Mesh simplification
