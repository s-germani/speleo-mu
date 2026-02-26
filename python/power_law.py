import numpy as np
import matplotlib.pyplot as plt








def plicum(c, Emin, Emax, gamma):
    """
    Power low inverse cumulative
    """

    return (1/(  (1-c)*Emin**-(gamma-1) +c*Emax**-(gamma-1)))**(1/(gamma-1))
    



def pldistr(Emin, Emax, gamma, N=10000):
    """
    Power low distribution from inverse cumulative
    """
    
    c = np.random.rand(N)
    print(c)
    
    return plicum(c, Emin, Emax, gamma)



def main():
    
    
    EE = pldistr(100, 10000, 2.7, int(1e6))
    print(EE)
    
    plt.hist(np.log10(EE))
    plt.yscale('log')
    plt.show()
    

    








if __name__ == "__main__":

    main()
