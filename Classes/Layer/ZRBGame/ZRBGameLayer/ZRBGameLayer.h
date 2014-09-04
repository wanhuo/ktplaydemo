

#ifndef __ZRBGameLayer_H__
#define __ZRBGameLayer_H__

#include "ZRBBaseGameLayer.h"

class ZRBGameLayer : public ZRBBaseGameLayer
{
private:

	/* Todo ktplay
	static void reportScoreCallBack( bool isSuccess , const char *leaderboardId , long long score , KTErrorC *error );*/

public:
	static const int top = 0x1111;

	ZRBGameLayer( );
	~ZRBGameLayer( );

	virtual bool init( );
	CREATE_FUNC( ZRBGameLayer );

	virtual void onEnter( );
	virtual void update( float delta );
	
	void initTimbos( );

	void replenishtimbosAndAddItem( );

	void gameBegain( Ref * sender );
	/// ��Ϸ����
	void showGameFinish( ) override;
	/// ��ͣ��Ϸ
	virtual void pauseItemClick( Ref *ref );

	///���������ҵ�����
	Sprite * createTimboRandomPosHaveGold( );
	// ����ٵĶ��� (�Ժ����С��
	Sprite * createTimbo( float length , Point pos );
	// �����ҳ��ʾ����
	void addTimboCall( float dt );

	// ��������
	void changePic( int idx );
	// ������ɫ
	void changeHero( Ref *sender );
	// ���¿�ʼ��Ϸ
	void resume( Ref * ref );
private:
	// ��Ϸ��ʼ ����
	CC_SYNTHESIZE( bool , _begainGame , BegainGame );
	// ��Ӹ���
	int count;

	// ����ҳ�� idx
	int _idx;

	// ʵʱ�߶� ������Ϸ
	float curHeight;
	// ��ʼ��Ϸʱ�ĸ߶� 
	float pBegainHeight;
};


#endif