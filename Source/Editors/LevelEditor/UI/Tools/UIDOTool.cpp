#include "stdafx.h"
#include "UIDOTool.h"
#include "ESceneDOTools.h"
UIDOTool::UIDOTool()
{
}

UIDOTool::~UIDOTool()
{
}

void UIDOTool::Draw()
{
	if (ImGui::TreeNode("Commands"))
	{
		ImGui::Unindent(ImGui::GetTreeNodeToLabelSpacing());
		{
			if (ImGui::Button("First Initialize", ImVec2(-1, 0)))
			{
				if (DM->Initialize())
					Scene->UndoSave(); 
			}
			if (ImGui::Button("Reinitialize All", ImVec2(-1, 0))) 
			{
				if (DM->Reinitialize())
					Scene->UndoSave();
			}
			if (ImGui::Button("Reinitialize Objects Only", ImVec2(-1, 0)))
			{
				if (DM->UpdateObjects(true, false))
					Scene->UndoSave();
			}
			if (ImGui::Button("Reinitialize Selected Slot Objects", ImVec2(-1, 0)))
			{
				if (DM->UpdateObjects(false, true))
					Scene->UndoSave();
			}
			ImGui::Separator();
			if (ImGui::Button("Update Renderer", ImVec2(-1, 0)))
			{
				DM->InvalidateCache();
				Scene->UndoSave();
			}
			ImGui::Separator();
			if (ImGui::Button("Clear Slots", ImVec2(-1, 0)))
			{
				if (ELog.DlgMsg(mtConfirmation, mbYes| mbNo, "Are you sure to reset slots?") == mrYes) {
					DM->ClearSlots();
					Scene->UndoSave();
				}
			}
			if (ImGui::Button("Clear Details", ImVec2(-1, 0)))
			{
				if (ELog.DlgMsg(mtConfirmation, mbYes | mbNo, "Are you sure to clear details?") == mrYes) {
					ExecCommand(COMMAND_UPDATE_PROPERTIES);
					DM->Clear();
					Scene->UndoSave();
				}
			}
			ImGui::Separator();
			if (ImGui::Button("Object List", ImVec2(-1, 0))) {}
		}

		ImGui::Indent(ImGui::GetTreeNodeToLabelSpacing());
		ImGui::TreePop();
	}
}