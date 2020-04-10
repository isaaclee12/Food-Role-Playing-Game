# TODO: you will need to install cv2
# Run "pip3 install opencv-python" in CLI
import cv2
import sys
# Extra credit requires numpy. Uncomment this line and install it if you need to.
#import numpy as np

# Store command line arguments in variables
# TODO: change the next line to store the filename
filename = None
#manip = sys.argv[2]

# Open the image file
img = cv2.imread('../' + filename)
# Get the dimensions (in pixels) of the image
dimensions = img.shape
# Copy the original image into an image for manipulation
#img_manip = cv2.resize(img, (dimensions[1], dimensions[0]))
# TODO: Store white in a list, where each of the three parts is on a scale of [0, 255]
#white = None
# for x in range(dimensions[0]):
#     for y in range(dimensions[1]):
#         if manip == 'flip':
#             img_manip[x, y] = img[dimensions[0]-1-x, y]
#         elif manip == 'mirror':
#             # TODO: mirror the image and store in img_manip[x, y]
#             pass
#         elif manip == 'invert':
#             # TODO: invert the image and store in img_manip[x, y]
#             # Hint: img[x, y] returns the color of the pixel at that coordinate.
#             # You can invert by subtracting that color from white.
#             pass

# Displays the original image in the top left corner of the screen.
image = 'Original image'
cv2.namedWindow(image)
cv2.moveWindow(image, 0, 0)
cv2.imshow(image, img)
# TODO: Display the manipulated image alongside the original image.

# Infinite loop to keep the windows open until the escape key is pressed.
while True:
    k = cv2.waitKey(1)
    if k == 27:
        cv2.destroyAllWindows()
        exit()

