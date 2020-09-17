#include "firmware/openfirmware/clientinterface.hpp"


namespace WamKern::Firmware::OpenFirmware {
#define CLEAN_CALL(args) if (Call(args) != 0) return Error

ClientInterface::ClientInterface(void* interface) {
    delegate = reinterpret_cast<Delegate>(interface);
}

long ClientInterface::Call(Args* arguments) {
    return (*delegate)(arguments);
}

Cell ClientInterface::Peer(Cell phandle) {
    Args args{"peer", 1, 1};
    args.data.peer.phandle = phandle;

    CLEAN_CALL(&args);

    return args.data.peer.peerPhandle;
}

Cell ClientInterface::Child(Cell phandle) {
    Args args{"child", 1, 1};
    args.data.child.phandle = phandle;

    CLEAN_CALL(&args);

    return args.data.child.childPhandle;
}

Cell ClientInterface::Parent(Cell phandle) {
    Args args{"parent", 1, 1};
    args.data.parent.childPhandle = phandle;

    CLEAN_CALL(&args);

    return args.data.parent.parentPhandle;
}

Cell ClientInterface::FindDevice(const char* devSpec) {
    Args args{"finddevice", 1, 1};
    args.data.finddevice.devSpec = devSpec;

    CLEAN_CALL(&args);

    return args.data.finddevice.phandle;
}

Cell ClientInterface::GetProp(Cell phandle, const char* name, void* buff, long buflen) {
    Args args{"getprop", 4, 1};
    args.data.getprop.phandle = phandle;
    args.data.getprop.name = (char*)name;
    args.data.getprop.buf = (char*)buff;
    args.data.getprop.buflen = buflen;

    CLEAN_CALL(&args);

    return args.data.getprop.size;
}

Cell ClientInterface::InstanceToPackage(Cell iHandle) {
    Args args{"instance-to-package", 1, 1};
    args.data.instanceToPackage.ihandle = iHandle;

    CLEAN_CALL(&args);

    return args.data.instanceToPackage.phandle;
}

Cell ClientInterface::Write(Cell ihandle, void* addr, long length) {
    Args args{"write", 3, 1};
    args.data.write.ihandle = ihandle;
    args.data.write.addr = (long)addr;
    args.data.write.length = length;

    CLEAN_CALL(&args);

    return args.data.write.actual;
}

[[noreturn]] void ClientInterface::Exit() {
    Args args{"exit"};
    Call(&args);

    for (;;)
        ;  // should never get here anyway
}
}  // namespace WamKern::Firmware::OpenFirmware