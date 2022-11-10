# Euler Operation

### Project Structure

```C++

├── Draw  // Using OpenGL draw solid models
    ├── Draw.hpp
    ├── Draw.cpp
├── EulerOp  // Five Euler operations(mvfs mev mef kemr kfmrh)
    ├── EulerOp.hpp
    ├── EulerOp.cpp
├── HalfEdgeDS  // HalfEdge data structures
    ├── HalfEdgeDS.hpp
    ├── HalfEdgeDS.cpp
├── Sweep // Sweep operations
    ├── Sweep.hpp
    ├── Sweep.cpp
├── main.cpp  // two examples(1.one cube with a hole 2.one cube with three holes  )
    
    
The solid models are built by sweeping operations.
```

### Configuration

- ThirdParty: glfw3  OpenGL  GLEW GLUT  glm

- OS:  Ubuntu22.04
- COMPILER: g++



#### USAGE

```shell
mkdir build && cd build
cmake ..
make

./CADCourse 1 
or
./CADCourse 2
you could use your keyboard up/down/right/left to rotate the picture
```

#### Examples

- cube with one hole

<img src="docs/cube_with_one_hole.png" style="zoom: 67%;" />

* cube with three holes

<img src="docs/cube_with_three_holes.png" style="zoom: 50%;" />

