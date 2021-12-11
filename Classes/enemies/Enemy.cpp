#pragma once
#include "Enemy.h"
#include "external/json/document.h"

USING_NS_CC;

int Enemy::id = -1;

Enemy::Enemy(std::string type, IEnemyBehaviour* behaviour)
	: IEnemy(behaviour) {
	init(type);
}

Enemy::~Enemy() {
}

Enemy* Enemy::create(Node* node, Vec2 pos, std::string type, IEnemyBehaviour* behaviour) {
	id++;
	Enemy* enemyObj = new (std::nothrow) Enemy(type, behaviour);
	if (enemyObj && enemyObj->initWithFile(enemyObj->_fileName)) {
		enemyObj->initBody(b2BodyType::b2_dynamicBody, 1, 0);
		enemyObj->autorelease();
		b2Filter filt;
		filt.categoryBits = static_cast<uint16>(eColCategory::enemy);
		filt.maskBits = static_cast<uint16>(eColMask::enemy);
		enemyObj->getFixtureDef()->filter = filt;
		enemyObj->setName(enemyObj->getName() + std::to_string(id));
		node->addChild(enemyObj);
		enemyObj->getBody()->SetFixedRotation(true);
		enemyObj->setPosition(pos);
		enemyObj->createHpLabel();
		behaviour->perform(enemyObj, Vec2( 0, 0 ), 0.f);
		return enemyObj;
	}
	CC_SAFE_DELETE(enemyObj);
	return nullptr;
}

bool Enemy::init(std::string type) {
	if (!b2Sprite::init()) {
		return false;
	}
	if (!_behaviour) {
		return false;
	}
	//Json init
	rapidjson::Document initFile;
	bool bRet = false;
	ssize_t size = 0;
	unsigned char* pBytes = NULL;
	do {
		pBytes = cocos2d::CCFileUtils::sharedFileUtils()->getFileData("nodeProperties/enemies.json", "r", &size);
		CC_BREAK_IF(pBytes == NULL || strcmp((char*)pBytes, "") == 0);
		std::string load_str((const char*)pBytes, size);
		CC_SAFE_DELETE_ARRAY(pBytes);
		initFile.Parse<0>(load_str.c_str());
		CC_BREAK_IF(initFile.HasParseError());

		if (!initFile.IsObject())
			return false;

		if (initFile.HasMember(type.c_str())) {
			const rapidjson::Value& ent = initFile[type.c_str()];
			if (ent.HasMember("name")) {
				const rapidjson::Value& name = ent["name"];
				setName(name.GetString());
			}
			if (ent.HasMember("specifications")) {
				const rapidjson::Value& valueEnt = ent["specifications"];
				if (valueEnt.HasMember("hp") /*and another specs*/) {
					const rapidjson::Value& hp = valueEnt["hp"];
					setHp(hp.GetInt());

					const rapidjson::Value& speed = valueEnt["speed"];
					setSpeed(speed.GetDouble());

					const rapidjson::Value& damage = valueEnt["damage"];
					setDamage(damage.GetInt());

					const rapidjson::Value& attackCooldown = valueEnt["attackCooldown"];
					_attackCooldown = attackCooldown.GetDouble();

					const rapidjson::Value& bulletSpeed = valueEnt["bulletSpeed"];
					_bulletSpeed = bulletSpeed.GetInt();
				}
			}
			if (ent.HasMember("components")) {
				const rapidjson::Value& compEnt = ent["components"];
				if (compEnt.HasMember("textureFile") && compEnt.HasMember("animationFile")) {
					const rapidjson::Value& fileName = compEnt["textureFile"];
					_fileName = fileName.GetString();

					const rapidjson::Value& animationFile = compEnt["animationFile"];
					_animationFile = animationFile.GetString();
				}
			}
		}

		bRet = true;

	} while (!bRet);

	setDamaged(false);
	setDestroyed(false);
	setAgressive(false);

	if (_animationFile != "") {
		//Idle animation
		_idleAnimFrames.reserve(4);
		_idleAnimFrames.pushBack(SpriteFrame::create(_animationFile, Rect(0, 0, 64, 64)));
		_idleAnimFrames.pushBack(SpriteFrame::create(_animationFile, Rect(64, 0, 64, 64)));
		_idleAnimFrames.pushBack(SpriteFrame::create(_animationFile, Rect(128, 0, 64, 64)));
		_idleAnimFrames.pushBack(SpriteFrame::create(_animationFile, Rect(192, 0, 64, 64)));
		//Move right animation 
		_moveRightAnimFrames.reserve(4);
		_moveRightAnimFrames.pushBack(SpriteFrame::create(_animationFile, Rect(0, 128, 64, 64)));
		_moveRightAnimFrames.pushBack(SpriteFrame::create(_animationFile, Rect(64, 128, 64, 64)));
		_moveRightAnimFrames.pushBack(SpriteFrame::create(_animationFile, Rect(128, 128, 64, 64)));
		_moveRightAnimFrames.pushBack(SpriteFrame::create(_animationFile, Rect(192, 128, 64, 64)));
		//Move left animation
		_moveLeftAnimFrames.reserve(4);
		_moveLeftAnimFrames.pushBack(SpriteFrame::create(_animationFile, Rect(0, 192, 64, 64)));
		_moveLeftAnimFrames.pushBack(SpriteFrame::create(_animationFile, Rect(64, 192, 64, 64)));
		_moveLeftAnimFrames.pushBack(SpriteFrame::create(_animationFile, Rect(128, 192, 64, 64)));
		_moveLeftAnimFrames.pushBack(SpriteFrame::create(_animationFile, Rect(192, 192, 64, 64)));
	}

	return true;
}
