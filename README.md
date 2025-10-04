Image Recovery

Project Description:

A C program that recovers a jpeg image format from a forensic image of a memory card. The program takes a singular input which is the raw card file, that contains a sequence of 512-byte blocks and scans the file for signatures of a jpeg, then extracts each jpeg seperately and stores them in different respective files.

Features:

Reads a raw file containing a sequence of 512-byte blocks.

Identifies JPEG images by detecting their start signatures (e.g., 0xff 0xd8 0xff 0xe*).

Writes each recovered JPEG to a new file in the current directory.

Names output files sequentially (e.g., 000.jpg, 001.jpg, ...).

Files Included: 

recover.c: The main C source file that performs the image recovery.
card.raw: A sample raw file containing JPEG images (not included in the repository due to size; available from CS50x).
README.md: This file, explaining the project and how to run it.

