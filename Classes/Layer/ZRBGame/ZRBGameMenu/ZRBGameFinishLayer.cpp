

#include "ZRBGameFinishLayer.h"
#include "Scene/ZRBScene.h"

ZRBGameFinishLayer::ZRBGameFinishLayer( )
{
	addition.push_back( 0 );
	addition.push_back( 0.1 );
	addition.push_back( 0.1 );
	addition.push_back( 0.3 );
	addition.push_back( 0.5 );
	addition.push_back( 0.75 );
}

ZRBGameFinishLayer::~ZRBGameFinishLayer( )
{
}


bool ZRBGameFinishLayer::init( )
{
	if ( !Layer::init( ) )
	{
		return false;
	}

	initLayer( );

	return true;
}


void ZRBGameFinishLayer::initLayer( )
{

	auto size = Size( ZRB_VISIBLE_SIZE.width * 0.73 , ZRB_VISIBLE_SIZE.height * 0.55 );

	auto bg = Scale9Sprite::createWithSpriteFrameName( "flow_bg.png" , Rect( 26 , 26 , 58 , 12 ) );
	bg->setPosition( ZRB_VISIBLE_SIZE.width / 2 , ZRB_VISIBLE_SIZE.height / 2 + 20 );
	bg->setContentSize( size );
	this->addChild( bg , 10 );


	auto title = Sprite::createWithSpriteFrameName( "gameFinish_GameOver.png" );
	title->setPosition( size.width / 2 , size.height );
	bg->addChild( title , 10 );

	auto gold_1 = Sprite::createWithSpriteFrameName( "gameFinish_gold.png" );
	gold_1->setPosition( size.width * 0.85 , size.height * 0.33 );
	bg->addChild( gold_1 );

	auto gold_2 = Sprite::createWithSpriteFrameName( "gameFinish_gold.png" );
	gold_2->setPosition( size.width * 0.85 , size.height * 0.24 );
	bg->addChild( gold_2 );

	auto gold_3 = Sprite::createWithSpriteFrameName( "gameFinish_gold.png" );
	gold_3->setPosition( size.width * 0.85 , size.height * 0.1 );
	bg->addChild( gold_3 );

	auto line_1 = Sprite::createWithSpriteFrameName( "line.png" );
	line_1->setPosition( size.width / 2 , size.height * 0.63 );
	line_1->setColor( Color3B( 69 , 193 , 255 ) );
	line_1->setScaleX( 1.2 );
	bg->addChild( line_1 );

	auto line_2 = Sprite::createWithSpriteFrameName( "line.png" );
	line_2->setPosition( size.width / 2 , size.height * 0.42 );
	line_2->setColor( Color3B( 69 , 193 , 255 ) );
	line_2->setScaleX( 1.2 );
	bg->addChild( line_2 );

	auto line_3 = Sprite::createWithSpriteFrameName( "line.png" );
	line_3->setPosition( size.width / 2 , size.height * 0.17 );
	line_3->setColor( Color3B( 69 , 193 , 255 ) );
	line_3->setScaleX( 1.2 );
	bg->addChild( line_3 );

	auto heighScore = Label::createWithTTF( ZRBLanguage::getValue( "Gameover_score_heigh" ) , "customfout.otf" , 40 );
	heighScore->setPosition( size.width / 2 , size.height * 0.8 );
	heighScore->setColor( Color3B( 69 , 193 , 255 ) );
	bg->addChild( heighScore );

	auto score = Label::createWithTTF( ZRBLanguage::getValue( "Gameover_score_cur" ) , "customfout.otf" , 40 );
	score->setPosition( size.width / 2 , size.height * 0.58 );
	score->setColor( Color3B( 69 , 193 , 255 ) );
	bg->addChild( score );

	auto baseReward = Label::createWithTTF( ZRBLanguage::getValue( "Gameover_score_base" ) , "customfout.otf" , 32 );
	baseReward->setPosition( size.width / 4 , size.height * 0.33 );
	baseReward->setColor( Color3B( 69 , 193 , 255 ) );
	bg->addChild( baseReward );

	auto roleReward = Label::createWithTTF( ZRBLanguage::getValue( "Gameover_score_role" ) , "customfout.otf" , 32 );
	roleReward->setPosition( size.width / 4 , size.height * 0.24 );
	roleReward->setColor( Color3B( 69 , 193 , 255 ) );
	bg->addChild( roleReward );

	auto total = Label::createWithTTF( ZRBLanguage::getValue( "Gameover_score_sum" ) , "customfout.otf" , 30 );
	total->setPosition( size.width / 4 , size.height * 0.1 );
	total->setColor( Color3B( 69 , 193 , 255 ) );
	bg->addChild( total );


	pHeighScore = Label::createWithTTF( "" , "customfout.otf" , 45 );
	pHeighScore->setPosition( size.width / 2 , size.height * 0.71 );
	pHeighScore->setColor( Color3B( 69 , 193 , 255 ) );
	bg->addChild( pHeighScore );

	pDistanceLabel = Label::createWithTTF( "" , "customfout.otf" , 45 );
	pDistanceLabel->setPosition( size.width / 2 , size.height * 0.5 );
	pDistanceLabel->setColor( Color3B( 69 , 193 , 255 ) );
	bg->addChild( pDistanceLabel );

	pBaseGoldNumLabel = Label::createWithTTF( "" , "customfout.otf" , 40 );
	pBaseGoldNumLabel->setPosition( size.width * 0.72 , size.height * 0.33 );
	pBaseGoldNumLabel->setColor( Color3B( 69 , 193 , 255 ) );
	bg->addChild( pBaseGoldNumLabel );

	pRoleGoldNumLabel = Label::createWithTTF( "" , "customfout.otf" , 40 );
	pRoleGoldNumLabel->setPosition( size.width * 0.72 , size.height * 0.24 );
	pRoleGoldNumLabel->setColor( Color3B( 69 , 193 , 255 ) );
	bg->addChild( pRoleGoldNumLabel );

	pSummaryGoldNumLabel = Label::createWithTTF( "" , "customfout.otf" , 40 );
	pSummaryGoldNumLabel->setPosition( size.width * 0.72 , size.height * 0.1 );
	pSummaryGoldNumLabel->setColor( Color3B( 69 , 193 , 255 ) );
	bg->addChild( pSummaryGoldNumLabel );

	// TODO 按钮下偏移
	int posY = -70;

	auto restarItem = MenuItemImage::create( );
	restarItem->setNormalSpriteFrame( SpriteFrameCache::getInstance( )->getSpriteFrameByName( "gameFinish_restart.png" ) );
	restarItem->setCallback( CC_CALLBACK_1( ZRBGameFinishLayer::restartClick , this ) );
	restarItem->setPosition( size.width * 0.5 , posY );

	auto ranking = MenuItemImage::create( );
	ranking->setNormalSpriteFrame( SpriteFrameCache::getInstance( )->getSpriteFrameByName( "gameFinish_ranking.png" ) );
	ranking->setCallback( CC_CALLBACK_1( ZRBGameFinishLayer::rankingClick , this ) );
	ranking->setPosition( size.width * 0.12 , posY );

	auto home = MenuItemImage::create( );
	home->setNormalSpriteFrame( SpriteFrameCache::getInstance( )->getSpriteFrameByName( "gameFinish_home.png" ) );
	home->setCallback( CC_CALLBACK_1( ZRBGameFinishLayer::homeClick , this ) );
	home->setPosition( size.width * 0.88 , posY );

	auto menu = Menu::create( restarItem , home , ranking , NULL );
	menu->setPosition( Vec2::ZERO );
	bg->addChild( menu );
}

// 更新显示信息
void ZRBGameFinishLayer::setInfo( int _distance , int _glod )
{
	// 获取保存的最高记录
	auto score = ZRBUserDate::getInstance( )->getDateInt( KEY_DATA_SCORE );

	if ( score <= _distance )
	{
		ZRBUserDate::getInstance( )->saveData( KEY_DATA_SCORE , &_distance );
		pHeighScore->setString( String::createWithFormat( "%dm" , _distance )->getCString( ) );
	}
	else
	{
		pHeighScore->setString( String::createWithFormat( "%dm" , score )->getCString( ) );
	}

	pDistanceLabel->setString( String::createWithFormat( "%dm" , _distance )->getCString( ) );

	pBaseGoldNumLabel->setString( String::createWithFormat( "%d" , _glod )->getCString( ) );

	auto roleCheck = ZRBUserDate::getInstance( )->getDateInt( KEY_CHECK_ROLE );

	auto additionGold = int( addition.at( roleCheck ) * _glod );

	pRoleGoldNumLabel->setString( String::createWithFormat( "%d" , additionGold )->getCString( ) );

	pSummaryGoldNumLabel->setString( String::createWithFormat( "%d" , _glod + additionGold )->getCString( ) );
	// 保存金币
	auto gold = ZRBUserDate::getInstance( )->getDateInt( KEY_DATA_GOLDNUM );
	gold += additionGold + _glod;
	ZRBUserDate::getInstance( )->saveData( KEY_DATA_GOLDNUM , &gold );

}



void ZRBGameFinishLayer::rankingClick( Ref *ref )
{
	if ( ZRBUserDate::getInstance( )->getDateBool( KEY_CHECK_SOUND ) )
	{
		CocosDenshion::SimpleAudioEngine::getInstance( )->playEffect( ZRBLanguage::getValue( "Music_Btclick" ) );
	}
	auto ranking = ZRBMenuChars::create( );
	ranking->setName( "ranking" );
	this->addChild( ranking , 10 );
}

void ZRBGameFinishLayer::restartClick( Ref *ref )
{
	if ( ZRBUserDate::getInstance( )->getDateBool( KEY_CHECK_SOUND ) )
	{
		CocosDenshion::SimpleAudioEngine::getInstance( )->playEffect( ZRBLanguage::getValue( "Music_Btclick" ) );
	}
	NotificationCenter::getInstance( )->postNotification( "NOTIFICATION_Resume" , __Bool::create( false ) );
}

void ZRBGameFinishLayer::homeClick( Ref *ref )
{
	if ( ZRBUserDate::getInstance( )->getDateBool( KEY_CHECK_SOUND ) )
	{
		CocosDenshion::SimpleAudioEngine::getInstance( )->playEffect( ZRBLanguage::getValue( "Music_Btclick" ) );
	}
	this->getScene( )->cleanup( );
	// back home
	Director::getInstance( )->replaceScene( ZRBScene::sceneCreate() );

}