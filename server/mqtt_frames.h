#include <arpa/inet.h>
#include <errno.h>
#include <netinet/in.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

typedef struct {
  uint8_t bFrameType; // 0x10
  uint16_t wMsgLen;
  uint16_t wProtlNameLen; // 0x0004
  char sProtName[4];      // String MQTT
  uint8_t bVersion;       // 0x04
  uint8_t bConnectFlags;  // 0x02
  uint16_t bKeepAlive;
  uint16_t wClientIdLen;
  char sClientID[100];
} sConnect;

typedef struct {
  uint8_t bFrameType;
  uint8_t bMsgLength;
  uint8_t bFlags;
  uint8_t bReturnCode;

} sConnACK;

typedef struct {
  uint8_t bFrameType;
  char *sTopic[3];
  char *sMessage[4];
  uint16_t wTopicLength;
  uint16_t wMessageLength;
  uint8_t bRemainingLength;

} sPublish;

typedef struct {
  uint8_t bFrameType;
  uint8_t bRemainingLength;
  uint16_t wPacketIdentifier;
  uint16_t wTopicNameLength;
  char *sTopic[3];
  uint8_t bRequestedQOS;

} sSubscribe;

typedef struct {
  uint8_t bFrameType;
  uint8_t bRemainingLength;
  uint16_t wPacketIdentifier;
  uint16_t wTopicNameLength;
  char *sTopic[3];

} sUnsubscribe;

typedef struct {

  uint8_t bFrameType;
  uint8_t bMsgLength;

} sPingReq;

typedef struct {

  uint8_t bFrameType;
  uint8_t bRemainingLength;

} sPingRes;

typedef struct {
  uint8_t bFrameType;
  uint8_t bRemainingLength;

} sDisconnect;

sConnect vfnCreateFrame(char *argv, uint16_t bNum);
sConnACK vfnCreateCONNACK();
sPublish vfnCreatePUBLISH();
sSubscribe vfnCreateSUBSCRIBE();
sUnsubscribe vfnCreateUNSUBSCRIBE();
sPingReq vfnCreateREQUEST();
sPingRes vfnCreateRESPONSE();
sDisconnect vfnDISCONNECT();
