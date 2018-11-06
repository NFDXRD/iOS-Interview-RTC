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
// 加入会议失败
- (void)joinConferenceFaild: (int)nCode;

// 会中出现异常
- (void)conferenceAbnormal: (int)nCode;

// 执行退出会议后，回调
- (void)conferenceDisconnect: (int)nCode;

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

@end

NS_ASSUME_NONNULL_END
