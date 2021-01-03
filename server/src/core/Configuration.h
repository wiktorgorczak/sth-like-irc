//
// Created by wiktor on 02.01.2021.
//

#ifndef STHLIKEIRCSERVER_CONFIGURATION_H
#define STHLIKEIRCSERVER_CONFIGURATION_H


class Configuration {
private:
    int maxThreadCount;
    int serverPort;
    int queueSize;
    int bufferSize;
public:
    int getMaxThreadCount() const;
    void setMaxThreadCount(int maxThreadCount);
    int getServerPort() const;
    void setServerPort(int serverPort);
    int getQueueSize() const;
    void setQueueSize(int queueSize);
    int getBufferSize() const;
    void setBufferSize(int bufferSize);
};


#endif //STHLIKEIRCSERVER_CONFIGURATION_H
