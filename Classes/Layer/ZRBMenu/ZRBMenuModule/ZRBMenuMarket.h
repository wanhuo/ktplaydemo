
#ifndef __ZRBMenuMarket_H__
#define __ZRBMenuMarket_H__

#include "../ZRBMenuBase.h"
#include "ZRBMenuMarket/ZRBMarketRole.h"
#include "ZRBMenuMarket/ZRBMarketGold.h"


class ZRBMenuMarket : public ZRBMenuBase
{
private:

	//  market ����λ������ ( ƫ�� 35)
	const int revise = 35;

	// ���水ťλ����������
	const int buttonRevise = 1;

	// ����̳�ѡ��ť ( ����, ����, ���)
	//    MenuItemImage * pProp;
	MenuItemImage * pRole;
	MenuItemImage * pGold_buy;

	// �̳ǲ˵�
	Menu * pMenuMarker;

	// ��ҳ
	Layer * paging;

	// ����̳Ƿ�ҳ����
	Label * pTitle;
	// ��ӽ����������
	Label * pGoldNum;

	//  ���� market ������С
	Size size;

	// ���� _backboard ���� menubase�еĵ��ͼ
	CC_SYNTHESIZE_RETAIN( Scale9Sprite * , _backboard , Backboard );

public:
	~ZRBMenuMarket( );
	virtual bool init( );

	Menu * setMarket( );

	// market �ص�����
	//    void call_prop();
	void call_role( );
	void call_gold_buy( );
	void call_buy( );
	void call_back( );
	void call_clear( );

	// ����
	void setGoldNum( Ref * sender );

	CC_SYNTHESIZE( SpriteBatchNode * , pBatchNode , BatchNode );

	CREATE_FUNC( ZRBMenuMarket );

};



#endif