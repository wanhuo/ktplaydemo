
#ifndef __ZRBMenuMarket_H__
#define __ZRBMenuMarket_H__

#include "../ZRBMenuBase.h"
#include "ZRBMenuMarket/ZRBMarketRole.h"
#include "ZRBMenuMarket/ZRBMarketGold.h"


class ZRBMenuMarket : public ZRBMenuBase
{
private:

	//  market 弹窗位置修正 ( 偏右 35)
	const int revise = 35;

	// 侧面按钮位置修正参数
	const int buttonRevise = 1;

	// 添加商城选择按钮 ( 道具, 人物, 金币)
	//    MenuItemImage * pProp;
	MenuItemImage * pRole;
	MenuItemImage * pGold_buy;

	// 商城菜单
	Menu * pMenuMarker;

	// 分页
	Layer * paging;

	// 添加商城分页标题
	Label * pTitle;
	// 添加金币数量字体
	Label * pGoldNum;

	//  保存 market 弹窗大小
	cocos2d::Size size;

	// 创建 _backboard 接收 menubase中的点九图
	CC_SYNTHESIZE_RETAIN( Scale9Sprite * , _backboard , Backboard );

public:
	~ZRBMenuMarket( );
	virtual bool init( );

	Menu * setMarket( );

	// market 回调函数
	//    void call_prop();
	void call_role( );
	void call_gold_buy( );
	void call_buy( );
	void call_back( );
	void call_clear( );

	// 设金币
	void setGoldNum( Ref * sender );

	CC_SYNTHESIZE( SpriteBatchNode * , pBatchNode , BatchNode );

	CREATE_FUNC( ZRBMenuMarket );

};



#endif