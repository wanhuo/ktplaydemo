// KTLeaderboardPaginatorC.h
//
// Copyright (c) 2014 KTplay  All rights reserved.
//


#ifndef ktplay_sdk_KTLeaderboardPaginatorC_h
#define ktplay_sdk_KTLeaderboardPaginatorC_h
#include "KTUserC.h"
#ifdef __cplusplus
extern "C" {
#endif

    /// 排行榜类
    class KTLeaderboardPaginatorC
    {
    public:
       
        /// 上榜人数
        int total;
        
        /// 下一页起始位置，nextCursor在gameLeaderboard中是无效的
        const char *nextCursor;
        
        /// 上一页起始位置，previousCursor在gameLeaderboard中是无效的
        const char *previousCursor;
        
        /// KTUser数组长度
        int itemCount;
        
        /// KTUser数组
        KTUserC * itemsArray;
        
        /// 排行榜名字
        const char *leaderboardName;
        
        /// 排行榜图标
        const char *leaderboardIcon;
        
        // 排行榜ID
        const char *leaderboardId;
        
        /// 排行榜单结算ID，保留字段，暂时无用
        const char *periodicalSummaryId;
        
        /// 我的排名 该属性仅在在gameLeaderboard有效
        int myRank;
        
        KTLeaderboardPaginatorC();
        ~KTLeaderboardPaginatorC();
    };
    
#ifdef __cplusplus
}
#endif

#endif

