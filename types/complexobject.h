#pragma once

#include "simpleobject.h"

class ComplexObject : public SimpleObject
{
protected:
    Rect** objectCollideVector = nullptr;
    int    objectCollideVectorLength = 0;
    void   recomputeCollideVector();
    virtual void fillCollide() {}
    ComplexObject(const Texture* t,
        const Plot& start,
        const int objectMainRectNomber = 0);
    ComplexObject(const ComplexObject&) = delete;
    ComplexObject& operator=(const ComplexObject&) = delete;

public:
    ~ComplexObject();
    bool operator==(const ComplexObject& o);
    bool operator==(const SimpleObject& s);

    int CmplObjectCollideVectorLength() const
         { return objectCollideVectorLength; }
    Rect** ObjectCollideVector() const { return objectCollideVector; }

};


