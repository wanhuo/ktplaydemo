
#include "ZRBHomeLayer.h"

#include "../ZRBGame/ZRBGameLayer/ZRBGameLayer.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "platform/android/jni/JniHelper.h"
#include <jni.h>
#endif

ZRBHomeLayer::ZRBHomeLayer( )
{
}

ZRBHomeLayer::~ZRBHomeLayer( )
{
	NotificationCenter::getInstance()->removeAllObservers(this);
}


bool ZRBHomeLayer::init( )
{
	if ( !Layer::init() )
	{
		return false;
	}

	SpriteFrameCache::getInstance( )->addSpriteFramesWithFile( "homeMenu.plist" , "homeMenu.png" );
	SpriteFrameCache::getInstance( )->addSpriteFramesWithFile( "gameFinish_Layer.plist" , "gameFinish_Layer.png" );

	// 取出保存的数据
	switch ( ZRBUserDate::getInstance( )->getDateInt( KEY_CHECK_ROLE ) )
	{
		case 0:
			ZRBTheme::setCurrentHero( ZRBTheme::getHeroTropius( ) );
			break;

		case 1:
			ZRBTheme::setCurrentHero( ZRBTheme::getHeroSpinarak( ) );
			break;

		case 2:
			ZRBTheme::setCurrentHero( ZRBTheme::getHeroHoot( ) );
			break;

		case 3:
			ZRBTheme::setCurrentHero( ZRBTheme::getHeroSpoink( ) );
			break;

		case 4:
			ZRBTheme::setCurrentHero( ZRBTheme::getHeroMagcargo( ) );
			break;

		case 5:
			ZRBTheme::setCurrentHero( ZRBTheme::getHeroGrotle( ) );
			break;


		default:
			break;
	}

	this->addChild( ZRBPageView::create( ) , 1, 1);

	auto keyboard = EventListenerKeyboard::create( );
	keyboard->onKeyReleased = [ & ] ( EventKeyboard::KeyCode key , Event * event )
	{
		if ( EventKeyboard::KeyCode::KEY_BACK == key )
		{
			auto page = this->getChildByTag(1);
			if ( page != nullptr)
			{
				auto menu = page->getChildByName("menu");
				if ( menu != nullptr)
				{
					auto set = menu->getChildByName("menu_set");
					if (set != nullptr)
					{
						auto t = dynamic_cast<ZRBMenuSet *>(set);
						if (t != nullptr)
						{
							t->call_back();
						}
						return;
					}

					auto market = menu->getChildByName("menu_market");
					if (market != nullptr)
					{
						auto t = dynamic_cast<ZRBMenuMarket *>(market);
						if (t != nullptr)
						{
							try
							{
								auto p = t->getBackboard( )->getChildByName( "mk_p" )->getChildByName( "mk_p_c" )->getChildByName( "mk_r_mes" );
								if ( p == nullptr )
								{
									throw p;
								}
								dynamic_cast< ZRBMessageLayer* >( p )->callback( );
								return;
							}
							catch ( ... )
							{								
								t->call_back();
								return;
							}
						}
						return;
					}

					auto ranking = menu->getChildByName("menu_ranking");
					if (ranking != nullptr)
					{
						auto t = dynamic_cast<ZRBMenuChars *>(ranking);
						if (t != nullptr)
						{
							t->call_back();
						}
						return;
					}

					auto mes = menu->getChildByName("menu_mes");
					if (mes != nullptr)
					{
						auto t = dynamic_cast<ZRBMessageLayer *>(mes);
						if (t != nullptr)
						{
							t->callback();
						}
						return;
					}
				}
				auto pageview = page->getChildByTag(11);
				if (pageview != nullptr)
				{
					auto mes = pageview->getChildByName("page_message");
					if (mes != nullptr)
					{
						auto t = dynamic_cast<ZRBMessageLayer*>(mes);
						if (t != nullptr)
						{
							t->callback();
						}
						return;
					}
				}

				auto game = page->getChildByName("game");
				if ( game != nullptr)
				{
					auto gameing = dynamic_cast<ZRBGameLayer *>(game);
					if ( gameing->getBegainGame() )
					{
						auto finish = gameing->getChildByName("finish");
						if (finish != nullptr)
						{
							auto tf = dynamic_cast<ZRBGameFinishLayer *>(finish);
							if (tf!= nullptr)
							{
								auto t = dynamic_cast<ZRBMenuChars *>(tf->getChildByName("ranking"));
								if (t!= nullptr)
								{
									t->call_back();
									return;
								}
								else
								{
									tf->homeClick(this);
								}
							}
						}

						auto pause = gameing->getChildByName("pause");
						if (pause != nullptr)
						{
							auto t = dynamic_cast<ZRBGameMenuLayer *>(pause);
							if (t != nullptr)
							{
								t->backGameItemClick(this);
							}
							return;
						}
						else
						{
							gameing->pauseItemClick(this);
							return;
						}

					}
					else
					{
						
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID )

//    typedef struct JniMethodInfo_
//    {
//        JNIEnv *    env;
//        jclass      classID;
//        jmethodID   methodID;
//    } JniMethodInfo;

						JniMethodInfo info;

						bool isHave = JniHelper::getStaticMethodInfo( info , "org/cocos2dx/cpp/AppActivity" , "exitGame" , "()V" );

						if ( isHave )
						{
							info.env->CallStaticVoidMethod(info.classID, info.methodID);
						}

#elif (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32 )
						Director::getInstance( )->end( );
#endif
					}
				}
			}
		}

	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority( keyboard , this );


	return true;
}
