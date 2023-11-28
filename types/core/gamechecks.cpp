#include "game.h"

//проверка на попадание лазером алиена в героя
void Game::checkHeroVSLaser(Node<Laser>* n)
{
	if (n == nullptr) return;
	if (n->object->ObjectStatus() == enumObjectStatus::isOnScreen)
	{
		if (*n->object == *hero)
		{
			n->object->NowIsCrashed();
			hero->NowIsCrashed();
			hud_lives->DecHeroLives();
			if (hud_lives->GetHeroLives() < 1)
			{
				storeCartoon->Push(new CartoonBlow{textureStore,
				hero->GetCenter()});
				gameState->gameOver = true;
				return;
			}

			doBlowHero();
			return;
		}

	}
	checkHeroVSLaser(n->next);
}


//проверка первого флота на сбитие от лазера героя
void Game::checkFirstFleetVSLaser(Node<Laser>* n)
{
	if (n == nullptr) return;
	for (auto& ship: fleet_AlienOne->GetFleet())
	{
		if (ship->ObjectStatus() == enumObjectStatus::isReady) break;
		if (ship->ObjectStatus() == enumObjectStatus::isCrashed) continue;

		if (*n->object == *ship)
		{
            ship->NowIsCrashed();
            fleet_AlienOne->DecCurrentFleetSize();
            hud_score->SetScore(ship->GetScore());
            n->object->NowIsCrashed();
            storeCartoon->
				Push(new CartoonBlow(textureStore, ship->GetCenter()));
		}
	}
	checkFirstFleetVSLaser(n->next);

}

//проверка первого флота на возможность выстрела
void Game::checkFirstFleetMayShoot()
{
	for (auto& ship: fleet_AlienOne->GetFleet())
	{
		if (ship->ObjectStatus() == enumObjectStatus::isReady) break;
		if (ship->ObjectStatus() == enumObjectStatus::isCrashed) continue;

		//если алиен может выстрелить и находится в эшелоне героя
		if (static_cast<Alien_one*>(ship)->ThisAlienMayShoot() &&
			ship->InEshelon(hero->GetHeroEshelon()))
		{
			//если пролетел героя, то не стреляет
			if (ship->GetCenter().x < hero->GetCenter().x) continue;

			//Делаем выстрел
			firstfleetStoreLaser->Push(new FirstFleetAlienLaser{textureStore->
			operator[](enumTextureType::lasersPack), *ship->GetLaserStart()});
			//Запрещаем делать выстрел до следующего раза
			static_cast<Alien_one*>(ship)->ThisAlienCantShoot();
		}
	}
}
