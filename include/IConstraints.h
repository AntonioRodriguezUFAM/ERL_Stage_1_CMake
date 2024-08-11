

//IConstraints.h

#ifndef ICONSTRAINTS_H
#define ICONSTRAINTS_H

class IConstraints {
public:
    virtual ~IConstraints() {}
    virtual void setup() = 0;
    virtual void run() = 0; // New method for continuous execution
};

#endif // ICONSTRAINTS_H
