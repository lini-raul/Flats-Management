#include "undo.h"

void UndoAdauga::doUndo()
{
	repo.sterge(apAdaugat);
}

void UndoSterge::doUndo()
{
	repo.add(locSters);
}

void UndoModify::doUndo()
{
	repo.modify(ap, nume, suprafata, tip);
}
