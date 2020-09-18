# import os module for reading and creating directories
import os
# import opencv-python to perform binarization on input images
import cv2
# import pythonRLSA to perform run-length smearing on images
from pythonRLSA.rlsa_fast import rlsa_fast
# import the time module for calculating how long each operation takes
from time import time as timer
# import the colorama module for printing colored text (just for fun)
from colorama import Fore, Style

# get the list of all images stored in the folder images/in/
input_images = os.listdir("input")
# sort the input image files in alphabetical order (just for aesthetics)
input_images.sort()

# variable to calculate how long the whole program took
start_time = timer()

# repeat the following for all images in the images/in/ folder
for image_name in input_images:
    # print the name of file currently being processed
    print( Style.BRIGHT + Fore.GREEN + " [ INFO ]" + Fore.CYAN + " NOW READING :: ", image_name)
    
    # read the image in grayscale format
    image = cv2.imread("input/" + image_name, 0)
    
    # reset the timer
    begin = timer()
    
    
    # perform horizontal and vertical smearing on the image
    out = rlsa_fast(image, True, True, 10)
    
    # print how long it took to perform smearing
    print( Fore.GREEN + " [ INFO ]" + Fore.WHITE + " performed horizontal and vertical smearing in...   " + Fore.YELLOW + str( round(timer() - begin, 4)) +  "s")
    
    # save this output as image
    cv2.imwrite("output/rlsa_fast/both/" + image_name, out)
    
    # reset the timer
    begin = timer()
    
    # perform horizontal and vertical smearing on the image
    out = rlsa_fast(image, True, False, 10)
    
    # print how long it took to perform smearing
    print( Fore.GREEN + " [ INFO ]" + Fore.WHITE + " performed horizontal smearing in...                " + Fore.YELLOW + str( round(timer() - begin, 4) ) + "s")
    
    # save this output as image
    cv2.imwrite("output/rlsa_fast/horizontal/" + image_name, out)
    
    # reset the timer
    begin = timer()
    
    # perform horizontal and vertical smearing on the image
    out = rlsa_fast(image, False, True, 10)
    
    # print how long it took to perform smearing
    print( Fore.GREEN + " [ INFO ]" + Fore.WHITE + " performed vertical smearing in...                  " +  Fore.YELLOW + str( round(timer() - begin, 4) ) + "s")
    
    # save this output as image
    cv2.imwrite("output/rlsa_fast/vertical/" + image_name, out)
    
    # reset the timer
    begin = timer()
    
    # perform horizontal and vertical smearing on the image
    out = rlsa_fast(image, False, False, 10)
    
    # print how long it took to perform smearing
    print( Fore.GREEN + " [ INFO ]" + Fore.WHITE + " performed no smearing in...                        " +  Fore.YELLOW + str( round(timer() - begin, 4) ) + "s")
    
    # save this output as image
    cv2.imwrite("output/rlsa_fast/none/" + image_name, out)
    
    print("_____________________________________________________________________\n")
    
print( Style.BRIGHT + "                PROCESSED ", len(input_images), " IMAGES IN " + str( round(timer() - start_time, 4) ) + "s !!!")
print("_____________________________________________________________________\n" + Style.RESET_ALL)
   