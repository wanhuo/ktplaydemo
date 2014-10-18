// KTAccountManagerC.h
//
// Copyright (c) 2014 KTplay  All rights reserved.
//



#ifndef ktplay_sdk_KTAccountManagerC_h
#define ktplay_sdk_KTAccountManagerC_h
#include "KTUserC.h"
#include "KTErrorC.h"
#ifdef __cplusplus
extern "C" {
#endif
    typedef void(*KTLoginStatusChangedCallBack) (bool isLoggedIn, KTUserC * account);
    
    /// 获取用户配置回调
    typedef void(*KTUserProfileCallBack) (bool isSuccess ,const char *userId,KTUserC * user,KTErrorC *error);
    /// 登录回调
    typedef void(*KTLoginCallBack) (bool isSuccess ,KTUserC * user,KTErrorC *error);
    
    
    /// 账户相关接口
    class KTAccountManagerC
    {
    public:
        /// @name 设置KTPlay登录状态变更回调
        /*
         *
         *  @param KTLoginStatusChangedCallBack 登录状态变更回调
         *
         **/
        static void setLoginStatusChangedCallback(KTLoginStatusChangedCallBack ktLoginStatus);
        
        
        /// @name 显示KTPlay登录窗口
        /**
         *
         *
         */
        static void showLoginView(bool closeable, KTLoginCallBack ktLoginCallback);
        
        
        ///@name 其他用户相关接口
        /** 获取用户信息
         *  @param userId KTPlay用户的ID
         *  @param callback 获取回调
         *          successCallBack  成功回调
         *          failureCallBack  失败回调
         *
         *   错误码：
         *
         *          - 150001	缺少必要参数
         *          - 150002	请求的API未找到
         *          - 150003	请求的http方法不被允许
         *          - 150004	无效参数
         *          - 150005	数据库访问错误
         *          - 150006	Reids访问错误
         *          - 150007	服务器内部错误
         *          - 150103	记录不存在
         *          - 150104	无效的登陆token ，需要重新登录
         *          - 150105	黑名单用户
         */
        static void  userProfile(const char *userId,KTUserProfileCallBack callback);
        
        
        ///@name 判断用户是否已登录
        /**
         *  @return KTPlay是否已有用户登录
         */
        static bool isLoggedIn();
        
        
        ///@name 获取当前用户信息
        /** @return 返回当前登录用户信息，如果用户未登录返回为NULL
         */
        static KTUserC* currentAccount();
        
    };
    
#ifdef __cplusplus
}
#endif

#endif
