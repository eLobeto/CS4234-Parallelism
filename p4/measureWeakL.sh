#!/bin/bash

rm weakScaling.txt

#measuring A
echo "Measuring A performance 480"
/usr/lib64/openmpi/bin/mpirun -np 1 -N 1 -q -hostfile nodes 1a 480 >> weakScaling.txt
echo "1 proc done..."
/usr/lib64/openmpi/bin/mpirun -np 2 -N 2 -q -hostfile nodes 1a 480 >> weakScaling.txt
echo "2 proc done..."
/usr/lib64/openmpi/bin/mpirun -np 4 -N 4 -q -hostfile nodes 1a 480 >> weakScaling.txt
echo "4 proc done..."
/usr/lib64/openmpi/bin/mpirun -np 8 -N 8 -q -hostfile nodes 1a 480 >> weakScaling.txt
echo "8 proc done..."
/usr/lib64/openmpi/bin/mpirun -np 16 -N 8 -q -hostfile nodes 1a 960 >> weakScaling.txt
echo "16 proc done..."
/usr/lib64/openmpi/bin/mpirun -np 24 -N 8 -q -hostfile nodes 1a 1920 >> weakScaling.txt
echo "24 proc done..."
/usr/lib64/openmpi/bin/mpirun -np 32 -N 8 -q -hostfile nodes 1a 2880 >> weakScaling.txt
echo "32 proc done..."

echo "Measuring A performance 960"
/usr/lib64/openmpi/bin/mpirun -np 1 -N 1 -q -hostfile nodes 1a 960 >> weakScaling.txt
echo "1 proc done..."
/usr/lib64/openmpi/bin/mpirun -np 2 -N 2 -q -hostfile nodes 1a 960 >> weakScaling.txt
echo "2 proc done..."
/usr/lib64/openmpi/bin/mpirun -np 4 -N 4 -q -hostfile nodes 1a 960 >> weakScaling.txt
echo "4 proc done..."
/usr/lib64/openmpi/bin/mpirun -np 8 -N 8 -q -hostfile nodes 1a 960 >> weakScaling.txt
echo "8 proc done..."
/usr/lib64/openmpi/bin/mpirun -np 16 -N 8 -q -hostfile nodes 1a 1920 >> weakScaling.txt
echo "16 proc done..."
/usr/lib64/openmpi/bin/mpirun -np 24 -N 8 -q -hostfile nodes 1a 2880 >> weakScaling.txt
echo "24 proc done..."
/usr/lib64/openmpi/bin/mpirun -np 32 -N 8 -q -hostfile nodes 1a 3840 >> weakScaling.txt
echo "32 proc done..."

echo "Measuring A performance 1920"
/usr/lib64/openmpi/bin/mpirun -np 1 -N 1 -q -hostfile nodes 1a 1920 >> weakScaling.txt
echo "1 proc done..."
/usr/lib64/openmpi/bin/mpirun -np 2 -N 2 -q -hostfile nodes 1a 1920 >> weakScaling.txt
echo "2 proc done..."
/usr/lib64/openmpi/bin/mpirun -np 4 -N 4 -q -hostfile nodes 1a 1920 >> weakScaling.txt
echo "4 proc done..."
/usr/lib64/openmpi/bin/mpirun -np 8 -N 8 -q -hostfile nodes 1a 1920 >> weakScaling.txt
echo "8 proc done..."
/usr/lib64/openmpi/bin/mpirun -np 16 -N 8 -q -hostfile nodes 1a 2880 >> weakScaling.txt
echo "16 proc done..."
/usr/lib64/openmpi/bin/mpirun -np 24 -N 8 -q -hostfile nodes 1a 3840 >> weakScaling.txt
echo "24 proc done..."
/usr/lib64/openmpi/bin/mpirun -np 32 -N 8 -q -hostfile nodes 1a 7680 >> weakScaling.txt
echo "32 proc done..."

#measuring B
echo "Measuring B performance 480"
/usr/lib64/openmpi/bin/mpirun -np 1 -N 1 -q -hostfile nodes 1b 480 >> weakScaling.txt
echo "1 proc done..."
/usr/lib64/openmpi/bin/mpirun -np 2 -N 2 -q -hostfile nodes 1b 480 >> weakScaling.txt
echo "2 proc done..."
/usr/lib64/openmpi/bin/mpirun -np 4 -N 4 -q -hostfile nodes 1b 480 >> weakScaling.txt
echo "4 proc done..."
/usr/lib64/openmpi/bin/mpirun -np 8 -N 8 -q -hostfile nodes 1b 480 >> weakScaling.txt
echo "8 proc done..."
/usr/lib64/openmpi/bin/mpirun -np 16 -N 8 -q -hostfile nodes 1b 960 >> weakScaling.txt
echo "16 proc done..."
/usr/lib64/openmpi/bin/mpirun -np 24 -N 8 -q -hostfile nodes 1b 1920 >> weakScaling.txt
echo "24 proc done..."
/usr/lib64/openmpi/bin/mpirun -np 32 -N 8 -q -hostfile nodes 1b 2880 >> weakScaling.txt
echo "32 proc done..."

echo "Measuring B performance 960"
/usr/lib64/openmpi/bin/mpirun -np 1 -N 1 -q -hostfile nodes 1b 960 >> weakScaling.txt
echo "1 proc done..."
/usr/lib64/openmpi/bin/mpirun -np 2 -N 2 -q -hostfile nodes 1b 960 >> weakScaling.txt
echo "2 proc done..."
/usr/lib64/openmpi/bin/mpirun -np 4 -N 4 -q -hostfile nodes 1b 960 >> weakScaling.txt
echo "4 proc done..."
/usr/lib64/openmpi/bin/mpirun -np 8 -N 8 -q -hostfile nodes 1b 960 >> weakScaling.txt
echo "8 proc done..."
/usr/lib64/openmpi/bin/mpirun -np 16 -N 8 -q -hostfile nodes 1b 1920 >> weakScaling.txt
echo "16 proc done..."
/usr/lib64/openmpi/bin/mpirun -np 24 -N 8 -q -hostfile nodes 1b 2880 >> weakScaling.txt
echo "24 proc done..."
/usr/lib64/openmpi/bin/mpirun -np 32 -N 8 -q -hostfile nodes 1b 3840 >> weakScaling.txt
echo "32 proc done..."

echo "Measuring B performance 1920"
/usr/lib64/openmpi/bin/mpirun -np 1 -N 1 -q -hostfile nodes 1b 1920 >> weakScaling.txt
echo "1 proc done..."
/usr/lib64/openmpi/bin/mpirun -np 2 -N 2 -q -hostfile nodes 1b 1920 >> weakScaling.txt
echo "2 proc done..."
/usr/lib64/openmpi/bin/mpirun -np 4 -N 4 -q -hostfile nodes 1b 1920 >> weakScaling.txt
echo "4 proc done..."
/usr/lib64/openmpi/bin/mpirun -np 8 -N 8 -q -hostfile nodes 1b 1920 >> weakScaling.txt
echo "8 proc done..."
/usr/lib64/openmpi/bin/mpirun -np 16 -N 8 -q -hostfile nodes 1b 2880 >> weakScaling.txt
echo "16 proc done..."
/usr/lib64/openmpi/bin/mpirun -np 24 -N 8 -q -hostfile nodes 1b 3840 >> weakScaling.txt
echo "24 proc done..."
/usr/lib64/openmpi/bin/mpirun -np 32 -N 8 -q -hostfile nodes 1b 7680 >> weakScaling.txt
echo "32 proc done..."

#measuring C
echo "Measuring C performance 480"
/usr/lib64/openmpi/bin/mpirun -np 1 -q -hostfile nodes 1c 480 1 >> weakScaling.txt
echo "1 proc done..."
/usr/lib64/openmpi/bin/mpirun -np 1 -q -hostfile nodes 1c 480 2 >> weakScaling.txt
echo "2 proc done..."
/usr/lib64/openmpi/bin/mpirun -np 1 -q -hostfile nodes 1c 480 4 >> weakScaling.txt
echo "4 proc done..."
/usr/lib64/openmpi/bin/mpirun -np 1 -q -hostfile nodes 1c 480 8 >> weakScaling.txt
echo "8 proc done..."
/usr/lib64/openmpi/bin/mpirun -np 2 -q -hostfile nodes 1c 960 8 >> weakScaling.txt
echo "16 proc done..."
/usr/lib64/openmpi/bin/mpirun -np 3 -q -hostfile nodes 1c 1920 8 >> weakScaling.txt
echo "24 proc done..."
/usr/lib64/openmpi/bin/mpirun -np 4 -q -hostfile nodes 1c 2880 8 >> weakScaling.txt
echo "32 proc done..."

echo "Measuring C performance 960"
/usr/lib64/openmpi/bin/mpirun -np 1 -q -hostfile nodes 1c 960 1 >> weakScaling.txt
echo "1 proc done..."
/usr/lib64/openmpi/bin/mpirun -np 1 -q -hostfile nodes 1c 960 2 >> weakScaling.txt
echo "2 proc done..."
/usr/lib64/openmpi/bin/mpirun -np 1 -q -hostfile nodes 1c 960 4 >> weakScaling.txt
echo "4 proc done..."
/usr/lib64/openmpi/bin/mpirun -np 1 -q -hostfile nodes 1c 960 8 >> weakScaling.txt
echo "8 proc done..."
/usr/lib64/openmpi/bin/mpirun -np 2 -q -hostfile nodes 1c 1920 8 >> weakScaling.txt
echo "16 proc done..."
/usr/lib64/openmpi/bin/mpirun -np 3 -q -hostfile nodes 1c 2880 8 >> weakScaling.txt
echo "24 proc done..."
/usr/lib64/openmpi/bin/mpirun -np 4 -q -hostfile nodes 1c 3840 8 >> weakScaling.txt
echo "32 proc done..."

echo "Mecsuring C performance 1920"
/usr/lib64/openmpi/bin/mpirun -np 1 -q -hostfile nodes 1c 1920 1 >> weakScaling.txt
echo "1 proc done..."
/usr/lib64/openmpi/bin/mpirun -np 1 -q -hostfile nodes 1c 1920 2 >> weakScaling.txt
echo "2 proc done..."
/usr/lib64/openmpi/bin/mpirun -np 1 -q -hostfile nodes 1c 1920 4 >> weakScaling.txt
echo "4 proc done..."
/usr/lib64/openmpi/bin/mpirun -np 1 -q -hostfile nodes 1c 1920 8 >> weakScaling.txt
echo "8 proc done..."
/usr/lib64/openmpi/bin/mpirun -np 2 -q -hostfile nodes 1c 2880 8 >> weakScaling.txt
echo "16 proc done..."
/usr/lib64/openmpi/bin/mpirun -np 3 -q -hostfile nodes 1c 3840 8 >> weakScaling.txt
echo "24 proc done..."
/usr/lib64/openmpi/bin/mpirun -np 4 -q -hostfile nodes 1c 7680 8 >> weakScaling.txt
echo "32 proc done..."

#measuring D
echo "Measuring D performance 480"
/usr/lib64/openmpi/bin/mpirun -np 1 -q -hostfile nodes 1d 480 1 >> weakScaling.txt
echo "1 proc done..."
/usr/lib64/openmpi/bin/mpirun -np 1 -q -hostfile nodes 1d 480 2 >> weakScaling.txt
echo "2 proc done..."
/usr/lib64/openmpi/bin/mpirun -np 1 -q -hostfile nodes 1d 480 4 >> weakScaling.txt
echo "4 proc done..."
/usr/lib64/openmpi/bin/mpirun -np 1 -q -hostfile nodes 1d 480 8 >> weakScaling.txt
echo "8 proc done..."
/usr/lib64/openmpi/bin/mpirun -np 2 -q -hostfile nodes 1d 960 8 >> weakScaling.txt
echo "16 proc done..."
/usr/lib64/openmpi/bin/mpirun -np 3 -q -hostfile nodes 1d 1920 8 >> weakScaling.txt
echo "24 proc done..."
/usr/lib64/openmpi/bin/mpirun -np 4 -q -hostfile nodes 1d 2880 8 >> weakScaling.txt
echo "32 proc done..."

echo "Measuring D performance 960"
/usr/lib64/openmpi/bin/mpirun -np 1 -q -hostfile nodes 1d 960 1 >> weakScaling.txt
echo "1 proc done..."
/usr/lib64/openmpi/bin/mpirun -np 1 -q -hostfile nodes 1d 960 2 >> weakScaling.txt
echo "2 proc done..."
/usr/lib64/openmpi/bin/mpirun -np 1 -q -hostfile nodes 1d 960 4 >> weakScaling.txt
echo "4 proc done..."
/usr/lib64/openmpi/bin/mpirun -np 1 -q -hostfile nodes 1d 960 8 >> weakScaling.txt
echo "8 proc done..."
/usr/lib64/openmpi/bin/mpirun -np 2 -q -hostfile nodes 1d 1920 8 >> weakScaling.txt
echo "16 proc done..."
/usr/lib64/openmpi/bin/mpirun -np 3 -q -hostfile nodes 1d 2880 8 >> weakScaling.txt
echo "24 proc done..."
/usr/lib64/openmpi/bin/mpirun -np 4 -q -hostfile nodes 1d 3840 8 >> weakScaling.txt
echo "32 proc done..."

echo "Mecsuring D performance 1920"
/usr/lib64/openmpi/bin/mpirun -np 1 -q -hostfile nodes 1d 1920 1 >> weakScaling.txt
echo "1 proc done..."
/usr/lib64/openmpi/bin/mpirun -np 1 -q -hostfile nodes 1d 1920 2 >> weakScaling.txt
echo "2 proc done..."
/usr/lib64/openmpi/bin/mpirun -np 1 -q -hostfile nodes 1d 1920 4 >> weakScaling.txt
echo "4 proc done..."
/usr/lib64/openmpi/bin/mpirun -np 1 -q -hostfile nodes 1d 1920 8 >> weakScaling.txt
echo "8 proc done..."
/usr/lib64/openmpi/bin/mpirun -np 2 -q -hostfile nodes 1d 2880 8 >> weakScaling.txt
echo "16 proc done..."
/usr/lib64/openmpi/bin/mpirun -np 3 -q -hostfile nodes 1d 3840 8 >> weakScaling.txt
echo "24 proc done..."
/usr/lib64/openmpi/bin/mpirun -np 4 -q -hostfile nodes 1d 7680 8 >> weakScaling.txt
echo "32 proc done..."
