
#ifndef __ZRBBaseGameLayer_H__
#define __ZRBBaseGameLayer_H__

#include <random>

#include "../ZRBHeroSprite.h"
#include "../ZRBGameMenu/ZRBGameFinishLayer.h"
#include "../ZRBGameMenu/ZRBGameMenuLayer.h"


#define PAUSE_ITEM_TAG 1000
#define COLOR_ITEM_1_TAG 1001
#define COLOR_ITEM_2_TAG 1002
#define COLOR_ITEM_3_TAG 1003
#define COLOR_ITEM_4_TAG 1004
#define COLOR_ITEM_5_TAG 1005
#define GOLD_ICON_TAG 1006
#define BG2_TAG 10001

enum layerBatchNodeBaseGame 
{
	batchNode1 ,
	batchNode2 , 
	batchNode3 , 
	menuItem 
};

enum layerBaseGame 
{ 
	bg1BaseGame ,
	bg2BaseGame ,
	TimboBaseGame ,
	itemBaseGame ,
	labelBaseGame 
};


class ZRBBaseGameLayer : public Layer
{
protected:
	// 随机数生成器
	default_random_engine engine;

	// 均匀离散随机数 0 1
	uniform_int_distribution<unsigned> dis_0_1;
	uniform_int_distribution<unsigned> dis_gold;

public:
	//    enum menu
	//    {
	//        pause = 0x1000,
	//    };

	ZRBBaseGameLayer( );
	~ZRBBaseGameLayer( );

	virtual bool init( );
	CREATE_FUNC( ZRBBaseGameLayer );

protected:
	virtual void onEnter( );
	virtual void update( float delta ) override;

	///带有随机金币的藤条
	virtual Sprite * createTimboRandomPosHaveGold( );


	/**
	*  创建给定长度的藤条
	*
	*  @param length 藤条的长度
	*  @param pos    藤条的位置
	*
	*  @return 返回藤条
	*/
	virtual Sprite * createTimbo( float length , Vec2 pos );

	//初始化藤
	virtual void initTimbos( );
	/// 增加藤和增加菜单按钮
	virtual void replenishtimbosAndAddItem( );
	/// 按钮点击回调
	void colorItemClick( Ref *ref );
	/// 暂停游戏
	virtual void pauseItemClick( Ref *ref );
	/// 创建不动背景
	void setBg1( std::string fileNameOrFrameFileName );
	/**
	*  背景随机出现 向后移动
	*
	*  @param ImageNum  背景图片数量
	*  @param _isRanPos 位置是否随机
	*/
	void setBg2( int ImageNum , bool _isRanPos );

	/// 子类实现
	virtual void createTimboRandomPosHaveGoldOtherFunc( Sprite *preSp , Sprite *sp );
	/// return pHero;
	ZRBHeroSprite* getHero( );

protected:

	/// 计量成绩
	const int standard = 50;
	/// 初始化藤条
	void initObject( );
	///    pCanJump=true;
	void setCanJump( );
	/// 创建颜色按钮 滑动退出
	void createMenuItem( );
	/// 跳到下一个藤
	void heroJumpNext( );
	///  按钮滑动出现动作
	void resetItemPos( );
	/// 游戏结束
	virtual void showGameFinish( );

	///  当前颜色数量
	int pColorNum;
	/// 当前高度
	float pCurrentHeight;
	/// 升级高度
	float pUpdateHeight;
	/// 失败
	bool pIsLost;
	/// 能否跳跃
	bool pCanJump;
	// 金币数量
	int pGoldNum;
	/// 素材名
	std::string pNameAfterStr;

	/// 游戏按钮
	Menu *pMenu;
	/// 当前成绩
	Label *pScoreLabel;
	/// 当前金币
	Label *pGoldNumLabel;
	///当前站着的藤
	Sprite *pCurrentTimbo;
	/// 不动背景
	Sprite *pBg1;
	/// 缓存池
	SpriteBatchNode *pBatchNode;
	//精灵
	ZRBHeroSprite *pHero;
	/// 按钮原始大小
	cocos2d::Size pItemDefaultSize;

	///5种颜色
	Color3B pAllColors [ 5 ];
	//藤s
	Vector<Sprite *> pTimbos;
	Vector<Sprite *> pGolds;
	/// 菜单
	Vector<MenuItemSprite *> pItems;
	///镜头向上的速度
	CC_SYNTHESIZE( int , pUpSpeed , UpSpeed );
	/// 屏幕高度的三倍
	CC_SYNTHESIZE( int , pDisplayItemHeight , DisplayItemHeight );
	
};


#endif