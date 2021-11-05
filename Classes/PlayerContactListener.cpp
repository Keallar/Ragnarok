#pragma once
#include "PlayerContactListener.h"
#include "box2d/b2dSprite.h"
#include "Player.h"

void PlayerContactListener::BeginContact(b2Contact* contact) {
	if (contact->GetFixtureA()->GetBody()->GetUserData() != NULL &&
		contact->GetFixtureB()->GetBody()->GetUserData() != NULL) {
		auto SpriteA = static_cast<b2Sprite*>(contact->GetFixtureA()->GetBody()->GetUserData());
		auto SpriteB = static_cast<b2Sprite*>(contact->GetFixtureB()->GetBody()->GetUserData());
	}
}

void PlayerContactListener::EndContact(b2Contact* contact) {
}

void PlayerContactListener::PreSolve(b2Contact* contact, const b2Manifold* oldManifold) {
	//Test
	/*if (contact->GetFixtureA()->GetBody()->GetUserData() != NULL) {
		auto SpriteA = static_cast<b2Sprite*>(contact->GetFixtureA()->GetBody()->GetUserData());
		auto spriteAName = SpriteA->getName();
		if (spriteAName == "player") {
			contact->SetEnabled(false);
		}
	}*/
	/*if (contact->GetFixtureB()->GetBody()->GetUserData() != NULL) {
		auto SpriteB = static_cast<b2Sprite*>(contact->GetFixtureB()->GetBody()->GetUserData());
		auto spriteBName = SpriteB->getName();
		if (spriteBName == "player") {
			contact->SetEnabled(false);
		}
	}*/
}

void PlayerContactListener::PostSolve(b2Contact* contact, const b2ContactImpulse* impulse) {
}
