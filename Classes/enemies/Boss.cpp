#pragma once
#include "external/json/document.h"
#include "Boss.h"
#include "IdleBehaviour.h"
#include "IShootingPattern.h"
#include "MainMenu.h"
#include "MainScene.h"
#include "MeleeCharacter.h"

Boss::Boss() : 
	IEnemy(new BossIdleBehaviour) {
	init();
	_bulletDamage = _damage;
	meleeInit();
}
Boss::~Boss() {
	
}

void Boss::setOnRemove() {
	getWorldNode()->setOnRemoveList(this);
	cleanHit();
	if (_hp <= 0) {
		getWorldNode()->setOnRemoveList(this);
		//static_cast<MainScene*>(Director::getInstance()->getRunningScene())->cleanAll();
		auto scene = WinScene::create();
		Director::getInstance()->replaceScene(scene);
	}
}

Boss* Boss::create(Node* node, Vec2 pos, IEnemyBehaviour* behaviour) {
	Boss* bossObj = new (std::nothrow) Boss();
	if (bossObj && bossObj->initWithFile(bossObj->_fileName)) {
		bossObj->initBody(b2BodyType::b2_dynamicBody, 1, 0);
		bossObj->autorelease();
		b2Filter filt;
		filt.categoryBits = static_cast<uint16>(eColCategory::enemy);
		filt.maskBits = static_cast<uint16>(eColMask::enemy);
		bossObj->getFixtureDef()->filter = filt;
		node->addChild(bossObj);
		bossObj->getBody()->SetFixedRotation(true);
		bossObj->setPosition(pos);
		bossObj->createHpLabel();
		bossObj->_behaviour->perform(bossObj, Vec2(0, 0), 0.f);
		return bossObj;
	}
	CC_SAFE_DELETE(bossObj);
	return nullptr;
}

bool Boss::init() {
	if (!b2Sprite::init()) {
		return false;
	}
	_type = "Boss";
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

		if (initFile.HasMember(_type.c_str())) {
			const rapidjson::Value& ent = initFile[_type.c_str()];
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

					const rapidjson::Value& filter = valueEnt["filter"];
					auto tempFilter = filter.GetString();

					const rapidjson::Value& shootingPattern = valueEnt["shootingPattern"];
					auto shootingPatternInfo = shootingPattern.GetString();
					setShootingPattern(shootingPatternInfo);

					const rapidjson::Value& agressivezone = valueEnt["agressiveZone"];
					_agressiveZone = agressivezone.GetInt();
				}
			}
			if (ent.HasMember("components")) {
				const rapidjson::Value& compEnt = ent["components"];
				if (compEnt.HasMember("textureFile")) {
					const rapidjson::Value& fileName = compEnt["textureFile"];
					_fileName = fileName.GetString();

					const rapidjson::Value& animIdleFile = compEnt["animIdleFile"];
					_animationIdleFile = animIdleFile.GetString();

					const rapidjson::Value& animMoveFile = compEnt["animMoveFile"];
					_animationMoveFile = animMoveFile.GetString();

					const rapidjson::Value& animAttackFile = compEnt["animAttackFile"];
					_animationAttackFile = animAttackFile.GetString();
				}
			}
		}

		bRet = true;

	} while (!bRet);

	setDamaged(false);
	setDestroyed(false);
	setAgressive(false);
	setIdleBehaviour();
	if (!_behaviour) {
		return false;
	}

	//Idle animation
	if (_fileName != "") {
		_idleAnimFrames.reserve(1);
		_idleAnimFrames.pushBack(SpriteFrame::create(_fileName, Rect(0, 0, 510, 214)));
	}
	//Attack animation
	if (_fileName != "") {
		_attackAnimFrames.reserve(1);
		_attackAnimFrames.pushBack(SpriteFrame::create(_fileName, Rect(0, 0, 510, 214)));
	}
	//Move animation
	if (_fileName != "") {
		_moveAnimFrames.reserve(1);
		_moveAnimFrames.pushBack(SpriteFrame::create(_fileName, Rect(0, 0, 510, 214)));
	}

	return true;
}

void Boss::shoot(Vec2 targetPos, IBulletTypeCreator* bulletCreator) {
	if (_attackCooldown <= 0) {
		_attackCooldown = ENEMY_ATTACK_COOLDOWN;
		Vec2 pos = getPosition();
		Vec2 dest = targetPos - pos;
		dest.normalize();
		dest *= _bulletSpeed;

		_shootingPattern->shoot(pos, dest, bulletCreator);
	}
}

void Boss::meleeInit() {
	_hitTime = 5;
	MeleeCharacter::_damage = 2;
}

void Boss::hit() {
	if (_meleeHit == nullptr) {
		_isMeleeAttack = true;
		MeleeCharacter::_time = 0;
		_meleeHit = MeleeHit::create(_damage);
		b2Filter filter;
		filter.categoryBits = static_cast<int>(eColCategory::enemyMelee);
		filter.maskBits = static_cast<int>(eColMask::enemyMelee);
		_meleeHit->getFixtureDef()->filter = filter;
		getParent()->addChild(_meleeHit);
		
		_meleeHit->setScaleX(_meleeHit->getScaleX() * -1);
		_meleeHit->setScaleX(_meleeHit->getScaleX() * -1);
		_meleeHit->setPosition(getPositionX() - /*510*3*/ - 64, getPositionY());
		if (getScaleX() > 0) {
			_meleeHit->setScaleX(getScaleX() * -1);
			_meleeHit->setPosition(getPositionX() - getContentSize().width, getPositionY());
		}
	}
}

void Boss::update(float dt) {
	/*if (_meleeHit != nullptr) {
		_meleeHit->setPosition(_meleeHit->getPosition().x - 64, _meleeHit->getPosition().y);
	}*/
	if (isAgressive() && getBehaviour()->getBehaviourName().substr(0, 9) != "Agressive") {
		setAgressiveBehaviour();
	}
	else if (!isAgressive() && getBehaviour()->getBehaviourName().substr(0, 9) == "Agressive") {
		setIdleBehaviour();
	}
	_behaviour->perform(this, _shootTarget, dt);
	checkAgressive();
	shootingCharacterUpdate(dt);
	meleeUpdate(dt);
	updateHpLabel();
	_attackCooldown -= dt;
}

void Boss::meleeUpdate(float dt) {
	MeleeCharacter::update(dt);
	if (_meleeHit) {
		_meleeHit->setPosition(getPosition().x - getContentSize().width/2, getPosition().y - 32);
		if (getScaleX() < 0) {
			_meleeHit->setScaleX(_meleeHit->getScaleX() * -1);
			_meleeHit->setPosition(getPosition().x + getContentSize().width/2, getPosition().y + 32);
		}
	}
}
