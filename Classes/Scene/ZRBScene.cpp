
#include "ZRBScene.h"

cocos2d::Scene * ZRBScene::sceneCreate( )
{
	auto scene = Scene::create( );


	CocosDenshion::SimpleAudioEngine::getInstance( )->playBackgroundMusic( ZRBLanguage::getValue( "Music_Bg" ) , true );
	CocosDenshion::SimpleAudioEngine::getInstance( )->pauseBackgroundMusic( );
	
	if ( ZRBUserDate::getInstance( )->getDateBool( KEY_CHECK_MUSIC ) )
	{
		CocosDenshion::SimpleAudioEngine::getInstance( )->resumeBackgroundMusic( );
	}


	scene->addChild( ZRBHomeLayer::create() );
	
	return scene;
}
