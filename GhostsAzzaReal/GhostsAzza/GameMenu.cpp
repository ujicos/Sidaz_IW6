#include "stdafx.h"

/*nst char* MapNames[] =
{
	"mp_chasm",
	"mp_dart",
	"mp_hashima",
	"mp_frag",
	"mp_lonestar",
	"mp_zebra",
	"mp_skeleton",
	"mp_prisonbreak",
	"mp_snow",
	"mp_strikezone",
	"mp_flooded",
	"mp_fahrenheit",
	"mp_warhawk",
	"mp_sovereign",
	"mp_descent_new",
	"mp_alien_armory",
	"mp_boneyard_ns",
	"mp_ca_red_river",
	"mp_ca_rumble",
	"mp_swamp",
	"mp_battery3",
	"mp_dome_ns",
	"mp_ca_behemoth",
	"mp_ca_impact",
	"mp_alien_beacon",
	"mp_dig",
	"mp_favela_iw6",
	"mp_pirate",
	"mp_zulu",
	"mp_alien_dlc3",
	"mp_conflict",
	"mp_mine",
	"mp_zerosub",
	"mp_shipment_ns",
	"mp_alien_last",
};

const char* GameTypes[] =
{
	"Team Deathmatch",
	"Search & Destroy",
	"Free For All"
};

std::string RealGametypes[] =
{
	"war",
	"sd",
	"dm"
};

const char* Teams[] =
{
	"Axis",
	"Allies"
};

struct ClientClass
{
	std::string Name;
	int Index;
};

std::vector<ClientClass> ClientVec;
char NameBuf[64];
char BotNameBuf[64];

int NameChangeCallback(ImGuiTextEditCallbackData* data)
{
	Toggles.NameToChange = std::string(NameBuf);
}
int BotNameChangeCallback(ImGuiTextEditCallbackData* data)
{
	Toggles.BotName = std::string(BotNameBuf);
}

void ClearPlayer(int i)
{
	Toggles.TA[i] = false;
	Toggles.UFO[i] = false;
	Toggles.GodMode[i] = false;
	Toggles.TA_IgnoreAim[i] = false;
	Toggles.TA_LimitWeapons[i] = true;
	Toggles.TA_FOV[i] = 180.0f;
	Toggles.SavedPositions[i] = Vector(0, 0, 0);
	Toggles.SpawnSaved[i] = false;
}

void AddNameTokens(int i, std::string &nam)
{
	if (Toggles.TA[i] || Toggles.UFO[i] || Toggles.GodMode[i])
	{
		nam += "  [";

		if (Toggles.TA[i])
			nam += " TA";
		if (Toggles.UFO[i])
			nam += " U";
		if (Toggles.GodMode[i])
			nam += " G";

		nam += " ]";
	}
}

void UpdateClientVector()
{
	ClientVec.clear();
	for (int i = 0; i < 18; i++)
	{
		if (Engine.IsPlayer(Engine.GetEntity(i)))
		{
			char namebuf[128];
			Engine.CL_GetClientName(*Engine.LocalPlayer, i, namebuf, 127);
			if (namebuf[0] != 0)
			{
				ClientClass t;
				t.Name = std::string(namebuf);
				t.Index = i;
				AddNameTokens(i, t.Name);
				ClientVec.push_back(t);
			}
			else
			{
				ClearPlayer(i);
			}
		}
		else
		{
			ClearPlayer(i);
		}
	}


}

typedef void(__cdecl* tSV_StartMap)(int clientnum, const char *map, bool mapispreloaded);
tSV_StartMap Startmap = (tSV_StartMap)0x140470170;

bool IsTeamBased()
{
	return Toggles.CurGameType != 2;
}

void OffGameHostMenu()
{
	ImGui::Begin("Host Menu", &Toggles.HostMenu, ImVec2(310, 350), 0.9f, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize);
	{
		ImGui::SetWindowSize("Host Menu", ImVec2(250, 350));
		if (ImGui::Button("Force Host"))
		{
			char buf[280];
			//sprintf(buf, "ui_mapname %s", MapNames[Toggles.CurMap]);

			sprintf(buf, "ui_mapname %s; ui_gametype %s; party_maxplayers %i; wait 10; g_gametype %s", MapNames[Toggles.CurMap], RealGametypes[Toggles.CurGameType].c_str(), Toggles.MaxPlayers, RealGametypes[Toggles.CurGameType].c_str());
			Engine.Cbuf_AddText(*Engine.LocalPlayer, buf);

			//dvar_t* party_minplayers = SimEngine::FindDvar("party_minplayers");
			Engine.party_minplayers->current.integer = 1;

			//Startmap(0, "mp_zebra" , false);



		}
		ImGui::Separator();
		ImGui::Combo("Gametype", &Toggles.CurGameType, GameTypes, ARRAYSIZE(GameTypes));
		ImGui::Separator();
		ImGui::SliderInt("Maxplayers", &Toggles.MaxPlayers, 1, 18);
		ImGui::Checkbox("Set Stuff", &Toggles.SetMaxPlayers);
		ImGui::Separator();
		ImGui::Combo("Map", &Toggles.CurMap, MapNames, ARRAYSIZE(MapNames));
		ImGui::Separator();
		if (ImGui::Checkbox("Unlock DLC", &Toggles.DLCUnlock))
			DLCUnlocker::SetDLCUnlock(Toggles.DLCUnlock);
		ImGui::Separator();

		ImGui::InputText("Name", NameBuf, 64, ImGuiInputTextFlags_CallbackAlways, (ImGuiTextEditCallback)NameChangeCallback);
		ImGui::Checkbox("Change Name", &Toggles.ChangeName);

	}
	ImGui::End();
}

void InGameHostMenu()
{
	UpdateClientVector();
	ImGui::Begin("Host Menu", &Toggles.HostMenu, ImVec2(250, 500), 0.9f, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize);
	{
		ImGui::SetWindowSize("Host Menu", ImVec2(250, 500));
		static int clnt = -1;
		static char buf1[128] = "";
		ImGui::ListBox("", &clnt, [](void* vecc, int idx, const char** out_text)
		{
			std::vector<ClientClass>* vectorr = reinterpret_cast<std::vector<ClientClass>*>(vecc);
			if (idx < 0 || idx >= vectorr->size())
				return false;

			*out_text = vectorr->at(idx).Name.c_str();
			return true;

		}, reinterpret_cast<void*>(&ClientVec), ClientVec.size(), 5);

		int realclient = -1;
		if (clnt != -1)
			realclient = ClientVec[clnt].Index;

		ImGui::Separator();
		if (realclient != -1 && realclient < 18)
		{
			ImGui::Text("Aimbot Settings");
			ImGui::Checkbox("Trickshot Aimbot", &Toggles.TA[realclient]);
			ImGui::Checkbox("Limited Weapons", &Toggles.TA_LimitWeapons[realclient]);
			ImGui::Checkbox("Ignore Client", &Toggles.TA_IgnoreAim[realclient]);
			ImGui::SliderFloat("AimFOV", &Toggles.TA_FOV[realclient], 2.0f, 180.0f, "%.2f");
			ImGui::Separator();
			ImGui::Text("Misc Settings");
			ImGui::Checkbox("God Mode", &Toggles.GodMode[realclient]);
			ImGui::Checkbox("UFO", &Toggles.UFO[realclient]);
			ImGui::Separator();
			ImGui::Text("Teleport Settings");
			if (realclient != *Engine.LocalPlayer)
			{
				if (ImGui::Button("Bring"))
				{
					void* ent = Engine.GetEntity(realclient);
					void* localEnt = Engine.GetEntity(*Engine.LocalPlayer);

					if (Engine.IsAlive(ent) && Engine.IsAlive(localEnt))
					{
						Vector outpos;
						Engine.G_GetOrigin(*Engine.LocalPlayer, *Engine.LocalPlayer, &outpos);
						Engine.TeleportPlayer(ent, &outpos);
					}
				}
				ImGui::SameLine();
				ImGui::PushItemWidth(100);
				if (ImGui::Button("Goto"))
				{
					void* ent = Engine.GetEntity(realclient);
					void* localEnt = Engine.GetEntity(*Engine.LocalPlayer);

					if (Engine.IsAlive(ent) && Engine.IsAlive(localEnt))
					{
						Vector outpos;
						Engine.G_GetOrigin(*Engine.LocalPlayer, realclient, &outpos);
						Engine.TeleportPlayer(localEnt, &outpos);
					}
				}
			}
			if (ImGui::Button("Save Pos"))
			{
				void* ent = Engine.GetEntity(realclient);
				if (Engine.IsAlive(ent))
					Engine.G_GetOrigin(*Engine.LocalPlayer, realclient, &Toggles.SavedPositions[realclient]);

			}
			ImGui::SameLine();
			ImGui::PushItemWidth(100);
			if (ImGui::Button("Load Pos"))
			{
				if (Toggles.SavedPositions[realclient] != Vector(0, 0, 0))
				{
					void* ent = Engine.GetEntity(realclient);
					if (Engine.IsAlive(ent))
						Engine.TeleportPlayer(ent, &Toggles.SavedPositions[realclient]);
				}
			}
			ImGui::Checkbox("Spawn Saved", &Toggles.SpawnSaved[realclient]);

			ImGui::Separator();
			ImGui::Text("Admin Settings");

			if (strcmp(Engine.g_gametype->current.string, "dm"))
			{
				ImGui::Combo("Team", &Toggles.Team_Selected,Teams,ARRAYSIZE(Teams));
				if (ImGui::Button("Set Team"))
				{
					Engine.SetTeam(Engine.GetEntity(realclient), Toggles.Team_Selected + 1);
				}
			}

			if (ImGui::Button("Slay Client"))
			{
				Engine.slayList.push_back(realclient);
			}
			if (realclient != *Engine.LocalPlayer)
			{
				if (ImGui::Button("Kick Client"))
				{
					Engine.SV_GameDropClient(ClientVec[realclient].Index, "EXE_COD_ONLINE_PERM_BAN_PLAYER");
				}
			}
		}
	}
	ImGui::End();
}

void ModMenu()
{
	ImGui::Begin("Mod Menu", &Toggles.ModMenu, ImVec2(250, 250), 0.9f, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize);
	{
		ImGui::SetWindowSize("Mod Menu", ImVec2(250, 250));
		ImGui::Text("Mods");
		ImGui::Separator();
		ImGui::Checkbox("HS Slowmo", &Toggles.HeadshotSlowmo);
		if (ImGui::Button("Fast Restart"))
		{
			Engine.SV_FastRestart(*Engine.LocalPlayer);
		}
		if (ImGui::Button("Disconnect"))
		{
			Engine.Cbuf_AddText(*Engine.LocalPlayer, "disconnect");
		}

		ImGui::Text("Bot Stuff");
		ImGui::Separator();
		if (ImGui::Button("Add Bot"))
		{
			int curTeam = Engine.G_GetEntityTeam(Engine.GetEntity(*Engine.LocalPlayer));
			Engine.CreateTestClient(curTeam);
		}

		ImGui::Checkbox("Think", &Toggles.Bot_Think);
		if (ImGui::Checkbox("No-Kick", &Toggles.Bot_NoKick))
		{
			Utils::PatchAddy<WORD>(0x140471C2B, Toggles.Bot_NoKick ? 0x9090 : 0x750E);
			Utils::PatchAddy<byte>(0x140471BD4, Toggles.Bot_NoKick ? 0x9090 : 0x747C);
		}

		ImGui::InputText("Bot Name", BotNameBuf, 64, ImGuiInputTextFlags_CallbackAlways, (ImGuiTextEditCallback)BotNameChangeCallback);
		ImGui::Checkbox("Set Name", &Toggles.Bot_Changename);
	}
	ImGui::End();
}


void GameMenu::DrawMenu()
{
	if (Toggles.HostMenu)
	{
		if (Engine.InGame())
		{
			InGameHostMenu();
		}
		else
		{
			OffGameHostMenu();
		}
	}
	if (Toggles.ModMenu)
	{
		if (Engine.InGame())
		{
			ModMenu();
		}
	}
}

void GameMenu::SetupMenu()
{
	ImGui::GetIO().IniFilename = "SimGhostTools.ini";
	ImGuiStyle& style = ImGui::GetStyle();
	style.Colors[ImGuiCol_Text] = ImVec4(0.80f, 0.80f, 0.80f, 1.00f);
	style.Colors[ImGuiCol_TextDisabled] = ImVec4(0.59f, 0.59f, 0.59f, 1.00f);
	style.Colors[ImGuiCol_WindowBg] = ImVec4(0.13f, 0.13f, 0.13f, 1.00f);
	style.Colors[ImGuiCol_ChildWindowBg] = ImVec4(0.11f, 0.11f, 0.11f, 1.00f);
	style.Colors[ImGuiCol_Border] = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
	style.Colors[ImGuiCol_FrameBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.09f);
	style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.39f, 0.39f, 0.39f, 1.00f);
	style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.04f, 0.04f, 0.04f, 0.88f);
	style.Colors[ImGuiCol_TitleBg] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
	style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.00f, 0.00f, 0.00f, 0.20f);
	style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
	style.Colors[ImGuiCol_MenuBarBg] = ImVec4(0.35f, 0.35f, 0.35f, 1.00f);
	style.Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.13f, 0.13f, 0.13f, 1.00f);
	style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.94f, 0.20f, 0.20f, 1.00f);
	style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.94f, 0.20f, 0.20f, 0.59f);
	style.Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
	style.Colors[ImGuiCol_SliderGrab] = ImVec4(1.00f, 1.00f, 1.00f, 0.59f);
	style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.94f, 0.20f, 0.20f, 1.00f);
	style.Colors[ImGuiCol_Button] = ImVec4(0.94f, 0.20f, 0.20f, 1.00f);
	style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.94f, 0.20f, 0.20f, 0.59f);
	style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.39f, 0.39f, 0.39f, 1.00f);
	style.Colors[ImGuiCol_Header] = ImVec4(0.94f, 0.20f, 0.20f, 1.00f);
	style.Colors[ImGuiCol_HeaderHovered] = ImVec4(0.94f, 0.20f, 0.20f, 0.59f);
	style.Colors[ImGuiCol_HeaderActive] = ImVec4(0.39f, 0.39f, 0.39f, 1.00f);
	style.Colors[ImGuiCol_ColumnHovered] = ImVec4(0.70f, 0.02f, 0.60f, 0.22f);
	style.Colors[ImGuiCol_CloseButton] = ImVec4(0.94f, 0.20f, 0.20f, 1.00f);
	style.Colors[ImGuiCol_CloseButtonHovered] = ImVec4(0.94f, 0.20f, 0.20f, 0.59f);
	style.WindowRounding = 0.f;
	style.FramePadding = ImVec2(4, 1);
	style.ScrollbarSize = 10.f;
	style.ScrollbarRounding = 0.f;
	style.GrabMinSize = 5.f;
}*/