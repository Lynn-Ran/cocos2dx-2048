#include "HelloWorldScene.h"
#include "CardSprite.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    auto scene = Scene::create();

    auto layer = HelloWorld::create();

    scene->addChild(layer);

    return scene;
}

bool HelloWorld::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan = CC_CALLBACK_2( HelloWorld::onTouchBegan, this );
	touchListener->onTouchEnded = CC_CALLBACK_2( HelloWorld::onTouchEnded, this );
	_eventDispatcher->addEventListenerWithSceneGraphPriority( touchListener, this );

	auto layerColorBG = cocos2d::LayerColor::create( cocos2d::Color4B( 187, 173, 162, 255 ) );
	this->addChild(layerColorBG);


	auto size = Director::getInstance()->getVisibleSize();

	// 分数
	auto labelTTFCardNumberName = LabelTTF::create("SCORE", "HiraKakuProN-W6",80); 
	labelTTFCardNumberName->setPosition( Point(150, size.height/2+40) );
	addChild(labelTTFCardNumberName);

	m_score = 0;
	m_labelTTFCardNumber = LabelTTF::create("0", "HiraKakuProN-W6",80); 
	m_labelTTFCardNumber->setPosition( Point(150, size.height/2-40) );
	addChild(m_labelTTFCardNumber);
	
	createCardSprite(size);
	autoCreateCardNumber();
	autoCreateCardNumber();

    return true;
}

bool HelloWorld::onTouchBegan( cocos2d::Touch* touch, cocos2d::Event* unused_event )
{
	// 获取触摸的X &Ｙ
	Point touchPoint = touch->getLocation();
	touch->getLocationInView();
	m_firstX = touchPoint.x;
	m_firstY = touchPoint.y;

	return true;
}

void HelloWorld::onTouchEnded( cocos2d::Touch* touch, cocos2d::Event* unused_event )
{
	Point touchPoint = touch->getLocation();
	m_endX = m_firstX - touchPoint.x;
	m_endY = m_firstY - touchPoint.y;

	if ( abs(m_endX) > abs(m_endY) )
	{
		if ( m_endX+5 > 0 )
		{
			doLeft();
		}
		else
		{
			doRight();
		}
	}
	else
	{
		if ( m_endY+5 > 0 )
		{
			doDown();
		}
		else
		{
			doUp();
		}
	}

	if ( !doCheckFullCard() )
	{
		autoCreateCardNumber();
	}
	
	doCheckGameOver();
}


bool HelloWorld::doUp()
{
	bool isdo = false;
	for ( int x=0; x<4; ++x ) 
	{
		for ( int y=3; y>=0; --y )
		{
			for ( int y1=y-1; y1>=0; --y1 )
			{
				CardSprite* card = m_cardArr[x][y];
				if ( m_cardArr[x][y1]->getNumber()>0 )
				{
					if ( card->getNumber() <=0 )
					{
						card->setNumber( m_cardArr[x][y1]->getNumber() );
						m_cardArr[x][y1]->setNumber(0);

						++y;
						isdo = true;
					}
					else if ( card->getNumber()==m_cardArr[x][y1]->getNumber() )
					{
						card->setNumber( card->getNumber()*2 );
						m_cardArr[x][y1]->setNumber(0);

						chgScore(card->getNumber());

						isdo = true;
					}
					break;
				}
			}
		}
	}

	return isdo;
}

bool HelloWorld::doDown()
{
	bool isdo = false;
	for ( int x=0; x<4; ++x ) 
	{
		for ( int y=0; y<4; ++y )
		{
			for ( int y1=y+1; y1<4; ++y1 )
			{
				CardSprite* card = m_cardArr[x][y];
				if ( m_cardArr[x][y1]->getNumber()>0 )
				{
					if ( card->getNumber() <=0 )
					{
						card->setNumber( m_cardArr[x][y1]->getNumber() );
						m_cardArr[x][y1]->setNumber(0);

						--y;
						isdo = true;
					}
					else if ( card->getNumber()==m_cardArr[x][y1]->getNumber() )
					{
						card->setNumber( card->getNumber()*2 );
						m_cardArr[x][y1]->setNumber(0);

						chgScore(card->getNumber());

						isdo = true;
					}
					break;
				}
			}
		}
	}

	return isdo;
}

bool HelloWorld::doLeft()
{
	bool isdo = false;
	for ( int y=0; y<4; ++y ) 
	{
		for ( int x=0; x<4; ++x )
		{
			for ( int x1=x+1; x1<4; ++x1 )
			{
				CardSprite* card = m_cardArr[x][y];
				if ( m_cardArr[x1][y]->getNumber()>0 )
				{
					if ( card->getNumber() <=0 )
					{
						card->setNumber( m_cardArr[x1][y]->getNumber() );
						m_cardArr[x1][y]->setNumber(0);

						--x;
						isdo = true;
					}
					else if ( card->getNumber()==m_cardArr[x1][y]->getNumber() )
					{
						card->setNumber( card->getNumber()*2 );
						m_cardArr[x1][y]->setNumber(0);

						chgScore(card->getNumber());

						isdo = true;
					}
					break;
				}
			}
		}
	}

	return isdo;
}

bool HelloWorld::doRight()
{
	bool isdo = false;
	for ( int y=0; y<4; ++y ) 
	{
		for ( int x=3; x>=0; --x )
		{
			for ( int x1=x-1; x1>=0; --x1 )
			{
				CardSprite* card = m_cardArr[x][y];
				if ( m_cardArr[x1][y]->getNumber()>0 )
				{
					if ( card->getNumber() <=0 )
					{
						card->setNumber( m_cardArr[x1][y]->getNumber() );
						m_cardArr[x1][y]->setNumber(0);

						++x;
						isdo = true;
					}
					else if ( card->getNumber()==m_cardArr[x1][y]->getNumber() )
					{
						card->setNumber( card->getNumber()*2 );
						m_cardArr[x1][y]->setNumber(0);

						chgScore(card->getNumber());

						isdo = true;
					}
					break;
				}
			}
		}
	}

	return isdo;
}


void HelloWorld::createCardSprite( cocos2d::Size size )
{
	int unitSize = (size.height-28)/4;

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			CardSprite* card = CardSprite::createCardSprite( 0, unitSize, unitSize, unitSize*i+340, unitSize*j+20 );
			addChild( card );
			m_cardArr[i][j] = card;
		}
	}
}

void HelloWorld::autoCreateCardNumber()
{
	int i = CCRANDOM_0_1()*4;
	int j = CCRANDOM_0_1()*4;

	if ( m_cardArr[i][j]->getNumber() > 0 )
	{
		autoCreateCardNumber();
	}
	else
	{
		m_cardArr[i][j]->setNumber(2);
	}
}

void HelloWorld::doCheckGameOver()
{
	bool isGameOver = true;
	for (int y = 0; y < 4; y++)
	{
		for (int x = 0; x < 4; x++)
		{
			CardSprite* card = m_cardArr[x][y];
			if ( card->getNumber()==0
				 || (x>0&&(card->getNumber()==m_cardArr[x-1][y]->getNumber()))
				 || (x<3&&(card->getNumber()==m_cardArr[x+1][y]->getNumber()))
				 || (y>0&&(card->getNumber()==m_cardArr[x][y-1]->getNumber()))
				 || (y<3&&(card->getNumber()==m_cardArr[x][y+1]->getNumber()))
				)
			{
				isGameOver = false;
			}
		}
	}

	if ( isGameOver )
	{
		Director::getInstance()->replaceScene( TransitionFade::create(1, HelloWorld::createScene()) );
	}
}

bool HelloWorld::doCheckFullCard()
{
	for (int y = 0; y < 4; y++)
	{
		for (int x = 0; x < 4; x++)
		{
			if ( m_cardArr[x][y]->getNumber()==0 )
			{
				return false;
			}
		}
	}

	return true;
}

void HelloWorld::chgScore( int score )
{
	m_score += score;
	m_labelTTFCardNumber->setString( String::createWithFormat("%d", m_score)->getCString() );
}


