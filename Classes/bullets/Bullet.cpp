#include "Bullet.h"
#include "external/json/document.h"

std::map<std::string, BulletVars> Bullet::_bulletsProp;

float Bullet::BULLET_MOVE_TIME = 2.0f;
float Bullet::BIG_BULLET_MOVE_TIME = 2.0f;
float Bullet::HOOK_BULLET_MOVE_TIME = 2;
float Bullet::HOOK_BULLET_LIFE_TIME = 7.0f;
float Bullet::ICE_BULLET_MOVE_TIME = 0.5f;
float Bullet::FIRE_BULLET_MOVE_TIME = 2.0f;


int Bullet::BULLET_DAMAGE = 100;
int Bullet::BIG_BULLET_DAMAGE = 150;


Bullet::Bullet() {
	b2Sprite::init();
}

Bullet::~Bullet() {

}

Bullet* Bullet::create(cocos2d::Node* world, Vec2 pos, Vec2 dest, b2Filter filter) {
	Bullet* bullet = new (std::nothrow) Bullet();
	bullet->init();
	if (bullet && bullet->initWithFile(bullet->_fileName)) {
		bullet->initBody(b2BodyType::b2_dynamicBody, 0.f, 0);
		bullet->autorelease();
		//bullet->init();
		bullet->setCoords(pos, dest);
		bullet->getFixtureDef()->filter = filter;
		bullet->ordinaryOptions(world, pos);
		return bullet;
	}
	CC_SAFE_DELETE(bullet);
	return nullptr;
}


bool Bullet::loadJson() {
	rapidjson::Document initFile;
	bool bRet = false;
	ssize_t size = 0;
	unsigned char* pBytes = NULL;
	do {
		pBytes = cocos2d::CCFileUtils::sharedFileUtils()->getFileData("nodeProperties/bullets.json", "r", &size);
		CC_BREAK_IF(pBytes == NULL || strcmp((char*)pBytes, "") == 0);
		std::string load_str((const char*)pBytes, size);
		CC_SAFE_DELETE_ARRAY(pBytes);
		initFile.Parse<0>(load_str.c_str());
		CC_BREAK_IF(initFile.HasParseError());

		if (!initFile.IsObject())
			return false;
		
		auto func = [&](std::string type) {
			BulletVars Vars;
			const rapidjson::Value& ent = initFile[type.c_str()];
			if (ent.HasMember("name")) {
				const rapidjson::Value& name = ent["name"];
				Vars.name = name.GetString();
			}
			if (ent.HasMember("specifications")) {
				const rapidjson::Value& valueEnt = ent["specifications"];
				if (valueEnt.HasMember("damage") && valueEnt.HasMember("lifeTime") && valueEnt.HasMember("moveTime")) {

					const rapidjson::Value& damage = valueEnt["damage"];
					Vars.damage = damage.GetInt();

					const rapidjson::Value& lifeTime = valueEnt["lifeTime"];
					Vars.lifeTime = lifeTime.GetDouble();

					const rapidjson::Value& moveTime = valueEnt["moveTime"];
					Vars.moveTime = moveTime.GetDouble();
				}
			}
			if (ent.HasMember("components")) {
				const rapidjson::Value& compEnt = ent["components"];
				if (compEnt.HasMember("textureFile")) {
					const rapidjson::Value& fileName = compEnt["textureFile"];
					Vars.fileName = fileName.GetString();
				}
			}
			_bulletsProp[type] = Vars;
		};

		func("Bullet");
		func("BigBullet");
		func("PlayerHookBullet");
		func("FireBullet");
		func("IceBullet");
		func("FireBlast");
		func("IceBlast");

		bRet = true;

	} while (!bRet);
}

bool Bullet::init() {
	setCoords(Vec2{ 0, 0 }, Vec2{ 0, 0 });

	//_moveTime = BULLET_MOVE_TIME;
	//_lifeTime = BULLET_MOVE_TIME;

	//if (_bulletsProp.size() == 0) {
	//	loadJson();
	//}

	initVars("Bullet");

	_isOnRemove = false;
	_startedMove = false;
	return true;
}

void Bullet::initVars(std::string type) {
	_moveTime = _bulletsProp[type].moveTime;
	_lifeTime = _bulletsProp[type].lifeTime;
	_damage = _bulletsProp[type].damage;
	_fileName = _bulletsProp[type].fileName;
}

void Bullet::update(float dt) {
	_moveTime -= dt;
	_lifeTime -= dt;
	move(dt);
	if (_moveTime <= 0 && getBody()->GetLinearVelocity() != b2Vec2(0, 0)) {
		getBody()->SetLinearVelocity(b2Vec2( 0, 0 ));
	}
	if (_lifeTime <= 0 && _isOnRemove != true) {
		setOnRemove();
	}
}

void Bullet::ordinaryOptions(cocos2d::Node* world, Vec2 pos) {
	world->addChild(this);
	this->setPosition(pos);
	this->getBody()->SetGravityScale(0);
}

void Bullet::setCoords(Vec2 pos, Vec2 dest) {
	_pos = pos;
	_dest = dest;
}

float Bullet::getMoveTime() {
	return _moveTime;
}

float Bullet::getLifeTime() {
	return _lifeTime;
}

void Bullet::setOnRemove() {
	_isOnRemove = true;
	b2Filter filter;
	filter.categoryBits = 0;
	filter.maskBits = 0;
	getBody()->GetFixtureList()->SetFilterData(filter);
}

bool Bullet::isRemoving() {
 	return _isOnRemove;
}

void Bullet::collideFunc() {
	setOnRemove();
}

int Bullet::getDamage() {
	return BULLET_DAMAGE;
}

void Bullet::move(float dt) {
	if (!_startedMove) {
		getBody()->SetLinearVelocity(b2Vec2(getDest().x, getDest().y));
		//_parent->setPosition(Vec2(_parent->getDest().x, _parent->getDest().y));
	}
	_startedMove = true;
}

Vec2 Bullet::getDest() {
	return _dest;
}

void Bullet::draw(Renderer* renderer, const Mat4& transform, uint32_t flags) {
	if (!_isOnRemove) {
		b2Sprite::draw(renderer, transform, flags);
	}
}