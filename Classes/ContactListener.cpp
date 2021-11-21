#include "ContactListener.h"
#include "box2d/b2dSprite.h"
#include "IEnemy.h"
#include "Player.h"

void ContactListener::BeginContact(b2Contact* contact) {
	if (contact->GetFixtureA()->GetBody()->GetUserData() != NULL &&
		contact->GetFixtureB()->GetBody()->GetUserData() != NULL) {
		auto SpriteA = static_cast<b2Sprite*>(contact->GetFixtureA()->GetBody()->GetUserData());
		auto SpriteB = static_cast<b2Sprite*>(contact->GetFixtureB()->GetBody()->GetUserData());
		//Player jump
		if (SpriteA->getFixtureDef()->filter.maskBits == static_cast<uint16>(eColMask::platform) &&
			SpriteB->getFixtureDef()->filter.maskBits == static_cast<uint16>(eColMask::player)) {
			const auto minYPlayer = SpriteB->getTextureRect().getMinY();
			const auto maxYPlatoform = SpriteA->getTextureRect().getMaxY();
			if (minYPlayer <= maxYPlatoform) {
				CCLOG("JUMP!");
			}
		}
		//Enemy with bullets
		if (SpriteA->getFixtureDef()->filter.maskBits == static_cast<uint16>(eColMask::enemy) &&
			SpriteB->getFixtureDef()->filter.maskBits == static_cast<uint16>(eColMask::playerBullet)) {
			auto enemy = dynamic_cast<IEnemy*>(SpriteA);
			enemy->setDamaged(true);
			enemy->changeHp(-100);
		} //Player with bullets
		else if (SpriteA->getFixtureDef()->filter.maskBits == static_cast<uint16>(eColMask::player) &&
			SpriteB->getFixtureDef()->filter.maskBits == static_cast<uint16>(eColMask::enemyBullet)) {
			auto player = dynamic_cast<Player*>(SpriteA);
			player->changeHp(-1);
		} //Bullets with platforms
		if (SpriteA->getFixtureDef()->filter.maskBits == static_cast<uint16>(eColMask::playerBullet) ||
			SpriteA->getFixtureDef()->filter.maskBits == static_cast<uint16>(eColMask::enemyBullet)) {
			auto bullet = dynamic_cast<Bullet*>(SpriteA);
			bullet->setOnRemove();
		}
		else if (SpriteB->getFixtureDef()->filter.maskBits == static_cast<uint16>(eColMask::playerBullet) ||
			SpriteB->getFixtureDef()->filter.maskBits == static_cast<uint16>(eColMask::enemyBullet)) {
			auto bullet = dynamic_cast<Bullet*>(SpriteB);
			bullet->setOnRemove();
		}
	}
}

void ContactListener::EndContact(b2Contact* contact) {
}

void ContactListener::PreSolve(b2Contact* contact, const b2Manifold* oldManifold) {
	
}

void ContactListener::PostSolve(b2Contact* contact, const b2ContactImpulse* impulse) {
}
