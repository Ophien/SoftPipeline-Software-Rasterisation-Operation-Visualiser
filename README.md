# -SoftPipeline-Software-Rasterisation-Operation-Visualiser
This project was realised to allow to visualize how raster operations are performed.

It was coded in C++ using OpenGL. The raster operation is performed by drawing pixels in a GL 2D texture. It implements a full render pipeline described as follows:

    Buffer configuration and transformation – Apply the necessary transformations to ensure that the objects will be at the right place.
    Camera transformation – Transform the camera position according to necessity.
    Illumination algorithms (Phong) – Calculate all direct and indirect lightning.
    Interpolation – Interpolate the scene.
    Projection – Project 3D objects into the 2D plane for rasterisation.
    Cut and raster – Select scene piece to be rendered and colour i
