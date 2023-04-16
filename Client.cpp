#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>
#include <cstring>
#include <fstream>
#include <iostream>
#include <memory>
#include <thread>

#include <fcntl.h>

#include <filesystem>
#include <chrono>
#include <ctime>

#include "Client.h"

/**************************************************************************************
**
***************************************************************************************/
#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif
#ifndef __EMSCRIPTEN__
int main(int argc , char *argv[]) {
  Client client("SVBONY SV305 0");
  client.connectServer();
  sleep(10);
  //client.takeExposure(1);
  client.toggleStream();
  std::cout << "Press Enter key to terminate the client.\n";
  std::cin.ignore();
};
#endif

Client::Client(const char *my_ccd)
{
  MYCCD = my_ccd;
  init();
}

Client::~Client()
{
}

/**************************************************************************************
**
***************************************************************************************/
void Client::takeExposure(double seconds)
{
    INDI::PropertyNumber ccdExposure = mSimpleCCD.getProperty("CCD_EXPOSURE");

    if (!ccdExposure.isValid())
    {
        IDLog("Error: unable to find CCD Simulator CCD_EXPOSURE property...\n");
        return;
    }

    setCaptureFormat("FORMAT_RAW8");

    // Take a 1 second exposure
    IDLog("Taking a %g second exposure.\n", seconds);
    ccdExposure[0].setValue(seconds);
    sendNewProperty(ccdExposure);
}

/**************************************************************************************
**
***************************************************************************************/
void Client::init()
{
  // wait for the availability of the device

  #ifdef __EMSCRIPTEN__
  emscripten_log(EM_LOG_CONSOLE, "Waiting for device %s", MYCCD);
  #endif
  watchDevice(MYCCD, [this](INDI::BaseDevice device)
  {
    mSimpleCCD = device; // save device

    #ifdef __EMSCRIPTEN__
    emscripten_log(EM_LOG_CONSOLE, "Waiting for device %s", MYCCD);
    #endif
    // wait for the availability of the "CONNECTION" property
    device.watchProperty("CONNECTION", [this](INDI::Property property)
    {
        IDLog("Connecting to INDI Driver...\n");
        IDLog("connection value: %s", property.getSwitch());
        if (mSimpleCCD.isConnected())
        {
            IDLog("CCD is connected.\n");
            setBLOBMode(B_ALSO, MYCCD, nullptr);
            mCCDProperties = mSimpleCCD.getProperties();
            for (const auto &oneProp : mCCDProperties) {
                IDLog("%s", oneProp.getName());
            }
                
        }
        else
        {
            #ifdef __EMSCRIPTEN__
            emscripten_log(EM_LOG_CONSOLE, "Waiting for device %s", MYCCD);
            #endif
            connectDevice(MYCCD);
        }
    }, INDI::BaseDevice::WATCH_NEW_OR_UPDATE);

    device.watchProperty("CCD_EXPOSURE", [this](INDI::Property property)
    {
        // exposure ready    
        IDLog("Exposure ready.\n");
    }, INDI::BaseDevice::WATCH_NEW_OR_UPDATE);

    // call if uD1"pdated of the "CC property - simplified way
    device.watchProperty("CCD1", [this](INDI::PropertyBlob property)
    {
      return onBlobUpdated(property);

    }, INDI::BaseDevice::WATCH_UPDATE);

    device.watchProperty("CCD0", [this](INDI::PropertyBlob property)
    {
      IDLog("CCD0 updated.\n");
    }, INDI::BaseDevice::WATCH_UPDATE);

    device.watchProperty("CCD2", [this](INDI::PropertyBlob property)
    {
      IDLog("CCD2 updated.\n");
    }, INDI::BaseDevice::WATCH_UPDATE);

    device.watchProperty("CCD_GAIN", [this](INDI::PropertyNumber property)
    {
      // gain ready
      auto val = property[0].getValue();
      IDLog("Gain value: %f\n", val);

      #ifdef __EMSCRIPTEN__
      MAIN_THREAD_EM_ASM({
        syncGain($0);
      }, val);
      #endif
    }, INDI::BaseDevice::WATCH_NEW_OR_UPDATE);

    device.watchProperty("CCD_CONTRAST", [this](INDI::PropertyNumber property)
    {
      // gain ready
      auto val = property[0].getValue();
      IDLog("Contrast value: %f\n", val);

      #ifdef __EMSCRIPTEN__
      MAIN_THREAD_EM_ASM({
        syncContrast($0);
      }, val);
      #endif
    }, INDI::BaseDevice::WATCH_NEW_OR_UPDATE);
    device.watchProperty("CCD_GAMMA", [this](INDI::PropertyNumber property)
    {
      // gain ready
      auto val = property[0].getValue();
      IDLog("Gamma value: %f\n", val);

      #ifdef __EMSCRIPTEN__
      MAIN_THREAD_EM_ASM({
        syncGamma($0);
      }, val);
      #endif
    }, INDI::BaseDevice::WATCH_NEW_OR_UPDATE);
    device.watchProperty("CCD_SATURATION", [this](INDI::PropertyNumber property)
    {
      // gain ready
      auto val = property[0].getValue();
      IDLog("Saturation value: %f\n", val);

      #ifdef __EMSCRIPTEN__
      MAIN_THREAD_EM_ASM({
        syncSaturation($0);
      }, val);
      #endif
    }, INDI::BaseDevice::WATCH_NEW_OR_UPDATE);
    device.watchProperty("CCD_SHARPNESS", [this](INDI::PropertyNumber property)
    {
      // gain ready
      auto val = property[0].getValue();
      IDLog("Sharpness value: %f\n", val);

      #ifdef __EMSCRIPTEN__
      MAIN_THREAD_EM_ASM({
        syncSharpness($0);
      }, val);
      #endif
    }, INDI::BaseDevice::WATCH_NEW_OR_UPDATE);
    device.watchProperty("CCD_WBB", [this](INDI::PropertyNumber property)
    {
      // gain ready
      auto val = property[0].getValue();
      IDLog("WBB value: %f\n", val);

      #ifdef __EMSCRIPTEN__
      MAIN_THREAD_EM_ASM({
        syncWBB($0);
      }, val);
      #endif
    }, INDI::BaseDevice::WATCH_NEW_OR_UPDATE);
    device.watchProperty("CCD_WBG", [this](INDI::PropertyNumber property)
    {
      // gain ready
      auto val = property[0].getValue();
      IDLog("WBG value: %f\n", val);

      #ifdef __EMSCRIPTEN__
      MAIN_THREAD_EM_ASM({
        syncWBG($0);
      }, val);
      #endif
    }, INDI::BaseDevice::WATCH_NEW_OR_UPDATE);
    device.watchProperty("CCD_WBR", [this](INDI::PropertyNumber property)
    {
      // gain ready
      auto val = property[0].getValue();
      IDLog("WBR value: %f\n", val);

      #ifdef __EMSCRIPTEN__
      MAIN_THREAD_EM_ASM({
        syncWBR($0);
      }, val);
      #endif
    }, INDI::BaseDevice::WATCH_NEW_OR_UPDATE);
    device.watchProperty("CCD_OFFSET", [this](INDI::PropertyNumber property)
    {
      // gain ready
      auto val = property[0].getValue();
      IDLog("Offset value: %f\n", val);

      #ifdef __EMSCRIPTEN__
      MAIN_THREAD_EM_ASM({
        syncOffset($0);
      }, val);
      #endif
    }, INDI::BaseDevice::WATCH_NEW_OR_UPDATE);
    device.watchProperty("CCD_CAPTURE_FORMAT", [this](INDI::Property property)
    {
      // image format ready
      auto captureFormatSP = property.getSwitch();
      auto onSwitch = captureFormatSP->findOnSwitch();
      if (strcmp(onSwitch->getName(), "FORMAT_RAW8") == 0) {
        IDLog("Image format ready.\n");
      } else {
        setCaptureFormat("FORMAT_RAW8");
      }

      IDLog("Capture format state changed to %s.\n", onSwitch->getName());
    }, INDI::BaseDevice::WATCH_NEW_OR_UPDATE);

    device.watchProperty("CCD_VIDEO_STREAM", [this](INDI::Property property)
    {
      // image format ready
      auto videoStreamSP = property.getSwitch();
      auto onSwitch = videoStreamSP->findOnSwitch();
      
      IDLog("Video stream state changed to %s.\n", onSwitch->getName());
    }, INDI::BaseDevice::WATCH_NEW_OR_UPDATE);

  });
}

void Client::newMessage(INDI::BaseDevice baseDevice, int messageID)
{
    if (!baseDevice.isDeviceNameMatch(MYCCD))
        return;

    IDLog("Recveing message from Server:\n"
          "    %s\n\n", 
          baseDevice.messageQueue(messageID).c_str());

    IDLog(baseDevice.isConnected() ? "CCD is connected.\n" : "CCD is disconnected.\n");
}

void onBlobUpdated(INDI::PropertyBlob property)
{
  IDLog("Received image");
  auto blob = property[0].getBlob();
  auto blobChar = static_cast<char *>(blob);
  auto blobLen = property[0].getBlobLen();
    #ifdef __EMSCRIPTEN__
    MAIN_THREAD_EM_ASM({
      updateImage($0, $1);
    }, blobChar, property[0].getBlobLen());
    #endif

    
  
}

/**************************************************************************************
**/

void Client::setGain(int value)
{
  INDI::PropertyNumber ccdGain = mSimpleCCD.getProperty("CCD_GAIN");
  
  IDLog("Setting gain to %d\n", value);
  ccdGain[0].setValue(value);
  sendNewProperty(ccdGain);
};

void Client::setContrast(int value)
{
  INDI::PropertyNumber ccdContrast = mSimpleCCD.getProperty("CCD_CONTRAST");
  
  IDLog("Setting contrast to %d\n", value);
  ccdContrast[0].setValue(value);
  sendNewProperty(ccdContrast);
};

void Client::setGamma(int value)
{
  INDI::PropertyNumber ccdGamma = mSimpleCCD.getProperty("CCD_GAMMA");
  
  IDLog("Setting gamma to %d\n", value);
  ccdGamma[0].setValue(value);
  sendNewProperty(ccdGamma);
};
void Client::setSaturation(int value)
{
  INDI::PropertyNumber ccdSaturation = mSimpleCCD.getProperty("CCD_SATURATION");
  
  IDLog("Setting saturation to %d\n", value);
  ccdSaturation[0].setValue(value);
  sendNewProperty(ccdSaturation);
};
void Client::setSharpness(int value)
{
  INDI::PropertyNumber ccdSharpness = mSimpleCCD.getProperty("CCD_SHARPNESS");
  
  IDLog("Setting contrast to %d\n", value);
  ccdSharpness[0].setValue(value);
  sendNewProperty(ccdSharpness);
};
void Client::setWBB(int value)
{
  INDI::PropertyNumber ccdWBB = mSimpleCCD.getProperty("CCD_WBB");
  
  IDLog("Setting contrast to %d\n", value);
  ccdWBB[0].setValue(value);
  sendNewProperty(ccdWBB);
};
void Client::setWBG(int value)
{
  INDI::PropertyNumber ccdWBG = mSimpleCCD.getProperty("CCD_WBG");
  
  IDLog("Setting contrast to %d\n", value);
  ccdWBG[0].setValue(value);
  sendNewProperty(ccdWBG);
};
void Client::setWBR(int value)
{
  INDI::PropertyNumber ccdWBR = mSimpleCCD.getProperty("CCD_WBR");
  
  IDLog("Setting contrast to %d\n", value);
  ccdWBR[0].setValue(value);
  sendNewProperty(ccdWBR);
};
void Client::setOffset(int value)
{
  INDI::PropertyNumber ccdOffset = mSimpleCCD.getProperty("CCD_OFFSET");
  
  IDLog("Setting contrast to %d\n", value);
  ccdOffset[0].setValue(value);
  sendNewProperty(ccdOffset);
};

void Client::setCaptureFormat(char *format)
{
  INDI::PropertySwitch ccdCaptureFormat = mSimpleCCD.getProperty("CCD_CAPTURE_FORMAT");
  
  IDLog("Setting capture format to %s\n", format);

  auto formatSwitch = ccdCaptureFormat.findWidgetByName(format);

  ccdCaptureFormat->reset();
  formatSwitch->setState(ISS_ON);

  sendNewSwitch(ccdCaptureFormat);
};

void Client::connect() {
  std::thread(&Client::connectServer, this).detach();
}

void Client::toggleStream() {
  INDI::PropertySwitch videoStreamSP = mSimpleCCD.getProperty("CCD_VIDEO_STREAM");
  auto onSwitch = videoStreamSP->findOnSwitch();
  videoStreamSP->reset();
  if (strcmp(onSwitch->getName(), "STREAM_ON") == 0) {
    // toggle stream off

    IDLog("Turning off stream.\n");
    auto streamOffSwitch = videoStreamSP.findWidgetByName("STREAM_OFF");   
    streamOffSwitch->setState(ISS_ON);
  } else {
    // toggle stream on

    IDLog("Turning on stream.\n");
    auto streamOnSwitch = videoStreamSP.findWidgetByName("STREAM_ON");
    streamOnSwitch->setState(ISS_ON);
  }

  sendNewSwitch(videoStreamSP);
}