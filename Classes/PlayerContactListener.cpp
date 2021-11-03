#pragma once
#include "PlayerContactListener.h"
#include "box2d/b2dSprite.h"
#include "Player.h"

void PlayerContactListener::BeginContact(b2Contact* contact) {
	if (contact->GetFixtureA()->GetBody()->GetUserData() != NULL &&
		contact->GetFixtureB()->GetBody()->GetUserData() != NULL) {
		auto SpriteA = static_cast<b2Sprite*>(contact->GetFixtureA()->GetBody()->GetUserData());
		auto SpriteB = static_cast<b2Sprite*>(contact->GetFixtureB()->GetBody()->GetUserData());
		auto spriteAName = SpriteA->getName();
		auto spriteBName = SpriteB->getName();

		if (spriteAName == "platform" || spriteBName == "platform") {
			return;
		}
		if (spriteAName == "player" && spriteBName.find("simpleEnemy") == 0) {
			CCLOG("%s CONTACT WITH %s \n", spriteAName.c_str(), spriteBName.c_str());
			SpriteB->setOnRemove();
		}
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
