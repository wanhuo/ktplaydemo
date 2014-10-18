// KTFriendshipC.h
//
// Copyright (c) 2014 KTplay  All rights reserved.
//


#ifndef ktplay_sdk_KTFriendship_h
#define ktplay_sdk_KTFriendship_h
#include "KTUserC.h"
#include "KTErrorC.h"


#ifdef __cplusplus
extern "C" {
#endif
    /// 好友邀请回调
    typedef void(*KTFriendRequestsCallBack) (bool isSuccess, int successCount, KTErrorC *error);
   
    /// 好友列表回调
    typedef void(*KTFriendListCallBack) (bool isSuccess,KTUserC *userArray,int userArrayCount,KTErrorC *error);
    

    /// 好友相关接口
    class KTFriendshipC
    {
    public:
    
        /// @name 显示KTPlay好友邀请窗口
        static void showFriendRequestsView();
        
        ///@name 其他Friendship接口
        /** 发送交友邀请，当对方收到邀请，确认后成为好友
         *  @param targetUserIdCount 邀请的
         *  @param targetUserIdsArray 邀请人的KTPlay userId，可添加多人
         *  @param callback 获取回调
         *          successCallBack  成功回调
         *          failureCallBack  失败回调
         *
         *   错误码：
         *
         *  + 150001	缺少必要参数
         *  + 150002	请求的API未找到
         *  + 150003	请求的http方法不被允许
         *  + 150004	无效参数
         *  + 150005	数据库访问错误
         *  + 150006	缓存访问错误
         *  + 150007	服务器内部错误
         *  + 150103	记录不存在
         *  + 150104	无效的登陆token ，需要重新登录
         *  + 150105	黑名单用户
         *  + 150701	不能加自己为好友
         *  + 150702	你们已经是好友
         *  + 150703	你已经达到好友数量上限
         *  + 150704	对方已经达到好友数量上限
         *  + 150705	你已经邀请过他了
         */
        
        static void sendFriendRequests(char *targetUserIdsArray[],int targetUserIdCount, KTFriendRequestsCallBack callback);
        
        ///@name 获取好友列表
        /** 获取好友列表
         *  @param callback 获取回调
         *          successCallBack  成功回调
         *          failureCallBack  失败回调
         *
         *   错误码：
         *
         *  + 150001	缺少必要参数
         *  + 150002	请求的API未找到
         *  + 150003	请求的http方法不被允许
         *  + 150004	无效参数
         *  + 150005	数据库访问错误
         *  + 150006	缓存访问错误
         *  + 150007	服务器内部错误
         *  + 150103	记录不存在
         *  + 150104	无效的登陆token ，需要重新登录
         *  + 150105	黑名单用户
         */
        static void friendList(KTFriendListCallBack callback);
        
        
    };
    
#ifdef __cplusplus
}
#endif


#endif
