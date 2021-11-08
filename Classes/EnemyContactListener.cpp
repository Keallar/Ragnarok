#include "EnemyContactListener.h"
#include "box2d/b2dSprite.h"
#include "IEnemy.h"

void EnemyContactListener::BeginContact(b2Contact* contact) {
	if (contact->GetFixtureA()->GetBody()->GetUserData() != NULL &&
		contact->GetFixtureB()->GetBody()->GetUserData() != NULL) {
		auto SpriteA = static_cast<b2Sprite*>(contact->GetFixtureA()->GetBody()->GetUserData());
		auto SpriteB = static_cast<b2Sprite*>(contact->GetFixtureB()->GetBody()->GetUserData());
		if (SpriteA->getFixtureDef()->filter.maskBits == static_cast<uint16>(eColMask::enemy) &&
			SpriteB->getFixtureDef()->filter.maskBits == static_cast<uint16>(eColMask::playerBullet)) {
			auto enemy = static_cast<IEnemy*>(SpriteA);
			enemy->changeHp(-100);
			auto curEnemyHp = enemy->getHp();
			if (curEnemyHp <= 0) {
				enemy->setDestroyed(true);
				SpriteA->setOnRemove();
			}
		}
	}
}

void EnemyContactListener::EndContact(b2Contact* contact) {
}

void EnemyContactListener::PreSolve(b2Contact* contact, const b2Manifold* oldManifold) {
	/*if (contact->GetFixtureA()->GetBody()->GetUserData() != NULL) {
		contact->SetEnabled(false);
	}
	if (contact->GetFixtureB()->GetBody()->GetUserData() != NULL) {
		contact->SetEnabled(false);
	}*/
}

void EnemyContactListener::PostSolve(b2Contact* contact, const b2ContactImpulse* impulse) {
}
