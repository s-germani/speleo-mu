import numpy as np
import pandas as pd
import matplotlib.pyplot as plt

from scipy import integrate

def groundf(Emu,theta):
    """
    dNmu/(dEmu dOmega)   1/(cm^2 s sr GeV)
    """

    C = 0.14*Emu**-2.7

    cE = 1.1*Emu * np.cos(theta)
    D1 = 1 + cE / 115 
    D2 = 1 + cE / 850

    f = C * ( 1/D1 + 0.054/D2 )

    return f





def muon_flux():

    print('Underground Muon Flux')

    Emu_s = np.logspace( 2, 3, 100)

    fmu_s_0 = groundf(Emu_s, 0)

    plt.plot(Emu_s, fmu_s_0)
    plt.xlabel(r'$E_{\mu}$ [GeV]')
    plt.ylabel(r'$dN_{\mu}/[dE_{\mu} d\Omega)$ ($cm^{-2} s^{-1} sr^{-1} GeV^{-1}$]')
    plt.xscale('log')
    plt.yscale('log')
    plt.show()




    
if __name__ == "__main__":

    muon_flux()
