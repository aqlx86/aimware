#pragma once
#include "Configuration.hpp"
#include "dropboxes.h"
#include "Variables.h"
#include "Themes.h"
#include <cctype>
#include "Logging.h"
#include "Listener.h"


#define RandomInt(nMin, nMax) (rand() % (nMax - nMin + 1) + nMin);
#define IM_ARRAYSIZE(_ARR)  ((int)(sizeof(_ARR)/sizeof(*_ARR)))
#define BUILDSTAMP ( __DATE__ )
typedef void(*CL_FullUpdate_t) (void);
CL_FullUpdate_t CL_FullUpdate = nullptr;

void FullUpdate()
{
	static auto CL_FullUpdate = reinterpret_cast<CL_FullUpdate_t>(U::FindPattern("engine.dll", reinterpret_cast<PBYTE>("\xA1\x00\x00\x00\x00\xB9\x00\x00\x00\x00\x56\xFF\x50\x14\x8B\x34\x85"), "x????x????xxxxxxx"));
	CL_FullUpdate();
}

//--------------------------------------------
//Weapon CFG stuff

const char* weaponnames(int id)
{
	switch (id)
	{
	case 1:
		return "deagle";
	case 2:
		return "elite";
	case 3:
		return "fiveseven";
	case 4:
		return "glock";
	case 7:
		return "ak47";
	case 8:
		return "aug";
	case 9:
		return "awp";
	case 10:
		return "famas";
	case 11:
		return "g3sg1";
	case 13:
		return "galilar";
	case 14:
		return "m249";
	case 60:
		return "m4a1_silencer";
	case 16:
		return "m4a1";
	case 17:
		return "mac10";
	case 19:
		return "p90";
	case 24:
		return "ump45";
	case 25:
		return "xm1014";
	case 26:
		return "bizon";
	case 27:
		return "mag7";
	case 28:
		return "negev";
	case 29:
		return "sawedoff";
	case 30:
		return "tec9";
	case 32:
		return "hkp2000";
	case 33:
		return "mp7";
	case 34:
		return "mp9";
	case 35:
		return "nova";
	case 36:
		return "p250";
	case 38:
		return "scar20";
	case 39:
		return "sg556";
	case 40:
		return "ssg08";
	case 61:
		return "usp_silencer";
	case 63:
		return "cz75a";
	case 64:
		return "revolver";
	case 508:
		return "knife_m9_bayonet";
	case 500:
		return "bayonet";
	case 505:
		return "knife_flip";
	case 506:
		return "knife_gut";
	case 507:
		return "knife_karambit";
	case 509:
		return "knife_tactical";
	case 512:
		return "knife_falchion";
	case 514:
		return "knife_survival_bowie";
	case 515:
		return "knife_butterfly";
	case 516:
		return "knife_push";

	default:
		return "";
	}
}

bool IsUtility(ItemDefinitionIndexx index)
{
	switch (index)
	{
	case ItemDefinitionIndexx::ITEM_NONE:
	case ItemDefinitionIndexx::WEAPON_C4:
	case ItemDefinitionIndexx::WEAPON_FLASH:
	case ItemDefinitionIndexx::WEAPON_HE:
	case ItemDefinitionIndexx::WEAPON_INC:
	case ItemDefinitionIndexx::WEAPON_MOLOTOV:
	case ItemDefinitionIndexx::WEAPON_SMOKE:
	case ItemDefinitionIndexx::WEAPON_DECOY:
	case ItemDefinitionIndexx::WEAPON_KNIFE_T:
	case ItemDefinitionIndexx::WEAPON_KNIFE_CT:
	case ItemDefinitionIndexx::GLOVE_T_SIDE:
	case ItemDefinitionIndexx::GLOVE_CT_SIDE:
	case ItemDefinitionIndexx::GLOVE_SPORTY:
	case ItemDefinitionIndexx::GLOVE_SLICK:
	case ItemDefinitionIndexx::GLOVE_LEATHER_WRAP:
	case ItemDefinitionIndexx::GLOVE_STUDDED_BLOODHOUND:
	case ItemDefinitionIndexx::GLOVE_MOTORCYCLE:
	case ItemDefinitionIndexx::GLOVE_SPECIALIST:
		return true;
	default:
		return false;
	}
}

bool Contains(const std::string &word, const std::string &sentence) {
	if (word == "" || sentence == "")
		return true;

	return sentence.find(word) != std::string::npos;
}

std::string ToLower(std::string str)
{
	std::transform(str.begin(), str.end(), str.begin(), (int(*)(int))std::tolower);

	return str;
}
//--------------------------------------------
bool defaultk;
bool bayonet;
bool flip;
bool gut;
bool karambit;
bool m9bayonet;
bool huntsman;
bool falchion;
bool bowie;
bool butterfly;
bool daggers;

void doknives(bool* disknife)
{
	defaultk = false;
	bayonet = false;
	flip = false;
	gut = false;
	karambit = false;
	m9bayonet = false;
	huntsman = false;
	falchion = false;
	bowie = false;
	butterfly = false;
	daggers = false;

	*disknife = true;
}

const char* HitmarkSound[] =
{
	"Disabled",
	"Default",
	"Roblox",
	"Trump",
	"Metallic"
};

const char* AngleStyles[] =
{
	"Disabled",
	"Ground",
	"Crosshair"
};


void RenderInterface() {


	auto& style = ImGui::GetStyle();
	bool is_renderer_active = renderer->IsActive();
	if (is_renderer_active)
	{
		g_Options.Menu.bShowTabs = true;
		if (style.Alpha < 1.f)
			style.Alpha += 0.01f;
	}
	if (!is_renderer_active)
	{

		if (style.Alpha > 0.f)
			style.Alpha -= 0.01f;
		g_Options.Menu.bShowTabs = false;
	}

	if (is_renderer_active)
	{

		if (Globals::error)
		{
			ImGui::SetNextWindowPosCenter(ImGuiSetCond_Appearing);
			ImGui::SetNextWindowSize(ImVec2(200, 50));
			if (ImGui::Begin(XorStr("Warning!"), &g_Options.Menu.Opened, ImVec2(400, 200), 1.f, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_ShowBorders))
			{
				ImGui::Text(XorStr("Please dont enable both Builder and Pre-set AAs!"));
				if (ImGui::Button(XorStr("OK!")))
				{
					g_Options.Ragebot.PreAAs = false;
					g_Options.Ragebot.BuilderAAs = false;
					Globals::error = false;
				}
			}ImGui::End();
		}

		if (g_Options.Menu.iTab == 0)
		{
			//normal font push
			ImGui::PushFont(fDefault);
			//style.Alpha = g_Options.Menu.flTabsAlpha;
			style.WindowPadding = ImVec2(0, 0);
			style.ItemSpacing = ImVec2(8, 4);
			ImGui::SetNextWindowPosCenter(ImGuiSetCond_Always);
			ImGui::SetNextWindowSize(ImVec2(840, 145));
			if (ImGui::Begin("##tabarea", &is_renderer_active, ImVec2(840, 145), 0.f, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse))
			{
				style.Colors[ImGuiCol_Button] = ImVec4(0.12, 0.12, 0.12, 1.f);
				style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.12, 0.12, 0.12, 1.);
				style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.12, 0.12, 0.12, 1.f);
				//icon font push
				ImGui::PushFont(fkek);
				if (ImGui::Button("A", ImVec2(133.3, 100))) g_Options.Menu.iTab = 1;
				ImGui::SameLine();
				if (ImGui::Button("D", ImVec2(133.3, 100))) g_Options.Menu.iTab = 2;
				ImGui::SameLine();
				if (ImGui::Button("B", ImVec2(133.3, 100))) g_Options.Menu.iTab = 3;
				ImGui::SameLine();
				if (ImGui::Button("C", ImVec2(133.3, 100))) g_Options.Menu.iTab = 4;
				ImGui::SameLine();
				if (ImGui::Button("E", ImVec2(133.3, 100))) g_Options.Menu.iTab = 5;
				ImGui::SameLine();
				if (ImGui::Button("F", ImVec2(133.3, 100))) g_Options.Menu.iTab = 6;
				ImGui::PopFont();

				ImVec4 col_theme = ImColor(130, 177, 255);

				style.Colors[ImGuiCol_Button] = ImVec4(col_theme.x, col_theme.y, col_theme.z, .97f);
				style.Colors[ImGuiCol_ButtonHovered] = ImVec4(col_theme.x, col_theme.y, col_theme.z, .97f);
				style.Colors[ImGuiCol_ButtonActive] = ImVec4(col_theme.x, col_theme.y, col_theme.z, .97f);

				if (ImGui::Button("RAGEBOT", ImVec2(133.3, 42))) g_Options.Menu.iTab = 1;
				ImGui::SameLine();
				if (ImGui::Button("LEGITBOT", ImVec2(133.3, 42))) g_Options.Menu.iTab = 2;
				ImGui::SameLine();
				if (ImGui::Button("VISUALS", ImVec2(133.3, 42))) g_Options.Menu.iTab = 3;
				ImGui::SameLine();
				if (ImGui::Button("MISC", ImVec2(133.3, 42))) g_Options.Menu.iTab = 4;
				ImGui::SameLine();
				if (ImGui::Button("SKINS", ImVec2(133.3, 42))) g_Options.Menu.iTab = 5;
				ImGui::SameLine();
				if (ImGui::Button("COLORS", ImVec2(133.3, 42))) g_Options.Menu.iTab = 6;
				ImGui::SameLine();
				ImGui::PopFont();
			}ImGui::End();
		}
		else if (g_Options.Menu.iTab == 1)
		{
			style.WindowPadding = ImVec2(8, 8);
			style.ItemSpacing = ImVec2(8, 4);
			ImGui::SetNextWindowPosCenter(ImGuiSetCond_Appearing);
			ImGui::SetNextWindowSize(ImVec2(840, 500));
			if (ImGui::Begin("Ragebot", &g_Options.Menu.Opened, ImVec2(840, 500), 1.f, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_ShowBorders))
			{
				if (ImGui::Button("<-- Back")) g_Options.Menu.iTab = 0;
				ImGui::SameLine();

				if (g_Options.Menu.rageSubtab == 0)
				{
					ImGui::Text("- Ragebot");
					ImGui::BeginChild("first child", ImVec2(200, 420), true);
					{
						ImGui::Checkbox(XorStr("Active"), &g_Options.Ragebot.MainSwitch);
						ImGui::Checkbox(XorStr("Enabled"), &g_Options.Ragebot.Enabled);
						ImGui::Checkbox(XorStr("Auto Fire"), &g_Options.Ragebot.AutoFire);
						ImGui::PushItemWidth(184);
						ImGui::SliderFloat(XorStr("FOV"), &g_Options.Ragebot.FOV, 1.f, 180.f, "%.0f");
						ImGui::Checkbox(XorStr("Silent Aim"), &g_Options.Ragebot.Silent);
						ImGui::Checkbox(XorStr("AutoPistol"), &g_Options.Ragebot.AutoPistol);
						ImGui::Separator();
						ImGui::Text(XorStr("Ragebot Key"));
						ImGui::PushItemWidth(184);
						ImGui::Hotkey(XorStr("Key##999"), &g_Options.Ragebot.KeyPress);

					}ImGui::EndChild();
					ImGui::SameLine();
					ImGui::BeginChild("second child", ImVec2(200, 420), true);
					{

						ImGui::Checkbox(XorStr("NoRecoil"), &g_Options.Ragebot.AntiRecoil);
						ImGui::Checkbox(XorStr("Auto Stop"), &g_Options.Ragebot.AutoStop);
						ImGui::Checkbox(XorStr("Auto Crouch"), &g_Options.Ragebot.AutoCrouch);
						ImGui::Checkbox(XorStr("Auto Scope"), &g_Options.Ragebot.AutoScope);
						ImGui::Separator();
						ImGui::PushItemWidth(184);
						ImGui::SliderFloat(("Min dmg Snipers"), &g_Options.Ragebot.MinimumDamageSniper, 1.f, 100.f, "%.2f");
						ImGui::SliderFloat(("Min dmg Rifles"), &g_Options.Ragebot.MinimumDamageRifle, 1.f, 100.f, "%.2f");
						ImGui::SliderFloat(("Min dmg Pistols"), &g_Options.Ragebot.MinimumDamagePistol, 1.f, 100.f, "%.2f");
						ImGui::SliderFloat(("Min dmg Heavies"), &g_Options.Ragebot.MinimumDamageHeavy, 1.f, 100.f, "%.2f");
						ImGui::SliderFloat(("Min dmg SMGs"), &g_Options.Ragebot.MinimumDamageSmg, 1.f, 100.f, "%.2f");
						ImGui::SliderFloat(("Min dmg Revolver/Deag"), &g_Options.Ragebot.MinimumDamageRevolver, 1.f, 100.f, "%.2f");

					}ImGui::EndChild();
					ImGui::SameLine();
					ImGui::BeginChild("third child", ImVec2(200, 420), true);
					{
						ImGui::Text(XorStr("Accuracy"));
						//ImGui::Separator();
						ImGui::Checkbox(XorStr("Friendly Fire"), &g_Options.Ragebot.FriendlyFire);
						ImGui::Combo(XorStr("Hitbox"), &g_Options.Ragebot.Hitbox, aimBones, ARRAYSIZE(aimBones));
						ImGui::Combo(XorStr("Hitscan"), &g_Options.Ragebot.Hitscan, hitscan, ARRAYSIZE(hitscan));
						ImGui::Separator();
						ImGui::PushItemWidth(184);
						ImGui::Checkbox(XorStr("Hitchance Enabled"), &g_Options.Ragebot.Hitchance);
						ImGui::SliderFloat(XorStr("Snipers"), &g_Options.Ragebot.HitchanceSniper, 0.f, 100.f, "%.1f");
						ImGui::SliderFloat(XorStr("Rifles"), &g_Options.Ragebot.HitchanceRifle, 0.f, 100.f, "%.1f");
						ImGui::SliderFloat(XorStr("Pistols"), &g_Options.Ragebot.HitchancePistol, 0.f, 100.f, "%.1f");
						ImGui::SliderFloat(XorStr("SMGs"), &g_Options.Ragebot.HitchanceSmgs, 0.f, 100.f, "%.1f");
						ImGui::SliderFloat(XorStr("Heavies"), &g_Options.Ragebot.HitchanceHeavy, 0.f, 100.f, "%.1f");
						ImGui::SliderFloat(XorStr("Revolver / Deagle"), &g_Options.Ragebot.HitchanceRevolver, 0.f, 100.f, "%.1f");
					}ImGui::EndChild();
					ImGui::SameLine();
					ImGui::BeginChild("fourth child", ImVec2(200, 420), true);
					{
						ImGui::PushItemWidth(184);
						ImGui::Checkbox(XorStr("Resolver"), &g_Options.Ragebot.Resolver);
						ImGui::Text(XorStr("Bruteforce after X bullets:"));
						ImGui::SliderFloat(XorStr("Shots: "), &g_Options.Ragebot.bruteAfterX, 0, 10, "%1.f");
						ImGui::Checkbox(XorStr("Fakelag Fix"), &g_Options.Ragebot.FakeLagFix);
						ImGui::Checkbox(XorStr("Position Adjustment"), &g_Options.Ragebot.PosAdjust);
						ImGui::Text(XorStr("BAIM Key"));
						ImGui::Hotkey(XorStr("BAIM key"), &g_Options.Ragebot.BAIMkey);
					}ImGui::EndChild();
				}
				else if (g_Options.Menu.rageSubtab == 1)
				{
					ImGui::Text(XorStr("- Antiaim"));
					ImGui::BeginChild("first child", ImVec2(200, 420), true);
					{
						ImGui::Checkbox(XorStr("Anti-Aim Enabled"), &g_Options.Ragebot.EnabledAntiAim);
						ImGui::Separator();
						if (ImGui::Button(XorStr("Pre-Set")))
						{
							g_Options.Ragebot.SubAATabs = 0;
						}
						ImGui::SameLine();
						if (ImGui::Button(XorStr("Builder")))
						{
							g_Options.Ragebot.SubAATabs = 1;
						}
						if (g_Options.Ragebot.SubAATabs == 0)
						{
							ImGui::Checkbox(XorStr("Enable"), &g_Options.Ragebot.PreAAs);
							ImGui::Combo(XorStr("Pitch"), &g_Options.Ragebot.Pitch, antiaimpitch, ARRAYSIZE(antiaimpitch));
							ImGui::SliderFloat(XorStr("Pitch Adder: "), &g_Options.Ragebot.PitchAdder, -180, 180, "%1.f");
							ImGui::Separator();
							ImGui::Combo(XorStr("Yaw"), &g_Options.Ragebot.YawTrue, antiaimyawtrue, ARRAYSIZE(antiaimyawtrue));
							ImGui::SliderFloat(XorStr("Real Adder: "), &g_Options.Ragebot.YawTrueAdder, -180, 180, "%1.f");
							ImGui::Separator();
							ImGui::Combo(XorStr("Fake-Yaw"), &g_Options.Ragebot.YawFake, antiaimyawfake, ARRAYSIZE(antiaimyawfake));
							ImGui::SliderFloat(XorStr("Fake Adder: "), &g_Options.Ragebot.YawFakeAdder, -180, 180, "%1.f");
						}
						if (g_Options.Ragebot.SubAATabs == 1)
						{
							ImGui::Checkbox(XorStr("Enable"), &g_Options.Ragebot.BuilderAAs);
							ImGui::SliderFloat(XorStr("Pitch Angle: "), &g_Options.Ragebot.BuilderPitch, -89, 89, "%1.f");
							ImGui::SliderFloat(XorStr("Real Angle: "), &g_Options.Ragebot.BuilderReal, -180, 180, "%1.f");
							ImGui::SliderFloat(XorStr("Fake Angle: "), &g_Options.Ragebot.BuilderFake, -180, 180, "%1.f");
							ImGui::Checkbox(XorStr("Enable Real Jitter"), &g_Options.Ragebot.Jitter);
							ImGui::SliderFloat(XorStr("Jitter Range: "), &g_Options.Ragebot.JitterRange, -90, 90, "%1.f");
							ImGui::Checkbox(XorStr("Enable Fake Jitter"), &g_Options.Ragebot.FJitter);
							ImGui::SliderFloat(XorStr("FJitter Range: "), &g_Options.Ragebot.FJitterRange, -90, 90, "%1.f");
							ImGui::Checkbox(XorStr("LBY Breaker"), &g_Options.Ragebot.LBYBreaker);
						}
						//ImGui::Separator();
						//ImGui::Checkbox(XorStr("Moving AA"), &g_Options.Ragebot.MovingAA);
						//ImGui::Combo(XorStr("Yaw"), &g_Options.Ragebot.YawTrueMove, antiaimyawtruemove, ARRAYSIZE(antiaimyawtruemove));
						//ImGui::Combo(XorStr("Fake-Yaw"), &g_Options.Ragebot.YawFakeMove, antiaimyawfakemove, ARRAYSIZE(antiaimyawfakemove));
						//ImGui::Checkbox(("At Players"), &g_Options.Ragebot.AtTarget);
						ImGui::Separator();
						ImGui::Checkbox(XorStr("Edge"), &g_Options.Ragebot.Edge);
						ImGui::Checkbox(XorStr("AntiAim on knife"), &g_Options.Ragebot.KnifeAA);
					}ImGui::EndChild();
					ImGui::SameLine();
					ImGui::BeginChild("second child", ImVec2(200, 420), true);
					{
						ImGui::Checkbox(XorStr("Enable FakeLag"), &g_Options.Ragebot.FakeLag);
						ImGui::SliderInt(XorStr("Amount"), &g_Options.Ragebot.FakeLagAmt, 0, 15, "%1.f");
					}ImGui::EndChild();
					ImGui::SameLine();
					ImGui::BeginChild("third child", ImVec2(200, 420), true);
					{

					}ImGui::EndChild();
					ImGui::SameLine();
					ImGui::BeginChild("fourth child", ImVec2(200, 420), true);
					{

					}ImGui::EndChild();
				}
				if (ImGui::Button("Ragebot", ImVec2(408, 20))) g_Options.Menu.rageSubtab = 0;
				ImGui::SameLine();
				if (ImGui::Button("Antiaim", ImVec2(408, 20))) g_Options.Menu.rageSubtab = 1;
			}ImGui::End();
		}
		else if (g_Options.Menu.iTab == 2)
		{
			style.WindowPadding = ImVec2(8, 8);
			style.ItemSpacing = ImVec2(8, 4);
			ImGui::SetNextWindowPosCenter(ImGuiSetCond_Appearing);
			ImGui::SetNextWindowSize(ImVec2(840, 500));
			if (ImGui::Begin("Legitbot", &g_Options.Menu.Opened, ImVec2(840, 500), 1.f, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_ShowBorders))
			{
				if (ImGui::Button("<-- Back")) g_Options.Menu.iTab = 0;
				ImGui::SameLine();

				ImGui::Text("- Legitbot");
				ImGui::SameLine();
				ImGui::Checkbox(XorStr("Enable"), &g_Options.Legitbot.MainSwitch);
				ImGui::BeginChild("first child", ImVec2(200, 420), true);
				{
					ImGui::Text("Rifles");
					ImGui::PushItemWidth(184);
					ImGui::Hotkey(XorStr("Key##0"), &g_Options.Legitbot.MainKey);
					//ImGui::Combo(("Key##0"), &menu.Legitbot.MainKey, keyNames, ARRAYSIZE(keyNames));
					//ImGui::Combo(XorStr("Hitbox"), &g_Options.Legitbot.hitboxrifle, aimBones, ARRAYSIZE(aimBones));
					ImGui::SliderFloat(XorStr("Smooth##0"), &g_Options.Legitbot.MainSmooth, 1.00f, 100.00f, "%.2f");
					ImGui::SliderFloat(XorStr("FOV##0"), &g_Options.Legitbot.Mainfov, 0.00f, 30.00f, "%.2f");
					ImGui::SliderFloat(XorStr("Min RCS##0"), &g_Options.Legitbot.main_recoil_min, 1.00f, 100.00f, "%.2f");
					ImGui::SliderFloat(XorStr("Max RCS##0"), &g_Options.Legitbot.main_recoil_max, 1.00f, 100.00f, "%.2f");
					ImGui::Separator();
					ImGui::Checkbox(XorStr("Legit Backtrack"), &g_Options.Legitbot.backtrack);
					ImGui::SliderFloat(XorStr("Ticks: "), &g_Options.Legitbot.backtrackTicks, 0, 12, "%1.f");
				}ImGui::EndChild();
				ImGui::SameLine();

				ImGui::BeginChild("second child", ImVec2(200, 420), true);
				{
					ImGui::Text("Pistols");
					ImGui::PushItemWidth(184);
					ImGui::Hotkey(XorStr("Key##1"), &g_Options.Legitbot.PistolKey);
					//ImGui::Combo(("Key##1"), &menu.Legitbot.PistolKey, keyNames, ARRAYSIZE(keyNames));
					//ImGui::Combo(XorStr("Hitbox"), &g_Options.Legitbot.hitboxpistol, aimBones, ARRAYSIZE(aimBones));
					ImGui::SliderFloat(XorStr("Smooth##1"), &g_Options.Legitbot.PistolSmooth, 1.00f, 100.00f, "%.2f");
					ImGui::SliderFloat(XorStr("FOV##1"), &g_Options.Legitbot.Pistolfov, 0.00f, 30.00f, "%.2f");
					ImGui::SliderFloat(XorStr("Min RCS##1"), &g_Options.Legitbot.pistol_recoil_min, 1.00f, 100.00f, "%.2f");
					ImGui::SliderFloat(XorStr("Max RCS##1"), &g_Options.Legitbot.pistol_recoil_max, 1.00f, 100.00f, "%.2f");
				}ImGui::EndChild();
				ImGui::SameLine();

				ImGui::BeginChild("third child", ImVec2(200, 420), true);
				{
					ImGui::Text("Snipers");
					ImGui::PushItemWidth(184);
					ImGui::Hotkey(XorStr("Key##2"), &g_Options.Legitbot.SniperKey);
					//ImGui::Combo(("Key##2"), &menu.Legitbot.SniperKey, keyNames, ARRAYSIZE(keyNames));
					//ImGui::Combo(XorStr("Hitbox"), &g_Options.Legitbot.hitboxsniper, aimBones, ARRAYSIZE(aimBones));
					ImGui::SliderFloat(XorStr("Smooth##2"), &g_Options.Legitbot.SniperSmooth, 1.00f, 100.00f, "%.2f");
					ImGui::SliderFloat(XorStr("FOV##2"), &g_Options.Legitbot.Sniperfov, 0.00f, 30.00f, "%.2f");
					ImGui::SliderFloat(XorStr("Min RCS##2"), &g_Options.Legitbot.sniper_recoil_min, 1.00f, 100.00f, "%.2f");
					ImGui::SliderFloat(XorStr("Max RCS##2"), &g_Options.Legitbot.sniper_recoil_max, 1.00f, 100.00f, "%.2f");
				}ImGui::EndChild();
				ImGui::SameLine();

				ImGui::BeginChild("fourth child", ImVec2(200, 420), true);
				{
					ImGui::Text("Triggerbot");
					//ImGui::Separator();
					ImGui::PushItemWidth(184);
					ImGui::Checkbox(XorStr("Enable Triggerbot"), &g_Options.Legitbot.Triggerbot.Enabled);
					//ImGui::SliderFloat(XorStr("Delay"), &g_Options.Legitbot.Triggerbot.Delay, 1.f, 150.f, "%.0f");
					ImGui::Hotkey(XorStr("Key##3"), &g_Options.Legitbot.Triggerbot.Key);
					//ImGui::Combo(("Triggerbot key"), &menu.Legitbot.Triggerbot.Key, keyNames, ARRAYSIZE(keyNames));
					ImGui::SliderFloat(XorStr("Hitchance"), &g_Options.Legitbot.Triggerbot.hitchance, 1.f, 100.f, "%.0f");

					ImGui::Text(XorStr("Filter"));

					ImGui::BeginChild(XorStr("Filter"), ImVec2(ImGui::GetWindowContentRegionWidth() * 0.5f, 21 * 5));
					{
						ImGui::Selectable(XorStr(" Head"), &g_Options.Legitbot.Triggerbot.Filter.Head);
						ImGui::Selectable(XorStr(" Arms"), &g_Options.Legitbot.Triggerbot.Filter.Arms);
						ImGui::Selectable(XorStr(" Chest"), &g_Options.Legitbot.Triggerbot.Filter.Chest);
						ImGui::Selectable(XorStr(" Stomach"), &g_Options.Legitbot.Triggerbot.Filter.Stomach);
						ImGui::Selectable(XorStr(" Legs"), &g_Options.Legitbot.Triggerbot.Filter.Legs);
					}ImGui::EndChild();
				}ImGui::EndChild();
			}ImGui::End();
		}
		else if (g_Options.Menu.iTab == 3)
		{
			style.WindowPadding = ImVec2(8, 8);
			style.ItemSpacing = ImVec2(8, 4);
			ImGui::SetNextWindowPosCenter(ImGuiSetCond_Appearing);
			ImGui::SetNextWindowSize(ImVec2(840, 500));
			if (ImGui::Begin("Visuals", &g_Options.Menu.Opened, ImVec2(840, 500), 1.f, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_ShowBorders))
			{
				if (ImGui::Button("<-- Back")) g_Options.Menu.iTab = 0;
				ImGui::SameLine();


				ImGui::Text("- Visuals");
				ImGui::BeginChild("first child", ImVec2(200, 420), true);
				{
					ImGui::Checkbox(XorStr("Team ESP"), &g_Options.Visuals.TeamESP);
					ImGui::SameLine();
					ImGui::MyColorEdit3("##ESP", g_Options.Colors.TeamESP, 1 << 7);
					ImGui::Checkbox(XorStr("Box"), &g_Options.Visuals.Box);
					ImGui::SameLine();
					ImGui::MyColorEdit3("##EdddSP", g_Options.Colors.EnemyESP, 1 << 7);
					ImGui::Combo("##boxkek", &g_Options.Visuals.BoxType, "Full\0\rCorners\0\r3D\0\0", -1);
					ImGui::Checkbox(XorStr("Skeleton"), &g_Options.Visuals.Skeleton);
					ImGui::Checkbox(XorStr("Name"), &g_Options.Visuals.Name);
					ImGui::Checkbox(XorStr("Weapon"), &g_Options.Visuals.Weapon);
					ImGui::Combo("##wpnkek", &g_Options.Visuals.wpnmode, "Name\0\rIcon\0\0", -1);
					ImGui::Checkbox(XorStr("Armor"), &g_Options.Visuals.Armor);
					ImGui::Checkbox(XorStr("Health"), &g_Options.Visuals.health);
					ImGui::Checkbox(XorStr("Money"), &g_Options.Visuals.Money);
					ImGui::Checkbox(XorStr("Callout"), &g_Options.Visuals.Callout);
					//ImGui::Checkbox(XorStr("Barrel"), &g_Options.Visuals.Barrel);
					//ImGui::SliderFloat(XorStr("##bamt"), &g_Options.Visuals.BarrelAmt, 0, 300, "%.0f");
					//ImGui::NextColumn();
					//ImGui::Checkbox(XorStr("Sounds"), &g_Options.Visuals.soundesp);
					ImGui::Checkbox(XorStr("Grenade Prediction"), &g_Options.Visuals.GrenadePrediction);
					//ImGui::Checkbox(XorStr("Crosshair"), &g_Options.Visuals.Xhair);
					//ImGui::Checkbox(XorStr("Dynamic"), &g_Options.Visuals.Recoilxhair);
					ImGui::Checkbox(XorStr("Enemy State"), &g_Options.Visuals.Flashed);
					ImGui::Checkbox(XorStr("Distance"), &g_Options.Visuals.Distance);
					//ImGui::Checkbox(XorStr("Spectators"), &g_Options.Visuals.speclist);
					ImGui::Checkbox(XorStr("Aimlines"), &g_Options.Visuals.AimLine);
					ImGui::Checkbox(XorStr("Angle Lines"), &g_Options.Visuals.angleLines);
					ImGui::Checkbox(XorStr("Awall Indicator"), &g_Options.Visuals.DrawAwall);
					ImGui::Checkbox(XorStr("LBY Indicator"), &g_Options.Visuals.LBYIndicator);
					//ImGui::Combo(XorStr("##safljg"), &g_Options.Visuals.AngleStyle, AngleStyles, ARRAYSIZE(AngleStyles));

				}ImGui::EndChild();
				ImGui::SameLine();

				ImGui::BeginChild("second child", ImVec2(200, 420), true);
				{
					ImGui::PushItemWidth(184);
					ImGui::SliderFloat(XorStr("FOV"), &g_Options.Visuals.FOVChanger, 0, 60, "%.0f");
					ImGui::SliderFloat(XorStr("VFOV"), &g_Options.Visuals.viewmodelChanger, 0, 130, "%.0f");
					//ImGui::Checkbox(XorStr("Angle Lines"), &g_Options.Visuals.angleLines);
					ImGui::Checkbox(XorStr("Bomb ESP"), &g_Options.Visuals.Bomb);
					ImGui::Checkbox(XorStr("Grenades"), &g_Options.Visuals.Grenades);
					ImGui::Checkbox(XorStr("Resolve Mode"), &g_Options.Visuals.resolveMode);
					ImGui::Checkbox(XorStr("Dropped Weapons"), &g_Options.Visuals.Droppedguns);
					ImGui::Checkbox(XorStr("No Smoke"), &g_Options.Visuals.NoSmoke);
					ImGui::Checkbox(XorStr("No Flash"), &g_Options.Visuals.NoFlash);
					ImGui::Checkbox(XorStr("No Scope"), &g_Options.Visuals.noscopeborder);
				}ImGui::EndChild();
				ImGui::SameLine();

				ImGui::BeginChild("third child", ImVec2(200, 420), true);
				{
					if (ImGui::Button("Player"))
					{
						g_Options.Visuals.glowsubtab = 0;
					}
					ImGui::SameLine();
					if (ImGui::Button("Drops"))
					{
						g_Options.Visuals.glowsubtab = 1;
					}
					ImGui::SameLine();
					if (ImGui::Button("Bomb"))
					{
						g_Options.Visuals.glowsubtab = 2;
					}
					if (g_Options.Visuals.glowsubtab == 0)
					{
						ImGui::Checkbox(XorStr("Glow Players"), &g_Options.Visuals.glowplayer);
						ImGui::SameLine();
						ImGui::MyColorEdit3("##glow", g_Options.Colors.EnemyGlow, 1 << 7);
						ImGui::Checkbox(XorStr("Glow Team"), &g_Options.Visuals.teamglow);
						ImGui::SameLine();
						ImGui::MyColorEdit3("##teamglow", g_Options.Colors.TeamGlow, 1 << 7);
						ImGui::PushItemWidth(184);
						ImGui::SliderInt(XorStr(" ##pga"), &g_Options.Visuals.playerglowalpha, 0, 255);
					}
					if (g_Options.Visuals.glowsubtab == 1)
					{
						ImGui::Checkbox(XorStr("Glow Weapons"), &g_Options.Visuals.weaponglow);
						ImGui::SameLine();
						ImGui::MyColorEdit3("##ESP", g_Options.Colors.WeaponGlow, 1 << 7);
						ImGui::PushItemWidth(184);
						ImGui::SliderInt(XorStr(" ##wga"), &g_Options.Visuals.weaponglowalpha, 0, 255);
					}
					if (g_Options.Visuals.glowsubtab == 2)
					{
						ImGui::Checkbox(XorStr("Glow Bomb"), &g_Options.Visuals.bombglow);
						ImGui::SameLine();
						ImGui::MyColorEdit3("##ESP", g_Options.Colors.C4glow, 1 << 7);
						ImGui::PushItemWidth(184);
						ImGui::SliderInt(XorStr(" ##bga"), &g_Options.Visuals.bombglowalpha, 0, 255);
					}
					ImGui::Separator();
					if (ImGui::Button("Player ##chams"))
					{
						g_Options.Visuals.chamsubtab = 0;
					}
					ImGui::SameLine();
					if (ImGui::Button("Weapon"))
					{
						g_Options.Visuals.chamsubtab = 1;
					}
					ImGui::SameLine();
					if (ImGui::Button("Hands"))
					{
						g_Options.Visuals.chamsubtab = 2;
					}

					if (g_Options.Visuals.chamsubtab == 0)
					{
						ImGui::Checkbox(XorStr("Cham Players"), &g_Options.Visuals.Chams);
						ImGui::SameLine();
						ImGui::MyColorEdit3("##45ESP", g_Options.Colors.EnemyChamsVis, 1 << 7);
						ImGui::Checkbox(XorStr("Cham Team"), &g_Options.Visuals.Teamchams);
						ImGui::SameLine();
						ImGui::MyColorEdit3("##E772SP", g_Options.Colors.TeamChamsVis, 1 << 7);
						ImGui::Checkbox(XorStr("Cham Weapon"), &g_Options.Visuals.Chamweapon);
						ImGui::Checkbox(XorStr("XQZ"), &g_Options.Visuals.XQZ);
						ImGui::SameLine();
						ImGui::MyColorEdit3("##43ESP", g_Options.Colors.EnemyChamsNVis, 1 << 7);
						ImGui::PushItemWidth(184);
						ImGui::SliderInt(XorStr(" ##pca"), &g_Options.Visuals.champlayeralpha, 0, 100);
						ImGui::Combo("##sdgl", &g_Options.Visuals.matierial, "Normal\0\rFlat\0\rWireframe\0\rGlass\0\rGold\0\rPlatinum\0\rPlastic\0\rCrystal\0\0", -1);
					}
					if (g_Options.Visuals.chamsubtab == 1)
					{
						ImGui::Checkbox(XorStr("Cham Viewmodel"), &g_Options.Visuals.weaponviewcham);
						ImGui::SameLine();
						ImGui::MyColorEdit3("##Easd445SP", g_Options.Colors.WeaponViewCham, 1 << 7);
						ImGui::PushItemWidth(184);
						ImGui::SliderInt(XorStr(" ##wca"), &g_Options.Visuals.weaponhandalpha, 0, 100);
						ImGui::Combo("##sdgl1", &g_Options.Visuals.handmat, "Normal\0\rFlat\0\rWireframe\0\rGlass\0\rGold\0\rPlatinum\0\rPlastic\0\rCrystal\0\0", -1);
					}
					if (g_Options.Visuals.chamsubtab == 2)
					{
						ImGui::Checkbox(XorStr("Cham Hands"), &g_Options.Visuals.handcham);
						ImGui::SameLine();
						ImGui::MyColorEdit3("##ES234P", g_Options.Colors.HandCham, 1 << 7);
						ImGui::PushItemWidth(184);
						ImGui::SliderInt(XorStr(" ##hca"), &g_Options.Visuals.chamhandalpha, 0, 100);
						ImGui::Combo("##sdgl2", &g_Options.Visuals.weaponmat, "Normal\0\rFlat\0\rWireframe\0\rGlass\0\rGold\0\rPlatinum\0\rPlastic\0\rCrystal\0\0", -1);
					}

				}ImGui::EndChild();
				ImGui::SameLine();

				ImGui::BeginChild("fourth child", ImVec2(200, 420), true);
				{
					ImGui::Checkbox(XorStr("Nightmode"), &g_Options.Misc.nightMode);
					ImGui::Checkbox(XorStr("Thirdperson"), &g_Options.Visuals.ThirdPerson);
					ImGui::Hotkey(XorStr("Key##273"), &g_Options.Visuals.TPKey);
					//ImGui::SliderFloat(XorStr("##tpdist"), &g_Options.Visuals.tpdist, 50.f, 500.f, "%.0f");
					ImGui::Checkbox(XorStr("Hitmarker"), &g_Options.Visuals.Hitmarker);
					ImGui::Text(XorStr("HitSound:"));
					ImGui::Combo(XorStr("##asad4asds"), &g_Options.Visuals.Hitsound, HitmarkSound, ARRAYSIZE(HitmarkSound));
					ImGui::Checkbox(XorStr("Event Log (Beta)"), &g_Options.Visuals.EventLog);
				}ImGui::EndChild();


			}ImGui::End();
		}
		else if (g_Options.Menu.iTab == 4)
		{
			style.WindowPadding = ImVec2(8, 8);
			style.ItemSpacing = ImVec2(8, 4);
			ImGui::SetNextWindowPosCenter(ImGuiSetCond_Appearing);
			ImGui::SetNextWindowSize(ImVec2(840, 500));
			if (ImGui::Begin("Misc", &g_Options.Menu.Opened, ImVec2(840, 500), 1.f, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_ShowBorders))
			{
				if (ImGui::Button("<-- Back")) g_Options.Menu.iTab = 0;
				ImGui::SameLine();

				ImGui::Text("- Misc");
				ImGui::BeginChild("first child", ImVec2(200, 420), true);
				{
					ImGui::Checkbox("Anti-Untrusted", &g_Options.Misc.antiuntrusted);
					ImGui::Text("Config");
					ImGui::Combo(("File"), &g_Options.Menu.ConfigFile, configFiles, ARRAYSIZE(configFiles));
					if (ImGui::Button("Save Config")) Config->Save();

					if (ImGui::Button("Load Config")) Config->Load();
				}ImGui::EndChild();
				ImGui::SameLine();

				ImGui::BeginChild("second child", ImVec2(200, 420), true);
				{
					ImGui::Text("Clantag");
					ImGui::Checkbox("AIMWARE Clantag", &g_Options.Misc.syncclantag);
					ImGui::Text("Clantag speed");
					ImGui::PushItemWidth(184);
					ImGui::Combo("##combo", &g_Options.Misc.ClanTagSpeed, "Speed1\0Speed2");
				}ImGui::EndChild();
				ImGui::SameLine();

				ImGui::BeginChild("third child", ImVec2(200, 420), true);
				{
					ImGui::Checkbox(XorStr("Bunny Hop"), &g_Options.Misc.Bhop);
					ImGui::Checkbox(XorStr("AutoStrafe"), &g_Options.Misc.AutoStrafe);
					//ImGui::Hotkey(XorStr("##SlowmoKey"), &g_Options.Misc.Slowmo);
				}ImGui::EndChild();
				ImGui::SameLine();

				ImGui::BeginChild("fourth child", ImVec2(200, 420), true);
				{
					ImGui::Text(XorStr("Unhook"));
					if (ImGui::Button(XorStr("Unhook")))
					{
						g_Engine->ClientCmd_Unrestricted("cl_mouseenable 1");
						unload = true;
					}
				}ImGui::EndChild();
			}ImGui::End();
		}
		else if (g_Options.Menu.iTab == 5)
		{
			style.WindowPadding = ImVec2(8, 8);
			style.ItemSpacing = ImVec2(8, 4);
			ImGui::SetNextWindowPosCenter(ImGuiSetCond_Appearing);
			ImGui::SetNextWindowSize(ImVec2(840, 500));
			static char filterWeapons[32];
			static char filterSkins[32];

			if (ImGui::Begin(XorStr("Skinchanger"), &g_Options.Menu.Opened, ImVec2(840, 500), 1.f, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_ShowBorders))
			{
				if (ImGui::Button(XorStr("<-- Back"))) g_Options.Menu.iTab = 0;
				ImGui::SameLine();


				ImGui::Checkbox(XorStr("Skinchanger"), &g_Options.Skinchanger.Enabled);
				ImGui::BeginChild("first child", ImVec2(200, 420), true);
				{
					ImGui::PushItemWidth(-1);
					ImGui::InputText(XorStr("##FILTERWEAPONS"), filterWeapons, IM_ARRAYSIZE(filterWeapons));
					ImGui::PopItemWidth();
					ImGui::ListBoxHeader(XorStr("##GUNS"), ImVec2(-1, -1));
					for (auto it : ItemDefinitionIndexMap)
					{
						bool isDefault = (int)it.first < 0;
						if (!isDefault && !Contains(ToLower(std::string(filterWeapons)), ToLower(ItemDefinitionIndexMap.at(it.first).entityName)))
							continue;

						if (IsUtility(it.first))
							continue;

						const bool item_selected = ((int)it.first == (int)g_Options.Menu.currentWeapon);
						//ImGui::PushID((int)it.first);
						std::string formattedName;

						formattedName = ItemDefinitionIndexMap.at(it.first).entityName;
						if (ImGui::Selectable(formattedName.c_str(), item_selected))
						{
							g_Options.Menu.currentWeapon = (int)it.first;
						}
						//ImGui::PopID();
					}
					ImGui::ListBoxFooter();
				}ImGui::EndChild();
				ImGui::SameLine();

				ImGui::BeginChild("second child", ImVec2(200, 420), true);
				{
					std::string skinName = weaponnames(g_Options.Menu.currentWeapon);
					{
						ImGui::PushItemWidth(-1);
						ImGui::InputText(XorStr("##FILTERSKINS"), filterSkins, IM_ARRAYSIZE(filterSkins));
						ImGui::InputInt(XorStr("##custom ID"), &g_Options.Skinchanger.W[g_Options.Menu.currentWeapon].ChangerSkin);
						ImGui::PopItemWidth();
						ImGui::ListBoxHeader(XorStr("##SKINS"), ImVec2(-1, -1));
						std::string skinStr = "";
						int curItem = -1;
						int s = 0;
						for (auto skin : g_Options.Skinchanger.weaponSkins[skinName])
						{
							int pk = g_Options.Skinchanger.skinMap[skin].paintkit;
							if (pk == g_Options.Skinchanger.W[g_Options.Menu.currentWeapon].ChangerSkin)
								curItem = s;
							bool selected = g_Options.Skinchanger.W[g_Options.Menu.currentWeapon].ChangerSkin == pk;

							skinStr = g_Options.Skinchanger.skinNames[g_Options.Skinchanger.skinMap[skin].tagName].c_str();
							skinStr += " | ";
							skinStr += std::to_string(g_Options.Skinchanger.skinMap[skin].paintkit);
							if (!Contains(ToLower(std::string(filterSkins)), ToLower(skinStr)))
								continue;
							if (ImGui::Selectable(skinStr.c_str(), selected))
							{
								pk = g_Options.Skinchanger.skinMap[skin].paintkit;
								g_Options.Skinchanger.W[g_Options.Menu.currentWeapon].ChangerSkin = pk;
								FullUpdate();
								break;
							}
							s++;
						}

						ImGui::ListBoxFooter();
					}
				}ImGui::EndChild();
				ImGui::SameLine();

				ImGui::BeginChild("third child", ImVec2(200, 420), true);
				{
					ImGui::ListBoxHeader("##KNIVES", ImVec2(-1, -1));
					{
						if (ImGui::RadioButton(XorStr("Default"), &g_Options.Skinchanger.knifemodel, 0))
						{
							FullUpdate();
						}
						if (ImGui::RadioButton(XorStr("Bayonet"), &g_Options.Skinchanger.knifemodel, 1))
						{
							FullUpdate();
						}
						if (ImGui::RadioButton(XorStr("Flip Knife"), &g_Options.Skinchanger.knifemodel, 2))
						{
							FullUpdate();
						}
						if (ImGui::RadioButton(XorStr("Gut Knife"), &g_Options.Skinchanger.knifemodel, 3))
						{
							FullUpdate();
						}
						if (ImGui::RadioButton(XorStr("Karambit"), &g_Options.Skinchanger.knifemodel, 4))
						{
							FullUpdate();
						}
						if (ImGui::RadioButton(XorStr("M9 Bayonet"), &g_Options.Skinchanger.knifemodel, 5))
						{
							FullUpdate();
						}
						if (ImGui::RadioButton(XorStr("Huntsman"), &g_Options.Skinchanger.knifemodel, 6))
						{
							FullUpdate();
						}
						if (ImGui::RadioButton(XorStr("Falchion"), &g_Options.Skinchanger.knifemodel, 7))
						{
							FullUpdate();
						}
						if (ImGui::RadioButton(XorStr("Bowie"), &g_Options.Skinchanger.knifemodel, 8))
						{
							FullUpdate();
						}
						if (ImGui::RadioButton(XorStr("Butterfly Knife"), &g_Options.Skinchanger.knifemodel, 9))
						{
							FullUpdate();
						}
						if (ImGui::RadioButton(XorStr("Shadow Daggers"), &g_Options.Skinchanger.knifemodel, 10))
						{
							FullUpdate();
						}
					}
					ImGui::ListBoxFooter();
				}ImGui::EndChild();
				ImGui::SameLine();

				ImGui::BeginChild("fourth child", ImVec2(200, 420), true);
				{
					if (ImGui::RadioButton(XorStr("Bloodhound"), &g_Options.Skinchanger.glove, 1))
					{
						FullUpdate();
					}
					if (ImGui::RadioButton(XorStr("Sport"), &g_Options.Skinchanger.glove, 2))
					{
						FullUpdate();
					}
					if (ImGui::RadioButton(XorStr("Driver"), &g_Options.Skinchanger.glove, 3))
					{
						FullUpdate();
					}
					if (ImGui::RadioButton(XorStr("Hand Wraps"), &g_Options.Skinchanger.glove, 4))
					{
						FullUpdate();
					}
					if (ImGui::RadioButton(XorStr("Motorcycle"), &g_Options.Skinchanger.glove, 5))
					{
						FullUpdate();
					}
					if (ImGui::RadioButton(XorStr("Specialst"), &g_Options.Skinchanger.glove, 6))
					{
						FullUpdate();
					}

					const char* gstr;
					if (g_Options.Skinchanger.glove == 1)
					{
						gstr = "Charred\0\rSnakebite\0\rBronzed\0\rGuerilla\0\0";
					}
					else if (g_Options.Skinchanger.glove == 2)
					{
						gstr = "Hedge Maze\0\rPandoras Box\0\rSuperconductor\0\rArid\0\0";
					}
					else if (g_Options.Skinchanger.glove == 3)
					{
						gstr = "Lunar Weave\0\rConvoy\0\rCrimson Weave\0\rDiamondback\0\0";
					}
					else if (g_Options.Skinchanger.glove == 4)
					{
						gstr = "Leather\0\rSpruce DDPAT\0\rSlaughter\0\rBadlands\0\0";
					}
					else if (g_Options.Skinchanger.glove == 5)
					{
						gstr = "Eclipse\0\rSpearmint\0\rBoom!\0\rCool Mint\0\0";
					}
					else if (g_Options.Skinchanger.glove == 6)
					{
						gstr = "Forest DDPAT\0\rCrimson Kimono\0\rEmerald Web\0\rFoundation\0\0";
					}
					else
					{
						gstr = "";
					}
					ImGui::PushItemWidth(-1);
					if (ImGui::Combo(XorStr("##2"), &g_Options.Skinchanger.gloeskin, gstr, -1))
						FullUpdate();

					ImGui::PopItemWidth();

				}ImGui::EndChild();

				if (ImGui::Button(XorStr("Apply"), ImVec2(-1, 20))) FullUpdate();
			}ImGui::End();
		}
	}
}
