#!/bin/bash

rm abResults.txt

#measuring A
echo "Measuring A performance 960x960"
/usr/lib64/openmpi/bin/mpirun -np 1 -N 1 -q -hostfile nodes 1a 960 >> abResults.txt
echo "1 proc done..."
/usr/lib64/openmpi/bin/mpirun -np 2 -N 2 -q -hostfile nodes 1a 960 >> abResults.txt
echo "2 proc done..."
/usr/lib64/openmpi/bin/mpirun -np 4 -N 4 -q -hostfile nodes 1a 960 >> abResults.txt
echo "4 proc done..."
/usr/lib64/openmpi/bin/mpirun -np 8 -N 8 -q -hostfile nodes 1a 960 >> abResults.txt
echo "8 proc done..."
/usr/lib64/openmpi/bin/mpirun -np 16 -N 8 -q -hostfile nodes 1a 960 >> abResults.txt
echo "16 proc done..."
/usr/lib64/openmpi/bin/mpirun -np 24 -N 8 -q -hostfile nodes 1a 960 >> abResults.txt
echo "24 proc done..."
/usr/lib64/openmpi/bin/mpirun -np 32 -N 8 -q -hostfile nodes 1a 960 >> abResults.txt
echo "32 proc done..."

echo "Measuring A performance 1920x1920"
/usr/lib64/openmpi/bin/mpirun -np 1 -N 1 -q -hostfile nodes 1a 1920 >> abResults.txt
echo "1 proc done..."
/usr/lib64/openmpi/bin/mpirun -np 2 -N 2 -q -hostfile nodes 1a 1920 >> abResults.txt
echo "2 proc done..."
/usr/lib64/openmpi/bin/mpirun -np 4 -N 4 -q -hostfile nodes 1a 1920 >> abResults.txt
echo "4 proc done..."
/usr/lib64/openmpi/bin/mpirun -np 8 -N 8 -q -hostfile nodes 1a 1920 >> abResults.txt
echo "8 proc done..."
/usr/lib64/openmpi/bin/mpirun -np 16 -N 8 -q -hostfile nodes 1a 1920 >> abResults.txt
echo "16 proc done..."
/usr/lib64/openmpi/bin/mpirun -np 24 -N 8 -q -hostfile nodes 1a 1920 >> abResults.txt
echo "24 proc done..."
/usr/lib64/openmpi/bin/mpirun -np 32 -N 8 -q -hostfile nodes 1a 1920 >> abResults.txt
echo "32 proc done..."

echo "Measuring A performance 2880x2880"
/usr/lib64/openmpi/bin/mpirun -np 1 -N 1 -q -hostfile nodes 1a 2880 >> abResults.txt
echo "1 proc done..."
/usr/lib64/openmpi/bin/mpirun -np 2 -N 2 -q -hostfile nodes 1a 2880 >> abResults.txt
echo "2 proc done..."
/usr/lib64/openmpi/bin/mpirun -np 4 -N 4 -q -hostfile nodes 1a 2880 >> abResults.txt
echo "4 proc done..."
/usr/lib64/openmpi/bin/mpirun -np 8 -N 8 -q -hostfile nodes 1a 2880 >> abResults.txt
echo "8 proc done..."
/usr/lib64/openmpi/bin/mpirun -np 16 -N 8 -q -hostfile nodes 1a 2880 >> abResults.txt
echo "16 proc done..."
/usr/lib64/openmpi/bin/mpirun -np 24 -N 8 -q -hostfile nodes 1a 2880 >> abResults.txt
echo "24 proc done..."
/usr/lib64/openmpi/bin/mpirun -np 32 -N 8 -q -hostfile nodes 1a 2880 >> abResults.txt
echo "32 proc done..."

#measuring B
echo "Measuring B performance 960x960"
/usr/lib64/openmpi/bin/mpirun -np 1 -N 1 -q -hostfile nodes 1b 960 >> abResults.txt
echo "1 proc done..."
/usr/lib64/openmpi/bin/mpirun -np 2 -N 2 -q -hostfile nodes 1b 960 >> abResults.txt
echo "2 proc done..."
/usr/lib64/openmpi/bin/mpirun -np 4 -N 4 -q -hostfile nodes 1b 960 >> abResults.txt
echo "4 proc done..."
/usr/lib64/openmpi/bin/mpirun -np 8 -N 8 -q -hostfile nodes 1b 960 >> abResults.txt
echo "8 proc done..."
/usr/lib64/openmpi/bin/mpirun -np 16 -N 8 -q -hostfile nodes 1b 960 >> abResults.txt
echo "16 proc done..."
/usr/lib64/openmpi/bin/mpirun -np 24 -N 8 -q -hostfile nodes 1b 960 >> abResults.txt
echo "24 proc done..."
/usr/lib64/openmpi/bin/mpirun -np 32 -N 8 -q -hostfile nodes 1b 960 >> abResults.txt
echo "32 proc done..."

echo "Measuring B performance 1920x1920"
/usr/lib64/openmpi/bin/mpirun -np 1 -N 1 -q -hostfile nodes 1b 1920 >> abResults.txt
echo "1 proc done..."
/usr/lib64/openmpi/bin/mpirun -np 2 -N 2 -q -hostfile nodes 1b 1920 >> abResults.txt
echo "2 proc done..."
/usr/lib64/openmpi/bin/mpirun -np 4 -N 4 -q -hostfile nodes 1b 1920 >> abResults.txt
echo "4 proc done..."
/usr/lib64/openmpi/bin/mpirun -np 8 -N 8 -q -hostfile nodes 1b 1920 >> abResults.txt
echo "8 proc done..."
/usr/lib64/openmpi/bin/mpirun -np 16 -N 8 -q -hostfile nodes 1b 1920 >> abResults.txt
echo "16 proc done..."
/usr/lib64/openmpi/bin/mpirun -np 24 -N 8 -q -hostfile nodes 1b 1920 >> abResults.txt
echo "24 proc done..."
/usr/lib64/openmpi/bin/mpirun -np 32 -N 8 -q -hostfile nodes 1b 1920 >> abResults.txt
echo "32 proc done..."

echo "Measuring b performance 2880x2880"
/usr/lib64/openmpi/bin/mpirun -np 1 -N 1 -q -hostfile nodes 1b 2880 >> abResults.txt
echo "1 proc done..."
/usr/lib64/openmpi/bin/mpirun -np 2 -N 2 -q -hostfile nodes 1b 2880 >> abResults.txt
echo "2 proc done..."
/usr/lib64/openmpi/bin/mpirun -np 4 -N 4 -q -hostfile nodes 1b 2880 >> abResults.txt
echo "4 proc done..."
/usr/lib64/openmpi/bin/mpirun -np 8 -N 8 -q -hostfile nodes 1b 2880 >> abResults.txt
echo "8 proc done..."
/usr/lib64/openmpi/bin/mpirun -np 16 -N 8 -q -hostfile nodes 1b 2880 >> abResults.txt
echo "16 proc done..."
/usr/lib64/openmpi/bin/mpirun -np 24 -N 8 -q -hostfile nodes 1b 2880 >> abResults.txt
echo "24 proc done..."
/usr/lib64/openmpi/bin/mpirun -np 32 -N 8 -q -hostfile nodes 1b 2880 >> abResults.txt
echo "32 proc done..."

#measuring C
echo "Measuring C performance 960x960"
/usr/lib64/openmpi/bin/mpirun -np 1 -q -hostfile nodes 1c 960 1 >> abResults.txt
echo "1 proc done..."
/usr/lib64/openmpi/bin/mpirun -np 1 -q -hostfile nodes 1c 960 2 >> abResults.txt
echo "2 proc done..."
/usr/lib64/openmpi/bin/mpirun -np 1 -q -hostfile nodes 1c 960 4 >> abResults.txt
echo "4 proc done..."
/usr/lib64/openmpi/bin/mpirun -np 1 -q -hostfile nodes 1c 960 8 >> abResults.txt
echo "8 proc done..."
/usr/lib64/openmpi/bin/mpirun -np 2 -q -hostfile nodes 1c 960 8 >> abResults.txt
echo "16 proc done..."
/usr/lib64/openmpi/bin/mpirun -np 3 -q -hostfile nodes 1c 960 8 >> abResults.txt
echo "24 proc done..."
/usr/lib64/openmpi/bin/mpirun -np 4 -q -hostfile nodes 1c 960 8 >> abResults.txt
echo "32 proc done..."

echo "Measuring C performance 1920x1920"
/usr/lib64/openmpi/bin/mpirun -np 1 -q -hostfile nodes 1c 1920 1 >> abResults.txt
echo "1 proc done..."
/usr/lib64/openmpi/bin/mpirun -np 1 -q -hostfile nodes 1c 1920 2 >> abResults.txt
echo "2 proc done..."
/usr/lib64/openmpi/bin/mpirun -np 1 -q -hostfile nodes 1c 1920 4 >> abResults.txt
echo "4 proc done..."
/usr/lib64/openmpi/bin/mpirun -np 1 -q -hostfile nodes 1c 1920 8 >> abResults.txt
echo "8 proc done..."
/usr/lib64/openmpi/bin/mpirun -np 2 -q -hostfile nodes 1c 1920 8 >> abResults.txt
echo "16 proc done..."
/usr/lib64/openmpi/bin/mpirun -np 3 -q -hostfile nodes 1c 1920 8 >> abResults.txt
echo "24 proc done..."
/usr/lib64/openmpi/bin/mpirun -np 4 -q -hostfile nodes 1c 1920 8 >> abResults.txt
echo "32 proc done..."

echo "Measuring C performance 2880x2880"
/usr/lib64/openmpi/bin/mpirun -np 1 -q -hostfile nodes 1c 2880 1 >> abResults.txt
echo "1 proc done..."
/usr/lib64/openmpi/bin/mpirun -np 1 -q -hostfile nodes 1c 2880 2 >> abResults.txt
echo "2 proc done..."
/usr/lib64/openmpi/bin/mpirun -np 1 -q -hostfile nodes 1c 2880 4 >> abResults.txt
echo "4 proc done..."
/usr/lib64/openmpi/bin/mpirun -np 1 -q -hostfile nodes 1c 2880 8 >> abResults.txt
echo "8 proc done..."
/usr/lib64/openmpi/bin/mpirun -np 2 -q -hostfile nodes 1c 2880 8 >> abResults.txt
echo "16 proc done..."
/usr/lib64/openmpi/bin/mpirun -np 3 -q -hostfile nodes 1c 2880 8 >> abResults.txt
echo "24 proc done..."
/usr/lib64/openmpi/bin/mpirun -np 4 -q -hostfile nodes 1c 2880 8 >> abResults.txt
echo "32 proc done..."

#measuring D
echo "Measuring D performance 960x960"
/usr/lib64/openmpi/bin/mpirun -np 1 -q -hostfile nodes 1d 960 1 >> abResults.txt
echo "1 proc done..."
/usr/lib64/openmpi/bin/mpirun -np 1 -q -hostfile nodes 1d 960 2 >> abResults.txt
echo "2 proc done..."
/usr/lib64/openmpi/bin/mpirun -np 1 -q -hostfile nodes 1d 960 4 >> abResults.txt
echo "4 proc done..."
/usr/lib64/openmpi/bin/mpirun -np 1 -q -hostfile nodes 1d 960 8 >> abResults.txt
echo "8 proc done..."
/usr/lib64/openmpi/bin/mpirun -np 2 -q -hostfile nodes 1d 960 8 >> abResults.txt
echo "16 proc done..."
/usr/lib64/openmpi/bin/mpirun -np 3 -q -hostfile nodes 1d 960 8 >> abResults.txt
echo "24 proc done..."
/usr/lib64/openmpi/bin/mpirun -np 4 -q -hostfile nodes 1d 960 8 >> abResults.txt
echo "32 proc done..."

echo "Measuring D performance 1920x1920"
/usr/lib64/openmpi/bin/mpirun -np 1 -q -hostfile nodes 1d 1920 1 >> abResults.txt
echo "1 proc done..."
/usr/lib64/openmpi/bin/mpirun -np 1 -q -hostfile nodes 1d 1920 2 >> abResults.txt
echo "2 proc done..."
/usr/lib64/openmpi/bin/mpirun -np 1 -q -hostfile nodes 1d 1920 4 >> abResults.txt
echo "4 proc done..."
/usr/lib64/openmpi/bin/mpirun -np 1 -q -hostfile nodes 1d 1920 8 >> abResults.txt
echo "8 proc done..."
/usr/lib64/openmpi/bin/mpirun -np 2 -q -hostfile nodes 1d 1920 8 >> abResults.txt
echo "16 proc done..."
/usr/lib64/openmpi/bin/mpirun -np 3 -q -hostfile nodes 1d 1920 8 >> abResults.txt
echo "24 proc done..."
/usr/lib64/openmpi/bin/mpirun -np 4 -q -hostfile nodes 1d 1920 8 >> abResults.txt
echo "32 proc done..."

echo "Measuring D performance 2880x2880"
/usr/lib64/openmpi/bin/mpirun -np 1 -q -hostfile nodes 1d 2880 1 >> abResults.txt
echo "1 proc done..."
/usr/lib64/openmpi/bin/mpirun -np 1 -q -hostfile nodes 1d 2880 2 >> abResults.txt
echo "2 proc done..."
/usr/lib64/openmpi/bin/mpirun -np 1 -q -hostfile nodes 1d 2880 4 >> abResults.txt
echo "4 proc done..."
/usr/lib64/openmpi/bin/mpirun -np 1 -q -hostfile nodes 1d 2880 8 >> abResults.txt
echo "8 proc done..."
/usr/lib64/openmpi/bin/mpirun -np 2 -q -hostfile nodes 1d 2880 8 >> abResults.txt
echo "16 proc done..."
/usr/lib64/openmpi/bin/mpirun -np 3 -q -hostfile nodes 1d 2880 8 >> abResults.txt
echo "24 proc done..."
/usr/lib64/openmpi/bin/mpirun -np 4 -q -hostfile nodes 1d 2880 8 >> abResults.txt
echo "32 proc done..."
