//
//  MGUnionENSDK.h
//  MGUnionENSDK
//
//  Created by Mr.Song on 2018/6/12.
//  Copyright © 2018 WeiYouHuDong. All rights reserved.
//


/*
 *************************************************************************
 
 --------- 接入指南 ---------
 
 1.工程配置
 配置 Other Linker Flags   -Objc && -all_load
 
 
 2. 配置 Facebook(info.plist 中)
 
 1>, info.plist 配置FacebookAppID,FacebookDisplayName
 
 2> //复制以下信息配置到 info.plist 中
 <?xml version="1.0" encoding="UTF-8"?>
 <!DOCTYPE plist PUBLIC "-//Apple//DTD PLIST 1.0//EN" "http://www.apple.com/DTDs/PropertyList-1.0.dtd">
 <plist version="1.0">
 <array>
 <string>fbapi</string>
 <string>fb-messenger-share-api</string>
 <string>fbauth2</string>
 <string>fbshareextension</string>
 </array>
 </plist>
 
 
 3> 配置 https 白名单
 

 
 3.AppDelegate 配置
 
 - (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {
    //{产品id:价格(单位元)}
    NSDictionary *products = @{@"SNGeva001":@"6",@"SNGeva002":@"12",...};
 [MGUnionENSDK registSDKwithAppkey:@"1187796482" productids:products loginType:MG_ForceSelect delegate:self application:application launchOptions:launchOptions];
    return YES;
 }
 
 // 以下用于同步状态(必须)
 - (void)applicationDidBecomeActive:(UIApplication *)application {
     [MGUnionENSDK applicationDidBecomeActive:application];
 }

 - (BOOL)application:(UIApplication *)application
             openURL:(NSURL *)url
             options:(NSDictionary<UIApplicationOpenURLOptionsKey,id> *)options {
     
     return [MGUnionENSDK application:application openURL:url options:options];
     
 }

 - (BOOL)application:(UIApplication *)application
             openURL:(NSURL *)url
   sourceApplication:(NSString *)sourceApplication
          annotation:(id)annotation {
     
     return [MGUnionENSDK application:application openURL:url
                                                         sourceApplication:sourceApplication
                                                                annotation:annotation];
 }

 - (BOOL)application:(UIApplication *)application continueUserActivity:(NSUserActivity *)userActivity restorationHandler:(void (^)(NSArray<id<UIUserActivityRestoring>> * _Nullable))restorationHandler {
     return [MGUnionENSDK application:application continueUserActivity:userActivity restorationHandler:restorationHandler];
 }

 - (void)application:(UIApplication *)application didReceiveRemoteNotification:(NSDictionary *)userInfo fetchCompletionHandler:(void (^)(UIBackgroundFetchResult))completionHandler {
     [MGUnionENSDK application:application didReceiveRemoteNotification:userInfo fetchCompletionHandler:completionHandler];
 }

 
 
 //代理配置
 
 - (void)mg_logout:(NSString *)uid {
 }
 
 
 - (void)mg_login:(MGUnionENSDKUser *)user error:(MGAuthErrCode)error {
    if (error == MGSDKAuth_Err_Ok) {
        NSLog(@"登录成功---%@",user.userID);
    } else {
        NSLog(@"登录失败");
    }
 }
 
 - (void)mg_oldOrderVerficationSuccess:(NSString *)orderNum {
 
 }
 

 4. A:自动登录;优先登录本地(最后一次登录)账户,没有本地账户先触发GameCenter登录,GameCenter失败后进行游客登录
    B:强制选择登录
 [MGUnionENSDK login]

 
 5. 个人中心
    登录再次进行账户的切换会触发mg_logout回调,会传回原账号的uid
 
 6. 支付

 * 发起支付成功且校验通过后会回调成功,错误会返回错误原因
 * 支付成功后但校验失败回调失败,在后续继续校验成功后会通过delegate告知


 
 *************************************************************************
 */

#import <Foundation/Foundation.h>
#import "MGUnionEnSDKProtocol.h"
#import "MGUnionENSDKUser.h"
#import <UIKit/UIKit.h>



typedef NS_ENUM (NSInteger,MGPayErrCode) {
    MGSDKPay_Err_Ok = 0,                //Pay成功
    MGSDKPay_Err_OrderErr = -1,         //获取订单失败
    MGSDKPay_Err_ProductErr = -2,       //获取产品失败
    MGSDKPay_Err_PaymentErr = -3,       //支付失败
    MGSDKPay_Err_VerifyErr = -4         //校验订单失败
};


typedef void (^MGPaymentBlock)(NSString *orderNum, MGPayErrCode error);


@interface MGUnionENSDK : NSObject


/**
 注册SDK

 @param appkey      游戏的appkey
 @param ids         可购买产品的ID与价格
 @param loginType   默认登录方式
 @param delegate    SDK代理(推荐用AppDelegate)
 */
+ (void)registSDKwithAppkey:(NSString *)appkey
                 productids:(NSDictionary *)ids
                  loginType:(MGDefaultLoginType) loginType
                   delegate:(id<MGUnionENSDKDelegate>)delegate
                application:(UIApplication *)application
              launchOptions:(NSDictionary *)launchOptions;


/**
 Debug信息
 
 @param flag  是否允许 Debug 信息,包括order的时候亦用test
 注意: 上传App Store的时候不要设置为YES
 */

+ (void) setDebug:(BOOL)flag;


/**
 * 执行登录命令
 * 已经登录过的默认会走本地账户登录
 */
+ (void)login;

+ (void)logout;


/**
 * 显示账户信息
 */
+ (void)showPersonCenter;

/**
 * 显示绑定用户界面(仅当当前用户是游客是起效)
 */
+ (void)linkAccout;

/**
 * Get The Price with local currency 例如：￥6.00，$0.99
 * productid 商品id
 */

+ (NSString *)getLocalePrice:(NSString *)productid;

/**
 支付(新)
 
 @param productid   下单的产品id
 @param orderid     订单ID(校验用)
 @param cpex        透传参数(不做处理,原样返回)
 @param paymentBlock    支付回调

 */
+ (void)paymentWithProductid:(NSString *)productid
                     orderid:(NSString *)orderid
                        cpex:(NSString *)cpex
                    callback:(MGPaymentBlock)paymentBlock;


/**
 支付(旧),兼容用,新接入不要使用,即将淘汰
 
 @param productid 下单的产品id
 @param orderNum   标记位(单号标识,用订单号或其md5)
 @param paymentBlock    支付回调

 */
+ (void)paymentWithProductid:(NSString *)productid
                        sign:(NSString *)orderNum
                    callback:(MGPaymentBlock)paymentBlock;


/**
 * 返回当前的用户(后台切换前台不需要登录时可直接获取用户信息)
 */
+ (MGUnionENSDKUser *)currentUser;

/**
 * 以下五个API与appdelegate同名,用于同步应用状态
 */
+ (void)applicationDidBecomeActive:(UIApplication *)application;

+ (BOOL)application:(UIApplication *)application
            openURL:(NSURL *)url
  sourceApplication:(NSString *)sourceApplication
         annotation:(id)annotation;

+ (BOOL)application:(UIApplication *)application
            openURL:(NSURL *)url
            options:(NSDictionary<UIApplicationOpenURLOptionsKey,id> *)options;

+ (BOOL)application:(UIApplication *)application continueUserActivity:(NSUserActivity *)userActivity restorationHandler:(void (^)(NSArray<id<UIUserActivityRestoring>> * _Nullable))restorationHandler;

+ (void)application:(UIApplication *)application didReceiveRemoteNotification:(NSDictionary *)userInfo fetchCompletionHandler:(void (^)(UIBackgroundFetchResult))completionHandler;


/**
 AppFlyer统计
 
 两个API,按需选用
 
 @eventName     事件名
 @values        事件参数
 */


/*
 AF的收入需要手动添加,参考如下
 [MGUnionENSDK  afTrackEvent: AFEventPurchase parameters:@{
     AFEventParamContentId:@"1234567", //商品
     AFEventParamContentType : @"category_a",//商品类型
     AFEventParamRevenue: @1.99,//价格
     AFEventParamCurrency:@"USD"//货币类型https://docs.openexchangerates.org/docs/supported-currencies
 }];
 */

+ (void)afTrackEvent:(NSString *)eventName parameters:(NSDictionary *)parameters;

+ (void)afTrackEvent:(NSString *)eventName;

/**
FaceBook统计
三个API,按需选用
需要注意支付的统计是FacebookSDK内部自动完成的,支付的打点统计需要用户自己调用自定义事件

@eventName     事件名
@valuesToSum    价格/评分/点数等,仅在部分标准事件中应用(参看Facebook文档:https://developers.facebook.com/docs/app-events/getting-started-app-events-ios/?translation#predefined-events)
*/

+ (void)fbTrackEvent:(NSString *)eventName parameters:(NSDictionary *)parameters;

+ (void)fbTrackEvent:(NSString *)eventName;



@end

