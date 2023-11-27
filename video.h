#pragma once
#include "types.h"

void DrawSimpleObject(Sdl* sdl, const SimpleObject& object, const Texture* t);
void DrawComplexObject(Sdl* sdl, const ComplexObject* o, const Texture* t);
//void DrawHUD_lives(const Sdl* sdl, const HUD_lives* hl, const Texture* t);
//void DrawHudScore(const Sdl* sdl, const HUD_score* hs, const Texture* t);
//void DrawLasers(Sdl& sdl, LaserNode* n, const Texture* t);
void DrawLasers(Sdl* sdl, Node<Laser>* n, const Texture* t);
//void DrawAlienOneFleet(Sdl& sdl, Alien_one** fleet, const Texture* t);
void DrawAlienOneFleetV(Sdl* sdl, FleetBase* f, const Texture* t);
//void DrawStarSky(const Sdl& sdl, const std::vector<Plot>& vector);
//void DrawingSky(const Sdl& sdl, const Plot* sky, const int length);
//void DrawSky(const Sdl* sdl, const Sky* sky);
//void DrawCartoons(Sdl& sdl, CartoonNode* n, const Texture* t);
void DrawCartoons(Sdl* sdl, Node<CartoonObject>* n, const Texture* t);
//void DrawCartoon(Sdl& sdl, const StoreCartoon<CartoonObject>& object, const Texture* t);
//void DrawMainMenu(Sdl* sdl, const MainMenu* mm, const Texture* t);
