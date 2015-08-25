#ifndef PLAYER_H
#define PLAYER_H

#include "Global.h"
#include "Clock.h"
#include "cocos2d.h"
#include "Strategy.h"
USING_NS_CC;


class Player:public cocos2d::Object,public cocos2d::Sprite
{
public:
	Player();
	~Player();

	/////////////////////////////
	//����
	void changeToImageBegin();
	void changeToImagePlay();//���� ũ��ͼƬ
	void changeToImageResult();//���� ũ���Ц
	void changeCloud(float dt);
	void SetPosition();
	void AddChild(Scene* scene);
	void clearSomeImage();
	bool isLord(int);

	void updateThreePoker(CCArray*arr);

	////////////
	void displayPokerNum();//��ʾ������
	void displayOutPoker();
	void updatePoker();
	void clearArray();
	void clearOutPoker();
	////////////
	void sortPoker();
	void sortSelectPoker();
	void sortOutPoker();
	////////////
	void Restart(Scene*);


	//���ݳ�Ա
	CCArray* _arrayPoker;//����Ŀǰӵ�е��˿���
	CCArray* _arraySelectPoker;//ѡ�����
	CCArray* _arrayOutPoker;//�������

	pSprite* _image;//���ͼƬ

	Sprite* _imageNotFollow;//����
	Sprite* _imageCall;//�е���
	Sprite* _imageRob;//������
	Sprite* _imageNotCall;//���е���
	Sprite* _imageNotRob;//��������
	Sprite* _imageJiabei;//�ӱ�
	Sprite* _imageNotJiabei;//���ӱ�

	Clock* _clockLord;//�е�������ʱ
	Clock* _clockJiabei;//�ӱ�����ʱ
	Clock* _clockPlay;//���Ƶ���ʱ
	Number* _pokerNum;//��ʾ������


	bool _ifWantToBeLord;//����һ���е���ʱ �Ƿ���˵���
	bool _ifJiabei;
	bool _isLord;
	bool _isWin;

	int _cloudNum;

private:
	CC_SYNTHESIZE(bool, _isMale, Male);//�Ա�
	CC_SYNTHESIZE(PlayerLocation, _location, Location);//self left right
	//CC_SYNTHESIZE(PlayerType, _type, Type);//�ǵ�������ũ��
	//CC_SYNTHESIZE(Point, _playerAnchor, PlayerAnchor);//ê��
};



#endif