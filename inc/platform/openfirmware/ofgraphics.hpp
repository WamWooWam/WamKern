#pragma once
#include "graphics/display.hpp"
#include "graphics/driver.hpp"
#include "platform/openfirmware/clientinterface.hpp"

namespace WamKern::Platform::OpenFirmware {
struct OFDisplayInfo {
    Cell screenPH = 0;
    Cell screenIH = 0;
    bool open = false;
    bool triedToOpen = false;
};

class OFDisplay : public Graphics::Display {
    friend class OFGraphicsDriver;

   public:
    OFDisplay(size_t width, size_t height, uint8_t bitDepth, size_t stride, uintptr_t frontBuffer, Cell screenPH, Cell screenIH)
        : Display(width, height, bitDepth, stride, frontBuffer), _screenPH(screenPH), _screenIH(screenIH) {
            
    }

    OFDisplay& operator=(const OFDisplay& other) {
        _width = other._width;
        _height = other._height;
        _bitDepth = other._bitDepth;
        _stride = other._stride;
        _screenPH = other._screenPH;
        _screenIH = other._screenIH;
        _frontBuffer = other._frontBuffer;
        _backBuffer = other._backBuffer;
        _bufferSize = other._bufferSize;
        return *this;
    }

   private:
    Cell _screenPH = 0;
    Cell _screenIH = 0;
};

class OFGraphicsDriver : public Graphics::GraphicsDriver {
   public:
    OFGraphicsDriver(ClientInterface interface, Cell stdoutIH, Cell stdoutPH)
        : _clientInterface(interface), _stdoutIH(stdoutIH), _stdoutPH(stdoutPH) {
        for (size_t i = 0; i < MaxDisplays; i++) {
            _displayInfo[i].screenPH = 0;
            _displayInfo[i].triedToOpen = false;
        }
    }

    bool Initialise();
    size_t GetDisplays(Graphics::Display** displays, size_t size);
    Graphics::Display* GetDisplay(size_t index);
    size_t DisplayCount();

   private:
    bool FindDisplays();
    bool InitDisplays();
    bool InitDisplay(size_t index);

    ClientInterface _clientInterface;
    Cell _stdoutIH = 0;
    Cell _stdoutPH = 0;

    OFDisplayInfo _displayInfo[MaxDisplays];
    size_t _displayInfoCount = 0;

    OFDisplay* _displays = nullptr;
    size_t _displayCount = 0;
    size_t _mainDisplayIndex = 0;
};
}  // namespace WamKern::Platform::OpenFirmware