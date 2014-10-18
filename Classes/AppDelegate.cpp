#include "AppDelegate.h"

#include "Scene/ZRBThreadLoading.h"

USING_NS_CC;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
        glview = GLView::create("ColorJump");
        director->setOpenGLView(glview);
    }

	glview->setDesignResolutionSize( 640 , 1136 , ResolutionPolicy::FIXED_WIDTH );

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32 )

	glview->setFrameSize( 640 , 1136 );
	glview->setFrameZoomFactor( 0.5 );

#endif
    // turn on display FPS
    director->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);

	// 资源路径
	std::vector<std::string> path;
	path.push_back( "menu" );
	path.push_back( "material" );
	path.push_back( "Language" );
	path.push_back( "hero" );
	path.push_back( "fonts" );
	path.push_back( "music" );
	// 设置包含资源查找路径
	FileUtils::getInstance( )->setSearchResolutionsOrder( path );


    // create a scene. it's an autorelease object
   // auto scene = ZRBScene::sceneCreate();

	auto scene = ZRBThreadLoading::createScene();



    // run
    director->runWithScene(scene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();
	NotificationCenter::getInstance( )->postNotification( "EnterBackground" );
    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
