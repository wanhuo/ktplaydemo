// KTLeaderboardC.h
//
// Copyright (c) 2014 KTplay  All rights reserved.
//



#ifndef ktplay_sdk_KTLeaderboardC_h
#define ktplay_sdk_KTLeaderboardC_h
#include "KTErrorC.h"
#include "KTLeaderboardPaginatorC.h"
#ifdef __cplusplus
extern "C" {
#endif
    
    /// 获取排行回调
    typedef void(*KTLeaderboardCallBack) (bool isSuccess,const char *leaderboardId ,KTLeaderboardPaginatorC *leaderboard,KTErrorC *error);
    
    /// 上传得分回调
    typedef void(*KTReportScoreCallBack) (bool isSuccess,const char *leaderboardId,long long score,KTErrorC *error);

    /// 排行榜相关接口
    class KTLeaderboardC
    {
    public:
        
        /** 获取好友排行榜数据
         *  @param leaderboardId 排行榜Type，此数据在开发者网站获取
         *  @param startIndex  排行榜起始位置，如果传-1 返回当前登录用户排名所处位置的排行榜数据。
         *  @param count  获取排行榜单页数据记录条数。
         *  @param callback 获取回调
         *          successCallBack  成功回调
         *          failureCallBack  失败回调
         *
         *  错误码：
         *
         *  +  150001	缺少必要参数
         *  +  150002	请求的API未找到
         *  +  150003	请求的http方法不被允许
         *  +  150004	无效参数
         *  +  150005	数据库访问错误
         *  +  150006	缓存访问错误
         *  +  150007	服务器内部错误
         *  +  150103	记录不存在
         *  +  150104	无效的登陆token ，需要重新登录
         *  +  150105	黑名单用户
         *  +  150901	排行榜不存在
         */
        static void friendsLeaderboard(const char *leaderboardId ,int startIndex,int count,KTLeaderboardCallBack callback);
        
        /** 获取游戏排行榜数据
         *  @param leaderboardId 排行榜id，此数据在开发者网站获取
         *  @param pageIndex  排行榜起始页,从0开始
         *  @param pageSize  每页数据条数
         *  @param callback 获取回调
         *          successCallBack  成功回调
         *          failureCallBack  失败回调
         *
         *  错误码：
         *
         *  + 150001	缺少必要参数
         *  + 150002	请求的API未找到
         *  + 150003	请求的http方法不被允许
         *  + 150004	无效参数
         *  + 150005	数据库访问错误
         *  + 150006	缓存访问错误
         *  + 150007	服务器内部错误
         *  + 150103	记录不存在
         *  + 150901	排行榜不存在
         
         */
        static void gameLeaderboard(const char *leaderboardId ,int pageIndex,int pageSize,KTLeaderboardCallBack callback);
        
        /** 上传得分
         *  @param leaderboardId 排行榜Type ，此数据在开发者网站获取
         *  @param score 游戏得分
         *  @param callback 获取回调
         *          successCallBack  成功回调
         *          failureCallBack  失败回调
         *
         *  错误码：
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
        static void reportScore(long long score ,const char *leaderboardId,KTReportScoreCallBack callback);
        
    };
    
#ifdef __cplusplus
}
#endif

#endif
