#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

class CardSprite;

class HelloWorld : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();  
    
    CREATE_FUNC(HelloWorld);

	virtual bool onTouchBegan( cocos2d::Touch* touch, cocos2d::Event* unused_event );
	virtual void onTouchEnded( cocos2d::Touch* touch, cocos2d::Event* unused_event );

	bool doUp();
	bool doDown();
	bool doLeft();
	bool doRight();

	// ������Ƭ
	void createCardSprite( cocos2d::Size size );

	// ������ɿ�Ƭ
	void autoCreateCardNumber();

	// ��Ϸ״̬���
	void doCheckGameOver();

	// ����Ƿ�����
	bool doCheckFullCard();

	// ���ķ���
	void chgScore(int score);

private:
	int	m_firstX, m_firstY, m_endX, m_endY;

	CardSprite* m_cardArr[4][4];

	int m_score;

	cocos2d::LabelTTF* m_labelTTFCardNumber;
};

#endif // __HELLOWORLD_SCENE_H__
