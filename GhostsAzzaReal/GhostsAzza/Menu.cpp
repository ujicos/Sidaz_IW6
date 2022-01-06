#include "stdafx.h"
#include "Menu.h"

using namespace ImGui;

float test = 1;





//dvar_t* party_minplayers = S1::DVAR::FindDvar("party_minplayers");

struct ClientClass
{
	std::string Name;
	int Index;
};


const char* Teams[] =
{
	"Axis",
	"Allies"
};


std::vector<ClientClass> ClientVec;


int* LocalPlayer = (int*)0x14155757C;

typedef signed __int64(__fastcall* tCL_GetClientName)(int localClientNum, int index, char *buf, int size);
tCL_GetClientName CL_GetClientName = (tCL_GetClientName)0X140213E40;


void AddNameTokens1(int i, std::string &nam)
{
	if (Toggles.EB[i] || Toggles.UFO[i] || Toggles.GodMode[i])
	{
		nam += "  [";

		if (Toggles.EB[i])
			nam += " EB";
		if (Toggles.UFO[i])
			nam += " U";
		if (Toggles.GodMode[i])
			nam += " G";

		nam += " ]";
	}
}


void ClearPlayer1(int i)
{
	Toggles.EB[i] = false;
	Toggles.UFO[i] = false;
	Toggles.GodMode[i] = false;
	Toggles.EB_IGNORE[i] = false;
	Toggles.EB_LimitWeapons[i] = true;
	//Toggles.TA_FOV[i] = 180.0f;
	Toggles.SavedPositions[i] = Vector(0, 0, 0);
	Toggles.SpawnSaved[i] = false;
}


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





void UpdateClientVector1()
{
	ClientVec.clear();
	for (int i = 0; i < 18; i++)
	{
		if (Engine.IsPlayer(Engine.GetEntity(i)))
		//if (g_entities[i].health >= 0)
		{
			char namebuf[128];
		//L_GetClientName(*LocalPlayer, i, namebuf, 127);
			Engine.CL_GetClientName(*Engine.LocalPlayer, i, namebuf, 127);
			if (namebuf[0] != 0)
			{
				ClientClass t;
				t.Name = std::string(namebuf);
				t.Index = i;
				AddNameTokens1(i, t.Name);
				ClientVec.push_back(t);
			}
			else
			{
				ClearPlayer1(i);
			}
		}
		else
		{
			ClearPlayer1(i);
		}
	}


}


const char* MapNames[] =
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







typedef void(__fastcall* tStartMapforParty)(__int64 localClientNum, const char *map, bool mapIsPreloaded, bool migrate);
tStartMapforParty StartMapforParty = (tStartMapforParty)0x1404702F0;





char BotNameBuf[64];


int BotNameChangeCallback(ImGuiTextEditCallbackData* data)
{
	Toggles.BotName = std::string(BotNameBuf);
}

void Menu::Render()
{

	ImGui_ImplDX11_NewFrame();

	static bool no_titlebar = false;
	static bool no_border = true;
	static bool no_resize = false;
	static bool auto_resize = false;
	static bool no_move = false;
	static bool no_scrollbar = false;
	static bool no_collapse = false;
	static bool no_menu = true;
	static bool start_pos_set = false;

	ImVec4* colors = ImGui::GetStyle().Colors;

	//colors[ImGuiCol_TitleBg] = ImVec4(0.6f, 0.7f, 0.8f, 1.00f);
	//colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.6f, 0.7f, 0.8f, 1.00f);
	//colors[ImGuiCol_TitleBgActive] = ImVec4(0.6f, 0.7f, 0.8f, 1.00f);

	colors[ImGuiCol_Text] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
	colors[ImGuiCol_TextDisabled] = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
	colors[ImGuiCol_WindowBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.83f);
	colors[ImGuiCol_ChildBg] = ImVec4(1.00f, 1.00f, 1.00f, 0.00f);
	colors[ImGuiCol_PopupBg] = ImVec4(0.08f, 0.08f, 0.08f, 0.94f);
	colors[ImGuiCol_Border] = ImVec4(0.43f, 0.43f, 0.50f, 0.50f);
	colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
	colors[ImGuiCol_FrameBg] = ImVec4(0.16f, 0.29f, 0.48f, 0.54f);
	colors[ImGuiCol_FrameBgHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.40f);
	colors[ImGuiCol_FrameBgActive] = ImVec4(0.26f, 0.59f, 0.98f, 0.67f);
	colors[ImGuiCol_TitleBg] = ImVec4(0.04f, 0.04f, 0.04f, 1.00f);
	colors[ImGuiCol_TitleBgActive] = ImVec4(0.16f, 0.29f, 0.48f, 1.00f);
	colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
	colors[ImGuiCol_MenuBarBg] = ImVec4(1.00f, 0.00f, 0.00f, 0.61f);
	colors[ImGuiCol_ScrollbarBg] = ImVec4(0.02f, 0.02f, 0.02f, 0.53f);
	colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.16f, 0.29f, 0.48f, 0.54f);
	colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.41f, 0.41f, 0.41f, 1.00f);
	colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.51f, 0.51f, 0.51f, 1.00f);
	colors[ImGuiCol_CheckMark] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
	colors[ImGuiCol_SliderGrab] = ImVec4(0.24f, 0.52f, 0.88f, 1.00f);
	colors[ImGuiCol_SliderGrabActive] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
	colors[ImGuiCol_Button] = ImVec4(0.26f, 0.59f, 0.98f, 0.40f);
	colors[ImGuiCol_ButtonHovered] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
	colors[ImGuiCol_ButtonActive] = ImVec4(0.06f, 0.53f, 0.98f, 1.00f);
	colors[ImGuiCol_Header] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
	colors[ImGuiCol_HeaderHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.80f);
	colors[ImGuiCol_HeaderActive] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
	colors[ImGuiCol_Separator] = ImVec4(0.43f, 0.43f, 0.50f, 0.50f);
	colors[ImGuiCol_SeparatorHovered] = ImVec4(0.10f, 0.40f, 0.75f, 0.78f);
	colors[ImGuiCol_SeparatorActive] = ImVec4(0.10f, 0.40f, 0.75f, 1.00f);
	colors[ImGuiCol_ResizeGrip] = ImVec4(0.26f, 0.59f, 0.98f, 0.25f);
	colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.67f);
	colors[ImGuiCol_ResizeGripActive] = ImVec4(0.26f, 0.59f, 0.98f, 0.95f);
	colors[ImGuiCol_PlotLines] = ImVec4(0.61f, 0.61f, 0.61f, 1.00f);
	colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
	colors[ImGuiCol_PlotHistogram] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
	colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
	colors[ImGuiCol_TextSelectedBg] = ImVec4(0.26f, 0.59f, 0.98f, 0.35f);
	colors[ImGuiCol_ModalWindowDarkening] = ImVec4(0.80f, 0.80f, 0.80f, 0.35f);
	colors[ImGuiCol_DragDropTarget] = ImVec4(1.00f, 1.00f, 0.00f, 0.90f);

	ImGuiWindowFlags	window_flags = 0;
	if (no_titlebar)	window_flags |= ImGuiWindowFlags_NoTitleBar;
	if (no_resize)		window_flags |= ImGuiWindowFlags_NoResize;
	if (auto_resize)	window_flags |= ImGuiWindowFlags_AlwaysAutoResize;
	if (no_move)		window_flags |= ImGuiWindowFlags_NoMove;
	if (no_scrollbar)	window_flags |= ImGuiWindowFlags_NoScrollbar;
	if (no_collapse)	window_flags |= ImGuiWindowFlags_NoCollapse;
	if (!no_menu)		window_flags |= ImGuiWindowFlags_MenuBar;
	ImGui::SetNextWindowSize(ImVec2(450, 600), ImGuiSetCond_FirstUseEver);
	if (!start_pos_set) { ImGui::SetNextWindowPos(ImVec2(25, 25)); start_pos_set = true; }

	ImGui::GetIO().MouseDrawCursor = Toggles.HostMenu;

	if (Toggles.HostMenu)
	{
		//UpdateClientVector();

		ImGui::Begin("Sidaz & uji's Ghosts Azza", &IsOpen, window_flags);

		ImGui::PushItemWidth(ImGui::GetWindowWidth() * 0.65f);
		ImGui::PushItemWidth(-140);

		//if (ImGui::CollapsingHeader("Host-Menu"))
		{

			if (ImGui::Checkbox("Unlock DLC", &Toggles.DLCUnlock))
				DLCUnlocker::SetDLCUnlock(Toggles.DLCUnlock);
			ImGui::Separator();

			
			ImGui::Combo("Gametype", &Toggles.CurGameType, GameTypes, ARRAYSIZE(GameTypes));
			ImGui::Separator();
			ImGui::SliderInt("Maxplayers", &Toggles.MaxPlayers, 1, 18);
			ImGui::Checkbox("Set Stuff", &Toggles.SetMaxPlayers);
			ImGui::Separator();
			ImGui::Combo("Map", &Toggles.CurMap, MapNames, ARRAYSIZE(MapNames));
			ImGui::Separator();
			//printf("%s\n", RealGametypes[Toggles.CurGameType].c_str());

			if (ImGui::Button("Force host and set game settings"))
			{
				Engine.party_maxTeamDiff->current.integer = 18;
				char buf[280];

				sprintf(buf, "ui_mapname %s; ui_gametype %s", MapNames[Toggles.CurMap], RealGametypes[Toggles.CurGameType].c_str());
				Engine.Cbuf_AddText(*Engine.LocalPlayer, buf);

				//if (!strcmp(g_gametype->current.string, "dm"))

				if (!strcmp(RealGametypes[Toggles.CurGameType].c_str(), "sd"))
				{
					Engine.party_teambased->current.integer = 1;


				}
				
				if (!strcmp(RealGametypes[Toggles.CurGameType].c_str(), "dm"))
				{

					Engine.party_teambased->current.integer = 0;

				}
				
				
				
				
				Engine.party_minplayers->current.integer = 1;
			}

			if (ImGui::Button("Fast Restart"))
			{
				Engine.SV_FastRestart(*Engine.LocalPlayer);
			}

			
			if (ImGui::Button("Disconnect"))
			{
				Engine.Cbuf_AddText(*Engine.LocalPlayer, "disconnect");
			}
			if (ImGui::Button("Add 30 seconds"))
			{
				const char* GetGameMode = Engine.va("scr_%s_timelimit", RealGametypes[Toggles.CurGameType].c_str());
				const char* Time = Engine.Dvar_GetString(GetGameMode);


				if (!strcmp(Time, "7"))
					Engine.Cbuf_AddText(0, "scr_sd_timelimit 7.5");

				if (!strcmp(Time, "6.5"))
					Engine.Cbuf_AddText(0, "scr_sd_timelimit 7");

				if (!strcmp(Time, "6"))
					Engine.Cbuf_AddText(0, "scr_sd_timelimit 6.5");

				if (!strcmp(Time, "5.5"))
					Engine.Cbuf_AddText(0, "scr_sd_timelimit 6");

				if (!strcmp(Time, "5"))
					Engine.Cbuf_AddText(0, "scr_sd_timelimit 5.5");

				if (!strcmp(Time, "4.5"))
					Engine.Cbuf_AddText(0, "scr_sd_timelimit 5");

				if (!strcmp(Time, "4"))
					Engine.Cbuf_AddText(0, "scr_sd_timelimit 4.5");

				if (!strcmp(Time, "3.5"))
					Engine.Cbuf_AddText(0, "scr_sd_timelimit 4");

				if (!strcmp(Time, "3"))
					Engine.Cbuf_AddText(0, "scr_sd_timelimit 3.5");
			
				if (!strcmp(Time, "2.5"))
					Engine.Cbuf_AddText(0, "scr_sd_timelimit 3");
			}


			ImGui::SliderInt("Time", &Toggles.time, 0, 10, "0.5");
			ImGui::Separator();
			//ImGui::SliderFloat("EB-Radius", &Toggles.EBRADIUS, 0.0f, 1000.0f, "%.2f");
			ImGui::Separator();
			ImGui::Checkbox("Think", &Toggles.Bot_Think);
			if (ImGui::Checkbox("No-Kick", &Toggles.Bot_NoKick))
			{
				Utils::PatchAddy<WORD>(0x140471C2B, Toggles.Bot_NoKick ? 0x9090 : 0x750E);
				Utils::PatchAddy<byte>(0x140471BD4, Toggles.Bot_NoKick ? 0x9090 : 0x747C);

				//75 AD
			}

			if (ImGui::Checkbox("Depatch Bounces", &Toggles.depatch))
			{
				//Utils::PatchAddy<WORD>(0x140471C2B, Toggles.Bot_NoKick ? 0x9090 : 0x750E);
				//Utils::PatchAddy<byte>(0x140471BD4, Toggles.Bot_NoKick ? 0x9090 : 0x747C);
				Utils::PatchAddy<byte>(0x140229003, Toggles.depatch ? 0x9090 : 0x7514);

				//75 AD
			}
			if (ImGui::Checkbox("Depatch Elevators", &Toggles.depatchele))
			{
				Utils::PatchAddy<WORD>(0x14021F0ED, Toggles.depatchele ? 0x9090 : 0x0675);
				Utils::PatchAddy<WORD>(0x140221F9B, Toggles.depatchele ? 0x9090 : 0x6875);
				Utils::PatchAddy<WORD>(0x140222003, Toggles.depatchele ? 0x42EB : 0x4274);
			}

			if (ImGui::Checkbox("patch shit", &Toggles.patchshit))
			{
				//Utils::PatchAddy<WORD>(0x140471C2B, Toggles.Bot_NoKick ? 0x9090 : 0x750E);
				//Utils::PatchAddy<byte>(0x140471BD4, Toggles.Bot_NoKick ? 0x9090 : 0x747C);
				Utils::PatchAddy<byte>(0x1402318B5, Toggles.patchshit ? 0x9090909090 : 0xE866250000);

				//75 AD
			}


			

			ImGui::InputText("Bot Name", BotNameBuf, 64, ImGuiInputTextFlags_CallbackAlways, (ImGuiTextEditCallback)BotNameChangeCallback);
			ImGui::Checkbox("Set Name", &Toggles.Bot_Changename);

			if (ImGui::Button("Add Bot"))
			{
				int curTeam = Engine.G_GetEntityTeam(Engine.GetEntity(*Engine.LocalPlayer));
				printf("curteam: %i\n", curTeam);
				
				




				Engine.CreateTestClient(curTeam);
			}


			UpdateClientVector1();
			ImGui::Begin("Host Menu", &Toggles.HostMenu, ImVec2(250, 500), 0.9f, window_flags);
			{
				//ImGui::SetWindowSize("Host Menu", ImVec2(250, 500));
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
					ImGui::Checkbox("Explosive Bullets", &Toggles.EB[realclient]);
					ImGui::Checkbox("Limited Weapons", &Toggles.EB_LimitWeapons[realclient]);
					ImGui::Checkbox("Ignore EB", &Toggles.EB_IGNORE[realclient]);
					ImGui::SliderFloat("EB-Radius", &Toggles.EBRADIUSplayer[realclient], 0.0f, 1000.0f, "%.2f");
					ImGui::Checkbox("Hitmarkers", &Toggles.EB_HitMarkers[realclient]);
					ImGui::SliderInt("HitmarkChance", &Toggles.Hitmarkchance[realclient], 1, 10);
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
						if (ImGui::Button("Bringtocrosshair"))
						{

							uint64_t client = *(int64_t*)(0x000000014427A0E0 + (0x2F0 * realclient) + 0x168);

							uint64_t clientlocal = *(int64_t*)(0x000000014427A0E0 + (0x2F0 * *Engine.LocalPlayer) + 0x168);
							//void* ent = Engine.GetEntity(realclient);
							//void* localEnt = Engine.GetEntity(*Engine.LocalPlayer);

							Vector3 forwardedAngles = Vector3(0, 0, 0);
							Vector3 angles = Vector3(Engine.PlayerCmd_GetAngles(*Engine.LocalPlayer)[0], Engine.PlayerCmd_GetAngles(*Engine.LocalPlayer)[1], Engine.PlayerCmd_GetAngles(*Engine.LocalPlayer)[2]);
							Vector3 getEye = Vector3(0, 0, 0);

							//Engine.Add_Ammo(client, *(int*)(client + 0x41C), 0, 999, 1);

							Engine.AngleVectorss(angles.vec, forwardedAngles.vec, NULL, NULL);
							Engine.G_GetPlayerEyePosition(clientlocal, getEye.vec);
							forwardedAngles.Multiply(999999);


							Vector3 end = Vector3(Engine.Scr_BulletTrace(*Engine.LocalPlayer, getEye.vec, forwardedAngles.vec));



							*(float*)(client + 0x1C) = end.vec[0];
							*(float*)(client + 0x20) = end.vec[1];
							*(float*)(client + 0x24) = end.vec[2];
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
						ImGui::Combo("Team", &Toggles.Team_Selected, Teams, ARRAYSIZE(Teams));
						if (ImGui::Button("Set Team"))
						{
							Engine.SetTeam(Engine.GetEntity(realclient), Toggles.Team_Selected + 1);
						}
					}

					if (ImGui::Button("Set Host Tean"))
					{
						int hostteam = Engine.SV_GetAssignedTeam(*LocalPlayer);

						Engine.SetTeam((void*)realclient, hostteam);

					}
					if (ImGui::Button("Slay Client"))
					{
						Engine.slayList.push_back(realclient);
					}
					if (ImGui::Button("Givekill Client"))
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
	}
	ImGui::Render();
}