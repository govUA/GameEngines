#ifndef ASSIGNMENT1_IUPDATABLE_H
#define ASSIGNMENT1_IUPDATABLE_H

#endif

class IUpdatable {
public:
    virtual void Update(float dt) = 0;

    virtual ~IUpdatable() = default;
};
