// KTPlayC.h
//
// Copyright (c) 2014 KTplay  All rights reserved.
//

#ifndef __ktplay_sdk__KTPlayC__
#define __ktplay_sdk__KTPlayC__

#ifdef __cplusplus
extern "C" {
#endif
    
    
    /// 奖励数据项，包含奖励所需数据
    class KTRewardItemC
    {
    public:
        
        /** 奖励名称
         */
        const char *name;
        
        /** 奖励ID
         *
         *  奖励ID用于标识奖励类型，如金币（GOLD），由开发者自己在开发者后台设定。
         */

        const char *typeId;
        
        
        /** 奖励值
         *
         * 奖励具体数值
         */
        unsigned long value;
        KTRewardItemC();
        ~KTRewardItemC();
        
        
    };
    
    /** KTPlay发放奖励回调，由游戏实现最终的奖励发放。
     */
    typedef void (*KTDispatchRewardsCallback)(KTRewardItemC * pRewardArray, int length);
    
    /// KTPlay窗口打开时的回调
    typedef void (*KTViewDidAppearCallback)();
    
    /// KTPlay窗口关闭时的回调
    typedef void (*KTViewDidDisappearCallback)();
    
    /// KTPlay收到新动态时的回调
    typedef void (*KTActivityStatusChangedCallback)(bool activityStatusChanged);
    
    /// KTPlay主类
    class KTPlayC
    {
    public:
        
        /** 设置KTPlay窗口显示时的回调
         *  @param appearCallback KTPlay窗口显示时的回调
         */
        static void setViewDidAppearCallback(KTViewDidAppearCallback appearCallback);
        
        /** 设置KTPlay窗口显示时的回调
         *  @param block KTPlay窗口显示时的回调
         */
        static void setViewDidDisappearCallback(KTViewDidDisappearCallback disappearCallback);
        
        /** 设置发放奖励的回调
         * 此方法必须被调用以完成奖励的最终发放，关于奖励的使用方法请参考SDK接入指南。
         * @param dispatchRewardsCallback 发放奖励回调
         */
        static void setDidDispatchRewardsCallback(KTDispatchRewardsCallback dispatchRewardsCallback);
        
        /** 设置KTPlay收到新动态时的回调
         * 关于新动态的作用和提示方法请参考DK接入指南
         *  @param activityStatusChangedCallback KTPlay收到新动态或已读新动态时的回调
         */
        static void setActivityStatusChangedCallback(KTActivityStatusChangedCallback activityStatusChangedCallback);
        
        /** 显示KTPlay窗口
         */
        static void show();
        
        /** 关闭KTPlay窗口
         * 通常情况下不需要调用此方法，因为KTPlay窗口会由玩家主动关闭。
         */
        static void dismiss();
        
        /** 判断KTPlay是否可用
         * KTPlay不可用的情况包括：</br>
         * 1、设备不被支持 <br/>
         * 2、开发者网站后台关闭了KT功能
         * @return KTPlay是否可用
         */
        static bool isEnabled();
        
        /** 判断KTPlay窗口是否正在显示
         * @return KTPlay窗口是否正在显示
         */
        static bool isShowing();

        /**  分享图片/文本到KTPlay平台
         *  @param imagePath 图片的绝对路径,为NULL时，不分享图片
         *  @param description 图片的描述,为NULL时，没有默认内容描述
         */
        static void shareImageToKT(const char *imagePath, const char* description);
        
        /** 截取游戏当前画面并分享到KTPlay平台
         *  @param description 图片的描述
         */
        static void shareScreenshotToKT(const char *description);
        
        /**
         * 设置截图旋转角度
         * 一般情况下不需要此方法，在截图角度不正常时（可能由游戏引擎或会游戏开发方式导致），再调用此方法进行调整
         * @param degrees 截图旋转角度（注意，是角度而不是弧度，取值如90,180等）
         */
        static void setScreenshotRotation(float degrees);
        
        /** 开启或关闭通知功能
         *
         *  @param enabled 为Yes时，开启通知，为No时关闭通知功能
         */
        static void setNotificationEnabled(bool isEnabled);

        /*!
		 @abstract update (Android only)
		 */
		static void update();
    };
    
#ifdef __cplusplus
}
#endif

#endif
