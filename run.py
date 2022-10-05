import matplotlib.pyplot as plt
import numpy as np
import pandas as pd
import os

def run(
    output_dir : str,
    output_data_file : str,
    output_log_file : str,
    alpha : float,
    D : float,
    gamma : float,
    dt : float,
    minDt : float,
    eta : float,
    T :float,
    t0 : float,
    x0 : float,
    y0 : float,
    Ntraj: int = 1,
    seed : int = np.NaN,
    potentialfile : str =""
    ) -> None:
    
    if potentialfile: 
        if np.isnan(seed):
            params=f"--alpha={alpha} --D={D} --gamma={gamma} --dt={dt} --minDt={minDt} --eta={eta} --T={T} --t0={t0} --x0={x0} --y0={y0} --Ntraj={Ntraj} --potentialfile={potentialfile}"
        else:
            params=f"--alpha={alpha} --D={D} --gamma={gamma} --dt={dt} --minDt={minDt} --eta={eta} --T={T} --t0={t0} --x0={x0} --y0={y0} --Ntraj={Ntraj} --seed={seed} --potentialfile={potentialfile}"
   
    if not potentialfile: 
        if np.isnan(seed):
            params=f"--alpha={alpha} --D={D} --gamma={gamma} --dt={dt} --minDt={minDt} --eta={eta} --T={T} --t0={t0} --x0={x0} --y0={y0} --Ntraj={Ntraj}"
        else:
            params=f"--alpha={alpha} --D={D} --gamma={gamma} --dt={dt} --minDt={minDt} --eta={eta} --T={T} --t0={t0} --x0={x0} --y0={y0} --Ntraj={Ntraj} --seed={seed}"
    line1=f"echo 't,x,y'>{output_dir}{output_data_file}"
    line2=f"./LevyFlight.run {params} >> {output_dir}{output_data_file} 2>{output_dir}{output_log_file}"
    os.system(line1)
    os.system(line2)
    return

    