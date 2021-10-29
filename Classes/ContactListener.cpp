#include "ContactListener.h"
#include "box2d/b2dSprite.h"

void ContactListener::BeginContact(b2Contact* contact) {

	b2Sprite* SpriteA; 
	b2Sprite* SpriteB;

	if (contact->GetFixtureA()->GetBody()->GetUserData() != NULL && contact->GetFixtureB()->GetBody()->GetUserData() != NULL) {
		SpriteA = static_cast<b2Sprite*>(contact->GetFixtureA()->GetBody()->GetUserData());

		SpriteB = static_cast<b2Sprite*>(contact->GetFixtureB()->GetBody()->GetUserData());

		auto spriteAName = SpriteA->getName();
		auto spriteBName = SpriteB->getName();

		if (/*spriteAName != spriteBName &&*/ spriteAName != "platform" && spriteBName != "platform") {
			SpriteA->setOnRemove();
			SpriteB->setOnRemove();
		}
	}
}

void ContactListener::EndContact(b2Contact* contact) {
}

void ContactListener::PreSolve(b2Contact* contact, const b2Manifold* oldManifold) {
}

void ContactListener::PostSolve(b2Contact* contact, const b2ContactImpulse* impulse) {
}
