#pragma once

class Observer {
public:
    virtual ~Observer() = default;
    virtual void NextDay() = 0;
};
