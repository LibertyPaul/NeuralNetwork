TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    Axon.cpp \
    Dendrite.cpp \
    InputNeuron.cpp \
    OutputNeuron.cpp \
    Neuron.cpp \
    NeuralNetwork.cpp \
    SuperNeuron.cpp \
    ExampleGenerator.cpp \
    CircularAverageCalculator.cpp

include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    Axon.hpp \
    Dendrite.hpp \
    InputNeuron.hpp \
    Neuron.hpp \
    OutputNeuron.hpp \
    NeuralNetwork.hpp \
    SuperNeuron.hpp \
    ExampleGenerator.hpp \
    CircularAverageCalculator.hpp

QMAKE_CXXFLAGS += -std=c++11
