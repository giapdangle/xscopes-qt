#ifndef LIBUSBDEVICE_H
#define LIBUSBDEVICE_H

#include <QObject>
#include <QtConcurrentRun>
#include <QFuture>
#include <libusb.h>
#include <libusbdeviceinfo.h>
#include <QDebug>



class LibUsbDevice : public QObject
{
    Q_OBJECT
public:
    explicit LibUsbDevice(QObject *parent = 0);
    void initializeDevice();
    void openDevice();
    void closeDevice();
    void eventThread();
  //  static void LIBUSB_CALL asyncBulkReadTransferCallback(struct libusb_transfer *);
   // static int LIBUSB_CALL hotplugCallback(libusb_context *, libusb_device *, libusb_hotplug_event, void *);
   // static int LIBUSB_CALL hotplugCallbackDetach (libusb_context *, libusb_device *, libusb_hotplug_event, void *);
    bool controlReadTransfer(uint8_t command, uint16_t value = 0, uint16_t index = 0 );
    void asyncBulkReadTransfer();
    void controlWriteTransfer(uint16_t index, uint8_t value);
    QString requestFirmwareVersion();
    void stopScope();
    void startScope();
    void forceTrigger();
    void autoSetup();

    QString getStringFromUnsignedChar( unsigned char *,int);

public:
    bool isDeviceConnected,isInitialiazed;
    QString cstatus;
    libusb_device_handle *deviceHandle;
    libusb_context *context;
    libusb_hotplug_callback_handle hotplugHandle[2];
    struct libusb_transfer *pcToUsbDeviceTransfer;
    struct libusb_transfer *usbDeviceToPcTransfer;
    bool dataAvailable;
    int count;
    uint8_t chData[LEN_BULK_IN_BUFFER];
    unsigned char inBuffer[LEN_CONTROL_BUFFER];
    bool enableEventThread,hasHotPlugSupport;
    QFuture<void> future;
    
signals:
    
public slots:
    
};

#endif // LIBUSBDEVICE_H