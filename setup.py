import setuptools
import sys
import os

with open("README.md", "r") as fh:
    long_description = fh.read()

setuptools.setup(
    name="pythonRLSA",
    version="0.0.1",
    author="VasistaReddy",
    author_email="vasista.1245@gmail.com",
    description="Python Run Length Smoothing Algorithm for Document Processing",
    long_description=long_description,
    long_description_content_type="text/markdown",
    packages=setuptools.find_packages(),
    install_requires=['numpy==1.14.5'],
    url="https://github.com/Vasistareddy/pythonRLSA",
    download_url='https://github.com/Vasistareddy/pythonRLSA',
    include_package_data=True,
    zip_safe=False,
    keywords=['opencv', 'rlsa', 'image', 'documents', 'article', 'OCR', 'extraction'],
    classifiers=[
        'Programming Language :: Python :: 3.5',
        'Topic :: Scientific/Engineering :: Image Recognition',
        'License :: Freeware',
        'Topic :: Software Development :: Version Control :: Git',
    ],
)