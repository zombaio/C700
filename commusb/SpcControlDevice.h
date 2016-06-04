﻿//
//  SpcControlDevice.h
//  gimicUsbSpcPlay
//
//  Created by osoumen on 2014/06/14.
//  Copyright (c) 2014年 osoumen. All rights reserved.
//

#ifndef __gimicUsbSpcPlay__SpcControlDevice__
#define __gimicUsbSpcPlay__SpcControlDevice__

#include "ControlUSB.h"

class SpcControlDevice {
public:
    SpcControlDevice();
    virtual ~SpcControlDevice();
    
    virtual bool InitUsb();
    virtual bool CloseUsb();
    virtual int Init();
    virtual int Close();
    virtual void Reset();
    virtual bool CheckHasRequiredModule();
    virtual void PortWrite(int addr, unsigned char data);
    virtual unsigned char PortRead(int addr);
    virtual void BlockWrite(int addr, unsigned char data);
    virtual void BlockWrite(int addr, unsigned char data, unsigned char data2);
    virtual void BlockWrite(int addr, unsigned char data, unsigned char data2, unsigned char data3);
    virtual void BlockWrite(int addr, unsigned char data, unsigned char data2, unsigned char data3, unsigned char data4);
    virtual void ReadAndWait(int addr, unsigned char waitValue);
    virtual void WriteAndWait(int addr, unsigned char waitValue);
    virtual void WriteBuffer();
    virtual void WriteBufferAsync();
    virtual int CatchTransferError();
    
    int UploadRAMDataIPL(const unsigned char *ram, int addr, int size, unsigned char initialP0state);
    int WaitReady();
    int JumpToCode(int addr, unsigned char initialP0state);
    virtual void setDeviceAddedFunc( void (*func) (void* ownerClass), void* ownerClass );
	virtual void setDeviceRemovedFunc( void (*func) (void* ownerClass) , void* ownerClass );

private:
    static const int GIMIC_USBVID = 0x16c0;
    static const int GIMIC_USBPID = 0x05e5;
    static const int GIMIC_USBWPIPE = 0x02;
    static const int GIMIC_USBRPIPE = 0x85;
    static const int BLOCKWRITE_CMD_LEN = 4;
    static const int MAX_ASYNC_READ = 64;
    static const int PACKET_SIZE = 64;

    ControlUSB      *mUsbDev;
    unsigned char   mWriteBuf[64];
    unsigned char   mReadBuf[64];
    int             mWriteBytes;
    
    //int mNumReads;  // Read待ちのパケット数
};

#endif /* defined(__gimicUsbSpcPlay__SpcControlDevice__) */
