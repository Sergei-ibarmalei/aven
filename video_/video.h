#pragma once

#include "../types/texture.h"
#include "../types/sdltype.h"
#include "../types/complexobject.h"
#include "../templates/templates.h"
#include "../types/laser.h"
#include "../types/fleetbase.h"
#include "../types/cartoonobject.h"

void DrawSimpleObject(Sdl* sdl, const SimpleObject& object, const Texture* t);
void DrawComplexObject(Sdl* sdl, const ComplexObject* o, const Texture* t);
void DrawLasers(Sdl* sdl, Node<Laser>* n, const Texture* t);
void DrawAlienOneFleetV(Sdl* sdl, FleetBase* f, const Texture* t);
void DrawCartoons(Sdl* sdl, Node<CartoonObject>* n, const Texture* t);
