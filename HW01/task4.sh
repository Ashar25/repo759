#!/usr/bin/env zsh
#SBATCH --job-name=FirstSlurm
#SBATCH --partition=instruction
#SBATCH --time 00:01:00
#SBATCH --ntasks=1
#SBATCH --cpus-per-task=2
#SBATCH --output=FirstSlurm.out
#SBATCH --error=FirstSlurm.err

hostname
