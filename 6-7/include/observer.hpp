#pragma once

#include <iostream>
#include <list>
#include <string>
#include <fstream>
#include <chrono>

class IEventListener {
public:
    virtual ~IEventListener(){};
    virtual void update(const std::string &message) = 0;

};

class IEventManager {
public:
    virtual ~IEventManager() {};
    virtual void subscribe(IEventListener* listener) = 0;
    virtual void unsubscribe(IEventListener* listener) = 0;
    virtual void notify() = 0;
};

class InGameEventManager : public IEventManager {
public:
    virtual ~InGameEventManager() {};

    void subscribe(IEventListener* listener) override {
        _listeners.push_back(listener);
    }

    void unsubscribe(IEventListener* listener) override {
        _listeners.remove(listener);
    }

    void notify() override {
        std::list<IEventListener*>::iterator iterator = _listeners.begin();
        while (iterator != _listeners.end()) {
            (*iterator)->update(_message);
            ++iterator;
        }
    }

    void createMessage(const std::string& message) {
        _message = message;
    }

private:
    std::list<IEventListener*> _listeners;
    std::string _message;

};



class LoggingListener : public IEventListener {
public:
    LoggingListener(const std::string &filename, InGameEventManager &eventManager) 
    : _manager(eventManager) {
        this->_manager.subscribe(this);
        this->_filename = filename;
        
        this->_file.open(this->_filename, std::ios::out | std::ios::app);
        // File open for writing: the internal stream buffer supports output operations.
        // All output operations happen at the end of the file, appending to its existing contents.
    }

    virtual ~LoggingListener() {
        if (_file.is_open()) {
            _file.close();
        }
    }

    void update(const std::string &message) override {
        log(message);
    }

    void log(const std::string &message) {
        // Get the current time
        auto now = std::chrono::system_clock::now();
        std::time_t currentTime = std::chrono::system_clock::to_time_t(now);

        // Convert the current time to a string in HH:MM:SS format
        std::tm localTime = *std::localtime(&currentTime);
        char timeString[9]; // HH:MM:SS + null terminator
        std::strftime(timeString, sizeof(timeString), "%H:%M:%S", &localTime);

        // Print the time to logs
        if (_file.is_open()) {
            _file << timeString << " : " << message << std::endl;
        }
    }

private:
    std::ofstream _file;
    std::string _filename;
    InGameEventManager &_manager;
};

class PrintingListener : public IEventListener {
public:
    PrintingListener(InGameEventManager &eventManager) 
    : _manager(eventManager) {
        this->_manager.subscribe(this);
    }

    virtual ~PrintingListener() {};

    void update(const std::string &message) override {
        _killfeed.push_front(message);
    }

    void printKillfeed() {
        for (int i = 0; i < _KillfeedSize; i++) {
            if (i == 0) {
                std::cout << "[ "<< _killfeed[i] << " ]" << std::endl;
            } else {
                std::cout << "  " << _killfeed[i] << std::endl;
            }
        }
    }

private:
    const unsigned long _KillfeedSize{ 3 };

    InGameEventManager &_manager;
    std::deque<std::string> _killfeed{ _KillfeedSize, "-" };
};

