#!/bin/sh

make all && ./main > img.ppm && timg img.ppm
