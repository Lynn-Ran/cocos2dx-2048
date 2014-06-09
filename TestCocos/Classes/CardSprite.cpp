#include "CardSprite.h"

USING_NS_CC;

const cocos2d::Color3B cardColorArr[12] =
{
	cocos2d::Color3B(204,192,180),	// 默认
	cocos2d::Color3B(238,228,218),	// 2
	cocos2d::Color3B(239,225,199),	// 4
	cocos2d::Color3B(245,176,117),	// 8
	cocos2d::Color3B(236,139,84),	// 16
	cocos2d::Color3B(245,124,95),	// 32
	cocos2d::Color3B(237,87,50),	// 64
	cocos2d::Color3B(244,215,111),	// 128
	cocos2d::Color3B(234,208,87),	// 256
	cocos2d::Color3B(253,210,48),	// 512
	cocos2d::Color3B(209,168,37),	// 1024
	cocos2d::Color3B(242,190,9),	// 2048
};

CardSprite* CardSprite::createCardSprite( int number, int width, int height, float CardSpriteX, float CardSpriteY )
{
	CardSprite* enemy = new CardSprite();
	if ( enemy && enemy->init() )
	{
		enemy->autorelease();
		enemy->enemyInit( number, width, height, CardSpriteX, CardSpriteY );

		return enemy;
	}

	CC_SAFE_DELETE(enemy);

	return NULL;
}

bool CardSprite::init()
{
	if ( !Sprite::init() )
	{
		return false;
	}

	return true;
}


int CardSprite::getNumber()
{
	return m_number;
}

static int two_pow(int x)
{
    if(x==1 || x==0)
        return 0;
    else
        return 1+two_pow(x>>1);
}

void CardSprite::setNumber( int number )
{
	m_number = number;

	if ( m_number>0 )
	{
		m_labelTTFCardNumber->setString( String::createWithFormat("%i", m_number)->getCString() );
	}
	else
	{
		m_labelTTFCardNumber->setString( "" );
	}

	m_layerColorBG->setColor(cardColorArr[two_pow(m_number)]);

	//字体大小
	int fontSize = 100;
	if ( m_number>=1000 )
	{
		fontSize = 40;
	}
	else if ( m_number>=100 )
	{
		fontSize = 60;
	}
	else if ( m_number>=10 )
	{
		fontSize = 90;
	}

	m_labelTTFCardNumber->setFontSize(fontSize);
}


void CardSprite::enemyInit( int number, int width, int height, float CardSpriteX, float CardSpriteY )
{
	m_number = number;

	// 卡片背景设置
	m_layerColorBG = cocos2d::LayerColor::create( cocos2d::Color4B(200,190,180,255), width-15, height-15);
	m_layerColorBG->setPosition( Point(CardSpriteX, CardSpriteY) );

	String* strNumber = NULL;
	if ( m_number>0 )
	{
		strNumber = String::createWithFormat("%i", m_number);
	}
	else
	{
		strNumber = String::create("");
	}

	m_labelTTFCardNumber = LabelTTF::create( strNumber->getCString(), "HiraKakuProN-W6", 100 );
	m_labelTTFCardNumber->setPosition( Point(m_layerColorBG->getContentSize().width/2, m_layerColorBG->getContentSize().height/2) );
	m_labelTTFCardNumber->setTag( 8 );
	m_layerColorBG->addChild( m_labelTTFCardNumber );

	this->addChild(m_layerColorBG);
}


