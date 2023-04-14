import os
import numpy as np
from types import SimpleNamespace
from settings import init
from run_ensemble_simulation import run_ensemble_simulation

def runmfpt():
    """Run ensemble simulation in loop
    Settings are given by init() function from settings.py
    """    
    os.system('cd ./output/; rm *.csv; rm *.log')

    params=init()
    n = SimpleNamespace(**params)
    i=0
    for alpha in np.arange(n.alpha_min,n.alpha_max,n.alpha_step):
        # print(f"i={i} seeds[i]={n.seeds[i]}")
        # print('\n')
        # print('=========================================')
        # print('Start simulation with alpha={:.1f}'.format(alpha))
        output_data_file=run_ensemble_simulation(alpha,n.seeds[i],params)
        # print('{:s} saved'.format(output_data_file))
        i=i+1

