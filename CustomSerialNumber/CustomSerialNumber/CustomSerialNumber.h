#pragma once

#define EXPORT_CUSTOMSERIALNUMBER _declspec(dllexport)


extern "C" EXPORT_CUSTOMSERIALNUMBER void SetCustomSerialNumber(const char* serial_name);

extern "C" EXPORT_CUSTOMSERIALNUMBER void DelCustomSerialNumber(const char* serial_name);

extern "C" EXPORT_CUSTOMSERIALNUMBER char* GetCustomSerialNumber(const char* serial_name,int nLoop=1);

extern "C" EXPORT_CUSTOMSERIALNUMBER void FreeMemory(void* p_addr);

