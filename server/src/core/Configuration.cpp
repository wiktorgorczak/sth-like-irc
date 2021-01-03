//
// Created by wiktor on 02.01.2021.
//

#include "Configuration.h"

int Configuration::getMaxThreadCount() const {
    return maxThreadCount;
}

void Configuration::setMaxThreadCount(int maxThreadCount) {
    Configuration::maxThreadCount = maxThreadCount;
}

int Configuration::getServerPort() const {
    return serverPort;
}

void Configuration::setServerPort(int serverPort) {
    Configuration::serverPort = serverPort;
}

int Configuration::getQueueSize() const {
    return queueSize;
}

void Configuration::setQueueSize(int queueSize) {
    Configuration::queueSize = queueSize;
}

int Configuration::getBufferSize() const {
    return bufferSize;
}

void Configuration::setBufferSize(int bufferSize) {
    Configuration::bufferSize = bufferSize;
}
