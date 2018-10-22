//
//  ZJVideoManager.h
//  ZjVideo
//
//  Created by zj on 3/12/18.
//  Copyright © 2018 Facebook. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <Foundation/Foundation.h>
#import "NSMutableDictionary+ZJSDKVideo.h"
#import "ZJSDKTypeDefine.h"
#import "ZJVideoManagerDelegate.h"

@interface ZjRCTManager : NSObject

/** 单例实现Manager */
+ (id)sharedManager;

/** 普通入会配置 */
/** api server address , 设置 api 私有云地址。
 *  apiServer : api server address
 *  未设置默认使用 公有云地址
 */
@property(nonatomic, readonly) NSString *apiServer;

- (void)setApiServer: (NSString *)apiServer;

/** 选择接收音视频方式
 * modelType : 接收音视频方式
 * 未设置默认使用 全编全解
 */
- (void)selectReceiveVideoModel:(ReceiveVideoModel )modelType ;

/** 加入会议
 *  @param conferenceModel  : 连接入会的参数设置（必填参数，密码为空时，可传空字符串）
 *  @param modelType : 连接入会的身份
 */
- (void)connectWithModel:(NSDictionary *)conferenceModel
             andCapacity:(ConncetCapacityModel )modelType ;

/** 加入会议
 *  @param conferenceModel  : 加入会议的参数设置（必填参数，密码为空时，可传空字符串）
 *  @param isShow           : 是否显示功能按钮（静音，静画，切换摄像头等）
 *  @param isAuto           : 是否自动跳转到控制器
 */
- (void)connectWithModel:(NSDictionary *)conferenceModel
        showFunctionItem:(BOOL)isShow
      isAutoPrePresentVC:(BOOL)isAuto;

/** 加入会议
 *  @param conferenceModel  : 加入会议的参数设置（必填参数，密码为空时，可传空字符串）
 *  @param params           : 通话质量的参数设置（非必填参数，传空字典类型，使用默认值）
 *  @param isShow           : 是否显示功能按钮（静音，静画，切换摄像头等）
 *  @param isAuto           : 是否自动跳转到控制器
 */
- (void)connectWithModel:(NSDictionary *)conferenceModel
             videoParams:(NSDictionary *)params
        showFunctionItem:(BOOL)isShow
      isAutoPrePresentVC:(BOOL)isAuto;

/* 会中界面 */
@property(nonatomic, strong)UIView *conferenceView;


/** 使用平台账号服务,实现注册到平台、被叫等功能 */

/**
 *  实现功能 : 设置voip推送服务证书名称和信令<token>
 *  cartificateName : voip推送服务证书名称
 *  voipToken : voip推送服务证书信令<token>
 *  获取方式具体见apple developer文档
 */
@property(nonatomic, readonly) NSString *cartificateName;

- (void)setCartificateName: (NSString *)cartificateName ;

@property(nonatomic, readonly) NSString *voipToken;

- (void)setVoipToken: (NSString *)voipToken;

/**
 *  注册账号到mcu
 *  @param account           : 注册的用户账号
 *  @param pwd               : 注册的用户密码
 *  @param completionHandler : 注册回调
 */
- (void)registerAccount:(NSString *)account
           withPassword:(NSString *)pwd
      completionHandler:(ZJVideoSDKCompletionHandler)completionHandler;

/**
 *  拒绝当前通话
 *  @param account           : 主叫的用户账号
 *  @param token             : 接口地址
 *  @param completionHandler : 拒接回调
 */
- (void)callRejectWithAccount:(NSString *)account
                    withToken:(NSString *)token
            completionHandler:(ZJVideoSDKCompletionHandler)completionHandler;



/** 使用图片分享功能，实现Library、iCloud、屏幕共享会中分享图片  */

/* apple developer registered groupId , 只要作用实现设备屏幕录制 */
@property(nonatomic, retain)NSString *groupId;
/* 自定制 video uri */
@property(nonatomic, strong)NSArray *videoUri;


/** 使用会中管理功能 */

@property(nonatomic, weak)id <ZJVideoManagerDelegate> delegate ;

/** 实现功能 : 切换本端音频
 *  静音本地，远端收不到本端音频。
 */
- (void)toggleLocalAudio;

/** 实现功能 : 切换本端视频
 *  关闭显示本地视频，但远端仍然能接受到视频。
 */
- (void)toggleLocalVideo;

/** 实现功能 : 开启／关闭本端视频
 *  关闭显示本地视频，且远端不能接受到视频。
 */
- (void)toggleVideo;

/** 实现功能 : 切换摄像头
 *  设备前后摄像头切换
 */
- (void)toggleCamera;

/** 实现功能 : 退出当前会议室
 *  本地参会者退出
 */
- (void)outOfCurrentMeeting;

/** 实现功能 : 结束当前会议
 * 断开所有与会者
 */
- (void)endAllMeeting;

/** 实现功能 : 邀请参会者入会
 *  param account 用户账号
 *  param role 入会身份
 *  param protocol 入会协议
 */
- (void)inviteUserAccount:(NSString *)account
                 withRole:(InviteParticipantRole )role
             withProtocol:(InviteParticipantProtocol )protocol;

/** 静音全部访客 */
- (void)muteAllGuest;

/** 锁定当前会议 */
- (void)lockCurConference;

/** 退出会议 */
- (void)disconnectConference;

/** 结束本次会议 */
- (void)disconnectAllConference;

/** 允许指定与会者参加会议
 *  @param Participant 指定与会者
 */
- (void)answerParticipant: (NSDictionary *)Participant;

/** 拒绝指定与会者参加会议
 *  @param Participant 指定与会者
 */
- (void)refuseParticipant: (NSDictionary *)Participant;

/** 取消邀请指定与会者  (遇到出现的问题，暂不可用)
 *  @param Participant 指定与会者
 */
- (void)cancelParticipant: (NSDictionary *)Participant;

/** 改变指定与会者显示名称
 *  @param Participant 指定与会者
 *  @param name 变化之后的名称
 */
- (void)changeParticipant: (NSDictionary *)Participant
                withName: (NSString *)name;

/** 移除指定与会者
 *  @param Participant 指定与会者
 */
- (void)removeParticipant: (NSDictionary *)Participant;

/** 静音指定与会者
 *  @param Participant 指定与会者
 */
- (void)muteParticipant: (NSDictionary *)Participant;

/** 改变指定与会者身份
 *  @param Participant 指定与会者
 */
- (void)transferParticipant: (NSDictionary *)Participant;

/** 开启录制
 *  @param isRecord 是否开启录制
 */
- (void)startRecord: (BOOL)isRecord;

/** 开启直播
 *  @param isLiving 是否开启直播
 */
- (void)startLiving: (BOOL)isLiving;

/** 更新布局
 *  @param hlayout 主持人布局
 *  @param glayout 访客布局
 */
- (void)updateLayout: (NSString *)hlayout
              withG: (NSString *)glayout;

/** 开启、关闭网络丢包
 *  @param open 是否开启网络丢包检测
 */
- (void)switchObtainPacketLoss:(BOOL)open;

/** 发送文字信息
 *  message : 文字信息
 */
- (void)sendMessage:(NSDictionary *)message ;


/**
 *  Deprecated
 *  加入会议室
 *  @param target        : 会议室的短号或者长地址
 *  @param name          : 入会显示名称
 *  @param pwd           : 入会密码
 *  @param server        : 接口地址
 *  @param input         : 接受速率
 *  @param output        : 发送速率
 *  @param minFps        : 发送帧率
 *  @param expectedFps   : 接受帧率
 *  @param videoSize     : 发送分辨率
 *  @param expectedSize  : 接受分辨率
 *  @param isShow        : 是否显示功能按钮（静音，静画，切换摄像头等）
 *  @param isAuto        : 是否自动跳转到控制器
 */
- (void)connectTarget:(NSString *)target
                 name:(NSString *)name
             password:(NSString *)pwd
            apiServer:(NSString *)server
          bandwidthIn:(NSInteger )input
         bandwidthOut:(NSInteger )output
               minFps:(NSInteger)minFps
          expectedFps:(NSInteger)expectedFps
            videoSize:(struct ZJVideoSize)videoSize
         expectedSize:(struct ZJVideoSize)expectedSize
     showFunctionItem:(BOOL )isShow
   isAutoPrepresentVC:(BOOL )isAuto;

@end
