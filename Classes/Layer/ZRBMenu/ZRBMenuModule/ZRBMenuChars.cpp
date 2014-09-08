
#include "ZRBMenuChars.h"


static int myranking;
static std::vector<std::string> KTNickname;
static std::vector<std::string> KTScore;

// Todo: ktplay
//void ZRBMenuChars::leaderboardCallback( bool isSuccess , const char *leaderboardId , KTLeaderboardPaginatorC *leaderboard , KTErrorC *error )
//{
//	if ( isSuccess )
//	{
//		KTNickname.clear( );
//		KTScore.clear( );
//		myranking = leaderboard->myRank;
//		for ( int i = 0; i < leaderboard->itemCount; i++ )
//		{
//			KTNickname.push_back( leaderboard->itemsArray [ i ].nickname );
//			KTScore.push_back( leaderboard->itemsArray [ i ].score );
//		}
//	}
//
//	NotificationCenter::getInstance( )->postNotification( "Notification_Ranking" , __Bool::create( isSuccess ) );
//}


bool ZRBMenuChars::init( )
{
	if ( !Layer::init( ) )
	{
		return false;
	}

	if ( ZRB_VISIBLE_SIZE.height > 1100 )
	{
		pCellNum = 6;
	}
	else if ( ZRB_VISIBLE_SIZE.height > 950 )
	{
		pCellNum = 5;
	}
	else
	{
		pCellNum = 4;
	}

	_nameLen = 12;
	size_charts = Size( ZRB_VISIBLE_SIZE.width * 0.75 , ZRB_VISIBLE_SIZE.height * 0.65 );

	auto layer = LayerColor::create( Color4B( 170 , 228 , 250 , 80 ) );
	auto item = MenuItemSprite::create( layer , layer );
	item->setPosition( Vec2::ZERO );
	item->setAnchorPoint( Vec2::ZERO );
	item->setCallback( CC_CALLBACK_0( ZRBMenuChars::call_back , this ) );

	auto layerBG = LayerColor::create( Color4B( 0 , 0 , 0 , 0 ) );
	layerBG->setContentSize( size_charts );
	auto itemBG = MenuItemSprite::create( layerBG , layerBG );
	itemBG->setPosition( ZRB_VISIBLE_SIZE.width / 2 , ZRB_VISIBLE_SIZE.height / 2 );
	auto menu = Menu::create( item , itemBG , NULL );
	menu->setPosition( Vec2::ZERO );
	this->addChild( menu );

	NotificationCenter::getInstance( )->addObserver( this , callfuncO_selector( ZRBMenuChars::setRanking ) , "Notification_Ranking" , nullptr );

	// Todo: ktplay
	//KTLeaderboardC::gameLeaderboard( "1234" , 0 , 10 , KTLeaderboardCallBack( leaderboardCallback ) );
	setCharts( );

	setRanking( __Bool::create(true) );
	return true;
}


void ZRBMenuChars::setCharts( )
{

	// 当前排名边距
	int gap = 20;


	// 添加 ZRBMenuBase
	auto layer = ZRBMenuBase::create( );

	// 添加 菜单背景
	_backboard = layer->getBackGround( );
	// 设置背板大小
	_backboard->setPreferredSize( size_charts );
	// 设置背板位置
	_backboard->setPosition( ZRB_VISIBLE_SIZE.width / 2 , ZRB_VISIBLE_SIZE.height * 3 / 2 );
	// 添加背板
	this->addChild( _backboard , 10 );

	// 创建背板出现的动作
	createAtionIn( );
	// 执行动作
	_backboard->runAction( getActionOut( ) );

	auto title = Sprite::createWithSpriteFrameName( ZRBLanguage::getValue( "Pic_ranking" ) );
	title->setPosition( size_charts.width / 2 , size_charts.height );
	_backboard->addChild( title , 10 );

	auto currank = Label::createWithTTF( ZRBLanguage::getValue( "Ranking_Rank" ) , "customfout.otf" , 35 );
	currank->setAnchorPoint( Vec2::ANCHOR_MIDDLE_BOTTOM );
	currank->setPosition( size_charts.width * 0.23 , gap );
	currank->setColor( Color3B( 69 , 193 , 255 ) );
	_backboard->addChild( currank );

	_curRank = Label::createWithTTF( "" , "customfout.otf" , 30 );
	_curRank->setAnchorPoint( Vec2::ANCHOR_MIDDLE_BOTTOM );
	_curRank->setPosition( size_charts.width * 0.6 , gap );
	_curRank->setColor( Color3B( 69 , 193 , 255 ) );
	_backboard->addChild( _curRank );

	_curScore = Label::createWithTTF( "" , "customfout.otf" , 30 );
	_curScore->setAnchorPoint( Vec2::ANCHOR_MIDDLE_BOTTOM );
	_curScore->setPosition( size_charts.width * 0.88 , gap );
	_curScore->setColor( Color3B( 69 , 193 , 255 ) );
	_backboard->addChild( _curScore );

	_leaderboard = Label::createWithTTF( ZRBLanguage::getValue( "Ranking_loading" ) , "customfout.otf" , 40 );
	_leaderboard->setPosition( size_charts / 2 );
	_leaderboard->setColor( Color3B::BLACK );
	_leaderboard->setAlignment( TextHAlignment::CENTER );
	_backboard->addChild( _leaderboard );

	// Todo: ktplay
	//if ( !KTPlayC::isEnabled( ) )
	{
		_leaderboard->setString( ZRBLanguage::getValue( "Ranking_unable" ) );
	}

	//    // 设置 back 按钮
	//    auto back = MenuItemImage::create();
	//    back->setNormalSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("back_button_marker.png"));
	//    back->setCallback(CC_CALLBACK_0(ZRBMenuChars::call_back, this));
	//    back->setPosition(size_charts.width / 2, size_charts.height * 0.1);
	//    
	//    auto menu = Menu::create(back, NULL);
	//    menu->setPosition(0, 0);
	//    _backboard->addChild(menu);

}

void ZRBMenuChars::setRanking( Ref * ref )
{
	if ( !dynamic_cast<__Bool *>( ref )->getValue( ) )
	{
		_leaderboard->setString( ZRBLanguage::getString( "Ranking_error_1" ) + "\n" + ZRBLanguage::getString( "Ranking_error_2" ) );
	}
	else
	{
		_leaderboard->setString( "" );
		/*Todo : 排行榜
		if ( KTAccountManagerC::isLoggedIn( ) )
		{
			_curRank->setString( String::createWithFormat( "NO.%d" , myranking )->getCString( ) );
			_curScore->setString( KTScore.at( myranking - 1 ) );
		}
		else*/
		{
			_curRank->setString( ZRBLanguage::getValue( "Ranking_curRank" ) );
		}
		pTableView = TableView::create( this , Size( size_charts.width - 1 , size_charts.width * pCellNum / 6 + 5 ) );

		pTableView->setDirection( ScrollView::Direction::VERTICAL );

		pTableView->setVerticalFillOrder( TableView::VerticalFillOrder::TOP_DOWN );
		pTableView->setDelegate( this );
		pTableView->setAnchorPoint( Point::ZERO );

		pTableView->setPosition( 1 , size_charts.height * 0.2 );

		_backboard->addChild( pTableView );
	}
}


TableViewCell * ZRBMenuChars::tableCellAtIndex( cocos2d::extension::TableView *table , ssize_t idx )
{
	auto cell = table->dequeueCell( );

	if ( !cell )
	{

		auto zcell = ZRBTableViewCell::create( );

		zcell->setSize( Size( size_charts.width , size_charts.width / 6 ) );
		// 设置第一部分
		zcell->setpartFirst( 1.5 );
		// 设置消除第二部分(原排名)
		zcell->setpartSecond( 0 );
		// 设置第三部分为(原名字) 使第四部分和第三部分水平方向上在一个位置
		zcell->setpartThree( 3 );
		zcell->setFoutRanking( 40 , "customfout.otf" , Color3B( 69 , 193 , 255 ) );
		// 设置道具名字体大小为30, 字体为 customfout.otf
		zcell->setFoutName( 30 , "customfout.otf" , Color3B( 69 , 193 , 255 ) );
		// 设置道具介绍字体大小为18 字体为 customfout.otf
		zcell->setFoutScorer( 30 , "customfout.otf" , Color3B( 69 , 193 , 255 ) );
		//  设置 Cell 的 Tag
		zcell->setTag( idx );

		cell = zcell;
	}
	else
	{
		cell->onEnter( );

		auto ranking = dynamic_cast<Label *>( cell->getChildByTag( ZRBTableViewCell::frist ) );

		ranking->setString( String::createWithFormat( "%ld." , idx + 1 )->getCString( ) );
		auto name = dynamic_cast<Label *>( cell->getChildByTag( ZRBTableViewCell::three ) );
		auto scorer = dynamic_cast<Label *>( cell->getChildByTag( ZRBTableViewCell::four ) );
		if ( idx < KTNickname.size( ) )
		{
			std::string nickname = KTNickname.at( idx );
			if ( !nickname.empty( ) )
			{
				if ( nickname.length( ) > _nameLen )
				{
					nickname = std::string( nickname , 0 , _nameLen );
					nickname.append( ".." );
				}
				name->setString( nickname );
				scorer->setString( KTScore.at( idx ) );
			}
		}
		else
		{
			name->setString( "" );
			scorer->setString( "" );
		}

	}

	return cell;
}

Size ZRBMenuChars::tableCellSizeForIndex( cocos2d::extension::TableView *table , ssize_t idx )
{
	return Size( size_charts.width , size_charts.width / pCellNum );
}

ssize_t ZRBMenuChars::numberOfCellsInTableView( cocos2d::extension::TableView *table )
{
	return 10;
}



/**
*  back 按钮回调函数
*/
void ZRBMenuChars::call_back( )
{
	if ( ZRBUserDate::getInstance( )->getDateBool( KEY_CHECK_SOUND ) )
	{
		CocosDenshion::SimpleAudioEngine::getInstance( )->playEffect( ZRBLanguage::getValue( "Music_Btclick" ) );
	}
	//创建菜单移除的动作
	createAtionOut( );
	//执行动作并调用清理函数
	_backboard->runAction( Sequence::create( dynamic_cast<FiniteTimeAction *>( getActionIn( ) ) ,
		CallFunc::create( CC_CALLBACK_0( ZRBMenuChars::call_clear , this ) ) , NULL ) );
}

void ZRBMenuChars::call_clear( )
{
	this->removeFromParentAndCleanup( true );
	NotificationCenter::getInstance( )->removeAllObservers( this );
}
