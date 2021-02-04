#define NPY_NO_DEPRECATED_API NPY_1_7_API_VERSION
#include<Python.h>
#include<numpy/arrayobject.h>
#include<stdbool.h>

/*
 Function : get_horizontal_smeared_image
 Parameters : image - 1d array representing the 2d image
                         rows - number of rows in the image
                         cols - number of columns in the image
                         range - minimum distance required between 2 black pixels if they are not to be colored black
 Return Value : 1d array representing the smeared image
 Description : performs horizontal smearing on the image
 Example : int* out = get_horizontal_image(image, 50, 50, 10);

*/
int* get_horizontal_smeared_image(int* image, long int rows, long int cols, int range)
{
    // create a variable to store the output, and allocated memory to it
    int* smeared = (int*)malloc(rows * cols * sizeof(int));

    // repeat the following for all rows in the image
    for(int i = 0; i < rows; ++i)
    {
         int j = 0;
        // find the first pixel in this image which is 0
        while(image[i * cols + j] != 0 && j < cols)
        {
            // copy the value of this pixel in the smeared image variable
            smeared[i * cols + j] = 255;
            ++j;
        }

        // store the position of this pixel in a variable, to be used when calculating the range
        int prev_black = j;

        // repeat the following for the remaining pixels
        for(; j < cols; ++j)
        {
            // copy the value of current pixel in the smeared image variable
            smeared[i * cols + j] = image[ i * cols + j];

            // if the current pixel is black ( 0 ),
            if( image[i * cols + j] == 0 )
            {
                // if the distance from this pixel to the previous black pixel is less than the required range,
                if( j - prev_black <= range )
                {
                    // mark all pixels from the previous black pixel to current pixel as black
                    for(int k = prev_black; k < j; ++k)
                        smeared[i * cols + k] = 0;
                }

                // store the position of current black pixel
                prev_black = j;
            }
        }
    }

   // return the smeared image variable
    return smeared;
}

/*

 Function : get_vertical_smeared_image
 Parameters : image - 1d array representing the 2d image
                         rows - number of rows in the image
                         cols - number of columns in the image
                         range - minimum distance required between 2 black pixels if they are not to be colored black
 Return Value : 1d array representing the smeared image
 Description : performs vertical smearing on the image
 Example : int* out = get_vertical_image(image, 50, 50, 10);

*/
int* get_vertical_smeared_image(int* image, long int rows, long int cols, int range)
{
    // create a variable to store the output, and allocated memory to it
    int* smeared = (int*)malloc(rows * cols * sizeof(int));

    // repeat the following for all rows in the image
    for(int i = 0; i < cols; ++i)
    {
         int j = 0;
        // find the first pixel in this image which is 0
        while(image[j * cols + i] != 0 && j < rows)
        {
            // copy the value of this pixel in the smeared image variable
            smeared[j * cols + i] = 255;
            ++j;
        }

        // store the position of this pixel in a variable, to be used when calculating the range
        int prev_black = j;

        // repeat the following for the remaining pixels
        for(; j < rows; ++j)
        {
            // copy the value of current pixel in the smeared image variable
            smeared[j * cols + i] = image[ j * cols + i];

            // if the current pixel is black ( 0 ),
            if( image[j * cols + i] == 0 )
            {
                // if the distance from this pixel to the previous black pixel is less than the required range,
                if( j - prev_black <= range )
                {
                    // mark all pixels from the previous black pixel to current pixel as black
                    for(int k = prev_black; k < j; ++k)
                        smeared[k * cols + i] = 0;
                }

                // store the position of current black pixel
                prev_black = j;
            }
        }
    }

   // return the smeared image variable
    return smeared;
}

/*

 Function : rlsa_smear_c
 Parameters : image - Python object representation of the numpy array image
                         horizontal - boolean value indicating whether horizontal smearing has to be performed
                         vertical - boolean value indicating whether vertical smearing has to be performed
                         range - Python tuple indicating values for horizontal and vertical range. Can be of length 0, 1 or 2
 Return Value : Python Object representation of numpy array containing the smeared image
 Description : performs horizontal and / or vertical run-length smearing on the input image

*/
PyObject* rlsa_smear_c(PyObject* self, PyObject* args)
{
    // create a variable to hold the image object input to the function
    PyArrayObject* image = NULL;
    // python tuple containing range value for horizontal and vertical smearing respectivaly
    int range = 0;
    // boolean values to indicate whether horizontal and / or vertical smearing is to be performed
    bool horizontal, vertical;

    // parse the input. if it is not in the given format, return from the function
    if( !PyArg_ParseTuple(args, "Obbi", &image,&horizontal, &vertical, &range) )
        return Py_None;

    // check if the input image passed is a python numpy array object
    if( ! PyArray_Check(image))
        return Py_None;

    // if range for smearing is negative, make it zero
    if( range < 0 )
        range = 0;

    // change the type of the array. this way, the function works for input with any dtype
    image = (PyArrayObject*) PyArray_Cast(image, NPY_INT32);

    // store the dimensions ( rows and cols ) of the input image
    npy_intp* dims = PyArray_DIMS(image);

    // create a pointer to store the array data of the image
    int* data = (int*)PyArray_DATA(image);

    // create a pointer to store the output of run-length smearing
    int* out = NULL;

    // if the user wants to perform horizontal and vertical smearing on the image
    if( horizontal == true && vertical == true )
    {

        // perform horizontal smearing on the input image and store the result in out
        out = get_horizontal_smeared_image(data, dims[0], dims[1], range);
        // perform vertical smearing on out and store this result in out
        out = get_vertical_smeared_image(out, dims[0], dims[1], range);
    }
    // if the user wants to perform only horizontal smearing
    else if( horizontal == true && vertical == false )
    {
        // perform horizontal smearing on the input image and store the result in out
        out = get_horizontal_smeared_image(data, dims[0], dims[1], range);
     }
     // if the user wants to perform only vertical smearing
    else if( horizontal == false && vertical == true )
    {
        // perform vertical smearing on input image and store the result in out
        out = get_vertical_smeared_image(data, dims[0], dims[1], range);
    }
    // if the user wants to perform neither of the above
    else
    {
        // store the input image in out as it is
        out = data;
    }

    // create a python numpy array from the out array
    PyArrayObject* output = (PyArrayObject*) PyArray_SimpleNewFromData(2, dims, NPY_INT32, (void*)out);

    // return this python array object
    return PyArray_Return(output);
}


//########        MODULE LEVEL FUNCTIONS        ########

// method definitions
static PyMethodDef methods[] = {
  { "rlsa_fast", rlsa_smear_c, METH_VARARGS, "performs run-length smearing on the image (horizontal and/or vertical)"},
  { NULL, NULL, 0, NULL }
};

// module definition
static struct PyModuleDef rlsa_fast = {
    PyModuleDef_HEAD_INIT,
    "rlsa_fast",
    "A Python module that caculates the run-length smearing of an image and returns it",
    -1,
    methods
};

// create the module
PyMODINIT_FUNC PyInit_rlsa_fast(void) {
  Py_Initialize();
  import_array();
  return PyModule_Create(&rlsa_fast);
}
