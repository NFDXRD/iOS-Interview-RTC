//
//  ZJSDKTypeDefine.h
//  iosRN
//
//  Created by 李志朋 on 2018/3/16.
//  Copyright © 2018年 Facebook. All rights reserved.
//

#ifndef ZJSDKTypeDefine_h
#define ZJSDKTypeDefine_h

typedef struct ZJVideoSize {
  int videoWidth;    /** < 视频分辨率宽 > **/
  int videoHeight;   /** < 视频分辨率高 > **/
} ZJVideoSize;

typedef NS_ENUM (NSUInteger, ZJSDKCallState){
  ZjCallConnected    =  0,         /** < 视屏通话建立连接成功 > **/
  ZjCallError        =  1,         /** < 视频通话建立过程中出现的错误 > **/
  ZjCallEnd          =  2,         /** < 视频通话结束 > **/
  ZjCallStateMute    =  3,         /** < 视频被静音 >  **/
  ZjCallHappenError  =  4,         /** < 视频通话过程中出现的错误 > **/
  ZjCallObtainUUID   =  5,         /** < 第一次获得uuid > **/
  ZjCallNetworkChange=  6,         /** < 网络发生改变 > **/
  ZjCallRegisterAccountFaild = 7,  /** < 注册账号到mcu失败 > **/
};

typedef NS_ENUM(NSUInteger, ZJAVCallGear){
  ZJAVCallGearVideoHD = 0,
  ZJAVCallGearVideoVGA = 1
};

/** 参数按< 下载带宽 上传带宽 下载分辨率 上传分辨率 >设置 **/
typedef NS_ENUM(NSInteger, ZJVideoParamState){
  ZJVideoParam_720P = 0, /** < 1280 1280 1280x720 1280x720 > **/
  ZJVideoParam_576P = 1, /** < 1024 1024 1024x576 1024x576 > **/
  ZJVideoParam_448P = 2, /** < 768 768 768x448 768x448 > **/
  ZJVideoParam_VGA  = 3, /** < 640 640 640x360 640x360 > **/
};

typedef NS_ENUM(NSInteger, ZJVideoType){
  ZJVideoTypeWithVideo  = 0, /** < 音视频正常入会 > **/
  ZJVideoTypeWithHideMe = 1  /** < 隐身加入会议 > **/
};

typedef NS_ENUM(int ,ZJAVCallCodec){
  ZJAVCallCodecH264    = 0,
  ZJAVCallCodecVP8     = 1,
  ZJAVCallCodecVP9     = 2,
  ZJAVCallCodecH264_P  = 3
};

typedef NS_ENUM(NSInteger, InviteParticipantRole) {
  InviteParticipantRoleHost = 0,
  InviteParticipantRoleGuest = 1
};

typedef NS_ENUM(NSInteger , InviteParticipantProtocol) {
  InviteParticipantProtocolSip = 0,
  InviteParticipantProtocolH323 = 1,
  InviteParticipantProtocolRtmp = 2,
  InviteParticipantProtocolMssip = 3,
  InviteParticipantProtocolAuto = 4
};

typedef NS_ENUM(NSInteger, ReceiveVideoModel ) {
  ReceiveVideoModelNormal = 0,   // 全编全解
  ReceiveVideoModelSimulcast = 1 // 转发（多流）
};

typedef NS_ENUM(NSInteger, ConncetCapacityModel) {
  ConncetCapacityModelHost = 0, // 面试官
  ConncetCapacityModelGuest = 1 // 面试者
};

typedef NS_ENUM(NSInteger, ConferenceCameraStatus) {
  ConferenceCameraStatusFront = 0, // 前摄像头
  ConferenceCameraStatusBack = 1 // 后摄像头
};

typedef void(^ZJVideoSDKCompletionHandler) (NSData *  data,NSURLResponse *  response,NSError *  error);

#endif /* ZJSDKTypeDefine_h */
