#include "Classes/ESaveGame.h"


bool UESaveGame::AddSlot(FName Name, FInstancedStruct Slot)
{
	if(NamedSlots.Contains(Name))
	{
		return false;
	}
	NamedSlots.Add(Name, Slot);
	return true;
}

bool UESaveGame::RemoveSlot(FName Name, FInstancedStruct Slot)
{
	if (!NamedSlots.Contains(Name))
	{
		return false;
	}
	NamedSlots.Remove(Name);
	return true;
}

bool UESaveGame::UpdateSlot(FName Name, FInstancedStruct Slot)
{
	if (NamedSlots.Contains(Name)) {
		NamedSlots.Add(Name, Slot);
		return true;
	}
	return false;
}

FInstancedStruct UESaveGame::GetSlot(FName Name, bool& bSuccess)
{
	if (NamedSlots.Contains(Name)) {
		bSuccess = true;
		return NamedSlots[Name];
	}
	bSuccess = false;
	return FInstancedStruct();
}
