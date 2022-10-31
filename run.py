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
    t_pfs_start : float = 0.,
    t_pfs_end : float = 0.,
    Ntraj: int = 1,
    seed : int = np.NaN,
    potentialfile : str="",
    potentialfile_second : str="" #TN
    ) -> None:
    
    if not potentialfile and potentialfile_second: #TN
        potentialfile = potentialfile_second

    if potentialfile and potentialfile_second: #TN
        if np.isnan(seed):
            params=f"--alpha={alpha} --D={D} --gamma={gamma} --dt={dt} --minDt={minDt} --eta={eta} --T={T} --t0={t0} --x0={x0} --y0={y0} --t_pfs_start={t_pfs_start} --t_pfs_end={t_pfs_end} --Ntraj={Ntraj} --potentialfile={potentialfile} --potentialfile_second={potentialfile_second}"
        else:
            params=f"--alpha={alpha} --D={D} --gamma={gamma} --dt={dt} --minDt={minDt} --eta={eta} --T={T} --t0={t0} --x0={x0} --y0={y0} --t_pfs_start={t_pfs_start} --t_pfs_end={t_pfs_end} --Ntraj={Ntraj} --seed={seed} --potentialfile={potentialfile} --potentialfile_second={potentialfile_second}"
   
    if not potentialfile_second: #TN

        potentialfile_second = potentialfile

        if potentialfile:
            if np.isnan(seed):
                params=f"--alpha={alpha} --D={D} --gamma={gamma} --dt={dt} --minDt={minDt} --eta={eta} --T={T} --t0={t0} --x0={x0} --y0={y0} --t_pfs_start={t_pfs_start} --t_pfs_end={t_pfs_end} --Ntraj={Ntraj} --potentialfile={potentialfile} --potentialfile_second={potentialfile_second}"
            else:
                params=f"--alpha={alpha} --D={D} --gamma={gamma} --dt={dt} --minDt={minDt} --eta={eta} --T={T} --t0={t0} --x0={x0} --y0={y0} --t_pfs_start={t_pfs_start} --t_pfs_end={t_pfs_end} --Ntraj={Ntraj} --seed={seed} --potentialfile={potentialfile} --potentialfile_second={potentialfile_second}"
    


        if not potentialfile: #TN 
            if np.isnan(seed):
                params=f"--alpha={alpha} --D={D} --gamma={gamma} --dt={dt} --minDt={minDt} --eta={eta} --T={T} --t0={t0} --x0={x0} --y0={y0} --t_pfs_start={t_pfs_start} --t_pfs_end={t_pfs_end} --Ntraj={Ntraj}"
            else:
                params=f"--alpha={alpha} --D={D} --gamma={gamma} --dt={dt} --minDt={minDt} --eta={eta} --T={T} --t0={t0} --x0={x0} --y0={y0} --t_pfs_start={t_pfs_start} --t_pfs_end={t_pfs_end} --Ntraj={Ntraj} --seed={seed}"
    


    line1=f"echo 't,x,y'>{output_dir}{output_data_file}"
    line2=f"./LevyFlight.run {params} >> {output_dir}{output_data_file} 2>{output_dir}{output_log_file}"
    os.system(line1)
    os.system(line2)
    return

    