# import random
# import time
# import sys

from run import run
from types import SimpleNamespace


def run_ensemble_simulation(alpha:float, params:dict)->str:
    """Run ensemble simulation with a chosen value of the Levy flight parameter alpha.  
    The simulation switches landscape 0 and landscape 1 in time.
    The function generates a file with columns: t,x,y. t: simulation end (here: when
    the trajectory reaches the square ((kmr1,kmr2),(kr1,kr2))). x,y: coordinates of the
    last point of the trajectory.

    Args:
        alpha (float): Levy flight parameter
        params (dict): Other parameters
    
    Returns:
        output_data_file (str):
    """   
    n = SimpleNamespace(**params)
    # random.seed(a=None)
    
    output_data_file=f"outT{n.T1:.0e}N{n.Ntraj1:.0e}dt{n.dt1:.0e}alpha{alpha:.2e}_ensemble.csv"
    
    run(
        n.output_dir,
        output_data_file,
        n.output_log_file,
        alpha=alpha, 
        D=n.D,
        gamma = n.gamma,
        dt=n.dt1, 
        minDt=n.minDt,
        eta=n.eta,
        T=n.T1, 
        t0=0., 
        x0=n.x0,
        y0=n.y0,
        kmr1=n.kmr1,
        kmr2=n.kmr2,
        kr1=n.kr1,
        kr2=n.kr2,
        Ntraj=n.Ntraj1,
        # seed = random.randrange(sys.maxsize), # ?? Does it work here?
        potentialfile=n.potentialfile1,
        potentialfile_second=n.potentialfile2
    )

    print(open('./output/out.log', 'r').read()) 
    return output_data_file
    