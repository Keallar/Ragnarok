#include "EnemyContactListener.h"
#include "box2d/b2dSprite.h"
#include "IEnemy.h"

void EnemyContactListener::BeginContact(b2Contact* contact) {

	b2Sprite* SpriteA; 
	b2Sprite* SpriteB;

	if (contact->GetFixtureA()->GetBody()->GetUserData() != NULL && 
			contact->GetFixtureB()->GetBody()->GetUserData() != NULL) {
		SpriteA = static_cast<b2Sprite*>(contact->GetFixtureA()->GetBody()->GetUserData());
		SpriteB = static_cast<b2Sprite*>(contact->GetFixtureB()->GetBody()->GetUserData());

		auto spriteAName = SpriteA->getName();
		auto spriteBName = SpriteB->getName();

		//UNDONE 
		//Удаление через имена пока не лучшая идея
		if (spriteAName != "platform" && spriteBName != "platform" &&
				spriteAName != "player" && spriteBName != "player") {
			CCLOG("%s CONTACT WITH %s \n", spriteAName.c_str(), spriteBName.c_str());
			SpriteA->setOnRemove();
			SpriteB->setOnRemove();
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
