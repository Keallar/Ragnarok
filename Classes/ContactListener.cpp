#include "ContactListener.h"
#include "box2d/b2dSprite.h"

void ContactListener::BeginContact(b2Contact* contact) {

	b2Sprite* SpriteA; 
	b2Sprite* SpriteB;

	if (contact->GetFixtureA()->GetBody()->GetUserData() != NULL && contact->GetFixtureB()->GetBody()->GetUserData() != NULL) {
		SpriteA = static_cast<b2Sprite*>(contact->GetFixtureA()->GetBody()->GetUserData());

		SpriteB = static_cast<b2Sprite*>(contact->GetFixtureB()->GetBody()->GetUserData());

		if (SpriteA->getName() == "somePlayer" && SpriteB->getName() == "somePlayer") {
			SpriteA->setOnRemove();
			SpriteB->setOnRemove();
		}
	}
}