
#include "mqtt_frames.h"
#include <stdio.h>
char pubRes;
sConnect vfnCreateFrame(char *argv, uint16_t wNum) {
  sConnect sFrameConnect;
  printf("Conectado...\n");

  sFrameConnect.bFrameType = 0x10;
  sFrameConnect.wMsgLen = wNum;
  sFrameConnect.wProtlNameLen = 0x0004;
  sFrameConnect.sProtName[0] = 'M';
  sFrameConnect.sProtName[1] = 'Q';
  sFrameConnect.sProtName[2] = 'T';
  sFrameConnect.sProtName[3] = 'T';
  sFrameConnect.bVersion = 0x04;
  sFrameConnect.bConnectFlags = 0x02;
  sFrameConnect.bKeepAlive = 0x40;
  sFrameConnect.wClientIdLen = 0x0005;
  sFrameConnect.sClientID[0] = 'J';
  sFrameConnect.sClientID[1] = 'S';
  sFrameConnect.sClientID[2] = 'C';
  sFrameConnect.sClientID[3] = 'H';
  sFrameConnect.sClientID[4] = 'N';

  return sFrameConnect;
}

sConnACK vfnCreateCONNACK() {
  sConnACK sFrameCONNACK;
  printf("ConnectionAckNowledge...\n");

  sFrameCONNACK.bFrameType = 0x20;
  sFrameCONNACK.bMsgLength = 2;
  sFrameCONNACK.bFlags = 0x00;
  sFrameCONNACK.bReturnCode = 0x00;

  return sFrameCONNACK;
}

sPublish vfnCreatePUBLISH() {
  sPublish sFramePublish;
  printf("Published...\n");

  sFramePublish.bFrameType = 0x30;
  sFramePublish.sTopic[0] = 'K';
  sFramePublish.sTopic[1] = 'F';
  sFramePublish.sTopic[2] = 'C';
  sFramePublish.sMessage[0] = 'P';
  sFramePublish.sMessage[1] = 'O';
  sFramePublish.sMessage[2] = 'l';
  sFramePublish.sMessage[3] = 'l';
  sFramePublish.sMessage[4] = 'o';
  sFramePublish.wTopicLength = strlen(sFramePublish.sTopic);
  sFramePublish.wMessageLength = strlen(sFramePublish.sMessage);
  sFramePublish.bRemainingLength = sFramePublish.wTopicLength + 3;
  scanf("%d", &pubRes);
  return sFramePublish;
}

sSubscribe vfnCreateSUBSCRIBE() {
  sSubscribe sFrameSubscribe;
  printf("Subscribed...\n");

  sFrameSubscribe.bFrameType = 0x82;
  sFrameSubscribe.wPacketIdentifier = 1234;
  sFrameSubscribe.sTopic[0] = 'K';
  sFrameSubscribe.sTopic[1] = 'F';
  sFrameSubscribe.sTopic[2] = 'C';
  sFrameSubscribe.bRequestedQOS = 0;
  sFrameSubscribe.wTopicNameLength = strlen(sFrameSubscribe.sTopic);
  sFrameSubscribe.bRemainingLength = sFrameSubscribe.wTopicNameLength + 3;
  printf("%s\n", pubRes);
  return sFrameSubscribe;
}

sPingReq vfnCreateREQUEST() {
  sPingReq sFramesPingReq;
  printf("Request");

  sFramesPingReq.bFrameType = 0xC0;
  sFramesPingReq.bMsgLength = 0;

  return sFramesPingReq;
}
sPingRes vfnCreateRESPONSE() {
  sPingRes sFramesPingRes;
  printf("Response");

  sFramesPingRes.bFrameType = 0x00;
  sFramesPingRes.bMsgLength = 0;

  return sFramesPingRes;
}

sDisconnect vfnDISCONNECT() {
  sDisconnect sFrameDisconnect;
  printf("Disconnect");
  sFrameDisconnect.bFrameType = 0xE0;
  sFrameDisconnect.bRemainingLength = 0;

  return sFrameDisconnect;
}
