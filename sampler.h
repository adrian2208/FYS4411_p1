#pragma once
#include<string>

class Sampler {
public:
    Sampler(class System* system);
    void setNumberOfMetropolisSteps(int steps);
    virtual void sample(bool acceptedStep);
    virtual void computeAverages();
    void printOutputToTerminal();
    void printOutputToFile();
    
    double getEnergy()          { return m_energy; }
    double getProductOfExpectations() { return m_productOfExpectations; }
    double getExpectationOfProduct() { return m_expectationOfProduct; }
    double getNumberAccepted() { return m_NrAcceptedSteps; }
    std::vector<double> getEnergyVector() { return m_energyVector; }

protected:

    void    samplePos();
    int     m_numberOfMetropolisSteps       = 0;
    int     m_stepNumber                    = 0;
    double  m_energy                        = 0;
    double  m_cumulativeEnergy              = 0;
    int     m_NrAcceptedSteps               = 0;
    // Required for Gradient Descent:
    double  m_cumulativeEnergyDiffWFProduct = 0;
    double  m_cumulativeDifferentiatedWF = 0;
    double  m_productOfExpectations = 0;
    double  m_expectationOfProduct = 0;
    std::vector<double> m_energyVector;
    
    class System* m_system = nullptr;
};
