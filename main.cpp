#include "detect.h"

#define dprintf(format, ...) DbgPrintEx(DPFLTR_DEFAULT_ID, DPFLTR_ERROR_LEVEL, (format), __VA_ARGS__)

EXTERN_C
NTSTATUS
DriverEntry(_In_ PDRIVER_OBJECT DriverObject, _In_ PUNICODE_STRING RegistryPath)
{
    dprintf("[Hello]: DriverEntry!\n");

    bool bDetect = AntiKernelDbgByPoolTag();
    if (bDetect)
    {
        dprintf("[Detect]: By AntiKernelDbgByPoolTag!\n");
    }

    return STATUS_VIRUS_DELETED;
}
