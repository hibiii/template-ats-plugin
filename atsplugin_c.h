// A rewrite of `atsplugin.h` for Simple C.
// Originally by Rock_On and mackoy.

// C version by hibi, designed for minimal disruption in development.

// Options for this header:
//
// - `ATSPLUGIN_C_NO_TYPEDEFS` (default undefined): If defined, structs will
//   not be typedef'd, and will require the `struct` keyword as is standard in
//   C. If undefined (the default behavior), structs are left typedef'd, making
//   it more like C++'s syntax.
//
// - `ATSPLUGIN_C_NO_FUNCTION_SIGNATURES` (default undefined): If defined, the
//   function signatures are commented out. This may be useful if you want to
//   have different function signatures, or are having signature conflict
//   issues (for some reason).
//
// Additionally, `atsplugin_c.h` will warn if function signatures are enabled,
// but `WINAPI` is undefined as it is used in the official `atsplugin.h`.
// If this is the case, then `WINAPI` will be temporarily defined as empty, and
// will be undefined before returning.

#ifndef ATSPLUGIN_C_H
#define ATSPLUGIN_C_H

#ifdef __cplusplus
extern "C" {
#endif

#ifdef ATS_EXPORTS
#   define ATS_API __declspec(dllexport)
#else
#   define ATS_API __declspec(dllimport)
#endif

// Plug-in Version
#define ATS_VERSION 0x00020000

#define ATS_KEY_S   0 // defaults to SPACE
#define ATS_KEY_A1  1 // defaults to Insert
#define ATS_KEY_A2  2 // defaults to Delete
#define ATS_KEY_B1  3 // defaults to Home
#define ATS_KEY_B2  4 // defaults to End
#define ATS_KEY_C1  5 // defaults to PageUp
#define ATS_KEY_C2  6 // defaults to PageDown
#define ATS_KEY_D   7 
#define ATS_KEY_E   8 
#define ATS_KEY_F   9 
#define ATS_KEY_G  10
#define ATS_KEY_H  11
#define ATS_KEY_I  12
#define ATS_KEY_J  13
#define ATS_KEY_K  14
#define ATS_KEY_L  15

// Initial position
#define ATS_INIT_SVC     0
#define ATS_INIT_EMG     1
#define ATS_INIT_REMOVED 2

// Sound control
#define ATS_SOUND_STOP    -1000
#define ATS_SOUND_CONTINUE    2
#define ATS_SOUND_PLAY        1
#define ATS_SOUND_PLAYLOOPING 0

#define ATS_HORN_PRIMARY   0
#define ATS_HORN_SECONDARY 1
#define ATS_HORN_MUSIC     2

#define ATS_CONSTANTSPEED_ENABLE   1
#define ATS_CONSTANTSPEED_CONTINUE 0
#define ATS_CONSTANTSPEED_DISABLE  2

#ifdef ATSPLUGIN_C_NO_TYPEDEFS
#   define _ATSPLUGIN_STRUCT_DEF(A, B) struct A B
#   define _ATSPLUGIN_STRUCT(A) (struct A)
#else
#   define _ATSPLUGIN_STRUCT_DEF(A, B) typedef struct B A
#   define _ATSPLUGIN_STRUCT(A) A
#endif

_ATSPLUGIN_STRUCT_DEF(ATS_VEHICLESPEC, {
    int BrakeNotches;
    int PowerNotches;
    int AtsNotch;
    int B67Notch;
    int Cars;
});

_ATSPLUGIN_STRUCT_DEF(ATS_VEHICLESTATE, {
    double Location;
    float Speed;
    int Time;
    float BcPressure;
    float MrPressure;
    float BpPressure;
    float SapPressure;
    float Current;
});

_ATSPLUGIN_STRUCT_DEF(ATS_BEACONDATA, {
    int Type;
    int Signal;
    float Distance;
    int Optional;
});

_ATSPLUGIN_STRUCT_DEF(ATS_HANDLES, {
    int Brake;
    int Power;
    int Reverser;
    int ConstantSpeed;
});

#ifndef ATSPLUGIN_C_NO_FUNCTION_SIGNATURES

#ifndef WINAPI
#   warning WINAPI undefined: defaulting to empty define
#   define _ATSPLUGIN_UNDEFINE_WINAPI
#   define WINAPI
#endif

ATS_API void WINAPI Load(void);

ATS_API void WINAPI Dispose(void);

ATS_API int WINAPI GetPluginVersion(void);

// void SetVehicleSpec (Spec)
ATS_API void WINAPI SetVehicleSpec(_ATSPLUGIN_STRUCT(ATS_VEHICLESPEC) specs);

ATS_API void WINAPI Initialize(int brake_position);

// Handles Elapse (State, int panel[], int sound[])
ATS_API _ATSPLUGIN_STRUCT(ATS_HANDLES) WINAPI
Elapse(_ATSPLUGIN_STRUCT(ATS_VEHICLESTATE), int panel_idx[], int sound_idx[]);

ATS_API void WINAPI SetPower(int notch);

ATS_API void WINAPI SetBrake(int notch);

ATS_API void WINAPI SetReverser(int position);

ATS_API void WINAPI KeyDown(int key_code);

ATS_API void WINAPI KeyUp(int key_code);

ATS_API void WINAPI HornBlow(int horn_type);

ATS_API void WINAPI DoorOpen();

ATS_API void WINAPI DoorClose();

ATS_API void WINAPI SetSignal(int signal);

// void SetBeaconData (BeaconData)
ATS_API void WINAPI SetBeaconData(_ATSPLUGIN_STRUCT(ATS_BEACONDATA) data);

#ifdef _ATSPLUGIN_UNDEFINE_WINAPI
#   undef _ATSPLUGIN_UNDEFINE_WINAPI
#   undef WINAPI
#endif

#endif // ATSPLUGIN_C_NO_FUNCTION_SIGNATURES

#undef _ATSPLUGIN_STRUCT_DEF
#undef _ATSPLUGIN_STRUCT

#ifdef __cplusplus
}
#endif

#endif // ATSPLUGIN_C_H
