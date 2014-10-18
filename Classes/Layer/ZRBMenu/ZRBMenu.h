

#ifndef __ZRBMenu_H__
#define __ZRBMenu_H__

#include "../ZRBLayer/ZRBPageView.h"

#include "ZRBMenuModule/ZRBMenuMarket.h"
#include "ZRBMenuModule/ZRBMenuChars.h"
#include "ZRBMenuModule/ZRBMenuSet.h"


class ZRBPageView;

class ZRBMenu : public Layer
{

public:

	// Menu move up or down
	Menu * pMenuDown;
	Menu * pMenuUp;

private:

	// Button menu
	MenuItemImage * pSetbutten;
	MenuItemImage * pKtplay;
	MenuItemImage * pBegin;
	MenuItemImage * pMarket;
	MenuItemImage * pCharts;
	MenuItemImage * pAddGold;
	//  TODO: 模式取消
	//    MenuItemImage * pModelEndless;
	//    MenuItemImage * pModelTime;

	// Gold label
	Label * pGold;

	// Save button 'begin' size
	cocos2d::Size size;

	// Save persent view index from pageview
	int pSsize;

	//    // Save model
	//    // True is endless
	//    // False is time
	//  TODO: 模式取消
	//    bool pModel;

public:

	ZRBMenu( );
	~ZRBMenu( );

	virtual bool init( );

	// Set menu point (move up , move down)
	void SetButtenPointDown( float p );
	void SetButtenPointUp( float p );

	// Receive index from pageview
	void setSsize( int x );

	// Set gold number (label  string )
	void setGold( Ref * sender );


	// Set different color with different view
	void setButtonColor0( );
	void setButtonColor1( );
	void setButtonColor2( );

	// Menu callback function
	void begainGame( Ref * ref );
	void addGold( );
	void modelEndless( );
	void modelTime( );
	void setting( );
	void Ktplay( );
	void market( );
	void charts( );

	CC_SYNTHESIZE( SpriteBatchNode * , pBatchNode , BatchNode );
	CREATE_FUNC( ZRBMenu );

};



#endif