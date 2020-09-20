#include "platform/openfirmware/clientinterface.hpp"

#include "kernel/kernel.hpp"
#include "lib/string.h"

namespace WamKern::Platform::OpenFirmware {
#define CLEAN_CALL(args) \
    if (Call(args) != 0) return Error

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

Cell ClientInterface::FindNode(Cell ph, long top, const char* prop, const char* value) {
    if (ph == 0)
        ph = Peer(0);

    char tempStr[4096];

    if (top == 0) {
        // Look for it in the current node.
        if (GetProp(ph, prop, tempStr, 4095) != -1) {
            if (strcmp(value, tempStr) == 0) {
                return ph;
            }
        }
    }

    // Look for it in the children.
    Cell curChild = Child(ph);
    Cell result = 0;

    while (curChild != 0) {
        result = FindNode(curChild, 0, prop, value);
        if (result != 0)
            return result;
        curChild = Peer(curChild);
    }

    if (top != 0) {
        while (ph != 0) {
            curChild = Peer(ph);
            while (curChild != 0) {
                result = FindNode(curChild, 0, prop, value);
                if (result != 0)
                    return result;
                curChild = Peer(curChild);
            }

            ph = Parent(ph);
        }
    }

    return 0;
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

Cell ClientInterface::PackageToPath(Cell phandle, char* buff, long bufflen) {
    Args args{"package-to-path", 3, 1};
    args.data.packageToPath.phandle = phandle;
    args.data.packageToPath.buf = buff;
    args.data.packageToPath.buflen = bufflen;

    CLEAN_CALL(&args);

    return args.data.packageToPath.length;
}

Cell ClientInterface::Open(char* devSpec) {
    Args args{"open", 1, 1};
    args.data.open.devSpec = devSpec;

    CLEAN_CALL(&args);

    return args.data.open.ihandle;
}

Cell ClientInterface::Write(Cell ihandle, void* addr, long length) {
    Args args{"write", 3, 1};
    args.data.write.ihandle = ihandle;
    args.data.write.addr = (long)addr;
    args.data.write.length = length;

    CLEAN_CALL(&args);

    return args.data.write.actual;
}

Cell ClientInterface::Claim(Cell virtualAddress, Cell size, Cell alignment) {
    Args args{"claim", 3, 1};
    args.data.claim.virt = virtualAddress;
    args.data.claim.size = size;
    args.data.claim.align = alignment;

    CLEAN_CALL(&args);

    return args.data.claim.baseaddr;
}

Cell ClientInterface::Interpret(Cell args, Cell rets, const char* forth, ...) {
    va_list argsList;
    va_start(argsList, forth);

    Args ciArgs{"interpret", args + 1, rets + 1};
    ciArgs.data.interpret.forth = forth;

    for (size_t i = 0; i < args; i++) {
        ciArgs.data.interpret.cells[args - i - 1] = va_arg(argsList, Cell);
    }

    Cell error = NoError;
    Cell ret = Call(&ciArgs);
    if (ret != 0)
        error = Error;
    else if (ciArgs.data.interpret.cells[args] != 0)
        error = Catch;

    if (error == NoError) {
        for (size_t i = 0; i < rets; i++) {
            *(va_arg(argsList, Cell*)) = ciArgs.data.interpret.cells[args + rets - i];
        }
    }

    va_end(argsList);
    return error;
}

[[noreturn]] void ClientInterface::Exit() {
    Args args{"exit"};
    Call(&args);

    for (;;)
        ;  // should never get here anyway
}
}  // namespace WamKern::Platform::OpenFirmware