import os
import numpy as np
from types import SimpleNamespace
from settings import init
from run_ensemble_simulation import run_ensemble_simulation

def runmfpt():
    """Run ensemble simulation in loop
    """    
    os.system('cd ./output/; rm *.csv; rm *.log')
    params=init()
    n = SimpleNamespace(**params)

    for alpha in np.arange(n.alpha_min,n.alpha_max,n.alpha_step):
        print('Start simulation with alpha={:.1f}'.format(alpha))
        output_data_file=run_ensemble_simulation(alpha,params)
        print('{:s} saved'.format(output_data_file))