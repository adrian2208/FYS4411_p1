#pragma once
#include <vector>
#include <string>


class WaveFunction {
public:
    WaveFunction(class System* system);
    int     getNumberOfParameters() { return m_numberOfParameters; }
    std::vector<double> getParameters() { return m_parameters; }
    virtual double evaluate(std::vector<class Particle*> particles) = 0;
    virtual double evaluate(std::vector<class Particle*> particles, int particleIndex) {
        return evaluate(particles);
    }
    virtual double computeVariationalDerivative(std::vector<class Particle*> particles) = 0;
    virtual double localEnergyDerivative() = 0;
    virtual double computeDoubleDerivative(std::vector<class Particle*> particles) = 0;
    virtual std::vector<double> driftTerm(std::vector<class Particle*> particles, int indx) =0;
    virtual std::string getName() = 0;
protected:
    int     m_numberOfParameters = 0;
    std::vector<double> m_parameters = std::vector<double>();
    class System* m_system = nullptr;
};
