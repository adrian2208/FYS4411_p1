#include <iostream>
#include <cmath>
#include <string>
#include <vector>
#include <fstream>
#include "sampler.h"
#include "system.h"
#include "particle.h"
#include "Hamiltonians/hamiltonian.h"
#include "WaveFunctions/wavefunction.h"

using std::cout;
using std::endl;


Sampler::Sampler(System* system) {
    m_system = system;
    m_stepNumber = 0;
}

void Sampler::setNumberOfMetropolisSteps(int steps) {
    m_numberOfMetropolisSteps = steps;
}

void Sampler::sample(bool acceptedStep) {
    // Making sure the sampling variables are initialized at the first step.
    if (m_stepNumber == 0) {
        m_cumulativeEnergy = 0;
        m_NrAcceptedSteps = 0;
    }

    /* Here you should sample all the interesting things you want to measure.
     * Note that there are (way) more than the single one here currently.
     */
    double localEnergy = m_system->getHamiltonian()->
                         computeLocalEnergy(m_system->getParticles());
    
    m_cumulativeEnergy  += localEnergy;
    m_NrAcceptedSteps += (int)acceptedStep;
    m_energyVector.push_back(localEnergy);
    m_stepNumber++;
}

void Sampler::samplePos() {
    std::vector<Particle*> particles = m_system->getParticles();
    double x;
    double r;
    for (Particle* particle : particles) {
        x = particle->getPosition()[0];
        r = sqrt(particle->positionSquared());
        if (x < 4) {
            if (x > -4) {
                m_x_list[(int)floor(x * 15) + 100]++;
            }
        }
        if (r < 8) {
            m_p[(int)floor(r * 15)] ++;
        }
    }
        
}

void Sampler::printOutputToTerminal() {
    int     np = m_system->getNumberOfParticles();
    int     nd = m_system->getNumberOfDimensions();
    int     ms = m_system->getNumberOfMetropolisSteps();
    int     p  = m_system->getWaveFunction()->getNumberOfParameters();
    double  ef = m_system->getEquilibrationFraction();
    std::vector<double> pa = m_system->getWaveFunction()->getParameters();

    cout << endl;
    cout << "  -- System info -- " << endl;
    cout << " Number of particles  : " << np << endl;
    cout << " Number of dimensions : " << nd << endl;
    cout << " Number of Metropolis steps run : 10^" << std::log10(ms) << endl;
    cout << " Number of equilibration steps  : 10^" << std::log10(std::round(ms*ef)) << endl;
    cout << endl;
    cout << "  -- Wave function parameters -- " << endl;
    cout << " Number of parameters : " << p << endl;
    for (int i=0; i < p; i++) {
        cout << " Parameter " << i+1 << " : " << pa.at(i) << endl;
    }
    cout << endl;
    cout << "  -- Results -- " << endl;
    cout << " Energy : " << m_energy << endl;
    cout << endl;
}

void Sampler::printOutputToFile() {
    int     np = m_system->getNumberOfParticles();
    int     nd = m_system->getNumberOfDimensions();
    int     ms = m_system->getNumberOfMetropolisSteps();
    int     p  = m_system->getWaveFunction()->getNumberOfParameters();
    double  ef = m_system->getEquilibrationFraction();
    double  sl = m_system->getStepLength();
    std::vector<double> pa = m_system->getWaveFunction()->getParameters();

    std::string WF = m_system->getWaveFunction()->getName();
    std::string H = m_system->getHamiltonian()->getName();

    //IMPORTANT: when this program is executed through python, the root directory is assumed to be 
    //the directory of the python program, not the executable, meaning the path below 
    // will output to variational-monte-carlo-fys4411/Output when called from python 
    // but to a subdirectory in the x64-Release directory when run from the executable

    std::string path = ".\\Output\\" + WF + "_" + H + "_" + ".csv";
    std::ofstream OutFile;
    OutFile.open(path, std::fstream::app);
    OutFile << np << "," << nd << "," << ms << "," << ef << "," << pa[0] << "," << sl << "," << m_energy << "\n";
    OutFile.close();
}



void Sampler::computeAverages() {
    m_energy = m_cumulativeEnergy / m_numberOfMetropolisSteps;
   
}
