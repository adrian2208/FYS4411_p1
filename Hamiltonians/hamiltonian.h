#pragma once
#include <vector>
#include <string>

class Hamiltonian {
public:
    Hamiltonian(class System* system);
    virtual double computeLocalEnergy(std::vector<class Particle*> particles) = 0;
    virtual std::string getName() = 0;
protected:
    class System* m_system = nullptr;
};

