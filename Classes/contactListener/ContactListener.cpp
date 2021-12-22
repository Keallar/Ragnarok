#include "ContactListener.h"
#include "box2d/b2dSprite.h"
#include "IEnemy.h"
#include "Player.h"
#include "Trigger.h"
#include "Bullet.h"

#define scp static_cast<Player*>
#define scb static_cast<Bullet*>
#define sce static_cast<IEnemy*>

void ContactListener::BeginContact(b2Contact* contact) {
	if (contact->GetFixtureA()->GetBody()->GetUserData() != NULL &&
		contact->GetFixtureB()->GetBody()->GetUserData() != NULL) {
		auto SpriteA = static_cast<b2Sprite*>(contact->GetFixtureA()->GetBody()->GetUserData());
		auto SpriteB = static_cast<b2Sprite*>(contact->GetFixtureB()->GetBody()->GetUserData());

		auto f = [&]() {
			//Player jump
			if (SpriteA->getFixtureDef()->filter.maskBits == static_cast<uint16>(eColMask::platform) &&
				SpriteB->getFixtureDef()->filter.maskBits == static_cast<uint16>(eColMask::player)) {
				//Check up and botton collision player with platforms for jumping
				const auto playerY2 = SpriteB->getPosition().y;
				const auto platformY2 = SpriteA->getPosition().y;
				if (playerY2 >= platformY2) {
					scp(SpriteB)->setJumpState(eJumpState::None);
					//static_cast<Player*>(SpriteB)->setAnimState(eAnimState::Move);
				}
				const auto playerY = SpriteB->getPosition().y + SpriteA->getTextureRect().getMaxY();
				const auto platformY = SpriteA->getPosition().y - SpriteA->getTextureRect().getMaxY();
				if (playerY >= platformY) {
					scp(SpriteB)->setJumpState(eJumpState::None);
				}
			}
			//Enemy with bullets
			if (SpriteA->getFixtureDef()->filter.maskBits == static_cast<uint16>(eColMask::enemy) &&
				SpriteB->getFixtureDef()->filter.maskBits == static_cast<uint16>(eColMask::playerBullet)) {
				auto enemy = sce(SpriteA);
				auto bullet = scb(SpriteB);
				enemy->setDamaged(true);
				enemy->changeHp(-1 * bullet->getDamage());
			} //Player with bullets
			else if (SpriteA->getFixtureDef()->filter.maskBits == static_cast<uint16>(eColMask::player) &&
				SpriteB->getFixtureDef()->filter.maskBits == static_cast<uint16>(eColMask::enemyBullet)) {
				auto player = scp(SpriteA);
				auto bullet = scb(SpriteB);
				player->changeHp(-1 * bullet->getDamage());
			} //Bullets with platforms
			if (SpriteA->getFixtureDef()->filter.maskBits == static_cast<uint16>(eColMask::playerBullet) ||
				SpriteA->getFixtureDef()->filter.maskBits == static_cast<uint16>(eColMask::enemyBullet) ||
				SpriteA->getFixtureDef()->filter.maskBits == static_cast<uint16>(eColMask::hook)) {
				auto bullet = scb(SpriteA);
				bullet->collideFunc();
			}
			else if (SpriteB->getFixtureDef()->filter.maskBits == static_cast<uint16>(eColMask::playerBullet) ||
				SpriteB->getFixtureDef()->filter.maskBits == static_cast<uint16>(eColMask::enemyBullet) ||
				SpriteB->getFixtureDef()->filter.maskBits == static_cast<uint16>(eColMask::hook)) {
				auto bullet = scb(SpriteB);
				bullet->collideFunc();
			}
			//melee attack player
			if (SpriteA->getFixtureDef()->filter.maskBits == static_cast<uint16>(eColMask::enemy) &&
				SpriteB->getFixtureDef()->filter.maskBits == static_cast<uint16>(eColMask::playerMelee)) {
				auto enemy = sce(SpriteA);
				enemy->setDamaged(true);
				enemy->changeHp(-100);
			}
			//melee attack enemy
			if (SpriteA->getFixtureDef()->filter.maskBits == static_cast<uint16>(eColMask::player) &&
				SpriteB->getFixtureDef()->filter.maskBits == static_cast<uint16>(eColMask::enemyMelee) &&
				SpriteB->getFixtureDef()->filter.categoryBits == static_cast<uint16>(eColCategory::enemyMelee)) {
				auto player = scp(SpriteA);
				auto enemy = sce(SpriteB);
				player->changeHp(-enemy->getMeleeDamage());
			}
		};

		f();

		SpriteB = static_cast<b2Sprite*>(contact->GetFixtureA()->GetBody()->GetUserData());
		SpriteA = static_cast<b2Sprite*>(contact->GetFixtureB()->GetBody()->GetUserData());

		f();
	}
}

void ContactListener::EndContact(b2Contact* contact) {
}

void ContactListener::PreSolve(b2Contact* contact, const b2Manifold* oldManifold) {
	if (contact->GetFixtureA()->GetBody()->GetUserData() != NULL &&
		contact->GetFixtureB()->GetBody()->GetUserData() != NULL) {
		auto SpriteA = static_cast<b2Sprite*>(contact->GetFixtureA()->GetBody()->GetUserData());
		auto SpriteB = static_cast<b2Sprite*>(contact->GetFixtureB()->GetBody()->GetUserData());

		auto f = [&]() {
			if (SpriteA->getFixtureDef()->filter.maskBits == static_cast<uint16>(eColMask::trigger) &&
				SpriteB->getFixtureDef()->filter.maskBits == static_cast<uint16>(eColMask::player)) {
				contact->SetEnabled(false);
				auto trigger = static_cast<Trigger*>(SpriteA);
				if (!trigger->getIsActive()) {
					trigger->onCollision();
				}
			}
		};

		f();

		SpriteB = static_cast<b2Sprite*>(contact->GetFixtureA()->GetBody()->GetUserData());
		SpriteA = static_cast<b2Sprite*>(contact->GetFixtureB()->GetBody()->GetUserData());

		f();
	}
};

void ContactListener::PostSolve(b2Contact* contact, const b2ContactImpulse* impulse) {
}
