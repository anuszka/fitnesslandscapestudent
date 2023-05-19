import pandas as pd
import random
import time
import numpy as np


def init()->dict:
    """Initialize simulation parameters

    Returns:
        dict: Simulation parameters dictionary
    """    

    input_dir="./input/"
    input_data_file1 = "landscape1.csv"
    input_data_file2 = "landscape2.csv"
    input_data_files=[input_data_file1,input_data_file2]
    potentialfile1 = input_dir+input_data_file1
    potentialfile2 = input_dir+input_data_file2
    output_dir="./output/"
    output_log_file="out.log"

    Ndatafiles=2
    dfv=[]
    for i in range (Ndatafiles):
        dfv.append(pd.read_csv(input_dir+input_data_files[i]))

    


    T1=10.0
    Ntraj1= 1 # Takes some time
    dt1= 0.1 #0.001
    minDt = 0. #1e-1
    eta=0.1
    D = 2. #1. #0.1
    gamma = 1. #0.5
    # alpha= # Will be given later
    x0=5.
    y0=5.
    kr1=10.
    kr2=20.
    kmr1=90.
    kmr2=100.
    mean_landscape_switching_times=5.
    alpha_min=0.1
    alpha_max=0.2
    alpha_step=0.1

    random.seed(time.time())
    seeds=[]
    for alpha in np.arange(alpha_min,alpha_max,alpha_step):
        seeds.append(random.randrange(100000))
    # display(seeds)
    
    params=dict(
        input_dir=input_dir,
        input_data_file1 =input_data_file1,
        input_data_file2 = input_data_file2,
        input_data_files=input_data_files,
        potentialfile1 = potentialfile1,
        potentialfile2 = potentialfile2,
        output_dir=output_dir,
        output_log_file=output_log_file,
        Ndatafiles=Ndatafiles,
        dfv=dfv,
        T1=T1,
        Ntraj1=Ntraj1,
        dt1= dt1,
        minDt =minDt,
        eta=eta,
        D = D,
        gamma = gamma,
        x0=x0,
        y0=y0,
        kr1=kr1,
        kr2=kr2,
        kmr1=kmr1,
        kmr2=kmr2,
        mean_landscape_switching_times=mean_landscape_switching_times,
        alpha_min=alpha_min,
        alpha_max=alpha_max,
        alpha_step=alpha_step,
        seeds=seeds
        )
    return params