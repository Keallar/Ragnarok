#include "ContactListener.h"
#include "box2d/b2dSprite.h"
#include "IEnemy.h"
#include "Player.h"

void ContactListener::BeginContact(b2Contact* contact) {
	if (contact->GetFixtureA()->GetBody()->GetUserData() != NULL &&
		contact->GetFixtureB()->GetBody()->GetUserData() != NULL) {
		auto SpriteA = static_cast<b2Sprite*>(contact->GetFixtureA()->GetBody()->GetUserData());
		auto SpriteB = static_cast<b2Sprite*>(contact->GetFixtureB()->GetBody()->GetUserData());
		//Enemy
		if (SpriteA->getFixtureDef()->filter.maskBits == static_cast<uint16>(eColMask::enemy) &&
			SpriteB->getFixtureDef()->filter.maskBits == static_cast<uint16>(eColMask::playerBullet)) {
			auto enemy = static_cast<IEnemy*>(SpriteA);
			enemy->changeHp(-100);
			const auto curEnemyHp = enemy->getHp();
			if (curEnemyHp <= 0 && enemy->isDestroyed() == false) {
				enemy->setDestroyed(true);
				//SpriteA->setOnRemove();
			}
		} //Player
		else if (SpriteA->getFixtureDef()->filter.maskBits == static_cast<uint16>(eColMask::player) &&
			SpriteB->getFixtureDef()->filter.maskBits == static_cast<uint16>(eColMask::enemy)) {
			auto player = static_cast<Player*>(SpriteA);
			player->changeHp(-1);
		}
	}
}

void ContactListener::EndContact(b2Contact* contact) {
}

void ContactListener::PreSolve(b2Contact* contact, const b2Manifold* oldManifold) {
	/*if (contact->GetFixtureA()->GetBody()->GetUserData() != NULL) {
		contact->SetEnabled(false);
	}
	if (contact->GetFixtureB()->GetBody()->GetUserData() != NULL) {
		contact->SetEnabled(false);
	}*/
}

void ContactListener::PostSolve(b2Contact* contact, const b2ContactImpulse* impulse) {
}