#ifndef ALGORITHMFACTORY_H
#define ALGORITHMFACTORY_H

#include "enum.h"
#include "Algorithm.h"

#include <memory>

// TODO: Implement Algorithm.cpp

namespace backlash {
    enum class E_ALGORITHMS;

    class AlgorithmFactory {
    public:
        virtual ~AlgorithmFactory();  
        friend class AlgorithmFactoryInitializer;

        // Static function so it can be called without an instantiation
        // TODO: do the static pointer cast in this function
        static std::shared_ptr<Algorithm> CreateAlgorithm(E_ALGORITHMS);

    private:
        virtual Algorithm* create() = 0;
        static std::map<E_ALGORITHMS, AlgorithmFactory*> CountryInit;
    };

    class AlgorithmFactoryInitializer {
        static AlgorithmFactoryInitializer initializer;
        AlgorithmFactoryInitializer();
        AlgorithmFactoryInitializer(const AlgorithmFactoryInitializer&);
    };

}

#endif