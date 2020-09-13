#include "firmware/openfirmware/clientinterface.hpp"

namespace WamKern::Firmware::OpenFirmware {
ClientInterface::Delegate ClientInterface::delegate = nullptr;

void ClientInterface::Init(void* interface) {
    delegate = reinterpret_cast<Delegate>(interface);
}

long ClientInterface::Call(Args* arguments) {
    return (*delegate)(arguments);
}

Cell ClientInterface::Peer(Cell phandle) {
    Args args = {};
    args.service = "peer";
    args.nArgs = 1;
    args.nReturns = 1;
    args.args.peer.phandle = phandle;

    if (Call(&args) != 0) return kCIError;

    return args.args.peer.peerPhandle;
}

Cell ClientInterface::FindDevice(char* devSpec) {
    Args args = {};
    args.service = "finddevice";
    args.nArgs = 1;
    args.nReturns = 1;
    args.args.finddevice.devSpec = devSpec;

    if (Call(&args) != 0) return kCIError;

    return args.args.finddevice.phandle;
}

Cell ClientInterface::GetProp(Cell phandle, char* name, char* buff, long buflen) {
    Args args = {};
    args.service = "getprop";
    args.nArgs = 4;
    args.nReturns = 1;

    args.args.getprop.phandle = phandle;
    args.args.getprop.name = name;
    args.args.getprop.buf = buff;
    args.args.getprop.buflen = buflen;

    if (Call(&args) != 0) return kCIError;

    return args.args.getprop.size;
}

Cell ClientInterface::InstanceToPackage(Cell iHandle) {
    Args args = {};
    args.service = "instance-to-package";
    args.nArgs = 1;
    args.nReturns = 1;

    args.args.instanceToPackage.ihandle = iHandle;

    if (Call(&args) != 0) return kCIError;

    return args.args.instanceToPackage.phandle;
}

Cell ClientInterface::Write(Cell ihandle, void* addr, long length) {
    Args args = {};
    args.service = "write";
    args.nArgs = 3;
    args.nReturns = 1;

    args.args.write.ihandle = ihandle;
    args.args.write.addr = (long)addr;
    args.args.write.length = length;
    
    if (Call(&args) != 0) return kCIError;

    return args.args.write.actual;
}

[[noreturn]] void ClientInterface::Exit() {
    Args args = {};
    args.service = "exit";

    Call(&args);
}
}  // namespace WamKern::Firmware::OpenFirmware