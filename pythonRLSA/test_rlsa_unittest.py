import unittest
import numpy
from rlsa import rlsa

value = 2
Input = [[255, 0, 255, 0, 255], [0, 0, 255, 0, 0], [255, 255, 0, 0, 255]]
image = numpy.array([numpy.array(l) for l in Input])
out_h = [[255, 0, 0, 0, 255], [0, 0, 0, 0, 0], [255, 255, 0, 0, 255]]
out_h = numpy.array([numpy.array(l) for l in out_h])
out_v = [[255, 0, 255, 0, 255], [0, 0, 255, 0, 0], [255, 255, 0, 0, 255]]
out_v = numpy.array([numpy.array(l) for l in out_v])
out_h_v = [[255, 0, 0, 0, 255], [0, 0, 0, 0, 0], [255, 255, 0, 0, 255]]
out_h_v = numpy.array([numpy.array(l) for l in out_h_v])

class TestRLSA(unittest.TestCase):
 
    def test_rlsa_hori(self):
        """
        RLSA horizontal test
        """
        self.assertEqual(rlsa(image.copy(), True, False, value).tolist(), out_h.tolist())

    def test_rlsa_vert(self):
        """
        RLSA vertical test
        """
        self.assertEqual(rlsa(image.copy(), False, True, value).tolist(), out_v.tolist())

    def test_rlsa_hori_vert(self):
        """
        RLSA horizontal and vertical test
        """
        self.assertEqual(rlsa(image.copy(), True, True, value).tolist(), out_h_v.tolist())

    def test_bool(self):
        """
        Bool Test

        when both the boolean variable "horizontal" and "vertical" are False
        output == input
        """
        self.assertEqual(rlsa(image.copy(), False, False, value).tolist(), image.copy().tolist())

    def test_value(self):
        """
        Value Test

        when the value is lessthan or equal to 1
        output == input
        """
        self.assertEqual(rlsa(image.copy(), True, False, -1).tolist(), image.copy().tolist())

    def test_image(self):
        """
        Image type Test

        when the Input is not ndarray, it throws 'None'
        """
        self.assertEqual(rlsa(list(image), True, False, value), None)
 
if __name__ == '__main__':
    unittest.main()