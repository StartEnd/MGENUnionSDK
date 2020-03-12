//
//  MGUnionENSDKUser.h
//  MGUnionENSDK
//
//  Created by Mr.Song on 2018/6/29.
//  Copyright © 2018 WeiYouHuDong. All rights reserved.
//

#import <Foundation/Foundation.h>

typedef NS_ENUM (NSInteger,MGUserType)
{
    MGUserType_Tourist,             //游客
    MGUserType_Register             //绑定了第三方账户
};

@interface MGUnionENSDKUser : NSObject

@property(strong, nonatomic) NSString*                          userID;

@property(strong, nonatomic) NSString*                          userToken;

@property(assign, nonatomic) MGUserType                         userType;

@property(assign, nonatomic,getter=isBindingFacebook)  BOOL     bindingFacebook;

@property(assign, nonatomic,getter=isBindingGameCenter) BOOL    bindingGameCenter;
@property(assign, nonatomic,getter=isBindingApple)      BOOL    bindingApple;

@property(strong, nonatomic)NSString*                           facebookNickName;

@property(strong, nonatomic)NSString*                           gamecenterNickName;
@property(strong, nonatomic)NSString*                           appleNickName;




@end
