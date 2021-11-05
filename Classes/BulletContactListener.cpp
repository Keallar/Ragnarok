#include "BulletContactListener.h"
#include "box2d/b2dSprite.h"

void BulletContactListener::BeginContact(b2Contact* contact) {
	if (contact->GetFixtureA()->GetBody()->GetUserData() != NULL &&
		contact->GetFixtureB()->GetBody()->GetUserData() != NULL) {
		auto SpriteA = static_cast<b2Sprite*>(contact->GetFixtureA()->GetBody()->GetUserData());
		auto SpriteB = static_cast<b2Sprite*>(contact->GetFixtureB()->GetBody()->GetUserData());
		if (SpriteA->getFixtureDef()->filter.maskBits == static_cast<uint16>(eColMask::playerBullet) &&
			SpriteB->getFixtureDef()->filter.maskBits == static_cast<uint16>(eColMask::enemy)) {
			SpriteA->setOnRemove();
		}
	}
}

void BulletContactListener::EndContact(b2Contact* contact) {
}

void BulletContactListener::PreSolve(b2Contact* contact, const b2Manifold* oldManifold) {
}

void BulletContactListener::PostSolve(b2Contact* contact, const b2ContactImpulse* impulse) {
}
