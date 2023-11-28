#pragma once
#include "object.h"
#include "texture.h"
#include "eshelon.h"
#include "enums/enumobjectstatus.h"
#include "../const/actionwindow.h"


class SimpleObject : public Object
{
protected:
    Init              init;
    enumObjectStatus  objectStatus = enumObjectStatus::isReady;
    Plot startPos{ 0, 0 };
    Plot objectCenter{ 0, 0 };
    Plot  objectVelocity{ 0, 0 };
    Rect* mainRectFromTexture = nullptr;
    Rect* objectMainRect = nullptr;
    void   recomputeObjectMainRect();
    bool setMainRectFromTexture(Rect* mainRectFromTexture) override;

    void initObjectMainRect() override;

public:
    SimpleObject(const Texture* t, /*������� �������*/
        const Plot& start, /* ��������� �����*/
        const int objectMainRectNomber = 0 /*���������� ����� main rect � ������� main rect ��������*/);
    SimpleObject(const SimpleObject&) = delete;
    SimpleObject& operator=(const SimpleObject&) = delete;
    ~SimpleObject();
    Rect* MainRectFromTexture() const { return mainRectFromTexture; }
    Rect* ObjectMainRect() const { return objectMainRect; }
    const Plot& GetCenter() const { return objectCenter; }
    enumObjectStatus ObjectStatus() const { return objectStatus; }
    void NowIsCrashed() { this->objectStatus = enumObjectStatus::isCrashed; }
    friend std::ostream& operator<<(std::ostream& os, const SimpleObject& o);
    bool InEshelon(const Eshelon& e);
    bool Init_ok() const {return init.Init_ok();}
};