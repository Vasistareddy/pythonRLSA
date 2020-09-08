- RUN LENGTH SMOOTHING ALGORITHM(RLSA) is a method mainly used for block segmentation and text discrimination.
- It is mainly used in Document Image Processing to extract out the ROI(region of interest) like block-of-text/title/content with applied heuristics.

# Latest Updates

	- now rlsa function accepts single value/tuple with pair of values. (before we need to call the function twice)
	- a single value be assign to both operations.
	- a tuple pair of values be assign to horizontal and vertical operations respectively

# Install

	- pip install pythonRLSA

# Install requirements

	- pip install -r requirements.txt

# Function Calls Snippet - Various Combinations

```
rlsa.rlsa(image_binary, True, True, (10,5)) # passing different values for H and V operations
rlsa.rlsa(image_binary, True, True, [10,5]) # passing different values for H and V operations
rlsa.rlsa(image_binary, True, True, (10)) # passing same value but in tuple
rlsa.rlsa(image_binary, True, True, [10]) # passing same value but in list
rlsa.rlsa(image_binary, True, True, 10) # passing same value as int
rlsa.rlsa(image_binary, True, False, 10.0) # passing same value as float
rlsa.rlsa(image_binary, False, True, 10) # passing same value as int for V operation only

* H - Horizontal 
* V - Vertical

- At the end of the readme, ipython snippet is attached
```

# Input & Output

## Output of 3 cases with value "10" can be seen in the below image

![Input&Output](https://github.com/Vasistareddy/pythonRLSA/blob/master/pythonRLSA/test_images/image1.png)

### [More sample images can be seen here](https://github.com/Vasistareddy/pythonRLSA/tree/master/pythonRLSA/test_images)

# How it works

	- '255'(white pixel) wil be converted to '0'(black pixel) in a image, if the number of adjacent 255's are less than the predefined limit "value".
	- The "value" varies among the different images.

# Sample Test Case

	- value = 3
	- input - [0, 0, 255, 255, 255, 0, 0, 255, 0, 0, 255, 0, 255]
	- output - [0, 0, 255, 255, 255, 0, 0, 0, 0, 0, 0, 0, 255]

# To test

	- python pythonRLSA/test_rlsa_unittest.py -v

# Unittest Results
```
$ test_bool (__main__.TestRLSA) ... ok
$ test_image (__main__.TestRLSA) ... Image must be an numpy ndarray and must be in binary ... ok
$ test_rlsa_hori (__main__.TestRLSA) ... ok
$ test_rlsa_hori_vert (__main__.TestRLSA) ... ok
$ test_rlsa_vert (__main__.TestRLSA) ... ok
$ test_value (__main__.TestRLSA) ... ok
```
----------------------------------------------------------------------
Ran 6 tests in 0.003s

OK

# Prerequisites
	
	- python3.5+
	- Image must be a binary ndarray(255's/1's/0's)
	- Must pass a predefined limit, a certain integer "value"

# Method

	- rlsa

# Parameters

	- image - numpy.ndarray(required)
	- horizantal - boolean(required)
	- vertial - boolean(required)
	- value - any positive integer(int)/list/tuple(required)

# IPython snippet to convert Image to Binary and RLSA usage
```
# convert the image to binary
import cv2
image = cv2.imread('test_images/image.jpg')
gray = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)
(thresh, image_binary) = cv2.threshold(gray, 150, 255, cv2.THRESH_BINARY | cv2.THRESH_OTSU)
# function call
from pythonRLSA import rlsa
image_rlsa_horizontal = rlsa.rlsa(image_binary, True, False, 10)
```
# Bugs/Errors

Please ensure that you have updated pip to the latest version before installing pythonRLSA.

If you find any bugs/errors in the usage of above code, please raise an issue through [Github](https://github.com/Vasistareddy/pythonRLSA) or send an email to vasista.1245@gmail.com with a clear example that can reproduce the issue.





