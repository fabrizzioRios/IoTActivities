#include "mqtt_frames.h"
#include <stdio.h>


sConnect vfnCreateFrame(char *argv, uint16_t wNum)
{
    sConnect sFrameConnect;
    printf("Hello From vfnCreateFrame");

    sFrameConnect.bFrameType = 0x10;
    sFrameConnect.wMsgLen = wNum;
    sFrameConnect.wProtlNameLen = 0x0004;
    sFrameConnect.sProtName [0]= 'M';
    sFrameConnect.sProtName [1]= 'Q';
    sFrameConnect.sProtName [2]= 'T';
    sFrameConnect.sProtName [3]= 'T';
    sFrameConnect.bVersion = 0x04;
    sFrameConnect.bConnectFlags = 0x02;
    sFrameConnect.bKeepAlive = 0x000A;
    sFrameConnect.wClientIdLen = 0x0005;
    sFrameConnect.sClientID [0] = 'J';
    sFrameConnect.sClientID [1] = 'S';
    sFrameConnect.sClientID [2] = 'C';
    sFrameConnect.sClientID [3] = 'H';
    sFrameConnect.sClientID [4] = 'N';

    return sFrameConnect;
}

sConnACK vfnCreateCONNACK()
{
    sConnACK sFrameCONNACK;
    printf("ConnectionAckNowledge");

    sFrameCONNACK.bFrameType = 0x20;
	sFrameCONNACK.bMsgLength = 2;
    sFrameCONNACK.bFlags = 0x00;
    sFrameCONNACK.bReturnCode = 0x00;

    return sFrameCONNACK;

}

sPublish vfnCreatePUBLISH()
{
    sPublish sFramePublish;
    printf("Published");

    sFramePublish.bFrameType = 0x30;
    sFramePublish.sTopic [3] = 'KFC';
    sFramePublish.sMessage [4] = 'HOLA';
    sFramePublish.wTopicLength = strlen(sFramePublish.sTopic);
    sFramePublish.wMessageLength = strlen(sFramePublish.sMessage);
    sFramePublish.bRemainingLength = sFramePublish.wTopicLength + 3;

    return sFramePublish;
}

sSubscribe vfnCreateSUBSCRIBE()
{
    sSubscribe sFrameSubscribe;
    printf("Subscribed");

    sFrameSubscribe.bFrameType = 0x82 ;
    sFrameSubscribe.wPacketIdentifier = 1234;
    sFrameSubscribe.sTopic [0] = 'S' ;
    sFrameSubscribe.sTopic [1] = 'U' ;
    sFrameSubscribe.sTopic [2] = 'B' ;
    sFrameSubscribe.bRequestedQOS = 0;
    sFrameSubscribe.wTopicNameLength = strlen(sFrameSubscribe.sTopic);
    sFrameSubscribe.bRemainingLength = sFrameSubscribe.wTopicNameLength + 3;

    return sFrameSubscribe;
}

sUnsubscribe vfnCreateUNSUBSCRIBE()
{
    sUnsubscribe sFrameUnsubscribe;
    printf("UnSubscribed");

    sFrameUnsubscribe.bFrameType = 0xA2;
    sFrameUnsubscribe.wPacketIdentifier = 1234;
    sFrameUnsubscribe.sTopic [0] = 'B' ;
    sFrameUnsubscribe.sTopic [1] = 'Y' ;
    sFrameUnsubscribe.sTopic [2] = 'E' ;
    sFrameUnsubscribe.wTopicNameLength = strlen(sFrameUnsubscribe.sTopic);
    sFrameUnsubscribe.bRemainingLength = sFrameUnsubscribe.wTopicNameLength + 3;

    return sFrameUnsubscribe;
}

sPingReq vfnCreateREQUEST()
{
    sPingReq sFramesPingReq;
    printf("Request");

    sFramesPingReq.bFrameType = 0xC0;
    sFramesPingReq.bMsgLength = 0;

    return sFramesPingReq;

}

sPingRes vfnCreateRESPONSE()
{
    sPingRes sFramesPingRes;
    printf("Response");

    sFramesPingRes.bFrameType = 0x00;
    sFramesPingRes.bRemainingLength = 0;

    return sFramesPingRes;
}

sDisconnect vfnDISCONNECT()
{
    sDisconnect sFrameDisconnect;
    printf("Disconnect");
    sFrameDisconnect.bFrameType = 0xE0;
    sFrameDisconnect.bRemainingLength = 0;

    return sFrameDisconnect;

}
