//
//  ZJVideoManagerDelegate.h
//  ZjVideo
//
//  Created by 李志朋 on 2018/10/22.
//  Copyright © 2018年 Facebook. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@protocol ZJVideoManagerDelegate <NSObject>

@optional

// 连接会议成功
- (void)conferenceConncted:(ZJSDKCallState) nCode ;

// 会中出现异常
- (void)conferenceAbnormal: (ZJSDKCallState )nCode abnormalReason:(NSString *)reason;

// 执行退出会议后，回调
- (void)conferenceDisconnect: (ZJSDKCallState )nCode;

/* 打开录制成功/失败
 * param open    : 打开录制 / 关闭录制
 * param success : 是否打开成功
 */
- (void)conferenceRecoderOpen:(BOOL )open successful:(BOOL )success ;

/* 自动获得参与者
 * 当参与者状态改变时回调此方法。
 * param participants : 本次会议所有与会者的名单。
 * 它包含关于参与者的详细信息，如文档中所示。
 */
- (void)changeParticipants: (NSArray *)participants;

/* 自动获取会议室状态
 * 当会议管理信息发生变化时，回调此方法。
 * param conferenceInfo : 当前会议管理的具体信息
 * 主要是指 1.静音全部访客; 2.锁定会议;
 */
- (void)changeConference: (NSDictionary *)conferenceInfo;

/* 自动获取本地参会者信息
 * 当会议管理信息发生变化时，回调此方法。
 * param localParticipant : 本地参会者信息
 */
- (void)localParticipant : (NSDictionary *)localParticipant;

/** 返回会中的信息 */
/** 获取会中丢包信息
 *  param packet : 音视频丢包信息
 */
- (void)packetLoss: (NSDictionary *)packet;

/** 接收文字消息
 *  param packet : 文字消息
 */
- (void)receiveMessage: (NSDictionary *)message;

/** 本地语音/视频模式发生切换
 *  param open : 是否为视频状态
 */
- (void)videoChangeStatus: (BOOL )open ;

/** 本地音频被其它程序占用
 */
- (void)audioInterruptionBegan ;

/** 另一程序 结束音频占用
 * timeInterval
 */
- (void)audioInterruptionEndedAnTime:(NSTimeInterval )timeInterval;
@end

NS_ASSUME_NONNULL_END
