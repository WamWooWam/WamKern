#include "kernel/kernel.hpp"
#include "lib/string.h"
#include "platform/openfirmware/ofgraphics.hpp"

namespace WamKern::Platform::OpenFirmware {
bool OFGraphicsDriver::Initialise() {
    if (FindDisplays()) {
        return InitDisplays();
    }

    return false;
}

bool OFGraphicsDriver::FindDisplays() {
    KernelLog("searching for displays");

    Cell screenPH = 0;
    for (size_t i = 0; i < MaxDisplays; i++) {
        screenPH = _clientInterface.FindNode(screenPH, 1, "device_type", "display");
        if (!ClientInterface::IsValidHandle(screenPH))
            break;

        _displayInfo[i].screenPH = screenPH;
        _displayInfoCount = i;
    }

    KernelLogF("firmware says %d displays", _displayInfoCount);

    Cell controlPH = _clientInterface.FindDevice("/chaos/control");
    screenPH = _clientInterface.FindDevice("screen");
    if (!ClientInterface::IsValidHandle(screenPH))
        screenPH = controlPH;

    bool contains = false;
    for (size_t i = 0; i < _displayInfoCount; i++) {
        if (_displayInfo[i].screenPH == screenPH) {
            contains = true;
            break;
        }
    }

    if (!contains) {
        _displayInfo[++_displayInfoCount].screenPH = screenPH;
    }

    for (size_t i = 0; i < _displayInfoCount; i++) {
        if (_displayInfo[i].screenPH == screenPH) {
            _mainDisplayIndex = i;
            break;
        }
    }

    return _displayInfoCount > 0;
}

bool OFGraphicsDriver::InitDisplays() {
    KernelLog("initialising displays");

    for (size_t i = 0; i < _displayInfoCount; i++) {
        if (_displayInfo[i].open || _displayInfo[i].triedToOpen)
            continue;
        if (InitDisplay(i)) {
            KernelLogF("Display %d: opened!", i);
            _displayCount++;
        } else {
            KernelLogF("Display %d: failed to open", i);
        }
    }

    return true;
}

bool OFGraphicsDriver::InitDisplay(size_t index) {
    OFDisplayInfo info = _displayInfo[index];
    Cell screenPH = info.screenPH;
    Cell screenIH = 0;

    char displayType[32];
    Cell size = _clientInterface.GetProp(screenPH, "display-type", displayType, 31);
    if (size != -1) {
        displayType[size] = '\0';

        KernelLogF("Display %d: type %s", index, displayType);
        if (!strcmp(displayType, "NONE"))
            return false;
    }

    // mac-boot is handy :)
    _clientInterface.Interpret(0, 1, "\" _screen-ihandle\" $find if execute else 0 then", &screenIH);

    if (screenIH != 0 && _clientInterface.InstanceToPackage(screenIH) != screenPH) {
        screenIH = 0;

        KernelLogF("Display %d: invalid handle from mac-boot", index);
    }

    // how about stdout?
    if (screenIH == 0 && screenPH == _stdoutPH) {
        screenIH = _stdoutIH;
        KernelLogF("Display %d: using stdout", index);
    }

    // maybe we can open it
    if (screenIH == 0) {
        char screenPath[255] = {0};
        Cell length = _clientInterface.PackageToPath(screenPH, screenPath, 255);
        strcat(screenPath, ":0");

        KernelLogF("Display %d: attempting to open %s", index, screenPath);
        screenIH = _clientInterface.Open(screenPath);
    }

    if (screenIH == 0)
        return false;

    Cell x = 0;
    OFDisplay display{};
    display._screenPH = screenPH;
    display._screenIH = screenIH;

    _clientInterface.GetProp(screenPH, "address", &x, sizeof x);
    display._address = x;

    _clientInterface.GetProp(screenPH, "width", &x, sizeof x);
    display._width = x;

    _clientInterface.GetProp(screenPH, "height", &x, sizeof x);
    display._height = x;

    _clientInterface.GetProp(screenPH, "depth", &x, sizeof x);
    display._bitDepth = x;

    _clientInterface.GetProp(screenPH, "linebytes", &x, sizeof x);
    display._stride = x;

    KernelLogF("Display %d: w:%d h:%d bpp:%d stride:%d addr:0x%x", index, display._width, display._height, display._bitDepth, display._stride, display._address);
    _displays[_displayCount] = display;

    return true;
}

size_t OFGraphicsDriver::GetDisplays(Graphics::Display** displays, size_t size) {
    if (size > _displayCount) {
        // die
    }

    Memory::Copy<OFDisplay>(_displays, (OFDisplay*)*displays, _displayCount);
    return _displayCount;
}

Graphics::Display* OFGraphicsDriver::GetDisplay(size_t index) {
    return (Graphics::Display*)&_displays[index];
}

size_t OFGraphicsDriver::DisplayCount() {
    return _displayInfoCount;
}
}  // namespace WamKern::Platform::OpenFirmware