#include "video.h"


#ifdef DRAW_RECTS
static int lengthCollideVector{ 0 };
#endif

void DrawSimpleObject(Sdl* sdl, const SimpleObject& object, const Texture* t)
{
    if (!t || object.ObjectStatus() != enumObjectStatus::isOnScreen) return;

    SDL_RenderCopy(sdl->Render(),
        t->GetTexture(),
        object.MainRectFromTexture(),
        object.ObjectMainRect());
#ifdef DRAW_RECTS
    SDL_SetRenderDrawColor(sdl->Render(), 0xFF, 0, 0, 0xFF);
    SDL_RenderDrawRect(sdl->Render(), object.ObjectMainRect());
    SDL_SetRenderDrawColor(sdl->Render(), 0, 0, 0, 0xFF);
#endif

}





void DrawComplexObject(Sdl* sdl, const ComplexObject* o, const Texture* t)
{
    if (!t) return;
    if (o->ObjectStatus() != enumObjectStatus::isOnScreen) return;

    SDL_RenderCopy(sdl->Render(),
        t->GetTexture(),
        o->MainRectFromTexture(),
        o->ObjectMainRect());

#ifdef DRAW_RECTS
    lengthCollideVector = o->CmplObjectCollideVectorLength();
    SDL_SetRenderDrawColor(sdl->Render(), 0xFF, 0, 0, 0xFF);
    SDL_RenderDrawRect(sdl->Render(), o->ObjectMainRect());
    for (auto r = 0; r < lengthCollideVector; r++)
    {
        SDL_RenderDrawRect(sdl->Render(), &(*o->ObjectCollideVector()[r]));
    }
    SDL_SetRenderDrawColor(sdl->Render(), 0, 0, 0, 0xFF);

#endif
}


void DrawLasers(Sdl* sdl, Node<Laser>* n, const Texture* t)
{
    if (!t || !n) return;
    DrawSimpleObject(sdl, *n->object, t);
    DrawLasers(sdl, n->next, t);
}

void DrawCartoon(Sdl* sdl, const CartoonObject* object, const Texture* t)
{
    if (!t || object->ObjectStatus() != enumObjectStatus::isOnScreen) return;
    SDL_RenderCopy(sdl->Render(),
        t->GetTexture(),
        object->CurrentSourceRect(),
        object->CurrentDestRect());

}



void DrawCartoons(Sdl* sdl, Node<CartoonObject>* n, const Texture* t)
{
    if (!t) return;
    if (!n) return;
    DrawCartoon(sdl, n->object, t);
    DrawCartoons(sdl, n->next, t);
}



void DrawAlienOneFleetV(Sdl* sdl, FleetBase* f, const Texture* t)
{
    /*for (auto& ship : f->GetFleet())
    {
        DrawComplexObject(sdl, ship, t);
    }*/
    for (auto ship = 0; ship < f->GetFleetVectorLength(); ++ship)
    {
        DrawComplexObject(sdl, f->operator[](ship), t);
    }
}


