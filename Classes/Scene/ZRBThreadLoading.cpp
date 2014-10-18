/*
 * ZRBThreadLoading.cpp
 *
 *  Created on: 2014年9月19日
 *      Author: 帅锋
 */

#include "ZRBThreadLoading.h"
#include "ZRBScene.h"

ZRBThreadLoading::ZRBThreadLoading()
	: isLoad( false )
	, _mutex( )
{
	name.push_back( "homeMenu" );
	name.push_back( "gameFinish_Layer" );
	name.push_back( "blueSky_material" );
	name.push_back( "summer_material" );
	name.push_back( "sweet_material" );
	name.push_back( "grotle_hero" );
	name.push_back( "hoot_hero" );
	name.push_back( "magcargo_hero" );
	name.push_back( "spoink_hero" );
	name.push_back( "tropius_hero" );
	name.push_back( "spinarak_hero" );

}

ZRBThreadLoading::~ZRBThreadLoading()
{
}

cocos2d::Scene * ZRBThreadLoading::createScene()
{
	auto scene = cocos2d::Scene::create();

	scene->addChild(ZRBThreadLoading::create());

	return scene;
}


bool ZRBThreadLoading::init()
{
	if (!Layer::init())
	{
		return false;
	}

	auto load = Sprite::create( "load.png" );
	load->setPosition( 320 , 568 );
	this->addChild( load );


	scheduleUpdate( );

	std::thread t1(&ZRBThreadLoading::thread1, this);
	t1.detach( );


	return true;
}


void ZRBThreadLoading::update( float dt )
{

	if ( isLoad )
	{

		for ( int i = 0; i < name.size( ); i++ )
		{
			auto text = TextureCache::getInstance( )->addImage( image.at( i ) , name.at( i ) + ".png" );
			image.at( i )->release( );
			SpriteFrameCache::getInstance( )->addSpriteFramesWithFile( name.at( i ) + ".plist" , text );
		}

		image.clear( );
		name.clear( );
		
		Director::getInstance( )->replaceScene( ZRBScene::sceneCreate( ) );
		isLoad = false;
	}
	
}


void ZRBThreadLoading::thread1( )
{
	_mutex.lock( );


	for (int i = 0; i < name.size( ); i++)
	{
		image.push_back( new Image( ) );
		image.at( i )->initWithImageFile( name.at(i)  + ".png" );
	}
	

	isLoad = true;	

	_mutex.unlock( );
}




