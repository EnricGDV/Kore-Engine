## Kore Engine

Kore Engine is a Game Engine developed by Enric-G. Durán and Clara Ratera for the Videogame Engines subject in CITM, supervised by Marc Garrigó.
It is an engine that integrates a User Interface System as well as other common functionality usually seen in popular Videogame Engines.

Code for the second delivery of this project was provided by Pol Casaú and Xavi Marin, who worked on [Tonic Engine](https://github.com/xavimarin35/TonicEngine)


## Team Members

### Enric-G. Durán

![](images/enric.jpg)

#### Tasks:
- Web
- Implementing Freetype Library
- Icon

### Clara Ratera

![](images/clara.jpg)

#### Tasks:
- Implementing UI Module
- Implementing 2DTransform Component

## Core Sub-Systems:

### 3D Model Rendering

Using OpenGL, our Engine allows users to visualize and edit 3D meshes in the way they wish. It also supports texture usage.

### GameObject System

The elements created or imported to Kore Engine will be categorized as Game Objects with a Transform or Transform2D Component (If they are UI Elements).
These objects can have other components depending on their utility.
They will be organized in a hierarchy that can be edited and used in order to make changes to more than one element at once.

Components:
- Transform
- 2DTransform
- Mesh
- Texture
- Camera
- ...

## UI System

The UI System allows the user to create new UI elements for their game.


## Video

## Repository

You can check out Kore Engine [here](https://github.com/EnricGDV/Kore-Engine)

And you can download the last release [here](https://github.com/EnricGDV/Kore-Engine/releases)

## License

MIT License

Copyright (c) 2020 EnricGDV

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
