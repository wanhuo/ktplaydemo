LOCAL_PATH := $(call my-dir)

#prebuild KTPlay library  
include $(CLEAR_VARS) 
LOCAL_MODULE := libKTPlay 
LOCAL_SRC_FILES := libKTPlay.so 
LOCAL_MODULE_FILENAME := libKTPlay 
include $(PREBUILT_SHARED_LIBRARY) 

include $(CLEAR_VARS) 
LOCAL_MODULE := libKTAccountmanager 
LOCAL_SRC_FILES := libKTAccountmanager.so 
LOCAL_MODULE_FILENAME := libKTAccountmanager 
include $(PREBUILT_SHARED_LIBRARY) 

include $(CLEAR_VARS) 
LOCAL_MODULE := libKTFriendship 
LOCAL_SRC_FILES := libKTFriendship.so 
LOCAL_MODULE_FILENAME := libKTFriendship 
include $(PREBUILT_SHARED_LIBRARY) 

include $(CLEAR_VARS) 
LOCAL_MODULE := libKTLeaderboard 
LOCAL_SRC_FILES := libKTLeaderboard.so 
LOCAL_MODULE_FILENAME := libKTLeaderboard 
include $(PREBUILT_SHARED_LIBRARY)

include $(CLEAR_VARS)

$(call import-add-path,$(LOCAL_PATH)/../../cocos2d)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/external)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/cocos)

LOCAL_MODULE := cocos2dcpp_shared

LOCAL_MODULE_FILENAME := libcocos2dcpp

LOCAL_SRC_FILES := hellocpp/main.cpp \
				   ../../Classes/AppDelegate.cpp \
				   ../../Classes/Layer/ZRBAuxiliary/ZRBLoadingLayer.cpp \
				   ../../Classes/Layer/ZRBAuxiliary/ZRBMessageLayer.cpp \
				   ../../Classes/Layer/ZRBGame/ZRBGameLayer/ZRBBaseGameLayer.cpp \
				   ../../Classes/Layer/ZRBGame/ZRBGameLayer/ZRBGameLayer.cpp \
				   ../../Classes/Layer/ZRBGame/ZRBGameMenu/ZRBGameFinishLayer.cpp \
				   ../../Classes/Layer/ZRBGame/ZRBGameMenu/ZRBGameMenuLayer.cpp \
				   ../../Classes/Layer/ZRBGame/ZRBHeroSprite.cpp \
				   ../../Classes/Layer/ZRBLayer/ZRBHomeLayer.cpp \
				   ../../Classes/Layer/ZRBLayer/ZRBPageView.cpp \
				   ../../Classes/Layer/ZRBMenu/ZRBMenu.cpp \
				   ../../Classes/Layer/ZRBMenu/ZRBMenuBase.cpp \
				   ../../Classes/Layer/ZRBMenu/ZRBMenuModule/ZRBMenuChars.cpp \
				   ../../Classes/Layer/ZRBMenu/ZRBMenuModule/ZRBMenuMarket.cpp \
				   ../../Classes/Layer/ZRBMenu/ZRBMenuModule/ZRBMenuMarket/ZRBMarketGold.cpp \
				   ../../Classes/Layer/ZRBMenu/ZRBMenuModule/ZRBMenuMarket/ZRBMarketRole.cpp \
				   ../../Classes/Layer/ZRBMenu/ZRBMenuModule/ZRBMenuSet.cpp \
				   ../../Classes/Layer/ZRBViewLayer/ZRBTableViewCell.cpp \
				   ../../Classes/Layer/ZRBViewLayer/ZRB_PageView.cpp \
				   ../../Classes/Scene/ZRBScene.cpp \
				   ../../Classes/Scene/ZRBThreadLoading.cpp \
				   ../../Classes/Utilities/ZRBLanguage/ZRBLanguage.cpp \
				   ../../Classes/Utilities/ZRBTheme/ZRBTheme.cpp \
				   ../../Classes/Utilities/ZRBUserDate/ZRBUserDate.cpp 
				   


LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes

LOCAL_SHARED_LIBRARIES := libKTPlay 
LOCAL_SHARED_LIBRARIES += libKTAccountmanager 
LOCAL_SHARED_LIBRARIES += libKTFriendship 
LOCAL_SHARED_LIBRARIES += libKTLeaderboard

LOCAL_WHOLE_STATIC_LIBRARIES := cocos2dx_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocosdenshion_static

# LOCAL_WHOLE_STATIC_LIBRARIES += box2d_static
# LOCAL_WHOLE_STATIC_LIBRARIES += cocosbuilder_static
# LOCAL_WHOLE_STATIC_LIBRARIES += spine_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocostudio_static
# LOCAL_WHOLE_STATIC_LIBRARIES += cocos_network_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocos_extension_static


include $(BUILD_SHARED_LIBRARY)

$(call import-module,.)
$(call import-module,audio/android)

# $(call import-module,Box2D)
# $(call import-module,editor-support/cocosbuilder)
# $(call import-module,editor-support/spine)
$(call import-module,editor-support/cocostudio)
# $(call import-module,network)
$(call import-module,extensions)
