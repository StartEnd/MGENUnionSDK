//
//  MGUnionEnSDKProtocol.h
//  MGUnionENSDK
//
//  Created by Mr.Song on 2018/6/14.
//  Copyright © 2018 WeiYouHuDong. All rights reserved.
//

#ifndef MGUnionEnSDKProtocol_h
#define MGUnionEnSDKProtocol_h

@class MGUnionENSDKUser;

typedef NS_ENUM (NSInteger,MGDefaultLoginType)
{
    MG_DefaultTourist = 0,          //默认游客登录,GameCenter登录状态会自动绑定GameCenter
    MG_ForceSelect = 1,             //无默认用户,默认弹出登录窗口,用户手动选择
};

typedef NS_ENUM (NSInteger,MGAuthErrCode) {
    MGSDKAuth_Err_Ok = 0,               //Auth成功
    MGSDKAuth_Err_NormalErr = -1,       //普通错误
    MGSDKAuth_Err_NetworkErr = -2,      //网络错误
};

typedef NS_ENUM (NSInteger,MGLogPlatform) {
    MGLogPlatform_Facebook = 0,         //Facebook统计
    MGLogPlatform_AppsFlyer = 1,        //AppsFlyer打点
    MGLogPlatform_FireBase = 2         //FireBase打点

};

@protocol MGUnionENSDKDelegate

@required

/**
 账号退出
 
 @param uid 退出账号的uid
 */
- (void)mg_logout:(NSString *)uid;

/**
 账号登录
 
 @param user    用户信息
 @param err   错误信息
 */
- (void)mg_login:(MGUnionENSDKUser *)user error:(MGAuthErrCode )err;



/**
 旧订单验证
 
 初次下单付款后因某些原因验证失败,后续中订单被验证通过
 注:这里还是会存在部分遗漏(初次验证失败,后用户更换账号,再次验证成功,但是本order非本uid所有,当用户切换会订单对应uid时不会再次通知)

 @param orderNum 订单标识
 */
- (void)mg_oldOrderVerficationSuccess:(NSString *)orderNum cpext:(NSString *)cpext;


@end


#endif /* MGUnionEnSDKProtocol_h */
