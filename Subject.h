#pragma once
#include <vector>
#include "Observer.h"

using namespace std;
using namespace glm;

class Subject
{
public:
    void addObserver(Observer* observer) {
        observers.push_back(observer);
    }

    void removeObserver(Observer* observer) {
        auto it = find(observers.begin(), observers.end(), observer);
        if (it != observers.end()) {
            observers.erase(it);
        }
    }

    void notifyViewMatrixObservers(const mat4& viewMatrix) {
        for (Observer* observer : observers) {
            observer->updateViewMatrix(viewMatrix); 
        }
    }

protected:
    vector<Observer*> observers;
};
