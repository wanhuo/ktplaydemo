// KTUserC.h
//
// Copyright (c) 2014 KTplay  All rights reserved.
//

#ifndef ktplay_sdk_KTUserC_h
#define ktplay_sdk_KTUserC_h


#ifdef __cplusplus
extern "C" {
#endif
    
    /// 用户类
    class KTUserC
    {
    public:
        
        ///KT用户唯一标识符
        const char *userId;
        
        ///KT用户头像
        const char *headerUrl;
        
        ///KT用户昵称
        const char *nickname;
        
        ///性别  0:未知;1:男;2:女
        int gender;
        
        ///城市
        const char *city;
        
        ///扩展属性，得分
        const char *score;
       
        ///扩展属性，排行
        long long rank;
       
        ///SNS用户ID
        const char *snsUserId;
       
        ///sns登录类型登录的，此值才有效
        const char *loginType;
        KTUserC();
        ~KTUserC();
       
        
    };
    
#ifdef __cplusplus
}
#endif


#endif

