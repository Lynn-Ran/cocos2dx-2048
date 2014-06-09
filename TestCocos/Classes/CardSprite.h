#ifndef __CARDSPRITE_SCENE_H__
#define __CARDSPRITE_SCENE_H__

#include "cocos2d.h"

class CardSprite : public cocos2d::Sprite
{
public:
	static CardSprite* createCardSprite( int number, int width, int height, float CardSpriteX, float CardSpriteY );
	virtual bool init();
	CREATE_FUNC(CardSprite);

	// ��ʾ������
	int getNumber();
	void setNumber( int number );

private:

	void enemyInit( int number, int width, int height, float CardSpriteX, float CardSpriteY );

private:

	// ��ǰ����
	int	m_number;
	
	// ���ֿؼ�
	cocos2d::LabelTTF* m_labelTTFCardNumber;

	// ��Ƭ����
	cocos2d::LayerColor* m_layerColorBG;
};

#endif // __CARDSPRITE_SCENE_H__
