#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#define ATS_EXPORTS
extern "C" {
#include "atsplugin.h"
}

// Necessary to passthrough the driver's inputs to the train
static int g_brake = 0;
static int g_power = 0;
static int g_reverser = 0;

// The plugin example on the BVE website has `DllMain` defined here.
// For this example, however, it is completely unnecessary.

ATS_API void WINAPI Load() {
    // empty function body
}

ATS_API void WINAPI Dispose() {
    // empty function body
    // [BVE4] Not called when exiting BVE with a route open, untested on 5+
}

ATS_API int WINAPI GetPluginVersion() {
    return ATS_VERSION;
}

ATS_API void WINAPI SetVehicleSpec(ATS_VEHICLESPEC specs) {
    (void) specs;
}

ATS_API void WINAPI Initialize(int brake) {
    (void) brake;
}

ATS_API ATS_HANDLES WINAPI Elapse(ATS_VEHICLESTATE state, int panel[], int sound[]) {
    (void) state;
    (void) panel;
    (void) sound;

    return ATS_HANDLES { g_brake, g_power, g_reverser, 0 };
}

ATS_API void WINAPI SetPower(int notch) {
    g_power = notch;
}

ATS_API void WINAPI SetBrake(int notch) {
    g_brake = notch;
}

ATS_API void WINAPI SetReverser(int pos) {
    g_reverser = pos;
}

ATS_API void WINAPI KeyDown(int atsKeyCode) {
    (void) atsKeyCode;
}

ATS_API void WINAPI KeyUp(int atsKeyCode) {
    (void) atsKeyCode;
}

ATS_API void WINAPI HornBlow(int atsHornBlowIndex) {
    (void) atsHornBlowIndex;
}

ATS_API void WINAPI DoorOpen() {
    // empty function body
}

ATS_API void WINAPI DoorClose() {
    // empty function body
}

ATS_API void WINAPI SetSignal(int signal) {
    (void) signal;
}

ATS_API void WINAPI SetBeaconData(ATS_BEACONDATA beaconData) {
    (void) beaconData;
}
