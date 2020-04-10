# TODO: you will need to install cv2
# Run "pip3 install opencv-python" in CLI
import cv2
import sys
# Extra credit requires numpy. Uncomment this line and install it if you need to.
#import numpy as np

# Store command line arguments in variables
# TODO: change the next line to store the filename
filename = None
manip = sys.argv[2]

# Open the image file
img = cv2.imread('../' + filename)
# Get the dimensions (in pixels) of the image
dimensions = img.shape

# Displays the original image in the top left corner of the screen.
image = 'Original image'
cv2.namedWindow(image)
cv2.moveWindow(image, 0, 0)
cv2.imshow(image, img)