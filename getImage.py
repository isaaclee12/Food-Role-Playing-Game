#getImage python file based on sample code given
# TODO: you will need to install cv2
# Run "pip3 install opencv-python" in CLI
import cv2
import sys

#remove pygame print text https://stackoverflow.com/questions/54246668/how-do-i-delete-the-hello-from-the-pygame-community-console-alert-while-using/54246669
from os import environ
environ['PYGAME_HIDE_SUPPORT_PROMPT'] = '1'

# TODO: you will need to install pygame
#Run "pip3 install pygame" in CLT to have sound
from pygame import mixer

#timer
from threading import Timer

# Store command line arguments in variables
# TODO: change the next line to store the filename
filename = sys.argv[1]

# Open the image file
img = cv2.imread('../' + filename)

#mp3 https://stackoverflow.com/questions/20021457/playing-mp3-song-on-python
#https://www.zapsplat.com/sound-effect-category/explosions/
mixer.init()
mixer.music.load('../' + 'boom.mp3')
mixer.music.play()


#TODO: S N A K E
# Displays the original image in the top left corner of the screen.
image = 'An enemy approaches!(Press Esc to exit and continue game)'
cv2.namedWindow(image)
cv2.moveWindow(image, 0, 0)
cv2.imshow(image, img)


# Infinite loop to keep the windows open until the escape key is pressed.
while True:
    k = cv2.waitKey(1)
    if k == 27:
        cv2.destroyAllWindows()
        exit()



# def end():
#     cv2.destroyAllWindows()
#     exit()
#
# #Closes the thing after 5 seconds
# t = Timer (5.0, end)
# t.start()




