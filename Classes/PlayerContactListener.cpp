#pragma once
#include "PlayerContactListener.h"
#include "box2d/b2dSprite.h"
#include "Player.h"

void PlayerContactListener::BeginContact(b2Contact* contact) {
	b2Sprite* SpriteA;
	b2Sprite* SpriteB;

	if (contact->GetFixtureA()->GetBody()->GetUserData() != NULL &&
		contact->GetFixtureB()->GetBody()->GetUserData() != NULL) {
		SpriteA = static_cast<b2Sprite*>(contact->GetFixtureA()->GetBody()->GetUserData());
		SpriteB = static_cast<b2Sprite*>(contact->GetFixtureB()->GetBody()->GetUserData());

		auto spriteAName = SpriteA->getName();
		auto spriteBName = SpriteB->getName();

		if (spriteAName != "platform" && spriteBName != "platform") {
			CCLOG("%s CONTACT WITH %s \n", spriteAName.c_str(), spriteBName.c_str());
			SpriteA->setOnRemove();
			SpriteB->setOnRemove();
		}
	}
}

void PlayerContactListener::EndContact(b2Contact* contact) {
}

void PlayerContactListener::PreSolve(b2Contact* contact, const b2Manifold* oldManifold) {
}

void PlayerContactListener::PostSolve(b2Contact* contact, const b2ContactImpulse* impulse) {
}
