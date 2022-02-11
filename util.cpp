#include "util.h"
/////////////////////////////////////////////////////////////////////////////
// NTAPI
EXTERN_C
NTSTATUS
NTAPI
ZwQuerySystemInformation(
    IN SYSTEM_INFORMATION_CLASS SystemInformationClass,
    OUT PVOID SystemInformation,
    IN ULONG Length,
    OUT PULONG ReturnLength);

/////////////////////////////////////////////////////////////////////////////
// FUNCTION
NTSTATUS
EnumPoolTagTable(OUT PSYSTEM_POOLTAG_INFORMATION *Buffer)
{
    NTSTATUS lStatus;
    PVOID pBuffer;
    ULONG uBufferSize;
    ULONG uAttempts;

    uBufferSize = 0x100;
    pBuffer = ExAllocatePoolWithTag(NonPagedPoolNx, uBufferSize, 'haha');
    if (!pBuffer)
    {
        return STATUS_MEMORY_NOT_ALLOCATED;
    }

    lStatus = ZwQuerySystemInformation(SystemPoolTagInformation, pBuffer, uBufferSize, &uBufferSize);
    uAttempts = 0;

    while (lStatus == STATUS_INFO_LENGTH_MISMATCH && uAttempts < 8)
    {
        if (pBuffer)
        {
            ExFreePoolWithTag(pBuffer, 'haha');
        }

        pBuffer = ExAllocatePoolWithTag(NonPagedPoolNx, uBufferSize, 'haha');

        lStatus = ZwQuerySystemInformation(SystemPoolTagInformation, pBuffer, uBufferSize, &uBufferSize);
        uAttempts++;
    }

    if (NT_SUCCESS(lStatus))
    {
        *Buffer = (PSYSTEM_POOLTAG_INFORMATION)pBuffer;
    }
    else
    {
        if (pBuffer)
        {
            ExFreePoolWithTag(pBuffer, 'haha');
        }
    }

    return lStatus;
}
