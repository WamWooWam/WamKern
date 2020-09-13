#pragma once

// based on ci.h from BootX
namespace WamKern::Firmware::OpenFirmware {
    typedef long Cell;

class ClientInterface {
   public:

    static constexpr Cell kCINoError = (0);
    static constexpr Cell kCIError = (-1);
    static constexpr Cell kCICatch = (-2);

    struct Args {
        char *service;
        Cell nArgs;
        Cell nReturns;

        union {
            struct {  // nArgs=1 + args, nReturns=1 + rets
                const char *forth;
                Cell cells[6 + 1 + 6];
            } interpret;

            struct {  // nArgs=2 + args, nReturns=1 + rets
                const char *method;
                Cell iHandle;
                Cell cells[6 + 1 + 6];
            } callMethod;

            struct {            // nArgs=1, nReturns=1	( device-specifier -- ihandle )
                char *devSpec;  // IN parameter
                Cell ihandle;   // RETURN value
            } open;

            struct {           // nArgs=1, nReturns=0	( ihandle -- )
                Cell ihandle;  // IN parameter
            } close;

            struct {  // nArgs=3, nReturns=1 ( ihandle addr length -- actual )
                Cell ihandle;
                Cell addr;
                Cell length;
                Cell actual;
            } read;

            struct {  // nArgs=3, nReturns=1 ( ihandle addr length -- actual )
                Cell ihandle;
                Cell addr;
                Cell length;
                Cell actual;
            } write;

            struct {  // nArgs=3, nReturns=1 ( ihandle pos.high pos.low -- result )
                Cell ihandle;
                Cell pos_high;
                Cell pos_low;
                Cell result;
            } seek;

            struct {  // nArgs=3, nReturns=1
                Cell virt;
                Cell size;
                Cell align;
                Cell baseaddr;
            } claim;

            struct {  // nArgs=2, nReturns=0
                Cell virt;
                Cell size;
            } release;

            struct {               // nArgs=1, nReturns=1	( phandle -- peer-phandle )
                Cell phandle;      // IN parameter
                Cell peerPhandle;  // RETURN value
            } peer;

            struct {                // nArgs=1, nReturns=1	( phandle -- child-phandle )
                Cell phandle;       // IN parameter
                Cell childPhandle;  // RETURN value
            } child;

            struct {                 // nArgs=1, nReturns=1	( phandle -- parent-phandle )
                Cell childPhandle;   // IN parameter
                Cell parentPhandle;  // RETURN value
            } parent;

            struct {            // nArgs=1, nReturns=1	( devSpec -- phandle )
                char *devSpec;  // IN parameter
                Cell phandle;   // RETURN value
            } finddevice;

            struct {           // nArgs=3, nReturns=1 ( ihandle buf buflen -- length )
                Cell ihandle;  // IN ihandle
                char *buf;     // IN buf
                Cell buflen;   // IN buflen
                Cell length;   // RETURN length
            } instanceToPath;

            struct {           // nArgs=1, nReturns=1 ( ihandle -- phandle )
                Cell ihandle;  // IN ihandle
                Cell phandle;  // RETURN phandle
            } instanceToPackage;

            struct {           // nArgs=3, nReturns=1 ( phandle buf buflen -- length )
                Cell phandle;  // IN phandle
                char *buf;     // IN buf
                Cell buflen;   // IN buflen
                Cell length;   // RETURN length
            } packageToPath;

            struct {           // nArgs=2, nReturns=1	( phandle name -- size )
                Cell phandle;  // IN parameter
                char *name;    // IN parameter
                Cell size;     // RETURN value
            } getproplen;

            struct {           // nArgs=4, nReturns=1	( phandle name buf buflen -- size )
                Cell phandle;  // IN parameter
                char *name;    // IN parameter
                char *buf;     // IN parameter
                Cell buflen;   // IN parameter
                Cell size;     // RETURN value
            } getprop;

            struct {             // nArgs=3, nReturns=1	( phandle previous buf -- flag )
                Cell phandle;    // IN parameter
                char *previous;  // IN parameter
                char *buf;       // IN parameter
                Cell flag;       // RETURN value
            } nextprop;

            struct {           // nArgs=4, nReturns=1	( phandle name buf buflen -- size )
                Cell phandle;  // IN parameter
                char *name;    // IN parameter
                char *buf;     // IN parameter
                Cell buflen;   // IN parameter
                Cell size;     // RETURN value
            } setprop;

            struct {  // nArgs=1, nReturns=0
                char *bootspec;
            } boot;
        } args;
    };

    typedef long (*Delegate)(Args *args);

    static void Init(void *interface);
    static long Call(Args *ciArgs);

    static Cell Peer(Cell phandle);
    // static Cell Child(Cell phandle);
    // static Cell Parent(Cell phandle);
    static Cell FindDevice(char *devSpec);

    static Cell GetProp(Cell handle, char* name, char* buff, long buflen);
    static Cell InstanceToPackage(Cell iHandle);

    static Cell Write(Cell ihandle, void* addr, long length);

    // static void Enter();
    [[noreturn]] static void Exit();
    // static void Quiesce();

   private:
    static Delegate delegate;
};

}  // namespace WamKern::Firmware::OpenFirmware