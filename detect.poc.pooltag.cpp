#include "detect.h"
#include "util.h"

bool
AntiKernelDbgByPoolTag()
{
    bool bKdbg = false;
    PSYSTEM_POOLTAG_INFORMATION pPoolTagTable = NULL;

    do
    {
        NTSTATUS lStatus = EnumPoolTagTable(&pPoolTagTable);
        if (!NT_SUCCESS(lStatus))
        {
            break;
        }

        ULONG uCount = pPoolTagTable->Count;
        for (ULONG i = 0; i < uCount; ++i)
        {
            auto pPoolTagInfo = pPoolTagTable->TagInfo[i];
            if (pPoolTagInfo.TagUlong == 'oIdK' && pPoolTagInfo.PagedAllocs == 0 && pPoolTagInfo.PagedFrees == 0 &&
                pPoolTagInfo.PagedUsed == 0 && pPoolTagInfo.NonPagedUsed >= PAGE_SIZE &&
                pPoolTagInfo.NonPagedUsed < 10 * PAGE_SIZE && pPoolTagInfo.NonPagedAllocs > 0x30 &&
                pPoolTagInfo.NonPagedFrees > 0x30)
            {
                bKdbg = true;
                break;
            }
        }

    } while (0);

    if (pPoolTagTable)
    {
        ExFreePoolWithTag(pPoolTagTable, 'haha');
    }

    return bKdbg;
}
