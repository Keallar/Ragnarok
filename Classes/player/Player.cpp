#include "Player.h"
#include "box2d/b2dRootWorldNode.h"
#include "external/json/document.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Player::Player() {
	init();
}

Player::~Player() {
}

Player* Player::create() {
	Player* playerObj = new (std::nothrow) Player();
	if (playerObj && playerObj->initWithFile("images/Tur_64.png")) {
		playerObj->initBody(b2BodyType::b2_dynamicBody, 0.03f, 0.01f);
		playerObj->autorelease();
		b2Filter filt;
		filt.categoryBits = static_cast<uint16>(eColCategory::player);
		filt.maskBits = static_cast<uint16>(eColMask::player);
		//filter.groupIndex = -1;
		playerObj->getFixtureDef()->filter = filt;
		playerObj->setName("Player");
		playerObj->setPlayerBody();
		return playerObj;
	}
	CC_SAFE_DELETE(playerObj);
	return nullptr;
}

bool Player::init() {
	if (!b2Sprite::init()) {
		return false;
	}
	//Json init
	rapidjson::Document initFile;
	bool bRet = false;
	ssize_t size = 0;
	unsigned char* pBytes = NULL;
	do {
		pBytes = cocos2d::CCFileUtils::sharedFileUtils()->getFileData("nodeProperties/player.json", "r", &size);
		CC_BREAK_IF(pBytes == NULL || strcmp((char*)pBytes, "") == 0);
		std::string load_str((const char*)pBytes, size);
		CC_SAFE_DELETE_ARRAY(pBytes);
		initFile.Parse<0>(load_str.c_str());
		CC_BREAK_IF(initFile.HasParseError());

		if (!initFile.IsObject())
			return false;

		if (initFile.HasMember("player")) {
			const rapidjson::Value& playerEnt = initFile["player"];
			if (playerEnt.HasMember("specifications")) {
				const rapidjson::Value& valueEnt = playerEnt["specifications"];
				if (valueEnt.HasMember("hp") && valueEnt.HasMember("mana") && valueEnt.HasMember("speed") && valueEnt.HasMember("jumpSpeed")) {
					const rapidjson::Value& hp = valueEnt["hp"];
					_hp = hp.GetInt();

					const rapidjson::Value& mana = valueEnt["mana"];
					_mana = mana.GetInt();

					const rapidjson::Value& speed = valueEnt["speed"];
					_speed = speed.GetDouble();

					const rapidjson::Value& maxSpeed = valueEnt["maxSpeed"];
					_maxSpeed = maxSpeed.GetDouble();

					const rapidjson::Value& jumpSpeed = valueEnt["jumpSpeed"];
					_jumpSpeed = jumpSpeed.GetInt();

					const rapidjson::Value& jumpHeight = valueEnt["jumpHeight"];
					_jumpHeight = jumpHeight.GetInt();

				}
			}
			if (playerEnt.HasMember("components")) {
				const rapidjson::Value& compEnt = playerEnt["components"];
				if (compEnt.HasMember("textureFile")) {
					const rapidjson::Value& fileName = compEnt["textureFile"];
					_fileName = fileName.GetString();

					const rapidjson::Value& idleAnimFile = compEnt["idleAnimFile"];
					_idleAnimFile = idleAnimFile.GetString();

					const rapidjson::Value& attackAnimFile = compEnt["attackAnimFile"];
					_attackAnimFile = attackAnimFile.GetString();

					const rapidjson::Value& jumpAnimFile = compEnt["jumpAnimFile"];
					_jumpAnimFile = jumpAnimFile.GetString();

					const rapidjson::Value& fallAnimFile = compEnt["fallAnimFile"];
					_fallAnimFile = fallAnimFile.GetString();

					const rapidjson::Value& moveAnimFile = compEnt["moveAnimFile"];
					_moveAnimFile = moveAnimFile.GetString();
				}
			}
		}
		bRet = true;

	} while (!bRet);
	//References
	_shootingPattern = new IdleShootingPattern(this);
	_attackCooldown = 0;
	_curSpeed = 0.f;
	_jumpBegin = 0;
	_playerJumpState = eJumpState::None;
	_playerAnimState = eAnimState::None;
	_isDied = false;
	_jumpCount = 0;
	_bulletDamage = 100;
	//Hook
	_hook = nullptr;
	_hookBody = DrawNode::create();
	_hookPattern = new IdleShootingPattern(this);
	addChild(_hookBody);
	//shoot
	_bulletCreator = new IdleBulletCreator(playerPhysMask(), this);

	//Sound effects
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("sounds/Step.mp3");

	//Animation
	//Idle animation
	_idleAnimFrames.reserve(8);
	_idleAnimFrames.pushBack(SpriteFrame::create(_idleAnimFile, Rect(0, 0, 64, 64)));
	_idleAnimFrames.pushBack(SpriteFrame::create(_idleAnimFile, Rect(64, 0, 64, 64)));
	_idleAnimFrames.pushBack(SpriteFrame::create(_idleAnimFile, Rect(128, 0, 64, 64)));
	_idleAnimFrames.pushBack(SpriteFrame::create(_idleAnimFile, Rect(192, 0, 64, 64)));
	_idleAnimFrames.pushBack(SpriteFrame::create(_idleAnimFile, Rect(256, 0, 64, 64)));
	_idleAnimFrames.pushBack(SpriteFrame::create(_idleAnimFile, Rect(320, 0, 64, 64)));
	_idleAnimFrames.pushBack(SpriteFrame::create(_idleAnimFile, Rect(384, 0, 64, 64)));
	_idleAnimFrames.pushBack(SpriteFrame::create(_idleAnimFile, Rect(448, 0, 64, 64)));
	//Start animation
	Animation* idleAnimation = Animation::createWithSpriteFrames(_idleAnimFrames, 0.13f);
	Animate* idleAnim = Animate::create(idleAnimation);
	Action* idleAction = RepeatForever::create(idleAnim);
	idleAction->setTag(static_cast<int>(eAnimState::None));
	runAction(idleAction);
	//Attack animation
	_attackAnimFrames.reserve(1);
	_attackAnimFrames.pushBack(SpriteFrame::create(_attackAnimFile, Rect(0, 0, 64, 64)));
	//Jump animation
	_jumpAnimFrames.reserve(12);
	_jumpAnimFrames.pushBack(SpriteFrame::create(_jumpAnimFile, Rect(0, 0, 64, 64)));
	_jumpAnimFrames.pushBack(SpriteFrame::create(_jumpAnimFile, Rect(64, 0, 64, 64)));
	_jumpAnimFrames.pushBack(SpriteFrame::create(_jumpAnimFile, Rect(128, 0, 64, 64)));
	_jumpAnimFrames.pushBack(SpriteFrame::create(_jumpAnimFile, Rect(192, 0, 64, 64)));
	_jumpAnimFrames.pushBack(SpriteFrame::create(_jumpAnimFile, Rect(256, 0, 64, 64)));
	_jumpAnimFrames.pushBack(SpriteFrame::create(_jumpAnimFile, Rect(320, 0, 64, 64)));
	_jumpAnimFrames.pushBack(SpriteFrame::create(_jumpAnimFile, Rect(0, 64, 64, 64)));
	_jumpAnimFrames.pushBack(SpriteFrame::create(_jumpAnimFile, Rect(64, 64, 64, 64)));
	_jumpAnimFrames.pushBack(SpriteFrame::create(_jumpAnimFile, Rect(128, 64, 64, 64)));
	_jumpAnimFrames.pushBack(SpriteFrame::create(_jumpAnimFile, Rect(192, 64, 64, 64)));
	_jumpAnimFrames.pushBack(SpriteFrame::create(_jumpAnimFile, Rect(256, 64, 64, 64)));
	_jumpAnimFrames.pushBack(SpriteFrame::create(_jumpAnimFile, Rect(320, 64, 64, 64)));
	//Fall animation
	_fallAnimFrames.reserve(4);
	_fallAnimFrames.pushBack(SpriteFrame::create(_fallAnimFile, Rect(0, 128, 64, 64)));
	_fallAnimFrames.pushBack(SpriteFrame::create(_fallAnimFile, Rect(64, 128, 64, 64)));
	_fallAnimFrames.pushBack(SpriteFrame::create(_fallAnimFile, Rect(128, 128, 64, 64)));
	_fallAnimFrames.pushBack(SpriteFrame::create(_fallAnimFile, Rect(192, 128, 64, 64)));
	//Move animation
	_moveAnimFrames.reserve(6);
	_moveAnimFrames.pushBack(SpriteFrame::create(_moveAnimFile, Rect(0, 0, 64, 64)));
	_moveAnimFrames.pushBack(SpriteFrame::create(_moveAnimFile, Rect(64, 0, 64, 64)));
	_moveAnimFrames.pushBack(SpriteFrame::create(_moveAnimFile, Rect(128, 0, 64, 64)));
	_moveAnimFrames.pushBack(SpriteFrame::create(_moveAnimFile, Rect(192, 0, 64, 64)));
	_moveAnimFrames.pushBack(SpriteFrame::create(_moveAnimFile, Rect(256, 0, 64, 64)));
	_moveAnimFrames.pushBack(SpriteFrame::create(_moveAnimFile, Rect(320, 0, 64, 64)));

	meleeInit();

	return true;
}

void Player::restart() {
	_shootingPattern = new IdleShootingPattern(this);
	_attackCooldown = 0;
	_curSpeed = 0.f;
	_jumpBegin = 0;
	_playerJumpState = eJumpState::None;
	_playerAnimState = eAnimState::None;
	_isDied = false;
	_jumpCount = 0;
	//Hook
	_hook = nullptr;
	_hookBody->clear();
	//shoot
	_bulletCreator = new IdleBulletCreator(playerPhysMask(), this);

	rapidjson::Document initFile;

	bool bRet = false;
	ssize_t size = 0;
	unsigned char* pBytes = NULL;
	pBytes = cocos2d::CCFileUtils::sharedFileUtils()->getFileData("nodeProperties/player.json", "r", &size);
	if (pBytes == NULL || strcmp((char*)pBytes, "") == 0) {
		throw("player suck");
	}

	std::string load_str((const char*)pBytes, size);
	CC_SAFE_DELETE_ARRAY(pBytes);

	initFile.Parse<0>(load_str.c_str());
	if (initFile.HasParseError()) {
		throw("player suck");
	}

	if (initFile.IsObject()) {
		if (initFile.HasMember("player")) {
			const rapidjson::Value& playerEnt = initFile["player"];
			if (playerEnt.HasMember("specifications")) {
				const rapidjson::Value& valueEnt = playerEnt["specifications"];
				if (valueEnt.HasMember("hp") && valueEnt.HasMember("mana")) {
					const rapidjson::Value& hp = valueEnt["hp"];
					_hp = hp.GetInt();

					const rapidjson::Value& mana = valueEnt["mana"];
					_mana = mana.GetInt();
				}
			}
		}
	}
}

void Player::meleeInit() {
	_hitTime = 0.2f;
	MeleeCharacter::_damage = 100;
}

void Player::meleeUpdate(float dt) {
	MeleeCharacter::update(dt);
	if (_meleeHit) {
		_meleeHit->setPosition(getPosition().x + 64, getPosition().y);
		if (getScaleX() < 0) {
			_meleeHit->setScaleX(getScaleX());
			_meleeHit->setPosition(getPosition().x - 64, getPosition().y);
		}
	}
}

void Player::update(float dt) {
	shootingCharacterUpdate(dt);
	meleeUpdate(dt);
	move(dt);
	jump(dt);
	if (getJumpState() == eJumpState::None && _curSpeed != 0) {
		setAnimState(eAnimState::Move);
	}
	hookBodyUpdate(dt);
}

void Player::cleanHit() {
	getParent()->removeChild(_meleeHit);
}

void Player::keyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event) {
	if (!_isMeleeAttack) {
		switch (keyCode) {
		case EventKeyboard::KeyCode::KEY_D:
		{
			setAnimState(eAnimState::Move);
			_curSpeed += _speed;
			auto scaleX = getScaleX();
			if (scaleX < 0) {
				scaleX *= -1;
				setScaleX(scaleX);
			}
			//_stepSound = CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sounds/Step.mp3");
			break;
		}
		case EventKeyboard::KeyCode::KEY_A:
		{
			setAnimState(eAnimState::Move);
			_curSpeed += -_speed;
			auto scaleX = getScaleX();
			if (scaleX > 0) {
				scaleX *= -1;
				setScaleX(scaleX);
			}
			//_stepSound = CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sounds/Step.mp3");
			break;
		}
		case EventKeyboard::KeyCode::KEY_SPACE:
		{
			if (getJumpState() == eJumpState::None || _jumpCount != 2) {
				getBody()->SetLinearVelocity({ getBody()->GetLinearVelocity().x, 3 });
				setJumpState(eJumpState::Jump);
				//_jumpCount++;
			}
			if (_hook && _hook->isHooked()) {
				_hook->setOnRemove();
				_hook = nullptr;
				getBody()->SetGravityScale(1);
				getBody()->SetLinearVelocity({ getBody()->GetLinearVelocity().x, 3 });
				setJumpState(eJumpState::Jump);
			}
		}
		case EventKeyboard::KeyCode::KEY_W:
		{
			if (getJumpState() == eJumpState::None || _jumpCount != 2) {
				getBody()->SetLinearVelocity({getBody()->GetLinearVelocity().x, 3});
				setJumpState(eJumpState::Jump);
				_jumpCount++;
			}
			if (_hook && _hook->isHooked()) {
				_hook->setOnRemove();
				_hook = nullptr;
				getBody()->SetGravityScale(1);
				getBody()->SetLinearVelocity({ getBody()->GetLinearVelocity().x, 3 });
				setJumpState(eJumpState::Jump);
			}
			break;
		}
		case EventKeyboard::KeyCode::KEY_R:
			if (_hook && _hook->isHooked()) {
				_hook->setOnRemove();
				_hook = nullptr;
			}
			else {
				if (_hook) {
					_hook->setOnRemove();
				}
				shoot(getPosition() + Vec2(45 * getScaleX(), -45), new HookBulletCreator(playerPhysMask(), this));
				_hook = dynamic_cast<PlayerHookBullet*>(BulletFactory::getInstance()->getLastBullet());
				break;
			}
			break;
		default:
			break;
		}
	}
}

void Player::KeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event) {
	if (!_isMeleeAttack) {
		switch (keyCode) {
		case EventKeyboard::KeyCode::KEY_A:
			_curSpeed -= -_speed;
			setAnimState(eAnimState::None);
			//CocosDenshion::SimpleAudioEngine::getInstance()->stopEffect(_stepSound);
			break;
		case EventKeyboard::KeyCode::KEY_D:
			_curSpeed -= _speed;
			setAnimState(eAnimState::None);
			//CocosDenshion::SimpleAudioEngine::getInstance()->stopEffect(_stepSound);
			break;
		case EventKeyboard::KeyCode::KEY_SPACE:
			setJumpState(eJumpState::Fall);
			break;
		case EventKeyboard::KeyCode::KEY_W:
			setJumpState(eJumpState::Fall);
			break;
		case EventKeyboard::KeyCode::KEY_R:
			break;
		default:
			break;
		}
	}
}

Vec2 Player::clickPosCalculate(EventMouse* mouse) {
	auto click = mouse->getLocation();
	setAnimState(eAnimState::Attack);
	auto director = Director::getInstance();
	Vec2 clickPos = Camera::getDefaultCamera()->getPosition() - Vec2{ director->getVisibleSize() / 2 };
	clickPos += click;
	return clickPos;
}

void Player::mousePressed(cocos2d::Event* event) {
	EventMouse* mouse = dynamic_cast<EventMouse*>(event);

	if (mouse->getMouseButton() == EventMouse::MouseButton::BUTTON_LEFT) {
		//shoot(clickPosCalculate(mouse), _bulletCreator);
		shoot(clickPosCalculate(mouse), _bulletCreator);
		//hit();
		setAnimState(eAnimState::Attack);
	}
	else if (mouse->getMouseButton() == EventMouse::MouseButton::BUTTON_RIGHT) {
		shoot(clickPosCalculate(mouse), new HookBulletCreator(hookPhysMask(), this));
		setAnimState(eAnimState::Attack);
	}
}

void Player::changeBulletCreator(IBulletTypeCreator* bulletCreator) {
	_bulletCreator = bulletCreator;
}

void Player::move(float dt) {
	if (getBody()->GetLinearVelocity().x < _maxSpeed && _curSpeed > 0) {
		getBody()->ApplyLinearImpulseToCenter({ _curSpeed * 120 * dt, 0 }, true);
	}
	else if(getBody()->GetLinearVelocity().x > -_maxSpeed && _curSpeed < 0) {
		getBody()->ApplyLinearImpulseToCenter({ _curSpeed * 120 * dt, 0 }, true);
	}
	else if (_curSpeed == 0) {
		getBody()->SetLinearVelocity({ 0, getBody()->GetLinearVelocity().y });
	}
}

void Player::shoot(Vec2 targetPos, IBulletTypeCreator* bulletCreator) {
	if (_attackCooldown <= 0) {
		_attackCooldown = PLAYER_ATTACK_COOLDOWN;

		Vec2 pos = getPosition();
		Vec2 dest = targetPos - pos;
		dest.normalize();
		dest.y *= -1;

		if (dynamic_cast<HookBulletCreator*>(bulletCreator)) {
			if (_hook) {
				_hook->setOnRemove();
				_hook = nullptr;
			}
			dest *= PLAYER_HOOK_SPEED;
			_hookPattern->shoot(pos, dest, bulletCreator);
			_hook = dynamic_cast<PlayerHookBullet*>(BulletFactory::getInstance()->getLastBullet());
			return;
		}

		dest *= PLAYER_BULLET_SPEED;
		_shootingPattern->shoot(pos, dest, bulletCreator);
	}
}

void Player::jump(float dt) {
	static auto tempPosY = getPositionY();
	auto a = getPositionY() - tempPosY;
	if (getJumpState() == eJumpState::Jump) {
		setAnimState(eAnimState::Jump);
		getBody()->ApplyLinearImpulseToCenter({ 0, _jumpSpeed * 60 * dt }, true);
	}
	if (_jumpBegin == 0 && _jumpCount == 0) {
		setJumpState(eJumpState::None);
	}
	else if (getPosition().y >= _jumpBegin) {
		setJumpState(eJumpState::Fall);
		setAnimState(eAnimState::Fall);
	}
	if (tempPosY == getPositionY()) {
		setJumpState(eJumpState::None);
	}
}

void Player::setJumpState(eJumpState state) {
	if (state == eJumpState::Jump) {
		_jumpBegin = getPosition().y + _jumpHeight;
	}
	if (state == eJumpState::None) {
		_jumpCount = 0;
		_jumpBegin = 0;
	}
	_playerJumpState = state;
}

void Player::hookBodyUpdate(float dt) {
	if (_hook && _hook->getLifeTime() > 0) {
		_hookBody->clear();

		if (_hook->isHooked()) {
			if (_hook->getDest().x / getScaleX() <= 0) {
				setScaleX(getScaleX() * -1);
			}
		}

		Vec2 dest = _hook->getPosition() - getPosition();
		dest.y += getContentSize().width / 2;
		dest.x += getContentSize().height / 2 * getScaleX();
		dest.x *= getScaleX();
		
		_hookBody->drawLine(Vec2(getContentSize() / 2), dest, Color4F::GRAY);

		if (_hook->isHooked()) {
			if (_hook->getDest().x / getScaleX() <= 0) {
				setScaleX(getScaleX() * -1);
			}
			dest.normalize();
			dest.x *= getScaleX();
			dest *= 30; //hooked player fly speed
			b2Vec2 playerVel = { dest.x, dest.y };
			if (_hook->getVelDest() == b2Vec2(0, 0)) {
				_hook->setVelDest(playerVel);
			}
			if (_hook->getPosition().x - getPosition().x < _hook->getContentSize().width*2 &&
				_hook->getPosition().x - getPosition().x > -_hook->getContentSize().width*2 &&
				_hook->getPosition().y - getPosition().y > -_hook->getContentSize().height*2 &&
				_hook->getPosition().y - getPosition().y < _hook->getContentSize().height*2) {
				getBody()->SetLinearVelocity({ 0, 0 });
				getBody()->SetGravityScale(0);
			}
			else {
				getBody()->SetLinearVelocity(playerVel);
			}
		}
		
	}
	else {
		getBody()->SetGravityScale(1);
		_hook = nullptr;
		_hookBody->clear();
	}
}

void Player::setAnimState(eAnimState state) {
	if (state == eAnimState::None) {
		if (!getActionByTag(static_cast<int>(eAnimState::None))) {
			stopAllActions();
			Animation* idleAnimation = Animation::createWithSpriteFrames(_idleAnimFrames, 0.13f);
			Animate* idleAnim = Animate::create(idleAnimation);
			Action* idleAction = RepeatForever::create(idleAnim);
			idleAction->setTag(static_cast<int>(eAnimState::None));
			runAction(idleAction);
		}
	}
	if (state == eAnimState::Move) {
		if (!getActionByTag(static_cast<int>(eAnimState::Move))) {
			stopAllActions();
			Animation* moveAnimation = Animation::createWithSpriteFrames(_moveAnimFrames, 0.13f);
			Animate* moveAnim = Animate::create(moveAnimation);
			Action* moveAction = RepeatForever::create(moveAnim);
			moveAction->setTag(static_cast<int>(eAnimState::Move));
			runAction(moveAction);
		}
	}
	if (state == eAnimState::Jump) {
		stopAllActions();
		Animation* jumpAnimation = Animation::createWithSpriteFrames(_jumpAnimFrames, 0.1f);
		Animate* jumpAnim = Animate::create(jumpAnimation);
		Action* jumpAction = Repeat::create(jumpAnim, 1);
		jumpAction->setTag(static_cast<int>(eAnimState::Jump));
		runAction(jumpAction);
	}
	if (state == eAnimState::Fall) {
		if (!getActionByTag(static_cast<int>(eAnimState::Fall))) {
			stopAllActions();
			Animation* fallAnimation = Animation::createWithSpriteFrames(_fallAnimFrames, 0.13f);
			Animate* fallAnim = Animate::create(fallAnimation);
			Action* fallAction = RepeatForever::create(fallAnim);
			fallAction->setTag(static_cast<int>(eAnimState::Fall));
			runAction(fallAction);
		}
	}
	if (state == eAnimState::Attack) {
		stopAllActions();
		Animation* attackAnimation = Animation::createWithSpriteFrames(_attackAnimFrames);
		Animate* attackAnim = Animate::create(attackAnimation);
		Action* attackAction = Repeat::create(attackAnim, 1);
		attackAction->setTag(static_cast<int>(eAnimState::Attack));
		runAction(attackAction);
		setAnimState(eAnimState::None);
	}
	_playerAnimState = state;
}

void Player::hit() {
	if (_meleeHit == nullptr) {
		_isMeleeAttack = true;
		move(0);
		MeleeCharacter::_time = 0;
		_meleeHit = b2Sprite::create("images/melee.png");
		b2Filter filter;
		filter.categoryBits = static_cast<int>(eColCategory::playerMelee);
		filter.maskBits = static_cast<int>(eColMask::playerMelee);
		_meleeHit->getFixtureDef()->filter = filter;
		getParent()->addChild(_meleeHit);
		_meleeHit->setPosition(getPosition().x + 64, getPosition().y);
		if (getScaleX() < 0) {
			//_meleeHit->setRotation(30);
			_meleeHit->setScaleX(getScaleX());
			_meleeHit->setPosition(getPosition().x - 64, getPosition().y);
		}
	}

}

eAnimState Player::getAnimState() noexcept {
	return _playerAnimState;
}

eJumpState Player::getJumpState() noexcept {
	return _playerJumpState;
}

int Player::getMana() const {
	return _mana;
}

void Player::setMana(int mana) noexcept {
	_mana = mana;
}

void Player::changeMana(int difMana) noexcept {
	if (_mana <= 0) {
		return;
	}
	_mana -= difMana;
}

int Player::getHp() const {
	return _hp;
}

void Player::setHp(int hp) noexcept {
	_hp = hp;
}

void Player::changeHp(float difHp) noexcept {
	if (_hp <= 0) {
		_isDied = true;
		return;
	}
	_hp += difHp;
}

bool Player::isDied() const {
	return _isDied;
}

void Player::setDied(bool state) noexcept {
	_isDied = state;
}

int Player::getJumpCount() const {
	return _jumpCount;
}

float Player::getJumpSpeed() {
	return _jumpSpeed;
}

PlayerSave Player::save() {
	PlayerSave save;
	save.pos = getPosition();
	save.bulletCreator = _bulletCreator;
	save.hp = _hp;
	save.mana = _mana;
	return save;
}

void Player::load(PlayerSave save) {
	setPosition(save.pos);
	_bulletCreator = save.bulletCreator;
	_hp = save.hp;
	_mana = save.mana;
	_isDied = false;
}