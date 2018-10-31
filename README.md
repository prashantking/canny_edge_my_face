# canny_edge_my_face
This Package is an implementation of canny edge detector

## Process
To use this package we need image data for which we need to run cv_camera package to get the raw image.
to run the cv_camera package use the following command
```
rosrun cv_camera cv_camera_node
```
from the cv_camera package we get raw images from the following topic 
```
/cv_camera/image_raw 
```
which this package subscribe and process with canny edge detection to produce output image under topic
```
/canny_edge/canny_image
```
## Files
canny_edge.cpp 

##Launch File
canny_edge.launch
