#include "b2dSprite.h"
//added struct for user data

#include "b2dRootWorldNode.h"

//		***	INSTANTIATION	***

b2Sprite::b2Sprite()
	:Sprite()
{
	_B2Body = nullptr;
	_B2Fixture = nullptr;
	_parentWorldNode = nullptr;
	//WTF
	//_isDeleting = false;
}

b2Sprite::~b2Sprite()
{


}


bool b2Sprite::init()
{
	initWithTexture(nullptr, Rect::ZERO);
	return true;

}

bool b2Sprite::initBody()
{
	return initBody(GameVars::defaultBody, GameVars::defaultFriction, GameVars::defaultRestitution);

}

bool b2Sprite::initBody(b2BodyType type)
{
	return initBody(type, GameVars::defaultFriction, GameVars::defaultRestitution);

}

bool b2Sprite::initBody(float32 friction, float32 restitution)
{
	return initBody(GameVars::defaultBody, friction, restitution);

}

bool b2Sprite::initBody(b2BodyType type, float32 friction, float32 restitution)
{
	_B2BodyDef.type = type;
	_B2BodyDef.allowSleep = true;
	_B2BodyDef.awake = true;
	_B2FixtureDef.shape = &_B2Shape;
	_B2FixtureDef.density = 1.0f;
	_B2FixtureDef.friction = friction;
	_B2FixtureDef.restitution = restitution;

	return true;
}

void b2Sprite::initWithSprite(Sprite* sprite) 
{
	setTexture(sprite->getTexture());
	setTextureRect(sprite->getTextureRect());
}

b2Sprite* b2Sprite::create()
{
	b2Sprite* sprite = new (std::nothrow) b2Sprite();
	if (sprite && sprite->init())
	{
		sprite->initBody();
		sprite->autorelease();
		return sprite;
	}
	CC_SAFE_DELETE(sprite);
	return nullptr;

}

b2Sprite* b2Sprite::create(const std::string& filename)
{
	b2Sprite *sprite = new (std::nothrow) b2Sprite();
	if (sprite && sprite->initWithFile(filename))
	{
		sprite->initBody();
		sprite->autorelease();
		return sprite;
	}
	CC_SAFE_DELETE(sprite);
	return nullptr;

}

b2Sprite* b2Sprite::create(const std::string& filename, b2BodyType type)
{
	b2Sprite *sprite = new (std::nothrow) b2Sprite();
	if (sprite && sprite->initWithFile(filename))
	{
		sprite->initBody(type);
		sprite->autorelease();
		return sprite;
	}
	CC_SAFE_DELETE(sprite);
	return nullptr;

}

b2Sprite* b2Sprite::create(const std::string& filename, b2BodyType type, float32 friction, float32 restitution)
{
	b2Sprite *sprite = new (std::nothrow) b2Sprite();
	if (sprite && sprite->initWithFile(filename))
	{
		sprite->initBody(type, friction, restitution);
		sprite->autorelease();
		return sprite;
	}
	CC_SAFE_DELETE(sprite);
	return nullptr;

}

b2Sprite* b2Sprite::create(const std::string& filename, const Rect& rect)
{
	b2Sprite *sprite = new (std::nothrow) b2Sprite();
	if (sprite && sprite->initWithFile(filename, rect))
	{
		sprite->initBody();
		sprite->autorelease();
		return sprite;
	}
	CC_SAFE_DELETE(sprite);
	return nullptr;

}

b2Sprite* b2Sprite::create(const std::string& filename, const Rect& rect, b2BodyType type)
{
	b2Sprite *sprite = new (std::nothrow) b2Sprite();
	if (sprite && sprite->initWithFile(filename, rect))
	{
		sprite->initBody(type);
		sprite->autorelease();
		return sprite;
	}
	CC_SAFE_DELETE(sprite);
	return nullptr;

}

b2Sprite* b2Sprite::create(const std::string& filename, const Rect& rect, b2BodyType type, float32 friction, float32 restitution)
{
	b2Sprite *sprite = new (std::nothrow) b2Sprite();
	if (sprite && sprite->initWithFile(filename, rect))
	{
		sprite->initBody(type, friction, restitution);
		sprite->autorelease();
		return sprite;
	}
	CC_SAFE_DELETE(sprite);
	return nullptr;

}

void b2Sprite::setTriangleShape()
{
	b2Vec2 vertices[3];
	vertices[0].Set(-0.5, -0.5);
	vertices[1].Set(0, 0.5);
	vertices[2].Set(0.5, -0.5);
	_B2Shape.Set(vertices, 3);
	_B2FixtureDef.shape = &_B2Shape;
}

void b2Sprite::setTiles(float _tileWidth, Node* world)
{
	if (_parentWorldNode == nullptr)
	{
		setWorldNode(dynamic_cast<b2WorldNode*>(world));
	}
	float _width = getContentSize().width;
	b2Vec2 vertices[4];
	float a = _parentWorldNode->getPTM();
	vertices[0].Set(0, -(this->getContentSize().height / _parentWorldNode->getPTM() / 2));
	vertices[1].Set(0, this->getContentSize().height / _parentWorldNode->getPTM() / 2);
	vertices[2].Set(getContentSize().width / _parentWorldNode->getPTM(), (this->getContentSize().height / _parentWorldNode->getPTM() / 2));
	vertices[3].Set(getContentSize().width / _parentWorldNode->getPTM(), -(this->getContentSize().height / _parentWorldNode->getPTM() / 2));
	_B2Shape.Set(vertices, 4);
	_B2FixtureDef.shape = &_B2Shape;
}

void b2Sprite::setPlayerBody() 
{
	b2Vec2 vertices[4];
	vertices[0].Set(-0.47, -0.5);
	vertices[1].Set(-0.47, 0.45);
	vertices[2].Set(0.47, 0.45);
	vertices[3].Set(0.47, -0.5);
	_B2Shape.Set(vertices, 4);
	_B2FixtureDef.shape = &_B2Shape;
	_B2FixtureDef.density = 1.9f;
}

void b2Sprite::setTrigger(float width, float height) {
	_B2BodyDef.type = b2BodyType::b2_kinematicBody;
	b2Vec2 vertices[4];
	vertices[0].Set(0, 0);
	vertices[1].Set(0, height);
	vertices[2].Set(width, height);
	vertices[3].Set(width, 0);
	_B2Shape.Set(vertices, 4);
	_B2FixtureDef.shape = &_B2Shape;
}
//		***	SET/GET	***

void b2Sprite::setPosition(const Vec2 & pos)
{
	Sprite::setPosition(pos);

}

void b2Sprite::setPosition(float x, float y)
{
	Sprite::setPosition(x, y);
	setB2BodyPosition(x, y);

}

void b2Sprite::setB2BodyPosition(float x, float y)
{
	_B2Body->SetTransform(b2Vec2(x / _parentWorldNode->getPTM(), y / _parentWorldNode->getPTM()), _B2Body->GetAngle());

}


void b2Sprite::setRotation(float rotation)
{
	Sprite::setRotation(rotation);
	setB2BodyRotation(rotation);

}

void b2Sprite::setB2BodyRotation(float rotation)
{
	_B2Body->SetTransform(_B2Body->GetPosition(), CC_DEGREES_TO_RADIANS(-rotation));

}

void b2Sprite::setWorldNode(b2WorldNode* world)
{
	_parentWorldNode = world;

}

b2WorldNode* b2Sprite::getWorldNode()
{
	return _parentWorldNode;

}

void b2Sprite::setBody(b2Body* body, b2WorldNode* world)
{
	//assign the body pointer and set bodies' user data to its' b2dSprite*
	_B2Body = body;
	_B2Body->SetUserData(this);
	// If the parent world hasn't been defined, set it
	if (_parentWorldNode == nullptr)
	{
		setWorldNode(world);
	}
	// If shape has 0 vertices, set a default shape using the sprites texture rect
	if(_B2Shape.m_count == 0)
	{
		_B2Shape.SetAsBox(this->getTextureRect().size.width / _parentWorldNode->getPTM() / 2, this->getTextureRect().size.height / _parentWorldNode->getPTM() / 2);
	} //#???????? ????????????
	_B2Fixture = _B2Body->CreateFixture(&_B2FixtureDef);

}

//WTF

void b2Sprite::setOnRemove()
{
	//_isDeleting = true;
	getWorldNode()->setOnRemoveList(this);
}

//bool b2Sprite::isDeleting()
//{
//	return _isDeleting;
//}

b2Body* b2Sprite::getBody()
{
	return _B2Body;
}

b2BodyDef* b2Sprite::getBodyDef()
{
	return &_B2BodyDef;
}

b2Fixture* b2Sprite::getFixture()
{
	return _B2Fixture;
}

b2FixtureDef* b2Sprite::getFixtureDef()
{
	return &_B2FixtureDef;
}