import matplotlib.pyplot as plt
from matplotlib import cm
import numpy as np
import pandas as pd



def plot_heatmap(output_path:str)->None:
    """Plot heatmap from the output data file columns x,y.

    Args:
        output_data_file (str):
    """    
    ensdf=pd.read_csv(output_path)
    fig, ax = plt.subplots(1,1)
    Nbins = 100
    x_bins = np.linspace(0, 100, Nbins)
    y_bins = np.linspace(0, 100, Nbins)
    h = ax.hist2d(np.array(ensdf.x), np.array(ensdf.y), bins =[x_bins, y_bins], cmap = plt.cm.jet) 
    # nipy_spectral
    fig.colorbar(h[3] , ax=ax) 
    ax.set_xlabel('kmr')
    ax.set_ylabel('kr')
    plt.tight_layout() 
    plt.show()
    return

def plot_fpt_hist(output_path:str, kmr1:float,kmr2:float,kr1:float,kr2:float)->tuple:
    """Plot a histogram from the output_data_file's 't' column.

    Args:
        output_data_file (str):
        kmr1,kmr2,kr1,kr2 (float): Rectangular region in which the simulation stopped
    Returns:
        (float, float): ('t' column mean, 't' column std dev)
    """    
    ensdf=pd.read_csv(output_path)
    fig,ax=plt.subplots(1,1)
    plt.hist(ensdf['t'], bins=30, density=True)

    x_label = 'Time to reach the maximum region (({:.0f},{:.0f}),({:.0f},{:.0f})), T'.format(kmr1,kmr2,kr1,kr2)

    ax.set_xlabel(x_label) 
    ax.set_ylabel('Probability')    
    plt.show()     
    return


def get_fpt_mean_sd(output_path:str)->tuple:
    """Get 't' column mean, 't' column std dev from the file
    Args:
        output_data_file (str):

    Returns:
        (float, float): ('t' column mean, 't' column std dev)
    """       
    ensdf=pd.read_csv(output_path)
    return(ensdf['t'].mean(), ensdf['t'].std())  