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
	for (auto ship = 0; ship < fleet_AlienOne->GetFleetVectorLength(); ++ship)
	{
		if (fleet_AlienOne->operator[](ship)->ObjectStatus() ==
			enumObjectStatus::isReady) break;
		if (fleet_AlienOne->operator[](ship)->ObjectStatus() ==
			enumObjectStatus::isCrashed) continue;
		if (*n->object == *fleet_AlienOne->operator[](ship))
		{
			fleet_AlienOne->operator[](ship)->NowIsCrashed();
			fleet_AlienOne->DecCurrentFleetSize();
			hud_score->SetScore(fleet_AlienOne->operator[](ship)->GetScore());
			n->object->NowIsCrashed();
			storeCartoon->
				Push(new CartoonBlow(textureStore, 
					fleet_AlienOne->operator[](ship)->GetCenter()));
		}

	}
	checkFirstFleetVSLaser(n->next);
}

//проверка первого флота на возможность выстрела
void Game::checkFirstFleetMayShoot()
{

	for (auto ship = 0; ship < fleet_AlienOne->GetFleetVectorLength(); ++ship)
	{
		if (fleet_AlienOne->operator[](ship)->ObjectStatus() ==
			enumObjectStatus::isReady) return;
		if (fleet_AlienOne->operator[](ship)->ObjectStatus() ==
			enumObjectStatus::isCrashed) continue;
		//если алиен может выстрелить и находится в эшелоне героя
		if (static_cast<Alien_one*>(fleet_AlienOne->operator[](ship))->
			ThisAlienMayShoot() &&
			fleet_AlienOne->operator[](ship)->InEshelon(hero->GetHeroEshelon()))
		{
			//если пролетел героя, то не стреляет
			if (fleet_AlienOne->operator[](ship)->GetCenter().x <
				hero->GetCenter().x) continue;
			
			//алиен делает выстрел
			firstfleetStoreLaser->Push(new FirstFleetAlienLaser {
				textureStore->operator[](enumTextureType::lasersPack),
				*fleet_AlienOne->operator[](ship)->GetLaserStart()});

			//запрещаем делать выстрел алиену до следующего раза
			static_cast<Alien_one*>(fleet_AlienOne->
				operator[](ship))->ThisAlienCantShoot();
		}
	}
}
