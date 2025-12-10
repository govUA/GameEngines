#ifndef MOVE_IUPDATABLE_H
#define MOVE_IUPDATABLE_H

#endif

class IUpdatable {
public:
    virtual void Update(float dt) = 0;

    virtual ~IUpdatable() = default;
};
