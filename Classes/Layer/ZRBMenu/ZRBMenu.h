

#ifndef __ZRBMenu_H__
#define __ZRBMenu_H__

#include "Layer/ZRBAuxiliary/ZRBMessageLayer.h"
#include "Layer/ZRBLayer/ZRBPageView.h"
#include "Utilities/ZRBTheme/ZRBTheme.h"


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
	//  TODO: ģʽȡ��
	//    MenuItemImage * pModelEndless;
	//    MenuItemImage * pModelTime;

	// Gold label
	Label * pGold;

	// Save button 'begin' size
	Size size;

	// Save persent view index from pageview
	int pSsize;

	//    // Save model
	//    // True is endless
	//    // False is time
	//  TODO: ģʽȡ��
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