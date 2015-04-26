DO NOT UPLOAD IMAGES FROM THE FERET DATABASE HERE. THIS VIOLATES THE FERET USER AGREEMENT.

The FERET database can be acquired from www.nist.gov/itl/iad/ig/colorferet.cfm
and is roughly 8GB.

Old PCA
***********************************
The old PCA code includes the old CUDA and C versions of the PCA code.  This code was difficult to read and work with, and has been replaced by the code in PCA Spring 2015.  This code follows the MATLAB version more closely. In general, use the code in this folder as a reference only.

PCA Spring 2015
***********************************
The new PCA code written by Connor Bolton.  Works well on small scale testing but I've been unable to get it to run with the FERET database.  This folder also contains an extraction tool for the FERET database to get it into a format that can be used with PCA.

Matrix Library Spring 2015
***********************************
New matrix library usable both in PCA and ICA.  As of Spring 2015 it needs testing and debugging.  Rewriting this library for CUDA should be straightforward. 